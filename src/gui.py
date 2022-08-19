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
            self._opacity_effect = dict()
            self._images = dict()

            for i in range(0,25):
                self.button_dict[i] = QPushButton(self)

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

                self.button_dict[i].setGeometry(67 + (133 * (i % 5)), 176 + 133 * heightMulti,133,133)
                self.button_dict[i].setObjectName(str(i))
                self.button_dict[i].installEventFilter(self)
                self.button_dict[i].setIcon(QIcon("images/mark.png"))
                self.button_dict[i].setIconSize(QSize(0,0))

        def eventFilter(self, obj, event):
            if event.type() == QEvent.MouseButtonPress:
                if event.button() == Qt.RightButton:
                    self.button_dict[int(obj.objectName())].setIconSize(QSize(0,0))
                elif event.button() == Qt.LeftButton:
                    self.button_dict[int(obj.objectName())].setIconSize(QSize(128,128))
            return QObject.event(obj, event)

        def init_background(self):
            CARD = QImage("images/RandomizedBingoCard.png")
            palette = QPalette()
            palette.setBrush(QPalette.Window, QBrush(CARD))
            self.setPalette(palette)
