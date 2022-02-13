#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
    : QObject{parent}
{
    connect(&_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    // when server sends client some data
    connect(&_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}


void TcpClient::connectToHost(const QString &ip, const QString &port)
{
    _socket.connectToHost(ip, port.toUInt());
}

void TcpClient::sendMessage(const QString &message)
{
    _socket.write(message.toUtf8());
    _socket.flush();
}

void TcpClient::onConnected()
{
    qInfo() << "Connected to host";
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}

void TcpClient::onReadyRead()
{
    const auto message = _socket.readAll();
    emit newMessage(message);
}
