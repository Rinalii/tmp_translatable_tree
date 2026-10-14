#include "mainwindow.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QTreeView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>

#include "translatableitemmodel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    model_ = new TranslatableItemModel(this);

    view_ = new QTreeView(this);
    view_->setModel(model_);
    view_->setAlternatingRowColors(true);
    view_->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    view_->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    view_->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    view_->expandAll();

    // UI
    switch_lang_btn_ = new QPushButton(this);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(switch_lang_btn_);
    layout->addWidget(view_);
    setCentralWidget(central);

    connect(switch_lang_btn_, &QPushButton::clicked, this, &MainWindow::slotSwitchLanguage);

    UpdateButtonText();

    resize(800, 400);
    setWindowTitle(QStringLiteral("Translatable Tree"));
}

void MainWindow::slotSwitchLanguage() {
    lang_ = (lang_ == Lang::Ru) ? Lang::En : Lang::Ru;
    model_->SetLanguage(lang_);
    UpdateButtonText();
}

void MainWindow::UpdateButtonText() {
    switch_lang_btn_->setText(lang_ == Lang::Ru
                             ? QStringLiteral("Переключить на EN")
                             : QStringLiteral("Switch to RU"));
}
