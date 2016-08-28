#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QAbstractSocket>
#include <QMessageBox>
#include "connectserver.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void init();
    void setConnect();

private:
    Ui::MainWidget *ui;
    ConnectServer *connectServer;

public slots:
    void recvMessage();
    void modifyState(QAbstractSocket::SocketState state);
};

#endif // MAINWIDGET_H
