import socket

def send_udp_message(message):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.sendto(message.encode(), ('localhost', 1234))

# Example usage
send_udp_message("Hello from client")
send_udp_message("Another message from client")
