#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include <QStringList>
#include <QString>
#include "message.h"

class MessageHandle
{
private:
    static MessageHandle *messageHandle;
    MessageHandle();
public:
    static MessageHandle * getInstance();
    Messages analyzeMessages(QString data);
    QString packageMesssages(Messages msg);
};

#endif // MESSAGEHANDLE_H
