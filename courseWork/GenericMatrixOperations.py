import random


def transpose(matrix):
    """
    Транспонування матриці.
    :param matrix: матриця 8х8.
    :return: транспонована матриця 8х8.
    """
    newMatrix = []
    for i in range(0, 8):
        newMatrix.append([0, 0, 0, 0, 0, 0, 0, 0])
    for i in range(0, 8):
        for j in range(0, 8):
            newMatrix[i][j] = matrix[j][i]
    return newMatrix


def isPresent(lst):
    """
    Перевірка, чи є в списку одиниця.
    :param lst: список на 8 елементів.
    :return: 0/1
    """
    for i in range(0, 8):
        if lst[i] == 1:
            return False
    return True


def getListOfFreeRows(matrix):
    """
    Повертає список індексів рядків, де немає одиниць, тобто, вони повністю заповнені нулями.
    :param matrix: матриця 8х8.
    :return: список індексів рядків.
    """
    lst = []
    for i in range(0, 8):
        if isPresent(matrix[i]) is True:
            lst.append(i)
    return lst


def createEmpty():
    """
    Створює матрицю 8х8, повністю заповнену нулями.
    :return: матрицю 8х8, повністю заповнена нулями
    """
    newMatrix = []
    for row in range(0, 8):
        newMatrix.append([])
    for rowID in range(0, 8):
        for colID in range(0, 8):
            newMatrix[rowID].append(0)
    return newMatrix


def eraseRow(matrix, row):
    """
    Заповнює певний рядок матриці нулями.
    :param matrix: матриця 8х8
    :param row: рядок (від нуля до семи включно)
    """
    for i in range(0, 8):
        matrix[row][i] = 0


def createRandom():
    RandomMatrix = []
    for i in range(0, 8):
        RandomMatrix.append([0, 0, 0, 0, 0, 0, 0, 0])
    counter = 0
    while counter != 8:
        RandomX = random.randint(0, 7)
        RandomY = random.randint(0, 7)
        if RandomMatrix[RandomX][RandomY] != 1:
            RandomMatrix[RandomX][RandomY] = 1
            counter += 1
    return RandomMatrix


def getCoords(matrix):
    """
    Повертає список координат віх одиниць в матриці.
    :param matrix: матриця 8х8
    :return: повертає матрицю на 8 списків,
    елементами яких на першій позицій стоїть рядок, а на другій стовпчик.
    """
    lst = []
    for i in range(0, 8):
        for j in range(0, 8):
            if matrix[i][j] == 1:
                lst.append([i, j])
    return lst


def placeQueensOnDifferentRows(matrix):
    """
    Якщо в матриці декілька одиниць на одному рядку, то функція розставляє їх на вільні рядки.
    :param matrix: матриця 8х8, у якій 8 одиниць, а інші - нулі.
    :return: матриця 8х8, у якої всі одиниці розставлені на різних рядках.
    """
    freeLst = getListOfFreeRows(matrix)
    if len(freeLst) == 0:
        return matrix
    else:
        print(freeLst)
        counter = 0
        lstCounter = 0
        for i in range(0, 8):
            for j in range(0, 8):
                if counter == 0 and matrix[i][j] == 1:
                    counter = 1
                elif counter > 0 and matrix[i][j] == 1:
                    matrix[i][j] = 0
                    matrix[freeLst[lstCounter]][j] = 1
                    lstCounter += 1
                if j == 7:
                    counter = 0
        return matrix


def Check(matrix):
    """
    Перевірка, чи є в матриці хоч одна пара одиниць,
    які знаходяться по діагоналі, по вертикалі
    або по горизонталі одна від іншої.
    :param matrix: матриця 8х8.
    :return: 0/1
    """
    lst = getCoords(matrix)
    for anItem in lst:
        for item in lst:
            if item != anItem:
                if anItem[0] == item[0]:
                    return False
                if anItem[0] - item[0] == anItem[1] - item[1]:
                    return False
                if anItem[0] + anItem[1] == item[0] + item[1]:
                    return False
                if anItem[1] == item[1]:
                    return False
    return True


def movement(colLst):
    """
    Список, який ми передаємо як параметр - це список індексів колонок одиниць в матриці,
    пронумеровані відповідно до рядка. тобто, в якщо 5 елемент в списку має значення 4,
    то це означає, що в 5 рядку в 4 колонці стоїть одиниця.
    Якщо колонка дорівнює семи, то заносимо в список -1. Інакше заносимо 1.
    :param colLst: список колонок одиниць матриці.
    :return: список з 8 елементів, які є 1 або -1.
    """
    directionList = []
    for num in colLst:
        if num == 7:
            directionList.append(-1)
        else:
            directionList.append(1)
    return directionList


def findCol(matrix, row):
    """
    Повертає номер колонки, в якій знаходиться одиниця в рядку певної матриці.
    :param matrix: матриця 8х8.
    :param row: рядок довжиною 8.
    :return:
    """
    for i in range(0, 8):
        if matrix[row][i] == 1:
            return i


def getCols(coordsLst):
    """
    Повертає список колонок рядків.
    :param coordsLst: список координатів одиниць.
    :return: список колонок.
    """
    newLst = []
    for item in coordsLst:
        newLst.append(item[1])
    return newLst


def copy(matrix):
    """
    Копіює матрицю.
    :param matrix: матриця 8х8.
    :return: копійована матриця 8х8.
    """
    m = []
    for i in range(0, 8):
        m.append([0, 0, 0, 0, 0, 0, 0, 0])
    for i in range(0, 8):
        for j in range(0, 8):
            m[i][j] = matrix[i][j]
    return m
