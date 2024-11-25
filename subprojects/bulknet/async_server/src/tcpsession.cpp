#include "tcpsession.h"

#include <iostream>

using std::cerr;
using std::endl;

uint32_t GlobalSessionID = 0;

TcpSession::TcpSession(std::shared_ptr<ba::ip::tcp::socket> socket) :
    m_tcpSocket{socket}
    , m_sessionId{GlobalSessionID++}
    , onSessionRead_{nullptr}
    , onSessionError_{nullptr}
{

}

TcpSession::~TcpSession()
{
    if(!m_tcpSocket)
        return;

    if(!m_tcpSocket->is_open())
        return;

    try
    {
        m_tcpSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        m_tcpSocket->close();
    }
    catch(boost::system::system_error &error)
    {
        cerr << "socket close error" << endl;
    }
}

bool TcpSession::waitReading()
{
    bool ret = false;
    if(onSessionRead_)
    {
        auto readerHandler = std::bind(&TcpSession::handlerRead, this, std::placeholders::_1, std::placeholders::_2);
        boost::asio::async_read(*m_tcpSocket, boost::asio::dynamic_buffer(m_buffer), boost::asio::transfer_exactly(1), readerHandler);
        ret = true;
    }

    return ret;
}

void TcpSession::handlerRead(const boost::system::error_code &err_code, size_t bytes_recieved)
{
    if(err_code)
    {
        if(err_code == boost::asio::error::operation_aborted)
            return;

        if(onSessionError_)
            onSessionError_(m_sessionId, err_code);

#if defined(_MSC_VER)
        if(err_code.value() == ERROR_CONNECTION_ABORTED)
            cerr << "windows session aborted";
#endif
        return;
    }

    if(!m_tcpSocket)
        return;

    auto avaliableBytes = m_tcpSocket->available();
    if(avaliableBytes == 0)
    {
        avaliableBytes = 1;
        cerr << "from session " << m_sessionId << " readed " << m_buffer.size() << " bytes" << endl;
        if(onSessionRead_)
            onSessionRead_(m_sessionId, m_buffer.data(), m_buffer.size());

        m_buffer.clear();
    }

    auto readHandler = std::bind(&TcpSession::handlerRead, this, std::placeholders::_1, std::placeholders::_2);
    boost::asio::async_read(*m_tcpSocket, boost::asio::dynamic_buffer(m_buffer), boost::asio::transfer_exactly(avaliableBytes), readHandler);
}
