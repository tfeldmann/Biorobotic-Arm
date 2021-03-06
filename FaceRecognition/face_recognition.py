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

import os
import sys
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
        self.ui.horizontal_speed.valueChanged.connect(self.set_hor_speed)
        self.ui.vertical_speed.valueChanged.connect(self.set_ver_speed)
        self.ui.serial_select.currentIndexChanged.connect(self.port_select)
        self.ui.command_edit.returnPressed.connect(self.command_send)

        # video and face recognition
        self.faces = []
        self.ui.video.face_callback = self.video_face_callback
        self.ui.video.image_callback = self.video_image_callback

        # serial connection
        self.serial = SerialConnection()
        for port in self.serial.list_ports():
            self.ui.serial_select.addItem(port)
        self.listener_timer = QTimer(self)
        self.listener_timer.timeout.connect(self.serial_read)
        self.listener_timer.start(50)

    def set_fan_speed(self, speed, update_dial=False):
        self.ui.speed_label.setText("%d %%" % speed)
        self.serial.send("VENT " + str(speed))
        if update_dial:
            self.ui.speed_dial.setValue(speed)

    def horizontal_stop(self):
        self.serial.send("STOP")
        self.ui.horizontal_speed.setValue(0)  # snap back

    def vertical_stop(self):
        self.serial.send("STOP")
        self.ui.vertical_speed.setValue(0)  # snap back

    def set_hor_speed(self, value):
        if not value == 0:
            self.serial.send("IBASE "+str(value))

    def set_ver_speed(self, value):
        if not value == 0:
            self.serial.send("IELBOW "+str(value))

    def serial_read(self):
        message_queue = self.serial.queue
        while not message_queue.empty():
            message = message_queue.get_nowait()
            if message[0] == "#":
                self.ui.log.append("<b>"+message+"</b>")
            elif message[0] == "!":
                self.ui.log.append("<font color=red>"+message+"</font>")
            message_queue.task_done()

    def command_send(self):
        command = self.ui.command_edit.text()
        self.serial.send(command)
        self.ui.command_edit.clear()

    def port_select(self, index):
        # disconnect
        if index == 0:
            self.serial.stop()
            self.ui.log.clear()
            self.ui.command_edit.clear()
            self.ui.command_edit.setEnabled(False)
            self.ui.fanbox.setEnabled(False)
            self.ui.movementbox.setEnabled(False)
        # connect
        else:
            try:
                port = self.ui.serial_select.currentText()
                self.serial.connect(port=port, baud=19200)
                self.ui.command_edit.setEnabled(True)
                self.ui.fanbox.setEnabled(True)
                self.ui.movementbox.setEnabled(True)
            except Exception, e:
                QMessageBox.warning(self, "Error", e.message)

    def video_face_callback(self, faces):
        self.faces = faces

        # ventilator automation: w and h can be anything from 100 to 640
        if self.ui.fan_enabled.isChecked():
            fanspeed = 0
            if faces:
                _,_,_,h = faces[0]
                fanspeed = map(h, 100, 480, 100, 0)
                fanspeed = constrain(fanspeed, 0, 100)
                wristangle = map(h, 100, 480, -30, 20)
                self.serial.send("WRIST "+str(wristangle))
            self.set_fan_speed(fanspeed, update_dial=True)

        # movement automation
        if self.ui.faces_enabled.isChecked():
            if faces:
                x,y,w,h = faces[0]
                corner_x_angle = 14  # was 20
                corner_y_angle = 8  # was 10
                # try to keep the face in center
                dx = (x + w / 2 - 320) * corner_x_angle / 320
                # y is measured from top
                dy = - (y + h / 2 - 240) * corner_y_angle / 240
                self.serial.send("IBASE " + str(dx))
                self.serial.send("IELBOW " + str(dy))

    def video_image_callback(self, image):
        for i, (x,y,w,h) in enumerate(self.faces):
            cv.Rectangle(image, (x,y), (x+w,y+h), cv.RGB(0, 155+100*i, 0), 2)


def constrain(value, min, max):
    if value < min:
        return min
    elif value > max:
        return max
    else:
        return value

def map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


if __name__ == "__main__":
    app = QApplication(sys.argv)
    face_detection = FaceDection()
    face_detection.show()
    sys.exit(app.exec_())
