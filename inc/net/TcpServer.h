#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "Noncopyable.h"
#include "EpollPoller.h"
#include "Socket.h"

namespace wd
{
class TcpServer : Noncopyable
{
public:
    typedef EpollPoller::EpollCallback TcpServerCallback;

    explicit TcpServer(const InetAddress &addr);

    void start()
    { poller_.loop(); }

    void setConnectionCallback(TcpServerCallback cb)
    { poller_.setConnectCallback(std::move(cb)); }
    void setMessageCallback(TcpServerCallback cb)
    { poller_.setMessageCallback(std::move(cb)); }
    void setCloseCallback(TcpServerCallback cb)
    { poller_.setCloseCallback(std::move(cb)); }

private:
    Socket sockfd_;
    EpollPoller poller_;
};

}


#endif //TCP_SERVER_H
