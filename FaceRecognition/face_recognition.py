# -*- coding: utf-8 -*-
"""
FaceRecognition

This software is meant to be used in combination with the BioRob ventilator
upgrade. With this hardware upgrade the robot will bring a fresh breeze to
everyone it sees. The FaceRecognition-software will automatically control the
ventilator strength and make the robot follow faces.

PySide is used for the GUI, so make sure you use pyside-uic tools to convert
the .ui- to a .py-file if you change something there. Please do not edit
mainwindow.py as all changes will be overwritten!
OpenCV is used to detect the faces.

Questions, issues?
feldmann.thomas@gmail.com
"""

import serial
import cv2.cv as cv
from SerialConnection import *
from PySide.QtCore import *
from PySide.QtGui import *
from mainwindow import Ui_FaceDetection


class FaceDection(QMainWindow):
    def __init__(self, parent=None):
        super(FaceDection, self).__init__(parent)

        # gui connections
        self.ui = Ui_FaceDetection()
        self.ui.setupUi(self)
        self.ui.speed_dial.sliderMoved.connect(self.set_fan_speed)
        self.ui.horizontal_speed.sliderReleased.connect(self.horizontal_stop)
        self.ui.vertical_speed.sliderReleased.connect(self.vertical_stop)
        self.ui.serial_select.currentIndexChanged.connect(self.port_select)

        # video and face recognition
        self.faces = []
        self.ui.video.face_callback = self.video_face_callback
        self.ui.video.image_callback = self.video_image_callback

        # serial connection
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
            cv.Rectangle(image, (x,y), (x+w,y+h), cv.RGB(0, 155+100*i, 0), 2)


if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    face_detection = FaceDection()
    face_detection.show()
    sys.exit(app.exec_())
