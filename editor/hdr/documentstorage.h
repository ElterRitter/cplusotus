#pragma once

#include "gotusdocument.h"

#include <QLoggingCategory>

#include <vector>
#include <functional>

Q_DECLARE_LOGGING_CATEGORY(documentstorage)

namespace otuseditor {

class DocumentStorage
{
public:
    using SPtr = std::shared_ptr<DocumentStorage>;  ///< указатель на хранилище документоа
    using currentDocumentChangedCallback = std::function<void(GOtusDocument::WPtr)>;

    DocumentStorage();
    GOtusDocument::WPtr currentDocument() const;

    bool load(const std::string &filePathName);
    bool saveCurrent(const std::string &filePathName);

    void onChangedCurrentDocument(currentDocumentChangedCallback clb) { m_onCurrentDocChanged = clb; }

private:
    using documents = std::vector<GOtusDocument::SPtr>;
    documents m_documents;
    currentDocumentChangedCallback m_onCurrentDocChanged;
    std::size_t m_currentDocumentIndex;
};

};
