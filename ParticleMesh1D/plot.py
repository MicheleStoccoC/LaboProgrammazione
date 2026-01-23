import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter
import sys

# Funzione per leggere i dati strutturati a blocchi
def read_blocks(filename):
    blocks = []
    current_block = []
    with open(filename, 'r') as f:
        for line in f:
            if line.startswith('#'): # Nuovo step temporale
                if current_block:
                    blocks.append(np.array(current_block))
                    current_block = []
                continue
            current_block.append([float(x) for x in line.split()])
    if current_block:
        blocks.append(np.array(current_block))
    return blocks

# Carichiamo i dati della griglia (Node, Density, Potential)
grid_data = read_blocks('DataGrid.txt')
# Carichiamo i dati delle particelle (Position, Velocity)
part_data = read_blocks('DataPart.txt')

fig, ax = plt.subplots()
line, = ax.plot([], [], color='blue')
ax.set_xlim(0, 10) # BoxL
ax.set_ylim(0, 1) # Regola in base ai tuoi dati

def update(frame):
    data = grid_data[frame]
    line.set_data(data[:,0], data[:,1])
    ax.set_title(f"Time Step: {frame}")
    return line,

ani = FuncAnimation(fig, update, frames=len(grid_data), blit=True)

# SALVA COME GIF
writer = PillowWriter(fps=5)
ani.save("dens_evol.gif", writer=writer)
print("Gif salvata come dens_evol.gif")

# Scegliamo 3 momenti: Inizio, Metà, Fine
steps = [0, len(part_data)//2, -1]
fig, axs = plt.subplots(2, 3, figsize=(15, 8))

for i, s in enumerate(steps):
    # Plot Densità
    axs[0, i].plot(grid_data[s][:,0], grid_data[s][:,1], color='red')
    axs[0, i].set_title(f'Densità - Step {s}')
    axs[0, i].set_ylim(0, np.max(grid_data[-1][:,1])*1.2)
    
    # Plot Spazio delle Fasi (X, V)
    axs[1, i].scatter(part_data[s][:,0], part_data[s][:,1], s=1, alpha=0.5)
    axs[1, i].set_title(f'Fase (X vs V) - Step {s}')
    axs[1, i].axhline(0, color='black', lw=0.5)

plt.tight_layout()
plt.show()
