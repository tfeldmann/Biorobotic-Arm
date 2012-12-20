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
import time
import thread
from serial.tools import list_ports
from SerialConnection import *


class App(object):
    def enable_serial_controls(self):
        self.port_option_menu.config(state=DISABLED)
        self.send_button.config(state=NORMAL)
        self.start_button.config(state=NORMAL)
        self.stop_button.config(state=NORMAL)

    def disable_serial_controls(self):
        self.port_option_menu.config(state=NORMAL)
        self.send_button.config(state=DISABLED)
        self.start_button.config(state=DISABLED)
        self.stop_button.config(state=DISABLED)

    def push_connect(self):
        try:
            port = self.selectedPort.get()
            self.scon = SerialConnection(port)
            self.scon.add_observer(self.serial_event)
            self.connect_button.configure(
                text="Disconnect",
                command=self.push_disconnect)
            self.enable_serial_controls()
        except Exception, e:
            tkMessageBox.showerror("Error", e.message)

    def push_disconnect(self):
        self.scon.stopUpdateSerial()
        self.connect_button.configure(
            text="Connect",
            command=self.push_connect)
        self.disable_serial_controls()

    def push_send(self, event):
        str = self.command_entry.get()
        str = str.upper()
        self.scon.send(str)
        self.command_entry.delete(0, END)

    def push_start_script(self):
        text = self.text_area.get(1.0, END)
        cmds = text.split('\n')
        thread.start_new_thread(self.start_automation_thread, (cmds,))
        self._stop_automation_thread = False

    def start_automation_thread(self, cmds):
        for cmd in cmds:

            # close thread when flag is set
            if self._stop_automation_thread:
                thread.exit()

            # handle command
            cmd = cmd.upper()

            if cmd[:4] == "WAIT":
                # wait command
                time.sleep(float(cmd.split(" ")[1]))
            elif cmd == "" or cmd[:1] == "#":
                # comment or empty line
                pass
            else:
                # send cmd to robot
                self.scon.send(cmd)
                time.sleep(0.1)  # wait 1/10s after every command

        # all commands send - done.
        thread.exit()

    def stop_automation_thread(self):
        self.scon.send("STOP")
        self._stop_automation_thread = True

    def push_new(self):
        self.text_area.delete(1.0, END)

    def push_save(self):
        filename = tkFileDialog.asksaveasfilename(
            initialfile='script.txt',
            title="Save script")
        f = open(filename, 'wb')
        f.write(self.text_area.get(1.0, END))
        f.close()

    def push_open(self):
        with open(tkFileDialog.askopenfilename(), 'rb') as f:
            file_content = f.read()
            self.text_area.delete(1.0, END)
            self.text_area.insert(1.0, file_content)

    def serial_event(self, str):
        def log(str, tags):
            """Display a logging message in the text field"""
            log_area = self.log_text
            log_area.config(state=NORMAL)
            log_area.insert(END, str + "\n", tags)
            log_area.config(state=DISABLED)
            log_area.see(END)

        # logging
        if (str[0] == '#'):
            log(str, ())

        # warning
        elif (str[0] == '!'):
            log(str, ('warning'))

        # infos
        elif (str[0] == '?'):
            tkMessageBox.showinfo("Info", str[2:])

        # position data
        elif (str[0] == "P"):
            p = str[1:].split(";")
            self.position_label.config(
                text="Base %s° Shoulder %s° Elbow %s°\n"
                "Wrist %s° Grip %s" % (p[0], p[1], p[2], p[3], p[4]),
                justify=RIGHT)

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

        #
        # Position label
        #
        self.position_label = Label(self.connect_frame)
        self.position_label.pack(side=RIGHT)

        #
        # Text areas
        #
        self.text_frame = Frame(root)
        self.text_frame.pack(padx=15, pady=(0, 15))

        self.log_text = Text(self.text_frame, width=50, state=DISABLED,
            bg="gray", bd=3)
        self.log_text.tag_configure('warning', background='yellow')
        self.log_text.pack(side=RIGHT)

        self.text_area = Text(self.text_frame, bd=1, width=50)
        self.text_area.pack(side=LEFT)
        self.text_area.focus_set()

        self.scrollbar = Scrollbar(self.text_frame)
        self.scrollbar.pack(side=RIGHT, fill=Y)

        self.scrollbar.config(command=self.text_area.yview)
        self.text_area.config(yscrollcommand=self.scrollbar.set)

        #
        # Controls
        #
        self.control_frame = Frame(root)
        self.control_frame.pack(padx=15, pady=(0, 15), fill=X)

        # command input
        self.command_entry = Entry(self.control_frame)
        self.command_entry.pack(side=LEFT)
        self.command_entry.bind("<Return>", self.push_send)

        # send button
        self.send_button = Button(self.control_frame, text="Send",
            command=lambda: self.push_send(None))
        self.send_button.pack(side=LEFT)

        # start button
        self.start_button = Button(self.control_frame, text="Start",
            command=self.push_start_script, width=10)
        self.start_button.pack(side=RIGHT)

        # stop button
        self.stop_button = Button(self.control_frame, text="Stop",
            command=self.stop_automation_thread, width=10)
        self.stop_button.pack(side=RIGHT)

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

        #
        # disable all controls that cannot be used at programm start
        #
        self.disable_serial_controls()


def main():
    root = Tk()
    root.title("BioRob Automation Software")
    root.geometry("+300+100")
    root.resizable(0, 0)
    App(root)
    root.mainloop()

if __name__ == '__main__':
    main()
