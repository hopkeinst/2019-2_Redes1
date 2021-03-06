#include "simplechatclient.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QBuffer>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QErrorMessage>
#include <QtGui/QImage>
#include <QtCore/QUrl>

static const quint16 DEFAULT_PORT = 6667;

SimpleChatClient::SimpleChatClient(QWidget* parent, Qt::WindowFlags flags) 
: QWidget(parent, flags)
{
	QVBoxLayout* main	= new QVBoxLayout(this);
	QGridLayout* top	= new QGridLayout;
	QHBoxLayout* bottom	= new QHBoxLayout;
	QHBoxLayout* bottom2	= new QHBoxLayout;

	QLabel* label	= new QLabel("Servidor:", this);
	server			= new QLineEdit(this);
	port			= new QSpinBox(this);
	conn			= new QPushButton("Conectar", this);
	port->setRange(1, 32767);
	port->setValue(DEFAULT_PORT);
	server->setText("localhost");
	top->addWidget(label, 0, 0);
	top->addWidget(server, 0, 1);
	top->addWidget(port, 0, 2);

	label	= new QLabel("Nick:", this);
	nick	= new QLineEdit(this);
	nick->setText("Anonimo");
	top->addWidget(label, 1, 0);
	top->addWidget(nick, 1, 1);
	top->addWidget(conn, 1, 2);

	chat	= new QTextEdit(this);             
	chat->setReadOnly(true);
	
	label	= new QLabel("Mensaje:", this);
	message	= new QLineEdit(this);
	send	= new QPushButton("Enviar", this);
	send->setDefault(true);
	bottom->addWidget(label);
	bottom->addWidget(message);
	bottom->addWidget(send);

	QPushButton* feliz			= new QPushButton(this);
	QPushButton* triste			= new QPushButton(this);
	QPushButton* bravo			= new QPushButton(this);
	QPushButton* sorpresa			= new QPushButton(this);
	QPushButton* llorando			= new QPushButton(this);
	QPushButton* clock			= new QPushButton(this);
	QPushButton* confundido			= new QPushButton(this);
	QPushButton* diablo			= new QPushButton(this);
	QPushButton* corazon			= new QPushButton(this);
	QPushButton* balon			= new QPushButton(this);
	QPushButton* estrella			= new QPushButton(this);
	QPushButton* enfermo			= new QPushButton(this);
	feliz->setStyleSheet("background-image: url(/home/Iconos/feliz.png);");
	triste->setStyleSheet("background-image: url(/home/Iconos/triste.png);");
	bravo->setStyleSheet("background-image: url(/home/Iconos/bravo.png);");
	sorpresa->setStyleSheet("background-image: url(/home/Iconos/sorpresa.png);");
	llorando->setStyleSheet("background-image: url(/home/Iconos/llorando.png);");
	clock->setStyleSheet("background-image: url(/home/Iconos/Clock.png);");
	confundido->setStyleSheet("background-image: url(/home/Iconos/confundido.png);");	
	diablo->setStyleSheet("background-image: url(/home/Iconos/diablo.png);");	
	corazon->setStyleSheet("background-image: url(/home/Iconos/corazon.png);");
	balon->setStyleSheet("background-image: url(/home/Iconos/balon.png);");	
	estrella->setStyleSheet("background-image: url(/home/Iconos/estrella.png);");	
	enfermo->setStyleSheet("background-image: url(/home/Iconos/enfermo.png);");	
	bottom2->addWidget(feliz);
	bottom2->addWidget(triste);
	bottom2->addWidget(bravo);
	bottom2->addWidget(sorpresa);
	bottom2->addWidget(llorando);
	bottom2->addWidget(clock);
	bottom2->addWidget(confundido);
	bottom2->addWidget(diablo);
	bottom2->addWidget(corazon);
	bottom2->addWidget(balon);
	bottom2->addWidget(estrella);
	bottom2->addWidget(enfermo);

	main->addLayout(top);
	main->addWidget(chat);
	main->addLayout(bottom);
	main->addLayout(bottom2);
	setLayout(main);

	buffer = new QBuffer(this);
	socket = new QTcpSocket(this);
	buffer->open(QIODevice::ReadWrite);

	connect(message, SIGNAL(returnPressed()), SLOT(sendMessage()));
	connect(send, SIGNAL(clicked()), SLOT(sendMessage()));
	connect(conn, SIGNAL(clicked()), SLOT(toggleConnection()));
	
	connect(socket, SIGNAL(connected()), SLOT(setConnected()));
	connect(socket, SIGNAL(disconnected()), SLOT(setDisconnected()));
	connect(socket, SIGNAL(readyRead()), SLOT(receiveMessage()));

	connect(feliz, SIGNAL(clicked()), SLOT(sendFeliz()));
	connect(triste, SIGNAL(clicked()), SLOT(sendTriste()));
	connect(bravo, SIGNAL(clicked()), SLOT(sendBravo()));
	connect(sorpresa, SIGNAL(clicked()), SLOT(sendSorpresa()));
	connect(llorando, SIGNAL(clicked()), SLOT(sendLlorando()));
	connect(clock, SIGNAL(clicked()), SLOT(sendClock()));
	connect(confundido, SIGNAL(clicked()), SLOT(sendConfundido()));
	connect(diablo, SIGNAL(clicked()), SLOT(sendDiablo()));
	connect(corazon, SIGNAL(clicked()), SLOT(sendCorazon()));
	connect(balon, SIGNAL(clicked()), SLOT(sendBalon()));
	connect(estrella, SIGNAL(clicked()), SLOT(sendEstrella()));
	connect(enfermo, SIGNAL(clicked()), SLOT(sendEnfermo()));

	setDisconnected();
}

