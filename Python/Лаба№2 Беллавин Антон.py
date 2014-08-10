from math import *
import time
#функция стат обработки
def stat(arr):
    p=sum((int(arr[i]) for i in range(len(arr))))/(len(arr))#Среднее ар.
    print("Среднее значеие:",p)
    print("Размах вариации:", max(arr)-min(arr))
    j = [] #Массив модулей
    for i in range(0,len(arr)):
        j.append(abs(arr[i]-p))
    h=sum((int(j[i]) for i in range(0,len(arr))))/len(arr)
    print("Среднее линейное отклонение:",h)
    b = []#Массив для дисперсии
    for i in range(0,len(arr)):
        b.append((arr[i]-p)**2)
    c=sum((int(b[i]) for i in range(0,len(arr))))/len(arr)
    print("Дисперсия:",c)
    print("Стандартное отклонение:",sqrt(c))
    return 1

#открытие файла для чтения
file = open("hello.csv")

#построчный просмотр файла
for line in file:
    #создание пустого массива
    a = []
    #удаление спецсимволов из строки
    line = line.strip()
    #поэлементный просмотр массива, сформированного из строки
    for i in line.split(";"):
        #добавление переведённого в целое число элемента строки
        a.append(int(i))
    #вызов функции стат обработки
    stat(a)
time.sleep(60)
#закрытие файла
file.close()
