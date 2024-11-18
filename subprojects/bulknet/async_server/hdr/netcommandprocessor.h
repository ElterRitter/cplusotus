#pragma once
#include "tcpsession.h"

#include "libasync.h"

#include <unordered_map>

class NetCommandProcessor
{
public:
    explicit NetCommandProcessor(uint32_t blockSize, const std::string &rootLogDirectory);
    ~NetCommandProcessor();

    void onAcceptedNewConnection(TcpSession::Ptr session);
    void onDataReaded();

private:
    std::unordered_map<int, TcpSession::Ptr> m_sessions;
    std::string m_rootLogDirectory;
    processorid m_processor;

    void onIncomingDataReaded(uint32_t sessionId, const char *pData, const std::size_t dataSize);
    void onSessionError(uint32_t sessionId, const boost::system::error_code &err_code);
};

