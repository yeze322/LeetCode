import socketserver
import os
import linecache
import sys

class MyTCPHandler(socketserver.BaseRequestHandler):
	path = "C:/Users/v-zeye/Desktop/ZhangLiangjie/INDEX/"
	def handle(self):
		self.data = self.request.recv(1024).strip()
		print("[{}] received : {}".format(self.client_address[0], self.data))
		word = self.data.decode("utf-8")
		resp = self.invertIndexFind(word)
		self.request.sendall(self.ListToBytes(resp))

	def invertIndexFind(self, word, lineNum = 10):
		fname = self.path + str(word)
		if(os.path.isfile(fname)):
			ret = [line for line in [linecache.getline(fname,i).strip() for i in range(1,lineNum+1)] if line != ""]
			return ret

	def ListToBytes(self, resp):
		return str.encode(str(resp))


if __name__ == "__main__":
    HOST, PORT = "localhost", 9595

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()