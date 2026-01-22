import matplotlib.pyplot as plt
import numpy as np
import os

def plot_density_evolution():
    # 1. Imposta la cartella di lavoro corrente a quella dello script
    script_dir = os.path.dirname(os.path.abspath(__file__))

    file_adaptive = os.path.join(script_dir, 'rho_adaptive.txt')
    file_midpoint = os.path.join(script_dir, 'rho_midpoint.txt')

    print(f"Lettura file dalla cartella: {script_dir}")

    try:
        # Verifica esistenza file
        if not os.path.exists(file_adaptive):
            raise FileNotFoundError(f"File non trovato: {file_adaptive}\nHai eseguito 'make' ed il programma C?")
        if not os.path.exists(file_midpoint):
            raise FileNotFoundError(f"File non trovato: {file_midpoint}")

        # 2. Caricamento dati
        # Formato colonne C: [0] t, [1] RHO, [2] y_numerica, [3] y_esatta
        data_ad = np.loadtxt(file_adaptive)
        data_mp = np.loadtxt(file_midpoint)

        # Estrazione colonne per leggibilità
        t_ad = data_ad[:, 0]
        y_ad = data_ad[:, 2]
        exact_ad = data_ad[:, 3]

        t_mp = data_mp[:, 0]
        y_mp = data_mp[:, 2]
        # exact_mp = data_mp[:, 3] # Non serve duplicarla, la soluzione analitica è la stessa

        # 3. Creazione del Grafico
        plt.figure(figsize=(10, 6))

        # Plot Soluzione Esatta (Linea continua nera)
        # La prendiamo dal file adaptive che solitamente ha una buona risoluzione
        plt.plot(t_ad, exact_ad, label='Soluzione Analitica (Exact)', 
                 color='black', linewidth=1.5, alpha=0.6)

        # Plot Midpoint (Linea tratteggiata rossa)
        plt.plot(t_mp, y_mp, label='Midpoint (Passo Fisso)', 
                 color='red', linestyle='--', linewidth=2)

        # Plot Adaptive (Pallini blu)
        # Usiamo i marker 'o' per evidenziare dove l'algoritmo ha scelto i passi temporali
        plt.plot(t_ad, y_ad, 'o', label='Adaptive RK (Passo Variabile)', 
                 color='blue', markersize=4, alpha=0.7)

        # 4. Formattazione
        plt.title('Evoluzione della Densità Stellare: Numerica vs Analitica', fontsize=14)
        plt.xlabel('Tempo $t$ [Gyr]', fontsize=12)
        plt.ylabel(r'Densità $\rho_*$ [$M_\odot/kpc^3$]', fontsize=12)
        
        plt.grid(True, linestyle=':', alpha=0.6)
        plt.legend()

        # Salvataggio
        output_file = os.path.join(script_dir, 'confronto_densita.png')
        plt.savefig(output_file, dpi=300)
        print(f"Grafico salvato in: {output_file}")
        plt.show()

    except Exception as e:
        print(f"ERRORE: {e}")

if __name__ == "__main__":
    plot_density_evolution()