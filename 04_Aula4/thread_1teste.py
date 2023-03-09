import threading
from random import randint
import time


def funcao (min,max):

    numero_randomico= randint(min,max)
    time.sleep(numero_randomico)
    print(threading.currentThread().getName())
    print(numero_randomico)




def main():

    thread1 = threading.Thread(target=funcao,args=(0,10),name="Thread 1")
    thread2 = threading.Thread(target=funcao,args=(0,10),name="Thread 2")
    thread3 = threading.Thread(target=funcao,args=(0,10),name="Thread 3")
    thread4 = threading.Thread(target=funcao,args=(0,10),name="Thread 4")
    thread5 = threading.Thread(target=funcao,args=(0,10),name="Thread 5")
    
    thread1.start() 
    thread2.start()
    thread3.start() 
    thread4.start()
    thread5.start() 
    
    
    thread1.join()
    thread2.join() 
    thread3.join()
    thread4.join()
    thread5.join()
    
    print("Continuando") # Só executa depois que todas as threas terminarem


if __name__ == "__main__":
   main()
