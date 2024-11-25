#include "netcommandprocessor.h"

#include <iostream>
using std::cerr;
using std::endl;

NetCommandProcessor::NetCommandProcessor(uint32_t blockSize, const std::string &rootLogDirectory) :
    m_rootLogDirectory{rootLogDirectory}
{
    m_processor = bulk_connect(blockSize, rootLogDirectory.c_str(), m_rootLogDirectory.size());
}

NetCommandProcessor::~NetCommandProcessor()
{
    if(m_processor != 0)
        bulk_disconnect(m_processor);
}

void NetCommandProcessor::onAcceptedNewConnection(TcpSession::Ptr session)
{
    if(!session)
        return;

    cerr << "Accepting new processor connection" << endl;
    m_sessions[session->sessionId()] = session;

    auto readHandler = std::bind(&NetCommandProcessor::onIncomingDataReaded, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    session->setReadCallback(readHandler);

    auto errorHandler = std::bind(&NetCommandProcessor::onSessionError, this, std::placeholders::_1, std::placeholders::_2);
    session->setErrorCallback(errorHandler);

    session->waitReading();
}

void NetCommandProcessor::onIncomingDataReaded(uint32_t sessionId, const char *pData, const size_t dataSize)
{
    auto it = m_sessions.find(sessionId);
    if(it == m_sessions.end())
    {
        cerr << "[NetCommandProcessor::onIncomingDataReaded] data incoming from unexpected session: " << sessionId << endl;
        return;
    }

    bulk_recieve(m_processor, pData, dataSize);
}

void NetCommandProcessor::onSessionError(uint32_t sessionId, const boost::system::error_code &err_code)
{
    if(!err_code)
        return;

    cerr << "Processing error of session " << sessionId << " code is " << err_code.value() << endl;
    auto it = m_sessions.find(sessionId);
    if(it == m_sessions.end())
        return;

    m_sessions.erase(it);
}
