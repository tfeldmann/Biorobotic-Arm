# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created: Tue Mar 12 18:30:01 2013
#      by: pyside-uic 0.2.14 running on PySide 1.1.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_FaceDetection(object):
    def setupUi(self, FaceDetection):
        FaceDetection.setObjectName("FaceDetection")
        FaceDetection.resize(860, 595)
        self.centralwidget = QtGui.QWidget(FaceDetection)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout_2 = QtGui.QHBoxLayout(self.centralwidget)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.video = QtGui.QWidget(self.centralwidget)
        self.video.setMinimumSize(QtCore.QSize(640, 480))
        self.video.setMaximumSize(QtCore.QSize(640, 480))
        self.video.setObjectName("video")
        self.verticalLayout.addWidget(self.video)
        spacerItem = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem)
        self.horizontal_speed = QtGui.QSlider(self.centralwidget)
        self.horizontal_speed.setCursor(QtCore.Qt.SizeHorCursor)
        self.horizontal_speed.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.horizontal_speed.setMinimum(-100)
        self.horizontal_speed.setMaximum(100)
        self.horizontal_speed.setPageStep(0)
        self.horizontal_speed.setOrientation(QtCore.Qt.Horizontal)
        self.horizontal_speed.setObjectName("horizontal_speed")
        self.verticalLayout.addWidget(self.horizontal_speed)
        self.horizontalLayout.addLayout(self.verticalLayout)
        self.vertical_speed = QtGui.QSlider(self.centralwidget)
        self.vertical_speed.setCursor(QtCore.Qt.SizeVerCursor)
        self.vertical_speed.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.vertical_speed.setMinimum(-100)
        self.vertical_speed.setMaximum(100)
        self.vertical_speed.setPageStep(0)
        self.vertical_speed.setOrientation(QtCore.Qt.Vertical)
        self.vertical_speed.setObjectName("vertical_speed")
        self.horizontalLayout.addWidget(self.vertical_speed)
        self.verticalLayout_2 = QtGui.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.serial_select = QtGui.QComboBox(self.centralwidget)
        self.serial_select.setMaximumSize(QtCore.QSize(148, 16777215))
        self.serial_select.setCursor(QtCore.Qt.PointingHandCursor)
        self.serial_select.setFocusPolicy(QtCore.Qt.StrongFocus)
        self.serial_select.setObjectName("serial_select")
        self.serial_select.addItem("")
        self.verticalLayout_2.addWidget(self.serial_select)
        self.command_edit = QtGui.QLineEdit(self.centralwidget)
        self.command_edit.setEnabled(False)
        self.command_edit.setObjectName("command_edit")
        self.verticalLayout_2.addWidget(self.command_edit)
        spacerItem1 = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout_2.addItem(spacerItem1)
        self.groupBox = QtGui.QGroupBox(self.centralwidget)
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout_6 = QtGui.QVBoxLayout(self.groupBox)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.fan_enabled = QtGui.QCheckBox(self.groupBox)
        self.fan_enabled.setCursor(QtCore.Qt.PointingHandCursor)
        self.fan_enabled.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.fan_enabled.setObjectName("fan_enabled")
        self.verticalLayout_6.addWidget(self.fan_enabled)
        self.speed_dial = QtGui.QDial(self.groupBox)
        self.speed_dial.setCursor(QtCore.Qt.PointingHandCursor)
        self.speed_dial.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.speed_dial.setMaximum(100)
        self.speed_dial.setSliderPosition(80)
        self.speed_dial.setOrientation(QtCore.Qt.Horizontal)
        self.speed_dial.setInvertedAppearance(False)
        self.speed_dial.setInvertedControls(False)
        self.speed_dial.setObjectName("speed_dial")
        self.verticalLayout_6.addWidget(self.speed_dial)
        self.speed_label = QtGui.QLabel(self.groupBox)
        self.speed_label.setAlignment(QtCore.Qt.AlignCenter)
        self.speed_label.setObjectName("speed_label")
        self.verticalLayout_6.addWidget(self.speed_label)
        self.verticalLayout_2.addWidget(self.groupBox)
        self.groupBox_2 = QtGui.QGroupBox(self.centralwidget)
        self.groupBox_2.setObjectName("groupBox_2")
        self.verticalLayout_4 = QtGui.QVBoxLayout(self.groupBox_2)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.faces_enabled = QtGui.QCheckBox(self.groupBox_2)
        self.faces_enabled.setCursor(QtCore.Qt.PointingHandCursor)
        self.faces_enabled.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.faces_enabled.setObjectName("faces_enabled")
        self.verticalLayout_4.addWidget(self.faces_enabled)
        self.verticalLayout_2.addWidget(self.groupBox_2)
        self.horizontalLayout.addLayout(self.verticalLayout_2)
        self.horizontalLayout_2.addLayout(self.horizontalLayout)
        FaceDetection.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar()
        self.menubar.setGeometry(QtCore.QRect(0, 0, 860, 22))
        self.menubar.setObjectName("menubar")
        self.menuBioRob_FaceDetection = QtGui.QMenu(self.menubar)
        self.menuBioRob_FaceDetection.setObjectName("menuBioRob_FaceDetection")
        FaceDetection.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(FaceDetection)
        self.statusbar.setObjectName("statusbar")
        FaceDetection.setStatusBar(self.statusbar)
        self.menubar.addAction(self.menuBioRob_FaceDetection.menuAction())

        self.retranslateUi(FaceDetection)
        QtCore.QMetaObject.connectSlotsByName(FaceDetection)

    def retranslateUi(self, FaceDetection):
        FaceDetection.setWindowTitle(QtGui.QApplication.translate("FaceDetection", "BioRob FaceDetection", None, QtGui.QApplication.UnicodeUTF8))
        self.serial_select.setItemText(0, QtGui.QApplication.translate("FaceDetection", "Not Connected", None, QtGui.QApplication.UnicodeUTF8))
        self.command_edit.setPlaceholderText(QtGui.QApplication.translate("FaceDetection", "Single Command", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBox.setTitle(QtGui.QApplication.translate("FaceDetection", "Fan", None, QtGui.QApplication.UnicodeUTF8))
        self.fan_enabled.setText(QtGui.QApplication.translate("FaceDetection", "Automatic", None, QtGui.QApplication.UnicodeUTF8))
        self.speed_label.setText(QtGui.QApplication.translate("FaceDetection", "80 %", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBox_2.setTitle(QtGui.QApplication.translate("FaceDetection", "Movement", None, QtGui.QApplication.UnicodeUTF8))
        self.faces_enabled.setText(QtGui.QApplication.translate("FaceDetection", "Follow faces", None, QtGui.QApplication.UnicodeUTF8))
        self.menuBioRob_FaceDetection.setTitle(QtGui.QApplication.translate("FaceDetection", "BioRob FaceDetection", None, QtGui.QApplication.UnicodeUTF8))

