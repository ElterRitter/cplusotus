#pragma once
#include "tcpsession.h"

#include <boost/asio/thread_pool.hpp>
#include <boost/asio.hpp>

#include <memory>
#include <string>
#include <cstdint>
#include <functional>

using boost::system::error_code;
using boost::asio::ip::tcp;
using std::function;

class BulkServer
{
public:
    using callbackConnected = std::function<void(TcpSession::Ptr)>;
    using callbackError = std::function<void(const boost::system::error_code&)>;
    using SocketPtr = std::shared_ptr<tcp::socket>;

    explicit BulkServer(callbackConnected cbConnected);
    ~BulkServer();

    bool listen(const std::string listenInterface, uint16_t port);

private:
    using AcceptorPtr = std::shared_ptr<tcp::acceptor>;
    using ThreadPool = boost::asio::thread_pool;
    using IoService = boost::asio::io_service;
    using IoServicePtr = std::unique_ptr<IoService>;
    using IoServiceWork = boost::asio::io_service::work;
    using IoServiceWorkPtr = std::unique_ptr<IoServiceWork>;

    AcceptorPtr m_acceptor;
    ThreadPool m_threadPool;
    IoServicePtr m_ioService;
    IoServiceWorkPtr m_ioServiceWork;

    callbackConnected m_callbackConnected;

    void handlerAccept(const error_code& erCode, SocketPtr socket);
};
