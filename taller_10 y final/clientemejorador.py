import socket

HOST = "127.0.0.1"
PORT = 65433


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        # Enviar mensaje al servidor
        mensaje = input("Cliente: ")
        s.sendall(mensaje.encode())
        # Recibir respuesta del servidor
        data = s.recv(1024)
        print(f"Servidor: {data.decode()}")
