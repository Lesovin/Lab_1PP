import numpy as np

M1 = np.zeros(shape=(400, 400), dtype=int)
M2 = np.zeros(shape=(400, 400), dtype=int)
Data1 = np.genfromtxt('C:\\Users\\a1806\\source\\repos\\Lab_1PP\\Lab_1PP\\Data1.txt', delimiter="\t", dtype=int)
Data2 = np.genfromtxt('C:\\Users\\a1806\\source\\repos\\Lab_1PP\\Lab_1PP\\Data2.txt', delimiter="\t", dtype=int)
k = 0
for i in range(400):
    for j in range(400):
        M1[i][j] = Data1[k]
        M2[i][j] = Data2[k]
        k += 1
ResMatrix = np.dot(M1, M2)
DataRes = np.genfromtxt('C:\\Users\\a1806\\source\\repos\\Lab_1PP\\Lab_1PP\\Res_Matrix.txt', delimiter="\t", dtype=int)
M3 = np.zeros(shape=(400, 400), dtype=int)
k = 0
for i in range(400):
    for j in range(400):
        M3[i][j] = DataRes[k]
        k += 1
if (np.array_equal(ResMatrix, M3)):
    print("Хорошо")
else:
    print("Плохо")
