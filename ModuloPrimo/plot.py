# -*- coding: utf-8 -*-
"""
Created on Tue Nov 18 18:35:28 2025

@author: Michele
"""

import numpy as np
import matplotlib.pyplot as plt
import os

# Ottiene il percorso assoluto della cartella in cui si trova questo script
script_dir = os.path.dirname(os.path.abspath(__file__))

# Costruisce i percorsi completi per i file
path1 = os.path.join(script_dir, 'Pianeta_1.txt')
path2 = os.path.join(script_dir, 'Pianeta_2.txt')
path3 = os.path.join(script_dir, 'Pianeta_3.txt')
path4 = os.path.join(script_dir, 'Pianeta_4.txt')

# Carica usando i percorsi completi
Pianeta1 = np.loadtxt(path1)
Pianeta2 = np.loadtxt(path2)
Pianeta3 = np.loadtxt(path3)
Pianeta4 = np.loadtxt(path4)

plt.figure(1)
plt.title("Orbite dei primi 4 pianeti del sistema Trappist-1")
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