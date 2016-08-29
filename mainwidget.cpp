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
    messageHandle = MessageHandle::getInstance();
}

void MainWidget::setConnect()
{
    connect(connectServer, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    connect(connectServer, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(modifyState(QAbstractSocket::SocketState)));
}

void MainWidget::recvMessage()
{
    QString data = connectServer->readAll();
    qDebug() << data;
    Messages msg = messageHandle->analyzeMessages(data);
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
{
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
    case MESSAGE_TYPE_INVIATION:
        if( QMessageBox::Yes == QMessageBox::question(this, "inviation", QString("receive inviation from %1 ?")
                                 .arg(msg.msg.at(0)), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes));
        break;
    case MESSAGE_TYPE_CONNECTION:
    case MESSAGE_TYPE_REPLY:
    case MESSAGE_TYPE_CONERROR:
    default:;
    }
}

void MainWidget::on_listPlayers_doubleClicked(const QModelIndex &index)
{
    Messages msg;
    msg.messageType = MESSAGE_TYPE_INVIATION;
    msg.msg.append(connectServer->localAddress().toString());
    msg.msg.append(index.data().toString());
    msg.msg.append("3277");
    QString data = messageHandle->packageMesssages(msg);
    qDebug() << data;
    connectServer->write(data.toLatin1().data(),data.size());
}
