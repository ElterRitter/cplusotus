#pragma once
#include "irendersurface.h"

#include <QWidget>
#include <QEvent>
#include <QLoggingCategory>

#include <memory>

Q_DECLARE_LOGGING_CATEGORY(renderpanel)

/*!
 * \brief Класс RenderPanel является реализацией контекста рисования документов для Qt-виджетов
 */
class RenderPanel : public QWidget, public otuseditor::IRenderSurface
{
public:
    explicit RenderPanel(QWidget *parent = nullptr);

    virtual void renderDocument(const otuseditor::GOtusDocument::WPtr &document) override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    using RenderDocumentPtr = std::weak_ptr<otuseditor::GOtusDocument>;
    RenderDocumentPtr m_renDoc;
};
