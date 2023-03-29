from multiprocessing import Queue, Process

def cubo(numbers, queue):
    for i in numbers:
        queue.put(i**3)
        
def add_uno(numbers, queue):
    for i in numbers:
        queue.put(i + 1)

q = Queue()
numbers = range(1,8)

p1=Process(target=cubo,args=(numbers,q))
p2=Process(target=add_uno,args=(numbers,q))

p1.start()
p2.start()

p1.join()
p2.join()
      
while not q.empty():
    print(q.get())      