import os
import sys
import math

ans = open("answer", "r")
ouf = open("user_out", "r")

x = []
stdcnt = 0
usrcnt = 0

stdans = ans.readlines()
for p in stdans:
	if p[0] == 'N':
		x.append(-1.0)
	else:
		x.append(float(p))
	stdcnt = stdcnt + 1

usrans = ouf.readlines()
for p in usrans:
	if usrcnt >= stdcnt:
		print (0)
		sys.stderr.write('More information!QAQ')
		ouf.close()
		ans.close()
		sys.exit(0)
	if x[usrcnt] == -1.0:
		p = p.strip()
		if p!='No solution':
			print (0)
			sys.stderr.write('Wrong format!QAQ')
			ouf.close()
			ans.close()
			sys.exit(0)
	else:
		p = p.strip()
		if p == 'No solution':
			print (0)
			sys.stderr.write('There is a solution to the input at Test #%d!QAQ'%(usrcnt+1))
			ouf.close()
			ans.close()
			sys.exit(0)
		try:
			m = float(p)
		except Exception:
			print (0)
			sys.stderr.write('Wrong format!QAQ')
			ouf.close()
			ans.close()
			sys.exit(0)
		if math.fabs(m-x[usrcnt])>0.01+1E-8:
			print (0)
			sys.stderr.write('Except %.10f, but found %.10f!QAQ'%(x[usrcnt],m))
			ouf.close()
			ans.close()
			sys.exit(0)
	usrcnt = usrcnt + 1

print (100)
sys.stderr.write('Your solution is acceptable!^ ^')

ouf.close()
ans.close()
