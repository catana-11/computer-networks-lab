import socket

# Create TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind server to IP and port
server.bind(("127.0.0.1", 12345))

# Listen for client connection
server.listen(1)

print("Server is waiting for connection...")

# Accept client connection
conn, addr = server.accept()

print("Connected to client:", addr)

# Keep chatting until either side types exit
while True:

    # Receive message from client
    message = conn.recv(1024).decode()

    if not message or message.lower() == "exit":
        print("Client ended the chat.")
        break

    print("Client:", message)

    # Send reply to client
    reply = input("Server: ")
    conn.sendall(reply.encode())

    if reply.lower() == "exit":
        break

# Close connection
conn.close()
server.close()

print("Chat ended.")