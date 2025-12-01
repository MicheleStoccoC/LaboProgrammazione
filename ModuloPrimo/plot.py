# -*- coding: utf-8 -*-
"""
Created on Tue Nov 18 18:35:28 2025

@author: Michele
"""
#   Librerie
import numpy as np
import matplotlib.pyplot as plt

#   Import pianeti
Pianeta1 = np.loadtxt('Pianeta_1.txt')
Pianeta2 = np.loadtxt('Pianeta_2.txt')
Pianeta3 = np.loadtxt('Pianeta_3.txt')
Pianeta4 = np.loadtxt('Pianeta_4.txt')

plt.figure(1)
plt.title("Orbite dei primi 4 pianeti del sistema")
Orb1 = plt.plot(Pianeta1[:,1], Pianeta1[:,2], '.', markersize=1, label='Pianeta 1')
Orb2 = plt.plot(Pianeta2[:,1], Pianeta2[:,2], '.', markersize=1, label='Pianeta 2')
Orb3 = plt.plot(Pianeta3[:,1], Pianeta3[:,2], '.', markersize=1, label='Pianeta 3')
Orb4 = plt.plot(Pianeta4[:,1], Pianeta4[:,2], '.', markersize=1, label='Pianeta 4')
Sun = plt.plot(0,0, 'o', color='yellow')
plt.gca().set_aspect('equal', adjustable='box')
plt.xlabel("Ascisse [km]")
plt.ylabel("Ordinate [km]")
plt.legend()
plt.grid(True)
plt.show()

plt.figure(2)
plt.title("Velocità del Pianeta 3 in funzione del tempo")
VelX = plt.plot(Pianeta3[:,0], Pianeta3[:,3], '.', markersize=3, label='vX')
VelY = plt.plot(Pianeta3[:,0], Pianeta3[:,4], '.', markersize=3, label='vY')
plt.xlabel("Tempo [yr]")
plt.ylabel("Velocità [m/s]")
plt.legend()
plt.grid(True)
plt.show()