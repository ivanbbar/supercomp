import time

def calcular_pi(n):
    pi = 0
    sinal = 1

    for i in range(1, n+1):
        termo = 1 / (2*i - 1)
        pi += sinal * termo
        sinal *= -1

    return pi * 4

n = 1000000000

inicio = time.time()
resultado = calcular_pi(n)
fim = time.time()

tempo_execucao = fim - inicio

print("Valor aproximado de π:", resultado)
print("Tempo de execução:", tempo_execucao, "segundos")