SimpleChatClient::~SimpleChatClient()
{
	buffer->close();
}

void SimpleChatClient::setConnected()
{
	port->setEnabled(false);
	server->setEnabled(false);
	nick->setEnabled(true);
	message->setEnabled(true);
	chat->setEnabled(true);
	chat->clear();
	send->setEnabled(true);
	conn->setText("Desconectar");
}

void SimpleChatClient::setDisconnected()
{
	port->setEnabled(true);
	server->setEnabled(true);
	nick->setEnabled(false);
	message->setEnabled(false);
	chat->setEnabled(false);
	send->setEnabled(false);
	conn->setText("Conectar");
}

void SimpleChatClient::toggleConnection()
{
	if (socket->state() == QAbstractSocket::UnconnectedState)
	{
		socket->connectToHost(server->text(), port->value());
	}
	else
	{
		socket->disconnectFromHost();
	}
}

void SimpleChatClient::sendMessage()
{
	socket->write("<html>" + nick->text().toLatin1() + " dice: " + message->text().toLatin1() + "\n" + "</html>");	
	message->clear();
}

void SimpleChatClient::receiveMessage()
{
	
	qint64 bytes = buffer->write(socket->readAll());
	
	buffer->seek(buffer->pos() - bytes);
	
	while (buffer->canReadLine())
	{
		QString line = buffer->readLine();
		chat->append(line.simplified());
	}
}

void SimpleChatClient::sendFeliz()
{
	
	QString html;	
	QImage img(":/home/Iconos/feliz.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/feliz.png"), img);
	html.append("<img src=/home/Iconos/feliz.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendTriste()
{
	
	QString html;	
	QImage img(":/home/Iconos/triste.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/triste.png"), img);
	html.append("<img src=/home/Iconos/triste.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendBravo()
{
	
	QString html;	
	QImage img(":/home/Iconos/bravo.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/bravo.png"), img);
	html.append("<img src=/home/Iconos/bravo.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendSorpresa()
{
	
	QString html;	
	QImage img(":/home/Iconos/sorpresa.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/sorpresa.png"), img);
	html.append("<img src=/home/Iconos/sorpresa.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendLlorando()
{
	
	QString html;	
	QImage img(":/home/Iconos/llorando.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/llorando.png"), img);
	html.append("<img src=/home/Iconos/llorando.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendClock()
{
	
	QString html;	
	QImage img(":/home/Iconos/Clock.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/Clock.png"), img);
	html.append("<img src=/home/Iconos/Clock.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendConfundido()
{
	
	QString html;	
	QImage img(":/home/Iconos/confundido.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/confundido.png"), img);
	html.append("<img src=/home/Iconos/confundido.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendDiablo()
{
	
	QString html;	
	QImage img(":/home/Iconos/diablo.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/diablo.png"), img);
	html.append("<img src=/home/Iconos/diablo.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendCorazon()
{
	
	QString html;	
	QImage img(":/home/Iconos/corazon.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/corazon.png"), img);
	html.append("<img src=/home/Iconos/corazon.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendBalon()
{
	
	QString html;	
	QImage img(":/home/Iconos/balon.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/balon.png"), img);
	html.append("<img src=/home/Iconos/balon.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendEstrella()
{
	
	QString html;	
	QImage img(":/home/Iconos/estrella.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/estrella.png"), img);
	html.append("<img src=/home/Iconos/estrella.png>");
	message->insert(html);
	
}

void SimpleChatClient::sendEnfermo()
{
	
	QString html;	
	QImage img(":/home/Iconos/enfermo.png");
	chat->document()->addResource(QTextDocument::ImageResource, QUrl(":/home/Iconos/enfermo.png"), img);
	html.append("<img src=/home/Iconos/enfermo.png>");
	message->insert(html);
	
}
