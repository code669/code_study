# coding: utf-8

def consumer():
    r=''
    while True:
        n= yield r
        if not n :
            return 
        #print '正在消费：%s' %n + '\n'
        r='200_OK' #完成情况
def producer(c):
    c.send(None)
    n=0
    while n<=10000*100:
        n=n+1
        #print '正在生产：%d' % n + '\n'
        r=c.send(n)
        #print '消费完毕：%s' % r + '\n'
    c.close() 
c=consumer()
producer(c)
