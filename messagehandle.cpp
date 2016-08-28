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
