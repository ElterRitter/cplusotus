#pragma once
#include "tcpsession.h"

#include "libasync.h"

#include <unordered_map>

class NetCommandProcessor
{
public:
    explicit NetCommandProcessor(uint32_t blockSize);

    void onAcceptedNewConnection(TcpSession::Ptr session);
    void onDataReaded();

private:
    struct SessionConnection
    {
        TcpSession::Ptr session;
        processorid processor;
    };
    using transportmap = std::unordered_map<int, SessionConnection>;

    uint32_t m_blockSize;
    transportmap m_transports;

    void onIncomingDataReaded(uint32_t sessionId, const char *pData, const std::size_t dataSize);
    void onSessionError(uint32_t sessionId, const boost::system::error_code &err_code);
};

