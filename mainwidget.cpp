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
    connectPlayer = ConnectPlayer::getInstance();
}

void MainWidget::setConnect()
{
    connect(connectServer, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    connect(connectServer, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(modifyState(QAbstractSocket::SocketState)));
    connect(connectPlayer, SIGNAL(connected()), this, SLOT(finishedConnection()));
}

void MainWidget::recvMessage()
{
    Messages msg = connectServer->recvFromServer();
    operateMessages(msg);
}

void MainWidget::modifyState(QAbstractSocket::SocketState state)
{
    switch(state){
    case QAbstractSocket::UnconnectedState:
        ui->labelConnectStatus->setText(" unconnected");
        break;
    case QAbstractSocket::ConnectingState:
        ui->labelConnectStatus->setText("connecting...");
        break;
    case QAbstractSocket::ConnectedState:
        ui->labelConnectStatus->setText("  connected");
        break;
    case QAbstractSocket::ClosingState:
        ui->labelConnectStatus->setText("breaking...");
        ui->listPlayers->clear();
        break;
    default:;
    }

}

void MainWidget::operateMessages(Messages msg)
{   qDebug() << "mainwidget.cpp:59:" << msg.messageType << msg.msg;
    switch (msg.messageType) {
    case MESSAGE_TYPE_LIST:
        ui->listPlayers->addItems(msg.msg);
        break;
    case MESSAGE_TYPE_ADD:
        ui->listPlayers->addItem(msg.msg.at(0));
        break;
    case MESSAGE_TYPE_REMOVE:{
        QListWidgetItem *it = ui->listPlayers->findItems(msg.msg.at(0), Qt::MatchStartsWith).at(0);
        ui->listPlayers->removeItemWidget(it);
        delete it;
        break;
    }
    case MESSAGE_TYPE_INVITATION:
        if( QMessageBox::Yes == QMessageBox::question(this, "invitation", QString("receive invitation from %1 ?")
                                 .arg(msg.msg.at(0)), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)){

            game = new Game(this);
            game->start();
            GameSocket *gameSocket = GameSocket::getInstance();
            gameSocket->connectToHost(msg.msg);
            msg.msg[1] = "ACCEPT";
        }else{
            msg.msg[1] = "REFUSED";
        }
        connectServer->sendToServer(MESSAGE_TYPE_REPLY, msg.msg);
        break;
    case MESSAGE_TYPE_CONNECTION:
    case MESSAGE_TYPE_REPLY:
        if(msg.msg.at(0) == "REFUSED"){
            QMessageBox::warning(this, "refused", "The other side refused!",
                                 QMessageBox::Apply, QMessageBox::Apply);
            connectPlayer->close();
        }
        break;
    case MESSAGE_TYPE_CONERROR:
    default:;
    }
}

void MainWidget::on_listPlayers_doubleClicked(const QModelIndex &index)
{
    game = new Game(this);
    game->start();
    connectServer->sendToServer(MESSAGE_TYPE_INVITATION, index.data());
}

void MainWidget::finishedConnection()
{
    qDebug() << game->getSocket()->peerAddress();
    ui->labelGameStatus->setText(QString("playing against %1").arg(game->getSocket()->peerAddress().toString().split(":").back()));
}
