#pragma once
#include "irendersurface.h"

#include <QWidget>
#include <QEvent>
#include <QLoggingCategory>

#include <memory>

Q_DECLARE_LOGGING_CATEGORY(renderpanel)

class RenderPanel : public QWidget, public IRenderSurface
{
public:
    explicit RenderPanel(QWidget *parent = nullptr);

    virtual void renderDocument(const GOtusDocument::WPtr &document) override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    using RenderDocumentPtr = std::weak_ptr<GOtusDocument>;
    RenderDocumentPtr m_renDoc;
};

