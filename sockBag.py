import socket

def makeSock():
    pySock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    pySock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    pySock.bind(('localhost', 18283))
    pySock.listen(5)
    (ceeSock, address) = pySock.accept()
    return ceeSock
