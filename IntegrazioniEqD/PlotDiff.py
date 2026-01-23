import matplotlib.pyplot as plt
import numpy as np
import os

def plot_diffusion():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(script_dir, 'InkDiff.txt')

    if not os.path.exists(file_path):
        print("File non trovato!")
        return

    # Carichiamo i dati
    data = np.loadtxt(file_path)
    
    # I dati sono [t, x, u]. Dobbiamo separare le curve in base al tempo t.
    times = np.unique(data[:, 0]) # Trova tutti i tempi unici salvati

    plt.figure(figsize=(10, 6))

    # Usiamo una colormap per distinguere i tempi (dal blu al rosso)
    colors = plt.cm.viridis(np.linspace(0, 1, len(times)))

    for i, t in enumerate(times):
        # Filtra i dati per questo specifico tempo t
        subset = data[data[:, 0] == t]
        
        plt.plot(subset[:, 1], subset[:, 2], 
                 label=f't = {t:.1f} s', color=colors[i], linewidth=2)

    plt.title('Diffusione 1D (Method of Lines)', fontsize=14)
    plt.xlabel('Posizione x [cm]', fontsize=12)
    plt.ylabel('Concentrazione u', fontsize=12)
    plt.legend(title="Tempo", loc='upper right')
    plt.grid(True, linestyle=':', alpha=0.6)
    
    output_file = os.path.join(script_dir, 'diffusion_plot.png')
    plt.savefig(output_file, dpi=300)
    print(f"Grafico salvato: {output_file}")
    plt.show()

if __name__ == "__main__":
    plot_diffusion()