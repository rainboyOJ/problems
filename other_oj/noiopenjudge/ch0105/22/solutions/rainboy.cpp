mom = 0 # 所有给妈妈的钱,mom = 1 表示mom有100元
jinjin = 0 # 津津每个月剩余的钱,刚开始剩余0
flag = 0 #标志,0表示成功,>0表示那个月失败的
for i in range(1,12+1): # 12个月份,重复12次
    spend = int(input()) # 读取要花的钱
    jinjin = jinjin + 300 # 上个月剩余的钱加上妈妈的给的钱
    jinjin = jinjin - spend #  花去这个月应该花的钱
    if jinjin < 0 : # 钱不够
        flag= i # 设置失败的月份
        break
    # 没有失败,把整百的钱给mom
    mom = mom + jinjin // 100
    jinjin = jinjin % 100 # 自己留下不足100的
 
    

if flag > 0 :
    print(flag*-1)
else:
    # 最后剩余的钱 加上 mom返给的钱
    jinjin = jinjin + mom * 120
    print(jinjin)
    
        
