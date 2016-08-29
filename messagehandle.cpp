#include "messagehandle.h"

MessageHandle * MessageHandle::messageHandle = NULL;

MessageHandle::MessageHandle()
{

}

MessageHandle *MessageHandle::getInstance()
{
    if( NULL == messageHandle){
        messageHandle = new MessageHandle();
    }

    return messageHandle;
}

Messages MessageHandle::analyzeMessages(QString data)
{
    Messages msg;
    QStringList temp = data.split("\n");
    msg.messageType = MessageType(temp[0].toInt());

    switch(msg.messageType){
    case MESSAGE_TYPE_ADD:
    case MESSAGE_TYPE_LIST:
        for(int i=1; i<temp.size(); ++i){
            QStringList sl = temp[i].split("\t");
            if((enum State)(sl.at(1).toInt()) == STATE_ONLINE )
                msg.msg.append(sl.at(0) + "\tonline");
            else
                msg.msg.append(sl.at(0) + "\tgaming");
        }
        break;
    case MESSAGE_TYPE_REMOVE:
    case MESSAGE_TYPE_INVIATION:
        for(int i=1; i<temp.size(); ++i){
            msg.msg.append(temp[i]);
        }
        break;
    default:;
    }

    return msg;
}

QString MessageHandle::packageMesssages(Messages msg)
{
    QString data;
    data = QString("%1").arg(msg.messageType);
    for(int i=0; i<msg.msg.size(); ++i){
        data.append("\n");
        data.append(msg.msg.at(i).split("\t").at(0));
    }

    return data;
}
