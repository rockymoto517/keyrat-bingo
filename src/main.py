from PyQt5.QtWidgets import QApplication
from os import startfile
from time import sleep
import gui
import sys

def main():
    startfile("bingoRandomizer.exe")
    sleep(0.2)
    app = QApplication(sys.argv)
    with open("Config/Stylesheet.qss", "r") as fh:
        app.setStyleSheet(fh.read())

    win = gui.fileWindow()
    win.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
