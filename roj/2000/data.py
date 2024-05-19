## 得到样例
from cyaron import * # 引入CYaRon的库


while 1:
    a = String.random(5)
    b = String.random(4)
    aa = list(map(lambda x: ord(x)-ord('a')+1,a))
    na = reduce(lambda x,y: x*y, aa)

    bb = list(map(lambda x: ord(x)-ord('a')+1,b))
    nb = reduce(lambda x,y: x*y, bb)
    if nb == na:
        print(a)
        print(b)
        print(na)
        print(nb)
        break;
