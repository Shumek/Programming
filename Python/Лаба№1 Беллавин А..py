from math import *
import time
a = int(input("Введите кол-во дней:"))
i = 0
v = []#Массив темп.
for i in range(a):
    v.append(int(input("Введите температуру:")))
p=sum((int(v[i]) for i in range(a)))/a#Среднее ар.
print("Среднее значеие:",p)
print("Размах вариации:", max(v)-min(v))
j = [] #Массив модулей
for i in range(a):
    j.append(abs(v[i]-p))
h=sum((int(j[i]) for i in range(a)))/a
print("Среднее линейное отклонение:",h)
b = []#Массив для дисперсии
for i in range(a):
    b.append((v[i]-p)**2)
c=sum((int(b[i]) for i in range(a)))/a
print("Дисперсия:",c)
print("Стандартное отклонение:",sqrt(c))
time.sleep(60)
