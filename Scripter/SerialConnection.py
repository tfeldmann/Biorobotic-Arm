# -*- coding: utf-8 -*-
import serial
import thread


class SerialConnection(object):
    """receives and sends serial data in a thread"""
    def __init__(self, serialPort):
        self.serialPort = serialPort
        self.startUpdateSerial(self.serialPort)
        self._observers = []

    def add_observer(self, observer):
        self._observers.append(observer)

    def startUpdateSerial(self, myPort):
        self.ser = serial.Serial(port=myPort, baudrate=115200)
        thread.start_new_thread(self.updateSerial, ())
        self._stop_serial_update_flag = False

    def stopUpdateSerial(self):
        self._stop_serial_update_flag = True

    def updateSerial(self):
        while (True and self.ser):
            try:
                if (self._stop_serial_update_flag):
                    self.ser.close()
                    thread.exit()
                else:
                    line = self.ser.readline().rstrip()
                    for observer in self._observers:
                        observer(line)
            except Exception, e:
                print e.message

    def send(self, str):
        self.ser.write(str + "\r\n")


if __name__ == '__main__':
    print "This file cannot be executed on its own"
