#include "renderpanel.h"

#include <QDebug>
#include <QPaintEvent>
#include <QMouseEvent>

Q_LOGGING_CATEGORY(renderpanel, "RenderPanel")

#define Debug qDebug(renderpanel)
#define Info qInfo(renderpanel)
#define Warn qWarning(renderpanel)

RenderPanel::RenderPanel(QWidget *parent) :
    QWidget{parent}
{

}

void RenderPanel::renderDocument(const otuseditor::GOtusDocument::WPtr &document)
{
    m_renDoc = document;
    QWidget::update();
}

void RenderPanel::paintEvent(QPaintEvent *event)
{
    Debug << Q_FUNC_INFO;
    QWidget::paintEvent(event);

    RenderContext ctx(event->rect(), this);
    if(auto doc = m_renDoc.lock())
    {
        doc->render(ctx);
    }
}

void RenderPanel::mousePressEvent(QMouseEvent *event)
{

}

