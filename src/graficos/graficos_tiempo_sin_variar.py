#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from math import log

#numeros del eje x
x = [50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000]

# valores primera funcion
y_gauss = []
y_LU = []
y_cholesky = []
          

#valores primer funcion
f = open('../resultadosTiempos/tiemposGaussSinVariar.txt', 'r')
for i in range(0,20):
  y_gauss.append(float(f.readline()[:-1]))

#valores segunda funcion
f = open('../resultadosTiempos/tiemposLUSinVariar.txt', 'r')
for i in range(0,20):
  y_LU.append(float(f.readline()[:-1]))

#valores tercer funcion
f = open('../resultadosTiempos/tiemposCholeskySinVariar.txt', 'r')
for i in range(0,20):
  y_cholesky.append(float(f.readline()[:-1]))

print len(y_gauss)
print len(y_LU)
print len(y_cholesky)
print len(x)
plt.plot(x,y_gauss,'ro', color='green', label="Gauss")
plt.plot(x,y_LU,'ro', color='red', label="LU")
plt.plot(x,y_cholesky,'ro', color='blue', label="Cholesky")

yfunction = []

a = 50
for m in range(0,20):
  if m == 0:
    yfunction.append(0)
  else:
    yfunction.append(0.00000001721*a*a*a)
    a += 50 

#sin 'ro' lo plotea como una funcion comun, continua
plt.plot(x,yfunction, color='purple', label='T(n)=k*(n^3)',linewidth=3)
plt.legend(bbox_to_anchor=(0.35,1))

#nombre que va en el eje x
plt.xlabel(u"Tamaño de la entrada (cantidad de equipos)")

#nombre que va en el eje y
plt.ylabel("Tiempo(segundos)")

plt.show()
