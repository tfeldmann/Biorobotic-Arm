import cv2.cv as cv
from PySide.QtCore import QPoint, QTimer
from PySide.QtGui import QWidget, QPainter, QImage, QApplication

CASCADE_PATH = "haarcascades/"  # path to cascades with trailing slash

class VideoWidget(QWidget):
    """A custom QWidget for displaying a webcam stream.

    It will resize the webcam image to 640*480. Callbacks are available for
    detecting faces and modifying the current frame before viewing.
    """

    def __init__(self, parent=None):
        QWidget.__init__(self)
        self.setMinimumSize(640, 480)
        self.setMaximumSize(self.minimumSize())

        # register this callbacks to interact with the faces and the camera
        # image before the widget will view the frame
        self.image_callback = None
        self.face_callback = None

        # init view with correct size, depth, channels
        self.frame = cv.CreateImage((640,480), cv.IPL_DEPTH_8U, 3)

        self.storage = cv.CreateMemStorage()
        self.capture = cv.CaptureFromCAM(0)
        self.face_cascade = cv.Load(CASCADE_PATH+"haarcascade_frontalface_alt.xml")
        self.fd_wait_frames = 1
        self._fd_wait = self.fd_wait_frames

        # get first frame
        self._query_frame()

        # set refresh rate
        self.timer = QTimer(self)
        self.timer.timeout.connect(self._query_frame)
        self.timer.start(75)

    def _build_image(self, image):
        """ resize the image if it does not fit into the application """
        if image.height == 480 and image.width == 640:
            self.frame = image
        else:
            cv.Resize(image, self.frame, cv.CV_INTER_NN)
        return OpenCVQImage(self.frame)

    def _query_frame(self):
        image = cv.QueryFrame(self.capture)

        # callback with an cvImage
        if self.image_callback:
            self.image_callback(image)

        if not self._fd_wait:
            self._fd_wait = self.fd_wait_frames
            faces = self._detect_faces(image)

            # callback with array of detected faces
            if self.face_callback:
                self.face_callback(faces)
        else:
            self._fd_wait -= 1

        self.qimage = self._build_image(image)
        self.update()

    def _detect_faces(self, image):
        detected = cv.HaarDetectObjects(
            image, self.face_cascade, self.storage, 1.2, 1,
            cv.CV_HAAR_DO_CANNY_PRUNING, (100,100))
        return [(x,y,w,h) for (x,y,w,h),n in detected]

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
    """A simple app to test the video stream"""
    import sys
    app = QApplication(sys.argv)
    video = VideoWidget()
    video.show()
    app.exec_()


if __name__ == '__main__':
    test()
