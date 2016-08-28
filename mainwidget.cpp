#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    init();
    setConnect();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::init()
{
    connectServer = ConnectServer::getInstance();
}

void MainWidget::setConnect()
{
    connect(connectServer, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    connect(connectServer, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(modifyState(QAbstractSocket::SocketState)));
}

void MainWidget::recvMessage()
{
    QString temp = connectServer->readAll();
    QStringList message = temp.split("\n");
    for(int i=0; i<message.size(); ++i){
        ui->listPlayers->addItem(message.at(i));
    }
}

void MainWidget::modifyState(QAbstractSocket::SocketState state)
{
    switch(state){
    case QAbstractSocket::UnconnectedState: ui->labelConnectStatus->setText(" unconnected");break;
    case QAbstractSocket::ConnectingState:  ui->labelConnectStatus->setText("connecting...");break;
    case QAbstractSocket::ConnectedState:   ui->labelConnectStatus->setText("  connected");break;
    case QAbstractSocket::ClosingState:     ui->labelConnectStatus->setText("breaking...");break;
    default:;
    }

}
