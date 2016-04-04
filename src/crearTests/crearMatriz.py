import random

#f1 = open('../tests/test_de_50_a_1000.txt', 'w')
#f2 = open('../tests/test_de_50_a_1000_con_muchos_partidos.txt', 'w')
  
#cantEquipos = 1000
#
#while (cantEquipos <= 1000):
#  print cantEquipos
#  cantPartidos = 0
#
#  if (i == 1):
#    cantPartidos = 2*cantEquipos
#    line = str(cantEquipos) + ' ' + str(cantPartidos) + '\n'
#    f1.write(line)
#  else:
#    cantPartidos = cantEquipos * cantEquipos
#    line = str(cantEquipos) + ' ' + str(cantPartidos) + '\n'
#    f2.write(line)
#
#
#  for j in range (0, cantPartidos):
#    equipo1 = random.randint(1, cantEquipos)
#    equipo2 = random.randint(1, cantEquipos)
#
#    while (equipo1 == equipo2):
#        equipo2 = random.randint(1, cantEquipos)
#
#    puntaje1 = random.randint(0, cantEquipos)
#    puntaje2 = random.randint(0, cantEquipos)
#
#    while (puntaje1 == puntaje2):
#        puntaje2 = random.randint(0, cantEquipos)
#
#    dia = 0
#
#    line =  str(dia) + ' ' + str(equipo1) + ' ' + str(puntaje1) + ' ' + str(equipo2) + ' ' + str(puntaje2) + '\n'
#
#    if i == 1:
#      f1.write(line)
#    else:
#      f2.write(line)
#
#  if i == 1:
#    i += 1
#  else:
#    cantEquipos += 50
#    i = 1
#

#f = open('../tests/test_grande.txt', 'w')
#
#cantEquipos = 1000
#
#while (cantEquipos <= 10000):
#
#  cantPartidos = 2*cantEquipos
#  line = str(cantEquipos) + ' ' + str(cantPartidos) + '\n'
#  f.write(line)
#
#
#  for j in range (0, cantPartidos):
#    equipo1 = random.randint(1, cantEquipos)
#    equipo2 = random.randint(1, cantEquipos)
#
#    while (equipo1 == equipo2):
#        equipo2 = random.randint(1, cantEquipos)
#
#    puntaje1 = random.randint(0, cantEquipos)
#    puntaje2 = random.randint(0, cantEquipos)
#
#    while (puntaje1 == puntaje2):
#        puntaje2 = random.randint(0, cantEquipos)
#
#    dia = 0
#
#    line =  str(dia) + ' ' + str(equipo1) + ' ' + str(puntaje1) + ' ' + str(equipo2) + ' ' + str(puntaje2) + '\n'
#
#    f.write(line)
#
#  cantEquipos += 1000

#f = open('../tests/test_grande_partidos.txt', 'w')
#
#cantEquipos = 500
#cantPartidos = 5000
#
#while (cantPartidos <= 100000):
#  print cantPartidos
#
#  line = str(cantEquipos) + ' ' + str(cantPartidos) + '\n'
#  f.write(line)
#
#  for j in range (0, cantPartidos):
#    equipo1 = random.randint(1, cantEquipos)
#    equipo2 = random.randint(1, cantEquipos)
#
#    while (equipo1 == equipo2):
#        equipo2 = random.randint(1, cantEquipos)
#
#    puntaje1 = random.randint(0, cantEquipos)
#    puntaje2 = random.randint(0, cantEquipos)
#
#    while (puntaje1 == puntaje2):
#        puntaje2 = random.randint(0, cantEquipos)
#
#    dia = 0
#
#    line =  str(dia) + ' ' + str(equipo1) + ' ' + str(puntaje1) + ' ' + str(equipo2) + ' ' + str(puntaje2) + '\n'
#
#    f.write(line)
#
#  cantPartidos += 5000

f = open('../tests/test_variando_resultado.txt', 'w')

cantEquipos = 500
cantPartidos = 500

line = str(cantEquipos) + ' ' + str(cantPartidos) + '\n'
f.write(line)

for j in range (0, cantPartidos):
  equipo1 = random.randint(1, cantEquipos)
  equipo2 = random.randint(1, cantEquipos)

  while (equipo1 == equipo2):
      equipo2 = random.randint(1, cantEquipos)

  puntaje1 = random.randint(0, cantEquipos)
  puntaje2 = random.randint(0, cantEquipos)

  while (puntaje1 == puntaje2):
      puntaje2 = random.randint(0, cantEquipos)

  dia = 0

  line =  str(dia) + ' ' + str(equipo1) + ' ' + str(puntaje1) + ' ' + str(equipo2) + ' ' + str(puntaje2) + '\n'

  f.write(line)
