import cv2
import cv2.cv as cv
from PySide.QtCore import QPoint, QTimer
from PySide.QtGui import QWidget, QPainter, QImage, QApplication


CASCADE_PATH = "/usr/local/Cellar/opencv/2.4.3/share/OpenCV/haarcascades/"
FRONTALFACE_PATH = CASCADE_PATH+"haarcascade_frontalface_alt.xml"
PROFILEFACE_PATH = CASCADE_PATH+"haarcascade_profileface.xml"
CAMERA_INDEX = 0


class VideoWidget(QWidget):
    """ A custom QWidget for displaying a webcam stream """

    def __init__(self, parent=None):
        QWidget.__init__(self)

        # set widget dimensions
        self.setMinimumSize(640, 480)
        self.setMaximumSize(self.minimumSize())

        # init view with correct size, depth, channels
        self.frame = cv.CreateImage((640,480), cv.IPL_DEPTH_8U, 3)

        # set the camera to capture from
        self.capture = cv.CaptureFromCAM(CAMERA_INDEX)
        self.storage = cv.CreateMemStorage()
        self.frontalface_cascade = cv.Load(FRONTALFACE_PATH)
        self.profileface_cascade = cv.Load(PROFILEFACE_PATH)

        # get first frame
        self._query_frame()

        # set refresh rate
        self.timer = QTimer(self)
        self.timer.timeout.connect(self._query_frame)
        self.timer.start(75)


    def _build_image(self, image):
        # resize the image if it does not fit into the application
        if image.height == 480 and image.width == 640:
            self.frame = image
        else:
            cv.Resize(image, self.frame, cv.CV_INTER_NN)
        return OpenCVQImage(self.frame)


    def _query_frame(self):
        image = cv.QueryFrame(self.capture)
        self.qimage = self._build_image(image)
        self.update()


    def paintEvent(self, event):
        painter = QPainter(self)
        painter.drawImage(QPoint(0, 0), self.qimage)


class OpenCVQImage(QImage):
    def __init__(self, opencvBgrImg):
        depth, nChannels = opencvBgrImg.depth, opencvBgrImg.nChannels
        if depth != cv.IPL_DEPTH_8U or nChannels != 3:
            raise ValueError("the input image must be 8-bit, 3-channel")

        w, h = cv.GetSize(opencvBgrImg)
        opencvRgbImg = cv.CreateImage((w, h), depth, nChannels)

        # it's assumed the image is in BGR format
        cv.CvtColor(opencvBgrImg, opencvRgbImg, cv.CV_BGR2RGB)
        self._imgData = opencvRgbImg.tostring()

        super(OpenCVQImage, self).__init__(self._imgData, w, h, \
            QImage.Format_RGB888)


def test():
    """A simple app to test the widget"""
    import sys
    app = QApplication(sys.argv)
    video = VideoWidget()
    video.show()
    app.exec_()


if __name__ == '__main__':
    test()
