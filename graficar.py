import numpy as np
import matplotlib.pyplot as plt

#grafica los elementos de valores.txt para cada uno de los hilos, y genera un archivo .png con la grafica
def graficar_tiempo_ns():
    #leer el archivo valores.txt
    data = np.loadtxt('valores.txt')
    print("Se ha leido el archivo valores.txt con los datos de los tiempos de ejecución.")
    #separar los datos en hilos, tiempo y tiempo2
    hilos = data[:,0]
    tiempo2 = data[:,2]
    #graficar los datos
    plt.figure()
    print("Generando grafica de los tiempos de ejecución...")
    plt.plot(hilos, tiempo2, label='Tiempo time()')
    plt.xlabel('Hilos')
    plt.ylabel('Tiempo (ns)')
    plt.title('Tiempo de ejecución en nanosegundos vs Hilos')
    plt.legend()
    plt.savefig('./grafica_ns.png')
    
def graficar_tiempo_reloj():
    #leer el archivo valores.txt
    data2 = np.loadtxt('valores.txt')
    #separar los datos en hilos, tiempo y tiempo2
    hilos2 = data2[:,0]
    tiempo2 = data2[:,1]
    #graficar los datos
    plt.figure()
    plt.plot(hilos2, tiempo2, label='Tiempo reloj()')
    plt.xlabel('Hilos')
    plt.ylabel('Tiempo (reloj)')
    plt.title('Ciclos de reloj vs Hilos')
    plt.legend()
    plt.savefig('./grafica_reloj.png')

graficar_tiempo_reloj()
graficar_tiempo_ns()
