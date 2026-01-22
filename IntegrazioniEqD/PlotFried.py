import os
import matplotlib.pyplot as plt
import numpy as np

# 1. Trova la cartella dove si trova fisicamente questo script (Plot.py)
script_dir = os.path.dirname(os.path.abspath(__file__))
    
# 2. Costruisci il percorso assoluto ai file .txt
file_adaptive = os.path.join(script_dir, 'Fried_adaptive.txt')
file_midpoint = os.path.join(script_dir, 'Fried_midpoint.txt')

print(f"Sto cercando i file in: {script_dir}")

def plot_cosmology():
    try:
        #Verifica se i file esistono prima di caricarli
        if not os.path.exists(file_adaptive):
            raise FileNotFoundError(f"Manca il file: {file_adaptive}")
        if not os.path.exists(file_midpoint):
            raise FileNotFoundError(f"Manca il file: {file_midpoint}")
        # Caricamento dati
        data_adaptive = np.loadtxt(file_adaptive)
        data_midpoint = np.loadtxt(file_midpoint)

        plt.figure(figsize=(10, 6))

        # Grafico Adaptive RK
        plt.plot(data_adaptive[:, 0], data_adaptive[:, 1], 
                 label='Adaptive RK (odeint)', color='blue', linewidth=2)

        # Grafico Midpoint
        plt.plot(data_midpoint[:, 0], data_midpoint[:, 1], 
                 label='Midpoint Step', color='red', linestyle='--', alpha=0.7)

        # Formattazione estetica
        plt.title('Evoluzione del Fattore di Scala $a(t)$', fontsize=14)
        plt.xlabel('Tempo [Gyr]', fontsize=12)
        plt.ylabel('Fattore di scala $a$', fontsize=12)
        
        plt.axhline(1.0, color='black', lw=0.5, ls=':') # Linea dell'universo oggi (a=1)
        plt.grid(True, which='both', linestyle='--', alpha=0.5)
        plt.legend()
        
        # Salvataggio e visualizzazione
        plt.savefig('confronto_metodi.png', dpi=300)
        print("Grafico salvato come 'confronto_metodi.png'")
        plt.show()

    except FileNotFoundError as e:
        print(f"Errore: Assicurati che i file .txt siano presenti. ({e})")
    except Exception as e:
        print(f"Si è verificato un errore: {e}")

if __name__ == "__main__":
    plot_cosmology()