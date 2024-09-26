#pragma once
#include "documentstorage.h"
#include "igotuselement.h"

#include <QMainWindow>


namespace Ui {
class mwnd;
}

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
    DocumentStorage::SPtr m_docStorage;
    IGotusElement::SPtr m_elementToAdd;

    void connectUI();
    void onCurrentDocumentChanged(GOtusDocument::WPtr doc);
};

