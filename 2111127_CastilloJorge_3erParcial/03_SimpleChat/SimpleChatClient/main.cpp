#include <QtWidgets/QApplication>
#include "simplechatclient.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimpleChatClient client;
	client.show();
	return a.exec();
}
