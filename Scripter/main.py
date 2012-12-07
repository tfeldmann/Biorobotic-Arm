# -*- coding: utf-8 -*-
from Tkinter import *
# import serial
# from serial.tools import list_ports


class App(object):
    """docstring for App"""
    def __init__(self, parent):
        super(App, self).__init__()
        self.parent = parent

    def init_gui(self):
        self.connect_frame = Frame(self.parent)
        self.connect_frame.pack(padx=15, pady=15, fill=X)

        self.connect_button = Button(self.connect_frame, text="Connect")
        self.connect_button.pack(side=LEFT)

        self.text_area = Text(self.parent, bd=3, relief=GROOVE)
        self.text_area.pack(padx=15, pady=(0, 15))

        self.control_frame = Frame(self.parent)
        self.control_frame.pack(padx=15, pady=(0, 15), fill=X)

        self.command_entry = Entry(self.control_frame)
        self.command_entry.pack(side=LEFT)
        self.command_entry.bind("<Return>", self.send_command)

        self.send_button = Button(self.control_frame, text="Send", command=self.send_command)
        self.send_button.pack(side=LEFT)

        self.start_button = Button(self.control_frame, text="Start")
        self.start_button.pack(side=RIGHT)

        self.cancel_button = Button(self.control_frame, text="Cancel")
        self.cancel_button.pack(side=RIGHT)

    def send_command(self, event=null):
        str = self.command_entry.get()
        str = str.upper()
        self.command_entry.delete(0, END)


def main():
    root = Tk()
    root.title("Helferlein Automation")
    root.geometry("+300+100")
    root.resizable(0, 0)
    app = App(root)
    app.init_gui()
    root.mainloop()

if __name__ == '__main__':
    main()
