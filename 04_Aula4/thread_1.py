import threading
from random import randint
import time

def tarefa1(min,max):
   time.sleep(randint(0,10))
   print(threading.currentThread().getName())
   print(randint(min,max))

def main():
   #pseudo-paralelismo (todas as threads vão para a mesma unidade de processamento, a programação em python é concorrente)
   #thread = threading.Thread(target=funcao, args=(x,y,),name='NOME')
    thread1 = threading.Thread(target=tarefa1, args=(0,10,),name='Tarefa 01')
    thread2 = threading.Thread(target=tarefa1, args=(10,100,),name='Tarefa 02')
    thread3 = threading.Thread(target=tarefa1, args=(100,1000,),name='Tarefa 03')
    thread4 = threading.Thread(target=tarefa1, args=(1000,10000,), name='Tarefa 04')

    thread1.start() #executa e já começa a próxima sem ter que esperar toda essa finalizar
    thread2.start()
    thread3.start() #comandos para esperar ( trava e só executa a próxima linha quando todas as execuções até aqui executarem)
    thread4.start()

    thread1.join()
    thread2.join()
    thread3.join()
    thread4.join()

    
if __name__ == "__main__":
   main()
