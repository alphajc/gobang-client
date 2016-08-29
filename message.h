#ifndef MESSAGE_H
#define MESSAGE_H

//#include <QList>
//#include <QMap>
#include <QStringList>

enum MessageType {
  MESSAGE_TYPE_LIST,       //发送玩家列表
  MESSAGE_TYPE_ADD,        //添加玩家
  MESSAGE_TYPE_REMOVE,     //移除玩家
  MESSAGE_TYPE_INVIATION,  // 邀请（端口）
  MESSAGE_TYPE_REPLY,      //受邀方回复
  MESSAGE_TYPE_CONNECTION, //连接信息（发起方IP和端口）
  MESSAGE_TYPE_CONERROR    //受邀方连接错误
};

enum State { STATE_ONLINE, STATE_GAMING }; //状态分为两种，在线上/游戏中

struct Messages{
    enum MessageType messageType;
 //   QList<QMap<QString, QString >> msg;
    QStringList msg;
};

#endif // MESSAGE_H
