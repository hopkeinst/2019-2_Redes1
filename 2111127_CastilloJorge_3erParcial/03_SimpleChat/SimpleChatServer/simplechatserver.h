#ifndef SIMPLECHATSERVER_H
#define SIMPLECHATSERVER_H

#include <QTcpServer>
#include <QList>
#include <QHash>

class QBuffer;
class QTcpSocket;

class SimpleChatServer : public QTcpServer
{
	Q_OBJECT

public:
	SimpleChatServer(QObject* parent = 0);
	~SimpleChatServer();

private slots:
	void addConnection();
	void removeConnection();
	void receiveMessage();

private:
	QList<QTcpSocket*> connections;
	QHash<QTcpSocket*, QBuffer*> buffers;
};

#endif // SIMPLECHATSERVER_H
