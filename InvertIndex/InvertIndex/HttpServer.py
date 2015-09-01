import socketserver
import os
import IRlib
from time import gmtime, strftime

class MyTCPHandler(socketserver.BaseRequestHandler):
	def handle(self):
		self.data = self.request.recv(2048)
		print (strftime("%a, %d %b %Y %H:%M:%S +0000", gmtime()))
		print("[{}] received : {}".format(self.client_address[0], self.data))
		word = self.data.decode("utf-8")
		start = word.find('{"query"')
		word = word[start:]
		print("Match Json = {}".format(word))
		sendStr = IRlib.GetJsonResponse(word)
		self.request.sendall(sendStr)
		print ("[Send] : {}\n".format(sendStr))



if __name__ == "__main__":
    HOST, PORT = "0.0.0.0", 9595

    # Create the server, binding to localhost on port 9999
    server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()