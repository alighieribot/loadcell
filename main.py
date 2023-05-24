import numpy as np
import matplotlib.pyplot as plt

# Valores de window_size
# O valor definido deve ser proporcional à carga
window_sizes = range(2, 21, 2)

def remove_first_line(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()

    with open(file_path, 'w') as f:
        f.writelines(lines[1:])

def load_data(file_path):
    data = np.loadtxt(file_path, delimiter=',')
    tempo = data[:, 0]
    massa = data[:, 1]
    torque = data[:, 2]
    return tempo, massa, torque

# Carregar dados do arquivo .txt
try:
    tempo, massa, torque = load_data('data.txt')
except Exception as e:
    print(f'{e}\nRemovendo o cabeçalho...')
    remove_first_line('data.txt')
    tempo, massa, torque = load_data('data.txt')

# Plotar gráficos e salvar em arquivos PNG separados
plt.figure(figsize=(10, 8))
for i, window_size in enumerate(window_sizes):
    filtered_massa = np.convolve(massa, np.ones(window_size)/window_size, mode='valid')
    filtered_torque = np.convolve(torque, np.ones(window_size)/window_size, mode='valid')

    plt.plot(tempo, massa, label='Dados Originais')
    plt.plot(tempo[window_size-1:], filtered_massa, label=f'Filtro (window_size={window_size})')
    plt.xlabel('Tempo')
    plt.ylabel('Massa (kg)')
    plt.title(f'Gráfico de Massa (window_size={window_size})', )
    plt.legend()
    plt.savefig(f'cache/grafico_massa_{window_size}.png', dpi=300)
    plt.clf()

# Salvar um PNG com todos os gráficos juntos
plt.figure(figsize=(10, 8))
for i, window_size in enumerate(window_sizes):
    filtered_massa = np.convolve(massa, np.ones(window_size)/window_size, mode='valid')
    filtered_torque = np.convolve(torque, np.ones(window_size)/window_size, mode='valid')

    plt.plot(tempo[window_size-1:], filtered_massa, label=f'Filtro (window_size={window_size})')

plt.plot(tempo, massa, '-', label=f'Dados Originais', color='black', linewidth=2.5)
plt.xlabel('Tempo')
plt.ylabel('Massa (kg)')
plt.title('Gráfico de Massa - Todos os Filtros')
plt.legend()
plt.tight_layout()
plt.savefig('cache/concat.png', dpi=300)
plt.show()

# Salvar outro PNG com todos os graficos separados
plt.figure(figsize=(10, 8))
for i, window_size in enumerate(window_sizes):
    filtered_massa = np.convolve(massa, np.ones(window_size)/window_size, mode='valid')
    filtered_torque = np.convolve(torque, np.ones(window_size)/window_size, mode='valid')

    plt.subplot(5, 2, i+1)
    plt.subplots_adjust(left=0.1, right=0.9, bottom=0.1, top=0.9, wspace=0.4, hspace=0.4)
    plt.plot(tempo, massa, label='Dados Originais')
    plt.plot(tempo[window_size-1:], filtered_massa, label=f'Filtro (window_size={window_size})')
    plt.xlabel('Tempo')
    plt.ylabel('Massa (kg)')
    plt.title(f'Gráfico de Massa (window_size={window_size})')
    plt.legend(loc='best', fontsize="7")

plt.savefig('cache/side_by_side.png', dpi=300)
plt.tight_layout()
plt.show()
