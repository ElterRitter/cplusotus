#pragma once

#include "gotusdocument.h"

#include <QLoggingCategory>

#include <vector>
#include <functional>

Q_DECLARE_LOGGING_CATEGORY(documentstorage)

namespace otuseditor {

/*!
 * \brief Класс DocumentStorage обеспечивает хранилище документов
 */
class DocumentStorage
{
public:
    using SPtr = std::shared_ptr<DocumentStorage>;  ///< указатель на хранилище документоа
    /*!
     *  currentDocumentChangedCallback коллбек, который будет вызываться при смене текущего документа
     */
    using currentDocumentChangedCallback = std::function<void(GOtusDocument::WPtr)>;

    /*!
     * \brief DocumentStorage конструктор
     */
    DocumentStorage();
    /*!
     * \brief currentDocument позволяет получить текущий активный документ в хранилище
     * \return "слабый" указатель на текущий документ
     */
    GOtusDocument::WPtr currentDocument() const;

    /*!
     * \brief load загружает документ из файла
     * \param filePathName полный путь к сохранённому файлу документа
     * \return результат попытки загрузить документ
     */
    bool load(const std::string &filePathName);

    /*!
     * \brief saveCurrent сохранить текущий документ в файл
     * \param filePathName полный путь к сохранённому документу
     * \return результат попытки сохранить документ
     */
    bool saveCurrent(const std::string &filePathName);

    /*!
     * \brief onChangedCurrentDocument
     * \param clb коллбек для индикации смены текущего документа
     */
    void onChangedCurrentDocument(currentDocumentChangedCallback clb) { m_onCurrentDocChanged = clb; }

private:
    using documents = std::vector<GOtusDocument::SPtr>;
    documents m_documents;
    currentDocumentChangedCallback m_onCurrentDocChanged;
    std::size_t m_currentDocumentIndex;
};

};
