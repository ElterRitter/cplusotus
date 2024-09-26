#include "documentstorage.h"
#include "qsettingsstorage.h"

#include <QDebug>

Q_LOGGING_CATEGORY(documentstorage, "DocumentStorage")
#define Debug qDebug(documentstorage)
#define Info qInfo(documentstorage)
#define Warn qWarning(documentstorage)


DocumentStorage::DocumentStorage()
{
    m_currentDocumentIndex = -1;
}

GOtusDocument::WPtr DocumentStorage::currentDocument() const
{
    if(m_currentDocumentIndex == -1)
        return std::weak_ptr<GOtusDocument>();

    return m_documents[m_currentDocumentIndex];
}

bool DocumentStorage::load(const std::string &filePathName)
{
    Debug << "[DocumentStorage::load] try to load document from path " << QString::fromStdString(filePathName);

    auto settings = std::make_shared<QSettingsStorage>(filePathName);
    auto loadDoc = GOtusDocument::create(settings);
    if(!loadDoc)
        return false;

    m_documents.emplace_back(loadDoc);
    m_currentDocumentIndex = m_documents.size() - 1;
    m_onCurrentDocChanged(currentDocument());
    return true;
}

bool DocumentStorage::saveCurrent(const std::string &filePathName)
{
    Info << "[DocumentStorage::saveCurrent] try to save file to file " << QString::fromStdString(filePathName);
    auto &doc = m_documents[m_currentDocumentIndex];
    QSettingsStorage::SPtr settings = std::make_shared<QSettingsStorage>(filePathName);
    return doc->save(settings);
}
