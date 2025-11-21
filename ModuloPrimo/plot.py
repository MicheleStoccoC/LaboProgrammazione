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
plt.title("Orbite dei primi 4 pianeti del sistema solare")
Orb1 = plt.plot(Pianeta1[:,0], Pianeta1[:,1], ',', label='Mercurio')
Orb2 = plt.plot(Pianeta2[:,0], Pianeta2[:,1], ',', label='Venere')
Orb3 = plt.plot(Pianeta3[:,0], Pianeta3[:,1], ',', label='Terra')
Orb4 = plt.plot(Pianeta4[:,0], Pianeta4[:,1], ',', label='Marte')
plt.xlabel("Ascisse [km]")
plt.ylabel("Ordinate [km]")
plt.legend()
plt.grid(True)
plt.show()