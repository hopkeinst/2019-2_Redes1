#include "simplechatserver.h"
#include <QBuffer>
#include <QTcpSocket>

SimpleChatServer::SimpleChatServer(QObject* parent) : QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(addConnection()));
}

SimpleChatServer::~SimpleChatServer()
{
}

void SimpleChatServer::addConnection()
{
	QTcpSocket* connection = nextPendingConnection();
	connections.append(connection);
	QBuffer* buffer = new QBuffer(this);
	buffer->open(QIODevice::ReadWrite);
	buffers.insert(connection, buffer);
	connect(connection, SIGNAL(disconnected()), SLOT(removeConnection()));
	connect(connection, SIGNAL(readyRead()),	SLOT(receiveMessage()));
}

void SimpleChatServer::removeConnection()
{
	QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
	QBuffer* buffer = buffers.take(socket);
	buffer->close();
	buffer->deleteLater();
	connections.removeAll(socket);
	socket->deleteLater();
}

void SimpleChatServer::receiveMessage()
{
	QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
	QBuffer* buffer = buffers.value(socket);
	
	
	qint64 bytes = buffer->write(socket->readAll());
	
	buffer->seek(buffer->pos() - bytes);
	
	while (buffer->canReadLine())
	{
		QByteArray line = buffer->readLine();
		foreach (QTcpSocket* connection, connections)
		{
			connection->write(line);
		}
	}
}
