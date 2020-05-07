from ctypes import *
import socket
from multiprocessing import Process
def handle_client(client_socket):
    request_data = client_socket.recv(1024)
    print("request data:", request_data)
    response = "HTTP/1.1 200 OK\r\n"
    client_socket.send(bytes(response, "utf-8"))
    client_socket.close()
if __name__ == "__main__":
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("", 8000))
    server_socket.listen(128)
    while True:
        client_socket, client_address = server_socket.accept()
        print("lock")
        user32 = windll.LoadLibrary('user32.dll')
        user32.LockWorkStation()
        handle_client_process = Process(target=handle_client, args=(client_socket,))
        handle_client_process.start()
        client_socket.close()
