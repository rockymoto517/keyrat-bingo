from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5 import *

class fileWindow(QWidget):
        def __init__(self,parent=None):
            super().__init__(parent)

            self.init_widgets()
            self.init_background()

            self.show()


        def init_widgets(self):
            self.setWindowTitle("Bingo")
            self.setGeometry(0,0,808,880)
            self.setWindowIcon(QIcon("bingoCard.png"))

            self.button_dict = dict()

            for i in range(0,25):
                self.button_dict[i] = QPushButton(self)

                # Set the heights of the marks based on the row
                if i < 5:
                    heightMulti = 0
                elif i < 10:
                    heightMulti = 1
                elif i < 15:
                    heightMulti = 2
                elif i < 20:
                    heightMulti = 3
                else:
                    heightMulti = 4

                # Space out the tiles correctly
                self.button_dict[i].setGeometry(67 + (133 * (i % 5)), 176 + 133 * heightMulti,133,133)
                self.button_dict[i].setObjectName(str(i))
                # Give an event callback
                self.button_dict[i].installEventFilter(self)
                # Set the bingo mark properly
                self.button_dict[i].setIcon(QIcon("images/mark.png"))
                # Make the mark invisible
                self.button_dict[i].setIconSize(QSize(0,0))

        def eventFilter(self, obj, event):
            # Toggle the O, left click toggles on and right click toggles off
            if event.type() == QEvent.MouseButtonPress:
                if event.button() == Qt.RightButton:
                    self.button_dict[int(obj.objectName())].setIconSize(QSize(0,0))
                elif event.button() == Qt.LeftButton:
                    self.button_dict[int(obj.objectName())].setIconSize(QSize(128,128))
            return QObject.event(obj, event)

        def init_background(self):
            # Use the randomized bingo card as a background image
            CARD = QImage("images/RandomizedBingoCard.png")
            palette = QPalette()
            palette.setBrush(QPalette.Window, QBrush(CARD))
            self.setPalette(palette)
