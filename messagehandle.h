#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H


class MessageHandle
{
private:
    enum MessageType {
      MESSAGE_TYPE_LIST,       //发送玩家列表
      MESSAGE_TYPE_ADD,        //添加玩家
      MESSAGE_TYPE_REMOVE,     //移除玩家
      MESSAGE_TYPE_INVIATION,  // 邀请（端口）
      MESSAGE_TYPE_REPLY,      //受邀方回复
      MESSAGE_TYPE_CONNECTION, //连接信息（发起方IP和端口）
      MESSAGE_TYPE_CONERROR    //受邀方连接错误
    };
    static MessageHandle *messageHandle;
    MessageHandle();
public:
    static MessageHandle * getInstance();
};

#endif // MESSAGEHANDLE_H
