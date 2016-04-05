#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from math import log

#numeros del eje x
x = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]

# valores primera funcion
y_LU = []
y_cholesky = []
          
#valores segunda funcion
f = open('../resultadosTiempos/tiemposLUSinVariarGrande.txt', 'r')
for i in range(0,10):
  y_LU.append(float(f.readline()[:-1]))

#valores tercer funcion
f = open('../resultadosTiempos/tiemposCholeskySinVariarGrande.txt', 'r')
for i in range(0,10):
  y_cholesky.append(float(f.readline()[:-1]))

plt.plot(x,y_LU,'ro', color='red', label="LU")
plt.plot(x,y_cholesky,'ro', color='blue', label="Cholesky")

yfunction = []

a = 50
for m in range(0,10):
  if m == 0:
    yfunction.append(0)
  else:
    yfunction.append(0.00016991721*a*a*a)
    a += 50 

#sin 'ro' lo plotea como una funcion comun, continua
plt.plot(x,yfunction, color='purple', label='T(n)=k*(n^3)',linewidth=3)
plt.legend(bbox_to_anchor=(0.35,1))

#nombre que va en el eje x
plt.xlabel(u"Tamaño de la entrada (cantidad de equipos)")

#nombre que va en el eje y
plt.ylabel("Tiempo(segundos)")

plt.show()
