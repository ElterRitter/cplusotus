#include "netcommandprocessor.h"

#include <iostream>
using std::cerr;
using std::endl;

NetCommandProcessor::NetCommandProcessor(uint32_t blockSize) :
    m_blockSize{blockSize}
{

}

void NetCommandProcessor::onAcceptedNewConnection(TcpSession::Ptr session)
{
    cerr << "Accepting new processor connection" << endl;
    SessionConnection scon;
    scon.processor = bulk_connect(m_blockSize);
    scon.session = session;
    m_transports[session->sessionId()] = scon;

    auto readHandler = std::bind(&NetCommandProcessor::onIncomingDataReaded, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    session->setReadCallback(readHandler);

    auto errorHandler = std::bind(&NetCommandProcessor::onSessionError, this, std::placeholders::_1, std::placeholders::_2);
    session->setErrorCallback(errorHandler);

    session->waitReading();
}

void NetCommandProcessor::onIncomingDataReaded(uint32_t sessionId, const char *pData, const size_t dataSize)
{
    auto it = m_transports.find(sessionId);
    if(it == m_transports.end())
    {
        cerr << "[NetCommandProcessor::onIncomingDataReaded] data incoming from unexpected session: " << sessionId << endl;
        return;
    }

    bulk_recieve(it->second.processor, pData, dataSize);
}

void NetCommandProcessor::onSessionError(uint32_t sessionId, const boost::system::error_code &err_code)
{
    if(!err_code)
        return;

    cerr << "Processing error of session " << sessionId << " code is " << err_code.value() << endl;
    auto it = m_transports.find(sessionId);
    if(it == m_transports.end())
        return;

    bulk_disconnect(it->second.processor);
    m_transports.erase(it);
}
