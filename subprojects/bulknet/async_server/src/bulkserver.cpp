#include "bulkserver.h"

#include <boost/bind/bind.hpp>
#include <iostream>

using std::cerr;
using std::endl;
using boost::asio::ip::address;

BulkServer::BulkServer(callbackConnected cbConnected) :
    m_threadPool(2)
    , m_callbackConnected(cbConnected)
{
    m_ioService = std::make_unique<IoService>();
    m_ioServiceWork = std::make_unique<IoServiceWork>(*m_ioService.get());

    auto binder = boost::bind(&boost::asio::io_service::run, m_ioService.get());
    boost::asio::post(m_threadPool, binder);
}

BulkServer::~BulkServer()
{
    if(m_acceptor)
    {
        boost::system::error_code ec;
        m_acceptor->cancel(ec);
        m_acceptor.reset();
    }

    if(m_ioServiceWork)
        m_ioServiceWork.reset();

    m_threadPool.join();
    m_ioService->reset();
}

bool BulkServer::listen(const std::string listenInterface, uint16_t port)
{
    bool ret = false;
    boost::system::error_code ec;
    auto iface = boost::asio::ip::make_address(listenInterface, ec);
    if(ec)
    {
        cerr << "Listen error: code " << ec.value();
        return ret;
    }

    tcp::endpoint ep{iface, port};
    m_acceptor = std::shared_ptr<tcp::acceptor>( new tcp::acceptor(*(m_ioService.get()), ep, false));
    ret = waitForNewConnection();

    return ret;
}

void BulkServer::handlerAccept(const error_code &erCode, SocketPtr socket)
{
    if(erCode)
    {
        if(erCode == boost::asio::error::operation_aborted)
            return;

        cerr << "[BulkServer::handlerAccept] error occuqared. Code " << erCode.value() << "; message " << erCode.message();
        return;
    }

    TcpSession::Ptr session = std::make_shared<TcpSession>(socket);
    m_callbackConnected(session);
    waitForNewConnection();
}

bool BulkServer::waitForNewConnection()
{
    bool ret = true;
    try
    {
        auto pSocket = std::make_shared<tcp::socket>(*(m_ioService.get()));
        auto accepterHandler = std::bind(&BulkServer::handlerAccept, this, std::placeholders::_1, pSocket);
        m_acceptor->async_accept(*(pSocket.get()), accepterHandler);
    }
    catch(boost::system::system_error &se)
    {
//        cerr << "Can't create tcp acceptor for interface " << listenInterface << ":" << port << ". Code " << se.what() <<  endl;
        ret = false;
    }

    return ret;
}
