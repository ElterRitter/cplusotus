#include "mwnd.h"
#include "ui_mwnd.h"

#include "gotuscircle.h"
#include "gotuspoint.h"


#include <QFileDialog>
#include <QStandardPaths>

#include <functional>

mwnd::mwnd(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mwnd)
{
    ui->setupUi(this);
    connectUI();

    auto fn = std::bind(&mwnd::onCurrentDocumentChanged, this, std::placeholders::_1);
    m_docStorage = std::make_shared<DocumentStorage>();
    m_docStorage->onChangedCurrentDocument(fn);
}

mwnd::~mwnd()
{
    delete ui;
}

void mwnd::onActionCloseActivated()
{
    QApplication::quit();
}

void mwnd::onActionSaveActivated()
{
    auto currentDocumentPtr = m_docStorage->currentDocument().lock();
    if(!currentDocumentPtr)
        return;

    auto settingsPath = currentDocumentPtr->settingsPathName();
    if(settingsPath.empty())
    {
        // file dialog
        auto homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить документ как"), homePath, "Config Files (*.ini)");
        if(fileName.isEmpty())
            return;

        settingsPath = fileName.toStdString();
    }

    m_docStorage->saveCurrent(settingsPath);
}

void mwnd::onActionLoadActivated()
{
    // TODO : open file dialog
    auto homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    auto filePath = QFileDialog::getOpenFileName(this, tr("Загрузить документ как"), homePath, "Config Files (*.ini)");
    if(filePath.isEmpty())
        return;

    m_docStorage->load(filePath.toStdString());
}

void mwnd::onActionNewActivated()
{
    m_docStorage->load("");
}

void mwnd::onActionAddCircle()
{
    auto weak_doc = m_docStorage->currentDocument();
    if(auto doc = weak_doc.lock())
    {
        auto elem = std::make_shared<GOtusCircle>(100, 50, 50);
        elem->setCenter(100, 50);
        elem->setRadius(50);
        doc->addElement(elem);
        this->update();
    }
}

void mwnd::onActionAddPoint()
{
    auto weak_doc = m_docStorage->currentDocument();
    if(auto doc = weak_doc.lock())
    {
        auto elem = std::make_shared<GOtusPoint>(30, 30);
        doc->addElement(elem);
        this->update();
    }
}

void mwnd::onActionRemoveAll()
{
    auto weak_doc = m_docStorage->currentDocument();
    if(auto doc = weak_doc.lock())
    {
        doc->removeAllElements();
        this->update();
    }
}

void mwnd::connectUI()
{
    connect(ui->actionExit, &QAction::triggered, this, &mwnd::onActionCloseActivated);
    connect(ui->actionSave, &QAction::triggered, this, &mwnd::onActionSaveActivated);
    connect(ui->actionLoad, &QAction::triggered, this, &mwnd::onActionLoadActivated);
    connect(ui->actionNew, &QAction::triggered, this, &mwnd::onActionNewActivated);
    connect(ui->actionCircle, &QAction::triggered, this, &mwnd::onActionAddCircle);
    connect(ui->actionPoint, &QAction::triggered, this, &mwnd::onActionAddPoint);
    connect(ui->actionClearAll, &QAction::triggered, this, &mwnd::onActionRemoveAll);
}

void mwnd::onCurrentDocumentChanged(GOtusDocument::WPtr doc)
{
    ui->renderpanel->renderDocument(doc);
}
