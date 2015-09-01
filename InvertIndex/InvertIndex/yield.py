def ydRet():
	for i in range(1,3):
		yield [j for j in range(0, i)]

a = ydRet()
for i in a:
	print (i)