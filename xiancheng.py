from threading import Thread, Lock
import sys

lock = Lock()
n = 0

def productor():
    global n
    while n <= 100*10000:
        lock.acquire()
        n = n + 1
        lock.release()

def customer():
    global n
    while n <= 100*10000:
        lock.acquire()
        lock.release()

if __name__ =='__main__':
    p = Thread(target=productor)
    c = Thread(target=customer)
    p.start()
    c.start()
    p.join()
    c.join()
