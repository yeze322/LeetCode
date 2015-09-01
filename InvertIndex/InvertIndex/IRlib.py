import os
import linecache
import sys
import json

path = "C:/Users/v-zeye/Desktop/ZhangLiangjie/INDEX/"	

def GetJsonResponse(word):
	items = jsonLayer(word)
	while len(word) != 0 and items == []:
		word = word[0:-1]
		items = jsonLayer(word)
	return ListToBytes(items)

def jsonLayer(jsonWord):
	try:
		J = json.loads(jsonWord)
		ret = invertIndexFind(J['query'], J['minN'])
		return ret
	except:
		return []

def invertIndexFind(wordStr, lineNum = 10):
	words = wordStr.split(' ')
	print ("search words {}".format(words))
	allresults = []
	for word in words:
		fname = path + str(word)
		print ("find Fname = {}".format(fname))
		if(os.path.isfile(fname)):
			allresults.append([line for line in [linecache.getline(fname,i).strip() for i in range(1,lineNum+1)] if line != ""])
	
	count = lineNum
	ret = []
	for i in range(0,lineNum):
		for lis in allresults:
			if len(lis) < lineNum:
				continue
			ret.append(lis[i])
			count -= 1
			if count == 0:
				return ret
	return ret

def ListToBytes(resp):
	ret = "[ "
	if resp != []:
		n = len(resp)
		for i in range(0,n):
			ret += resp[i] + ', '
		ret += resp[n-1]
	ret += "]"
	return str.encode(ret)