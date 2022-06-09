import GenericMatrixOperations as GMO
import sys
import math

sys.setrecursionlimit(10000)


def isSafe(matrix, row, col):
    """
    Перевірка, чи б'є ферзь будь-якого іншого ферзя на дошці:
    :param matrix: матриця, тобто відображення дошки.
    :param row: рядок ферзя.
    :param col: колонка ферзя.
    :return: 0/1.
    """
    coordsLst = GMO.getCoords(matrix)
    for item in coordsLst:
        if not (item[0] == row and item[1] == col):
            if row == item[0]:
                return False
            if row - item[0] == col - item[1]:
                return False
            if row + col == item[0] + item[1]:
                return False
            if col == item[1]:
                return False
    return True


def AStar(SomeMatrix):
    """
    Метод розв'язання задачі розміщення ферзів за допомогою методу А*.
    Алгоритм полягає у знаходженні будь-яких розв'язків задачі, які "здається" ведуть
    до розв'язку.
    Принцип роботи алгоритму:
    1) розв'язок починається з того, що змінній row, тобто, ряд, присвоюється значення 0.
    2) на відповідний ряд, за який відповідає змінна row, ставиться ферзь, якщо це є безпечним.
    3) Якщо весь ряд не є безпечним, то змінюємо позицію ферзя на минулому ряду.
    4) Якщо матриця повна, то її додаємо в список матриць.
    Вибір колонки працює наступним чином:
    Початкова колонка - це колонка матриці, де початково стояв ферзь.
    Евристичною функцією є функція pickClosest(), в принципі - це евклідова евристика.
    Якщо в даній колонці ферзь б'ється будь-яким іншим ферзем, то ставимо його у колонку справа від нього.
    Так йдемо, поки не дійшли або до безпечного поля, або доки не дійшли до крайнього поля справа.
    У другому випадку, ми йдемо в іншу сторону, тобто, якщо початкова колонка ферзя - 4, то спочатку йдемо
    від 4 до 8, а потім від 4 до 0.
    Якщо ферзь стоїть безпечно, то ми змінюємо його номер колонки, ставимо ферзя на відповідній позиції та йдемо далі.
    Інакше, якщо весь ряд не є безпечним, то заповнюємо ряд нулями, змінюємо колонку минулого ряда на наступний та
    переміщаємося на ряд назад.

    :param SomeMatrix: матриця з ферзями, кожний з яких стоїть на окремому рядку.
    :return: список розв'язків, тобто, матриць з правильно розставленими ферзями.
    """
    newMatrix = GMO.createEmpty()
    matrixLst = []
    row = 0
    directionList = GMO.movement(GMO.getCoords(SomeMatrix))
    colList = GMO.getCols(GMO.getCoords(SomeMatrix))
    firstRowCounter = 0
    while firstRowCounter != 7:
        placed = 0
        if directionList[row] == 1:  # Рухаємося до правого краю дошки
            for tmpCol in range(colList[row], 8):
                if tmpCol == 7:
                    directionList[row] = -1
                newMatrix[row][tmpCol] = 1
                if isSafe(newMatrix, row, tmpCol) is True:
                    colList[row] = tmpCol
                    row += 1
                    placed = 1
                    break
                else:
                    newMatrix[row][tmpCol] = 0
        if row != 8:
            for tmpCol in range(colList[row] - 1, -1, -1):  # Рухаємося до лівого краю дошки
                if placed == 1:
                    break
                newMatrix[row][tmpCol] = 1
                if isSafe(newMatrix, row, tmpCol) is True:
                    colList[row] = tmpCol
                    placed = 1
                    row += 1
                    break
                else:
                    newMatrix[row][tmpCol] = 0
            if placed != 1:  # Ідемо на рядок назад
                if directionList[row - 1] == 1:
                    colList[row - 1] += 1
                else:
                    colList[row - 1] -= 1
                GMO.eraseRow(newMatrix, row)
                colList[row] = 0
                directionList[row] = 1
                GMO.eraseRow(newMatrix, row - 1)
                row -= 1
        if row == 8:  # Додаємо матрицю до списку потенційних розв'язків
            if GMO.Check(newMatrix) is True and newMatrix not in matrixLst:
                matrixLst.append(GMO.copy(newMatrix))
            GMO.eraseRow(newMatrix, 7)
            if directionList[7] == 1:
                colList[7] += 1
            else:
                colList[7] -= 1
            row -= 1
            if directionList[0] == -1 and colList[0] == 1:
                return matrixLst


