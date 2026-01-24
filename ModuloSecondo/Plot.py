import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import glob
import os

# ================= CONFIGURAZIONE =================
# Imposta True per la versione Linked List, False per Qsort
USA_LINKED_LIST_STRUCT = False       # True

DATA_DIR = "." 
PATTERN = "snapshot_*"
# ==================================================

def get_particle_dtype(use_linked_list):
    fields = [
        ('i', 'i4'), ('h', 'f8'), ('x', 'f8'), ('v', 'f8'),
        ('rho', 'f8'), ('P', 'f8'), ('u', 'f8'), ('ax', 'f8'),
        ('au', 'f8'), ('neigh_num', 'i4'), ('neighbors', '(120,)i4')
    ]
    if use_linked_list:
        fields.append(('next', 'u8')) # Puntatore 64-bit
    return np.dtype(fields, align=True)

def read_snapshot(filename, dtype):
    data = np.fromfile(filename, dtype=dtype)
    return np.sort(data, order='x') if len(data) > 0 else None

def create_single_gif(variable_name, label, color, files, dtype):
    print(f"Generazione GIF per: {label}...")
    fig, ax = plt.subplots(figsize=(8, 5))
    line, = ax.plot([], [], 'o-', markersize=2, color=color, linewidth=1)
    
    ax.set_title(f"Evoluzione {label}")
    ax.set_xlabel("Posizione (x)")
    ax.set_ylabel(label)
    ax.set_xlim(0, 1.0) # Dominio L=1 [cite: 63]
    ax.grid(True, alpha=0.3)

    # Pre-analisi per i limiti dell'asse Y (opzionale, per evitare scatti)
    y_min, y_max = float('inf'), float('-inf')
    
    def init():
        line.set_data([], [])
        return line,

    def update(frame):
        data = read_snapshot(files[frame], dtype)
        if data is not None:
            x = data['x']
            y = data[variable_name]
            line.set_data(x, y)
            
            # Autoscale Y dinamico
            ax.set_ylim(np.min(y)*0.9, np.max(y)*1.1 + 1e-5)
        return line,

    ani = animation.FuncAnimation(fig, update, frames=len(files), init_func=init, blit=True)
    filename = f"evol_QS_{variable_name}.gif"            # evol_LL_{variable_name}.gif
    ani.save(filename, writer='pillow', fps=15)
    plt.close(fig)
    print(f"Salvato: {filename}")

def main():
    files = sorted(glob.glob(os.path.join(DATA_DIR, PATTERN)))
    if not files:
        print("Errore: Nessun file snapshot trovato.")
        return

    dt = get_particle_dtype(USA_LINKED_LIST_STRUCT)

    # Definizione delle 6 grandezze richieste [cite: 66]
    quantities = [
        ('rho', 'Densita (rho)', 'blue'),
        ('P',   'Pressione (P)', 'red'),
        ('v',   'Velocita (v)', 'green'),
        ('u',   'Energia Interna (u)', 'orange'),
        ('ax',  'Accelerazione (ax)', 'purple'),
        ('h',   'Smoothing Length (h)', 'black') # Fondamentale per SPH adattivo [cite: 6]
    ]

    for var, label, color in quantities:
        create_single_gif(var, label, color, files, dt)

if __name__ == "__main__":
    main()