import cv2
import cv2.cv as cv
from PySide.QtCore import QPoint, QTimer
from PySide.QtGui import QWidget, QPainter, QImage, QApplication


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
        self.capture = cv.CaptureFromCAM(0)

        # get first frame
        self._query_frame()

        # set refresh rate
        self.timer = QTimer(self)
        self.timer.timeout.connect(self._query_frame)
        self.timer.start(50)


    def _build_image(self, image):
        cv.Resize(image, self.frame, cv.CV_INTER_NN)
        return OpenCVQImage(self.frame)


    def _query_frame(self):
        image = cv.QueryFrame(self.capture)
        self.qimage = self._build_image(image)
        self.update()


    def paintEvent(self, event):
        painter = QPainter(self)
        painter.drawImage(QPoint(0, 0), self.qimage)



class IplQImage(QImage):
    """
    http://matthewshotton.wordpress.com/2011/03/31/python-opencv-iplimage-to-pyqt-qimage/
    A class for converting iplimages to qimages
    """
    def __init__(self,iplimage):
        # Rough-n-ready but it works dammit
        alpha = cv.CreateMat(iplimage.height,iplimage.width, cv.CV_8UC1)
        cv.Rectangle(alpha, (0, 0), (iplimage.width,iplimage.height), cv.ScalarAll(255) ,-1)
        rgba = cv.CreateMat(iplimage.height, iplimage.width, cv.CV_8UC4)
        cv.Set(rgba, (1, 2, 3, 4))
        cv.MixChannels([iplimage, alpha],[rgba], [
        (0, 0), # rgba[0] -> bgr[2]
        (1, 1), # rgba[1] -> bgr[1]
        (2, 2), # rgba[2] -> bgr[0]
        (3, 3)  # rgba[3] -> alpha[0]
        ])
        self.__imagedata = rgba.tostring()
        super(IplQImage,self).__init__(self.__imagedata, iplimage.width, iplimage.height, QImage.Format_RGB32)



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
