#pragma once

#include <boost/asio.hpp>

#include <memory>
#include <vector>
#include <functional>

namespace ba = boost::asio;

class TcpSession
{
public:
    using Ptr = std::shared_ptr<TcpSession>;
    using cbError = std::function<void(uint32_t sessionID, const boost::system::error_code &code)>;
    using cbRead = std::function<void(uint32_t sessionID, const char* pData, const size_t dataSize)>;

    explicit TcpSession(std::shared_ptr<ba::ip::tcp::socket> socket);
    ~TcpSession();

    inline uint32_t sessionId() const { return m_sessionId; }
    bool waitReading();
    void setReadCallback(const cbRead &callRead) { onSessionRead_ = callRead; };
    void setErrorCallback(const cbError &callErr) { onSessionError_ = callErr; }

private:
    std::shared_ptr<ba::ip::tcp::socket> m_tcpSocket;
    std::vector<char> m_buffer;
    uint32_t m_sessionId;
    cbRead onSessionRead_;
    cbError onSessionError_;

    void handlerRead(const boost::system::error_code &err_code, size_t bytes_recieved);
};