def pickClosest(currMatrix, matrices):
    """
    Відбирає матрицю,"найближчу" до початкової.
    :param currMatrix: початкова матриця, до якої потрібно знайти найближчу матрицю
    :param matrices: список матриць, з яких шукаємо найближчу
    :return: найближча матриця.
    """

    def countDifference(oneMatrix, anotherMatrix):
        """
        Порівняння двох конкретних матриць, тобто, знаходження відстані між ферзями однієї та
        іншої матриць. Функція порівнює відстані між відповідними ферзями зі списку координат
        ферзів, який вона отримує за допомогою функції getCoords()
        :param oneMatrix: матриця 8х8
        :param anotherMatrix: інша матриця 8х8
        :return: сумарна відстань між всіма ферзями.
        """
        Sum = 0
        lstOfGiven = GMO.getCoords(oneMatrix)
        lstOfSolved = GMO.getCoords(anotherMatrix)
        for queenNum in range(0, 8):
            Sum += math.sqrt((lstOfSolved[queenNum][0] - lstOfGiven[queenNum][0]) ** 2 +
                             (lstOfSolved[queenNum][1] - lstOfGiven[queenNum][1]) ** 2)
        return Sum

    smallest = countDifference(currMatrix, matrices[0])
    closest = matrices[0]
    for comparedMatrix in matrices:
        if countDifference(currMatrix, comparedMatrix) < smallest:
            smallest = countDifference(currMatrix, comparedMatrix)
            closest = comparedMatrix
    return closest


def AStarSolution(matrix):
    """
    Послідовність функцій, яка дає розв'язок задачі розміщення ферзів для дошки 8х8 методом A*.
    :param matrix: матриця 8х8, в якій є 8 одиниць та інші елементи - нулі.
    :return: матриця-розв'язок.
    """
    newMatrix = GMO.copy(matrix)
    newMatrix = GMO.placeQueensOnDifferentRows(matrix)
    solvedMatrix = pickClosest(matrix, AStar(newMatrix))
    return solvedMatrix


def RBFS(newMatrix, colList, direction, row):
    """
    Функція розв'язання задачі розміщення ферзів алгоритмом RBFS.
    (Рекурсивний пошук по першому найкращому співпадінню.)
    Працює схожим чином на А*. За виключенням, що рекурсія - це головний
    елемент цієї функції. Один з параметрів, який ми передаємо -
    це номер рядка, в якому ми знаходимося.
    За допомогою нього, та ряду інших змінних можемо переміщатися з
    рядка на рядок і правильним чином розставляти ферзів.
    :param newMatrix: матриця, в якій ми розставляємо ферзів. Важливо, на початку - це пуста матриця,
    тобто, заповнена нулями.
    :param colList: список колонок де знаходяться ферзі. Номери розставлені
    відповідно до рядків.
    :param direction: список чисел, за допомогою яких ми можемо зрозуміти, в яку сторону нам
    потрібно рухати ферзів.
    :param row: рядок, в якому ми зараз знаходимося.
    :return: матриця-розв'язок.
    """
    if row >= 8:
        return newMatrix
    else:
        if direction[row] == 1:  # Рухаємося до правого краю дошки
            for column in range(colList[row], 8):
                if column == 7:
                    direction[row] = -1
                newMatrix[row][column] = 1
                if isSafe(newMatrix, row, column) is True:
                    colList[row] = column
                    return RBFS(newMatrix, colList, direction, row + 1)
                else:
                    newMatrix[row][column] = 0
        for column in range(colList[row] - 1, -1, -1):  # Рухаємося до лівого краю дошки
            newMatrix[row][column] = 1
            if isSafe(newMatrix, row, column):
                colList[row] = column
                return RBFS(newMatrix, colList, direction, row + 1)
            newMatrix[row][column] = 0
        if direction[row - 1] == 1:  # Ідемо на рядок назад
            colList[row - 1] += 1
        else:
            colList[row - 1] -= 1
        GMO.eraseRow(newMatrix, row)
        colList[row] = 0
        direction[row] = 1
        GMO.eraseRow(newMatrix, row - 1)
        return RBFS(newMatrix, colList, direction, row - 1)


def RBFS_solution(matrix):
    """
    Послідовність функцій, необхідна для розв'язання задачі розміщення ферзів
    шляхом RBFS.
    :param матриця 8х8, в якій є 8 одиниць та інші елементи - нулі.
    :return: матриця-розв'язок.
    """
    matrix = GMO.placeQueensOnDifferentRows(matrix)
    colLst = GMO.getCols(GMO.getCoords(matrix))
    directionLst = GMO.movement(colLst)
    newMatrix = GMO.createEmpty()
    matrix = RBFS(newMatrix, colLst, directionLst, 0)
    return matrix
