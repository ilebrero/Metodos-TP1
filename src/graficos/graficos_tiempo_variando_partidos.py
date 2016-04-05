#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from math import log

#numeros del eje x
x = [50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000]
#x = [5000,10000,15000,20000,25000,30000,35000,40000,45000,50000,55000,60000,65000,70000,75000,80000,85000,90000,95000,100000]

# valores primera funcion
y_gauss = []
y_gauss2 = []
y_LU = []
y_LU2 = []
y_cholesky = []
y_cholesky2 = []
          

#valores primer funcion
f = open('../resultadosTiempos/tiemposGaussSinVariar.txt', 'r')
for i in range(0,20):
  y_gauss.append(float(f.readline()[:-1]))

f = open('../resultadosTiempos/tiemposGaussSinVariarConMuchosPartidos.txt', 'r')
for i in range(0,20):
  y_gauss2.append(float(f.readline()[:-1]))

#valores segunda funcion
f = open('../resultadosTiempos/tiemposLUSinVariar.txt', 'r')
for i in range(0,20):
  y_LU.append(float(f.readline()[:-1]))

f = open('../resultadosTiempos/tiemposLUSinVariarConMuchosPartidos.txt', 'r')
for i in range(0,20):
  y_LU2.append(float(f.readline()[:-1]))

#valores tercer funcion
f = open('../resultadosTiempos/tiemposCholeskySinVariar.txt', 'r')
for i in range(0,20):
  y_cholesky.append(float(f.readline()[:-1]))

f = open('../resultadosTiempos/tiemposCholeskySinVariarConMuchosPartidos.txt', 'r')
for i in range(0,20):
  y_cholesky2.append(float(f.readline()[:-1]))

#f = open('../resultadosTiempos/tiemposCholeskyGrandePartidos.txt', 'r')
#for i in range(0,20):
#  y_cholesky.append(float(f.readline()[:-1]))


#print len(y_gauss)
#print len(y_LU)
#print len(y_cholesky)
#print len(x)
#print len(y_cholesky)
plt.plot(x,y_gauss,'ro', color='red', label="Gauss")
plt.plot(x,y_gauss2,'ro', color='blue', label="Gauss variando partidos")
#plt.plot(x,y_LU,'ro', color='red', label="LU")
#plt.plot(x,y_LU2,'ro', color='blue', label="LU variando partidos")
#plt.plot(x,y_cholesky,'ro', color='red', label="Cholesky")
#plt.plot(x,y_cholesky2,'ro', color='blue', label="Cholesky variando partidos")
#plt.plot(x,y_cholesky,'ro', color='blue', label="Cholesky variando partidos")

yfunction = []

#a = 5000
#for m in range(0,20):
  #if m == 0:
  #  yfunction.append(0.32650)
  #else:
    #yfunction.append(0.00000991721*a)
#  yfunction.append(0.32610)

  #  a += 5000 

#print "yfunction"
#print len(yfunction)
#sin 'ro' lo plotea como una funcion comun, continua
#plt.plot(x,yfunction, color='purple', label='T(n)=k',linewidth=3)
plt.legend(bbox_to_anchor=(0.58,1))

#nombre que va en el eje x
plt.xlabel(u"Tamaño de la entrada (cantidad de equipos)")

#nombre que va en el eje y
plt.ylabel("Tiempo(segundos)")

plt.show()
