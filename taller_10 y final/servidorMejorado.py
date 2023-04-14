import socket


def jugar_triki(conn):
    # Enviar mensaje de bienvenida
    conn.sendall(
        "Bienvenido al juego del Triki! Esperando a que tu oponente haga el primer movimiento...".encode())

    # Inicializar el tablero del triki
    tablero = [" ", " ", " ", " ", " ", " ", " ", " ", " "]

    # Loop principal del juego
    turno = "X"
    ganador = None
    while not ganador:
        # Mostrar el tablero
        tablero_str = f"\n {tablero[0]} | {tablero[1]} | {tablero[2]} \n---+---+---\n {tablero[3]} | {tablero[4]} | {tablero[5]} \n---+---+---\n {tablero[6]} | {tablero[7]} | {tablero[8]} "
        conn.sendall(tablero_str.encode())

        # Esperar al movimiento del jugador
        conn.sendall(
            f"Turno de {turno}. Ingresa el número de la celda: ".encode())
        celda = conn.recv(1024).decode().strip()

        # Validar la celda ingresada
        if not celda.isdigit() or int(celda) < 1 or int(celda) > 9:
            conn.sendall(
                "La celda ingresada no es válida. Por favor ingresa un número entre 1 y 9.".encode())
            continue
        celda = int(celda) - 1
        if tablero[celda] != " ":
            conn.sendall(
                "La celda ya está ocupada. Por favor ingresa otra celda.".encode())
            continue

        # Realizar el movimiento
        tablero[celda] = turno

        # Verificar si hay un ganador o empate
        if (tablero[0] == tablero[1] == tablero[2] != " " or
            tablero[3] == tablero[4] == tablero[5] != " " or
            tablero[6] == tablero[7] == tablero[8] != " " or
            tablero[0] == tablero[3] == tablero[6] != " " or
            tablero[1] == tablero[4] == tablero[7] != " " or
            tablero[2] == tablero[5] == tablero[8] != " " or
            tablero[0] == tablero[4] == tablero[8] != " " or
                tablero[2] == tablero[4] == tablero[6] != " "):
            ganador = turno
        elif " " not in tablero:
            ganador = "Empate"
        else:
            # Cambiar de turno
            turno = "O" if turno == "X" else "X"

    # Mostrar el tablero final
    tablero_str = f"\n {tablero[0]} | {tablero[1]} | {tablero[2]} \n---+---+---\n {tablero[3]} | {tablero[4]} | {tablero[5]} \n---+---+---\n {tablero[6]} | {tablero[7]} | {tablero[8]} "
    conn.sendall(tablero_str.encode())

    # Mostrar el resultado del juego
    # Mostrar el resultado del juego
    if ganador == "Empate":
        conn.sendall("El juego ha terminado en empate.".encode())
    else:
        conn.sendall(f"¡El ganador es {ganador}!".encode())
    

HOST = "127.0.0.1"
PORT = 65433

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Servidor escuchando en {HOST}:{PORT}")
    conn, addr = s.accept()
    print(f"Conexión establecida desde {addr}")

    # Variable para indicar si se está jugando una partida de triki
    jugando_triki = False

    while True:
        # Recibe mensaje del cliente
        data = conn.recv(1024)
        if not data:
            break

        # Si el mensaje es "/jugar", inicia una partida de triki
        if data == b"/jugar":
            jugando_triki = True
            jugar_triki(conn)
            jugando_triki = False

        # Si se está jugando una partida de triki, espera a que termine antes de enviar o recibir mensajes
        elif jugando_triki:
            continue

        # Si el mensaje no es "/jugar" y no se está jugando una partida de triki, envía respuesta al cliente
        else:
            mensaje = data.decode()
            print(f"Cliente: {mensaje}")
            respuesta = input("Servidor: ")
            conn.sendall(respuesta.encode())

    print(f"Conexión cerrada con {addr}")





