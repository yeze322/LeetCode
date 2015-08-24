import socket
import sys

HOST, PORT = "localhost", 9595
data = " ".join(sys.argv[1:])

while True:
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	sock.connect((HOST, PORT))
	word = input("Input KeyWord:")
	if word == "--exit":
		break
	print("Sent:     {}".format(word))
	sock.sendall(bytes(word + "\n", "utf-8"))
	received = str(sock.recv(1024), "utf-8")
	print("Received: {}".format(received))
	sock.close()
