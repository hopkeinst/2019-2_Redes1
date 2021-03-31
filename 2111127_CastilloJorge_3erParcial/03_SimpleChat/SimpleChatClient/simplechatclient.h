#ifndef SIMPLECHATCLIENT_H
#define SIMPLECHATCLIENT_H

#include <QtWidgets/QWidget>

class QBuffer;
class QSpinBox;
class QLineEdit;
class QTextEdit;
class QTcpSocket;
class QPushButton;

class SimpleChatClient : public QWidget
{
	Q_OBJECT

public:
	SimpleChatClient(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	~SimpleChatClient();

private slots:
	void setConnected();
	void setDisconnected();
	void toggleConnection();
	void sendMessage();
	void receiveMessage();
	void sendFeliz();
	void sendTriste();
	void sendBravo();
	void sendSorpresa();
	void sendLlorando();
	void sendClock();
	void sendConfundido();
	void sendDiablo();
	void sendCorazon();
	void sendBalon();
	void sendEstrella();
	void sendEnfermo();

private:
	
	QBuffer*		buffer;
	QSpinBox*		port;
	QLineEdit*		nick;
	QLineEdit*		server;
	QLineEdit*		message;
	QTextEdit*		chat;
	QTcpSocket*		socket;
	QPushButton*	conn;
	QPushButton*	send;
	QPushButton*	feliz;
	QPushButton*	triste;
	QPushButton*	bravo;
	QPushButton*	sorpresa;
	QPushButton*	llorando;
	QPushButton*	clock;
	QPushButton*	confundido;
	QPushButton*	diablo;
	QPushButton*	corazon;
	QPushButton*	balon;
	QPushButton*	estrella;
	QPushButton*	enfermo;
};

#endif // SIMPLECHATCLIENT_H
