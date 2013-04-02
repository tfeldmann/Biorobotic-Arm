# -*- coding: utf-8 -*-
"""
FaceRecognition

Controls the BioRob's integrated fan and is able to follow faces
"""

import serial
import cv2.cv as cv
from SerialConnection import *
from PySide.QtCore import *
from PySide.QtGui import *
from mainwindow import Ui_FaceDetection


class FaceDection(QMainWindow):
    """ The main application """

    def __init__(self, parent=None):
        super(FaceDection, self).__init__(parent)

        self.ui = Ui_FaceDetection()
        self.ui.setupUi(self)
        self.ui.speed_dial.sliderMoved.connect(self.set_fan_speed)
        self.ui.horizontal_speed.sliderReleased.connect(self.horizontal_stop)
        self.ui.vertical_speed.sliderReleased.connect(self.vertical_stop)
        self.ui.serial_select.currentIndexChanged.connect(self.port_select)
        self.ui.video.image_callback = self.video_image_callback
        self.ui.video.face_callback = self.video_face_callback

        self.faces = []
        self.scon = SerialConnection()
        for port in self.scon.list_ports():
            self.ui.serial_select.addItem(port)

    def set_fan_speed(self, speed, update_dial=False):
        self.ui.speed_label.setText("%d %%" % speed)

    def horizontal_stop(self):
        self.ui.horizontal_speed.setValue(0)  # snap back

    def vertical_stop(self):
        self.ui.vertical_speed.setValue(0)  # snap back

    def port_select(self, index):
        # disconnect
        if index == 0:
            QMessageBox.warning(self, "Warnung", "asdasdasdtext"+str(index))
        # connect
        else:
            QMessageBox.warning(self, "connect", "connection established")

    def video_face_callback(self, faces):
        self.faces = faces

    def video_image_callback(self, image):
        for i, (x,y,w,h) in enumerate(self.faces):
            cv.Rectangle(image, (x,y), (x+w,y+h), cv.RGB(0, 155 + 100*i, 0), 2)


if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    face_detection = FaceDection()
    face_detection.show()
    sys.exit(app.exec_())
