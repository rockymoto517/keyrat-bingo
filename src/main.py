from PyQt5.QtWidgets import QApplication
from os import startfile
from time import sleep
import gui
import sys

def main():
    # Create the randomized bingo image
    startfile("bingoRandomizer.exe")
    # Sleep because the exe takes some time to run
    sleep(0.2)
    # Start the app
    app = QApplication(sys.argv)
    # Set the stylesheet
    with open("Config/Stylesheet.qss", "r") as fh:
        app.setStyleSheet(fh.read())

    # Create the window
    win = gui.fileWindow()
    win.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
