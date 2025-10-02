import matplotlib.pyplot as plt
import numpy as np
P_h1 = 0.1
P_h2 = 0.2
P_h3 = 0.4
P_h4 = 0.2
P_h5 = 0.1

p_hi = [0.1,0.2,0.4,0.2,0.1]
N_ph = [0,0.25,0.5,0.75,1]

N_p_h1 = 0
N_p_h2 = 0.25
N_p_h3 = 0.5
N_p_h4 = 0.75
N_p_h5 = 1

def P_Di_h(i,k):
    return (N_ph[i]**k)*p_hi[i]

h1_dist=[]
h2_dist=[]
h3_dist=[]
h4_dist=[]
h5_dist=[]

K=10

for i in range(K):
    k=i+1
    dist = [P_Di_h(j,k) for j in range(5)]
    dist = dist/np.sum(dist)
    
    h1_dist.append(dist[0])
    h2_dist.append(dist[1])
    h3_dist.append(dist[2])
    h4_dist.append(dist[3])
    h5_dist.append(dist[4])

plt.figure(figsize=(10, 5))
plt.plot(h1_dist, label='h1', linewidth=2,marker='o')
plt.plot(h2_dist, label='h2', linewidth=2,marker='o')
plt.plot(h3_dist, label='h3', linestyle='--',marker='o') # Uso uno stile diverso
plt.plot(h4_dist, label='h4', linestyle=':',marker='o')  # Uso uno stile diverso
plt.plot(h5_dist, label='h5', linestyle='-.',marker='o') # Uso uno stile diverso

# Aggiungi titolo, etichette e legenda
plt.xlabel('number of lime candy extracted')
plt.ylabel('Posterior probability of hypothesis')
plt.legend()
plt.grid(True)

# Mostra il plot (se stai eseguendo in un ambiente locale interattivo)
plt.show()