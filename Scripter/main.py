# -*- coding: utf-8 -*-
"""BioRob Scripting Software

Repository and readme:
github.com/tfeldmann/Biorobotic-Arm

Mechatronics Master 2012
Westfälische Hochschule
"""

from Tkinter import *
import tkMessageBox
import tkFileDialog
from serial.tools import list_ports
from SerialConnection import *
import time
import gzip


class App(object):
    def push_connect(self):
        try:
            port = self.selectedPort.get()
            self.scon = SerialConnection(port)
            self.scon.add_observer(self.serial_event)
            self.connect_button.configure(
                text="Disconnect",
                command=self.push_disconnect)
            self.port_option_menu.config(state=DISABLED)
        except Exception, e:
            tkMessageBox.showerror("Error", e.message)

    def push_disconnect(self):
        self.scon.stopUpdateSerial()
        self.connect_button.configure(
            text="Connect",
            command=self.push_connect)
        self.port_option_menu.config(state=NORMAL)

    def push_send(self, event):
        str = self.command_entry.get()
        str = str.upper()
        self.scon.send(str)
        self.command_entry.delete(0, END)

    def push_start(self):
        text = self.text_area.get(1.0, END)
        cmds = text.split('\n')
        for i, cmd in enumerate(cmds):
            cmd = cmd.upper()
            if (cmd[:4] == "WAIT"):
                time.sleep(float(cmd.split(" ")[1]))
            else:
                self.scon.send(cmd)

    def push_stop(self):
        pass

    def push_new(self):
        self.text_area.delete(1.0, END)

    def push_save(self):
        filename = tkFileDialog.asksaveasfilename(
            initialfile='script.hlf',
            title="Save script")

        f = gzip.open(filename, 'wb')
        f.write(self.text_area.get(1.0, END))
        f.close()

        tkMessageBox.showinfo("Finished", "The file " + filename + " has been successfully saved.")

    def push_open(self):
        pass

    def serial_event(self, str):
        # logging
        if (str[0] == '#'):
            self.log(str)

        # infos
        elif (str[0] == '?'):
            tkMessageBox.showinfo("Info", str[1:])

    def __init__(self, root):
        super(App, self).__init__()
        self.root = root

        #
        # Connect Frame
        #
        self.connect_frame = Frame(root)
        self.connect_frame.pack(padx=15, pady=15, fill=X)

        # port select box
        self.selectedPort = StringVar(root)
        portOptions = [port[0] for port in list_ports.comports()]
        self.selectedPort.set(portOptions[-1])  # set default value
        self.port_option_menu = OptionMenu(
            self.connect_frame,
            self.selectedPort,
            *portOptions)
        self.port_option_menu.pack(side=LEFT)

        # connect button
        self.connect_button = Button(self.connect_frame, text="Connect",
            command=self.push_connect)
        self.connect_button.pack(side=LEFT)

        # send button
        self.send_button = Button(self.connect_frame, text="Send",
            command=lambda: self.push_send(null))
        self.send_button.pack(side=RIGHT)

        # command input
        self.command_entry = Entry(self.connect_frame)
        self.command_entry.pack(side=RIGHT)
        self.command_entry.bind("<Return>", self.push_send)

        #
        # Text area
        #
        self.text_frame = Frame(root)
        self.text_frame.pack(padx=15, pady=(0, 15))
        self.text_area = Text(self.text_frame, bd=1, relief=GROOVE)
        self.scrollbar = Scrollbar(self.text_frame)
        self.text_area.pack(side=LEFT)
        self.scrollbar.pack(side=RIGHT, fill=Y)
        self.scrollbar.config(command=self.text_area.yview)
        self.text_area.config(yscrollcommand=self.scrollbar.set)

        #
        # Controls
        #
        self.control_frame = Frame(root)
        self.control_frame.pack(padx=15, pady=(0, 15), fill=X)

        self.start_button = Button(self.control_frame, text="Start",
            command=self.push_start)
        self.start_button.pack(side=RIGHT)

        #
        # Menu
        #
        menubar = Menu(root)
        filemenu = Menu(menubar, tearoff=0)
        filemenu.add_command(label="New", command=self.push_new)
        filemenu.add_command(label="Open", command=self.push_open)
        filemenu.add_command(label="Save", command=self.push_save)

        filemenu.add_separator()

        filemenu.add_command(label="Exit", command=root.quit)
        menubar.add_cascade(label="File", menu=filemenu)

        helpmenu = Menu(menubar, tearoff=0)
        helpmenu.add_command(label="About", command=lambda:
            tkMessageBox.showinfo("About", __doc__))
        menubar.add_cascade(label="Help", menu=helpmenu)

        root.config(menu=menubar)


def donothing():
    pass


def main():
    root = Tk()
    root.title("BioRob Automation Software")
    root.geometry("+300+100")
    root.resizable(0, 0)
    App(root)
    root.mainloop()

if __name__ == '__main__':
    main()
