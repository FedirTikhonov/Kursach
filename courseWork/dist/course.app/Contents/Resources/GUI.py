import tkinter as tk
from PIL import ImageTk, Image
import GenericMatrixOperations as GMO
import Solutions


class board:
    """
    Клас "дошка". Відповідає за графічне зображення та функціональність дошки.
    """
    def __init__(self, x, y, root):
        """
        Конструктор з параметрами для классу "дошка". В списку параметрів передаються 3 параметри:

        :param x: Як далеко перемістити дошку по горизонталі (в пікселях)
        :param y: Як далеко перемістити дошку по вертикалі (в пікселях)
        :param root: Вікно, в якому розміщується дошка

        Ініціалізує дошку як об'єкт, разом з матрицею, початковою кількістю ферзів та кнопками.
        """
        self._root = root
        self._initialHorizontal = x
        self._solveRBFSButton = tk.Button(text='RBFS', command=lambda: self.__RBFS_ButtonOperation(450, 52))
        self._solveRBFSButton.place(x=x + 300, y=y + 40)
        self._solveRBFSButton["state"] = "disable"
        self._solveAStarButton = tk.Button(text='A*', command=lambda: self.__AStar_buttonOperation(800, 52))
        self._solveAStarButton.place(x=x + 300, y=y + 80, width=69)
        self._solveAStarButton["state"] = "disable"
        self._InitialVertical = y
        self._activatedTiles = []
        self._activityMatrix = GMO.createEmpty()
        board._boardSymbols(30, 30, root)
        self._tileList = []
        for row in range(0, 8):
            self._tileList.append([])
            for col in range(0, 8):
                t = board._tile(row, col, x, y, self)
                self._tileList[row].append(t)
        self.__remainingQueensLabel = tk.Label(text=f'{8 - len(self._activatedTiles)} queens remaining')
        self.__remainingQueensLabel.place(x=self._initialHorizontal + 100, y=self._InitialVertical + 350)

    def _updateList(self):
        """
        Оновлює лічильник ферзів.
        """
        self.__remainingQueensLabel = tk.Label(text=f'{8 - len(self._activatedTiles)} queens remaining')
        self.__remainingQueensLabel.place(x=self._initialHorizontal + 100, y=self._InitialVertical + 350)

    def __RBFS_ButtonOperation(self, x, y):
        """
        Розв'язує задачу розміщення ферзів за допомогою RBFS-алгоритму, а саме:
        1) Створює нову шахову дошку.
        2) Оброблює матрицю згідно з алгоритмом.
        3) Правильним чином розставляє ферзів на дошці, робить всі поля недоступними для натискання.

        :param x: відстань від дошки відносно головної дошки по горизонталі (у пікселях)
        :param y: відстань від дошки відносно головної дошки по вертикалі (у пікселях)
        """
        label = tk.Label(text="RBFS solution:")
        label.place(y=y-22, x=x+80)
        matrix = GMO.copy(self._activityMatrix)
        if GMO.Check(matrix) is True:
            matrix = matrix
        else:
            matrix = Solutions.RBFS_solution(matrix)
        board._boardSymbols(self._initialHorizontal + x - 80, self._InitialVertical - y + 35, self._root)
        for row in range(0, 8):
            for col in range(0, 8):
                tmp = board._tile(row, col, x, y, self)
                if matrix[row][col] == 1:
                    tmp._createQ(self)
                else:
                    tmp._createNormal(self)
        matrix.clear()

    def __AStar_buttonOperation(self, x, y):
        """
        Розв'язує задачу розміщення ферзів за допомогою A*-алгоритму, а саме:
        1) Створює нову шахову дошку.
        2) Оброблює матрицю згідно з алгоритмом.
        3) Правильним чином розставляє ферзів на дошці, робить всі поля недоступними для натискання.

        :param x: відстань від дошки відносно головної дошки по горизонталі (у пікселях)
        :param y: відстань від дошки відносно головної дошки по вертикалі (у пікселях)
        """
        label = tk.Label(text='A* solution:')
        label.place(x=x+80, y=y-22)
        matrix = GMO.copy(self._activityMatrix)
        if GMO.Check(matrix) is True:
            matrix = matrix
        else:
            matrix = Solutions.AStarSolution(matrix)
        for i in range(0, 8):
            print(matrix[i])
        board._boardSymbols(self._initialHorizontal + x - 80, self._InitialVertical - y + 35, self._root)
        for row in range(0, 8):
            for col in range(0, 8):
                tmp = board._tile(row, col, x, y, self)
                if matrix[row][col] == 1:
                    tmp._createQ(self)
                else:
                    tmp._createNormal(self)
        matrix.clear()

    class _boardSymbols:
        """
        Клас "символи на дошці". Не несе в собі функціональності,
        тільки розставляє символи біля дошки для того, щоб користувачу було легше
        зрозуміти положення ферзя.
        """
        def __init__(self, x, y, root):
            """
            Конструктор з параметрами. Створює символи біля дошки.
            :param x: Здвиг по горизонталі(якщо дошка теж зміщена по горизонталі).
            :param y: Здвиг по вертикалі(якщо дошка теж зміщена по вертикалі).
            :param root: Вікно, в якому існує дошка.
            """
            self.__x = x
            self.__y = y
            for c in range(1, 9):
                _label = tk.Label(root, text=f'{c}')
                _label.place(x=self.__x, y=self.__y + c * 35.5 - 15)
            for c in range(1, 9):
                _label = tk.Label(root, text=f'{chr(c + 64)}')
                _label.place(x=self.__x + c * 36, y=self.__y + 300)

    class _tile:
        """
        Клас "поле". Відповідає за графічне зображення поля на дошці. Графічно є кнопкою,
        натиснувши на яку можна прибрати або поставити ферзя.
        """
        def __init__(self, row, col, move_x, move_y, someBoard):
            """
            Конструктор з параметрами для класу "поле". Приймає наступні параметри:
            :param row: ряд, в якому знаходиться поле.
            :param col: колонка, в якій знаходиться поле.
            :param move_x: зміщення колонки в горизонталі (якщо дошка зміщена, то й поле теж).
            :param move_y: зміщення колонки в вертикалі (якщо дошка зміщена, то й поле теж).
            :param someBoard: об'єкт "дошка", на якій ми ставимо поле.
            """
            self.__row = row
            self.__col = col
            self.__move_x = move_x
            self.__move_y = move_y
            self.__bl = ImageTk.PhotoImage(Image.open("Black.png"))
            self.__wh = ImageTk.PhotoImage(Image.open("White.png"))
            self.__bl_q = ImageTk.PhotoImage(Image.open("BlackWithQ.png"))
            self.__wh_q = ImageTk.PhotoImage(Image.open("WhiteWithQ.png"))
            if row % 2 == 1:
                if col % 2 == 1:
                    self.__color = self.__wh
                else:
                    self.__color = self.__bl
            else:
                if col % 2 == 1:
                    self.__color = self.__bl
                else:
                    self.__color = self.__wh
            self.__button = tk.Button(someBoard._root, image=self.__color, command=lambda: self.__place_queen(someBoard))
            self.__button.place(x=35 * row + move_x, y=35 * col + move_y)

        def __place_queen(self, someBoard):
            """
            Метод, яким ми ставимо ферзя на поле. Змінює вид поля графічно та ставить одиницю в матриці активності.
            :param someBoard: дошка, на якій ми ставимо ферзя.
            """
            someBoard._activityMatrix[self.__row][self.__col] = 1
            self.__button.destroy()
            if self.__color == self.__wh:
                self.__color = self.__wh_q
            else:
                self.__color = self.__bl_q
            self.__button = tk.Button(someBoard._root, image=self.__color, command=lambda: self.__remove_queen(someBoard))
            self.__button.place(x=35 * self.__row + self.__move_x, y=35 * self.__col + self.__move_y)
            someBoard._activatedTiles.append(self)
            someBoard._updateList()
            if len(someBoard._activatedTiles) >= 8:
                for d in range(0, 8):
                    for j in range(0, 8):
                        someBoard._tileList[d][j].__button["state"] = "disable"
                for d in range(len(someBoard._activatedTiles)):
                    someBoard._activatedTiles[d].__button["state"] = "normal"
                someBoard._solveRBFSButton["state"] = "normal"
                someBoard._solveAStarButton["state"] = "normal"

        def _createQ(self, someBoard):
            """
            Створюємо поле, на якому стоїть ферзь, і якого не можна прибрати.
            :param someBoard: шахова дошка, на якій ми бажаємо створити поле та поставити ферзя.
            """
            self.__bl_q = ImageTk.PhotoImage(Image.open("BlackWithQ.png"))
            self.__wh_q = ImageTk.PhotoImage(Image.open("WhiteWithQ.png"))
            self.__button.destroy()
            if self.__color == self.__wh:
                self.__color = self.__wh_q
            else:
                self.__color = self.__bl_q
            self.__button = tk.Button(someBoard._root, image=self.__color, command=lambda: self.__place_queen(someBoard))
            self.__button.place(x=35 * self.__row + self.__move_x, y=35 * self.__col + self.__move_y)
            self.__button["state"] = "disable"

        def _createNormal(self, someBoard):
            """
            Створюємо пусте поле, на яке не можна поставити ферзя.
            :param someBoard: шахова дошка, на якій ми бажаємо створити поле.
            """
            self.__bl_q = ImageTk.PhotoImage(Image.open("BlackWithQ.png"))
            self.__wh_q = ImageTk.PhotoImage(Image.open("WhiteWithQ.png"))
            self.__button.destroy()
            self.__button = tk.Button(someBoard._root, image=self.__color, command=lambda: self.__place_queen(someBoard))
            self.__button.place(x=35 * self.__row + self.__move_x, y=35 * self.__col + self.__move_y)
            self.__button["state"] = "disable"

        def __remove_queen(self, someBoard):
            """
            Прибираємо ферзя з певного поля. На його місці в матриці активності ставимо нуль.
            :param someBoard: дошка, з якої ми прибираємо ферзя.
            """
            someBoard._activityMatrix[self.__row][self.__col] = 0
            self.__button.destroy()
            if self.__color == self.__bl_q:
                self.__color = self.__bl
            else:
                self.__color = self.__wh
            newButton = tk.Button(someBoard._root, image=self.__color, command=lambda: self.__place_queen(someBoard))
            newButton.place(x=35 * self.__row + self.__move_x, y=35 * self.__col + self.__move_y)
            self.__button = newButton
            someBoard._activatedTiles.remove(self)
            someBoard._updateList()
            if len(someBoard._activatedTiles) < 8:
                for k in range(0, 8):
                    for j in range(0, 8):
                        someBoard._tileList[k][j].__button["state"] = "normal"
                someBoard._solveRBFSButton["state"] = "disable"
                someBoard._solveAStarButton["state"] = "disable"


def main():
    """
    Основна програма. Створює об'єкт класу "дошка", на якому виконуються всі операції.
    """
    root = tk.Tk()
    root.title("КУРСОВА РОБОТА ТИХОНОВА Ф.С.")
    root.geometry('1920x1080')
    board(50, 50, root)
    root.mainloop()
