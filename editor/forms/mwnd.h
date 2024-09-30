#pragma once
#include "documentstorage.h"
#include "igotuselement.h"

#include <QMainWindow>


namespace Ui {
class mwnd;
}

/*!
 * \brief Класс mwnd главного окна приложения
 */
class mwnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit mwnd(QWidget *parent = nullptr);
    virtual ~mwnd();

private slots:
    void onActionCloseActivated();
    void onActionSaveActivated();
    void onActionLoadActivated();
    void onActionNewActivated();
    void onActionAddCircle();
    void onActionAddPoint();
    void onActionRemoveAll();

private:
    Ui::mwnd *ui;
    otuseditor::DocumentStorage::SPtr m_docStorage;
    otuseditor::IGotusElement::SPtr m_elementToAdd;

    void connectUI();
    void onCurrentDocumentChanged(otuseditor::GOtusDocument::WPtr doc);
};

