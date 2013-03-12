# -*- coding: utf-8 -*-
"""
Thomdo

A simple todo-list application written in Python + PySide
"""

from PySide.QtCore import *
from PySide.QtGui import *
import cv
import sys
import serial
from SerialConnection import *

from videowidget import VideoWidget
from mainwindow import Ui_FaceDetection


class FaceDection(QMainWindow):
    def __init__(self, parent=None):
        super(FaceDection, self).__init__(parent)
        self.ui = Ui_FaceDetection()
        self.ui.setupUi(self)

        # self.ui.video = VideoWidget(self.ui.centralwidget)
        # self.ui.video.repaint()

        self.ui.speed_dial.sliderMoved.connect(self.set_fan_speed)
        self.ui.horizontal_speed.sliderReleased.connect(self.horizontal_stop)
        self.ui.vertical_speed.sliderReleased.connect(self.vertical_stop)
        self.ui.serial_select.currentIndexChanged.connect(self.port_select)

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
            QMessageBox.warning(self, "Warnung", "asdasdasdtext"+ str(index))
        # connect
        else:
            self.ui.serial_select.setCurrentIndex(0)



if __name__ == "__main__":
    app = QApplication(sys.argv)
    face_detection = FaceDection()
    face_detection.show()
    app.exec_()
