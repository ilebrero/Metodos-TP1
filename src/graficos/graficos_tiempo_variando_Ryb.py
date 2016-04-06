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
#f = open('../resultadosTiempos/tiemposGaussVariandoB.txt', 'r')
#for i in range(0,20):
#  y_gauss.append(float(f.readline()[:-1]))

#valores segunda funcion
f = open('../resultadosTiempos/tiemposLUVariandoRyM.txt', 'r')
for i in range(0,20):
  y_LU.append(float(f.readline()[:-1]))

f = open('../resultadosTiempos/tiemposCholeskyVariandoRyM.txt', 'r')
for i in range(0,20):
  y_cholesky.append(float(f.readline()[:-1]))


#print len(y_gauss)
#print len(y_LU)
#print len(y_cholesky)
#print len(x)
#print len(y_cholesky)
#plt.plot(x,y_gauss,'ro', color='blue', label="Gauss variando vector resultado")
plt.plot(x,y_LU,'ro', color='green', label="LU variando vector resultado")
plt.plot(x,y_cholesky,'ro', color='red', label="Cholesky variando vector resultado")

yfunction = []

a = 50
for m in range(0,20):
  if m == 0:
    yfunction.append(0)
  else:
    yfunction.append(0.0000000191721*a*a*a)
    a += 50

#sin 'ro' lo plotea como una funcion comun, continua
plt.plot(x,yfunction, color='purple', label='T(n)=k*(n^3)',linewidth=3)
plt.legend(bbox_to_anchor=(0.70,1))

#nombre que va en el eje x
plt.xlabel(u"cantidad de soluciones")

#nombre que va en el eje y
plt.ylabel("Tiempo(segundos)")

plt.show()
