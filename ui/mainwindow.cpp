#include "mainwindow.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QTreeView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QMessageBox>

#include "translatableitemmodel.h"

/**
 * @file mainwindow.cpp
 * @brief Реализация @ref MainWindow
 */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    if (!json_provider_.Load(Lang::Ru, ":/data/ru.json") ||
        !json_provider_.Load(Lang::En, ":/data/en.json")) {
        QMessageBox::critical(this, "Error",
                              "Не удалось загрузить словари переводов.");
    }

    if (!qt_provider_.Load(Lang::Ru, ":/translations/tree_ru.qm") ||
        !qt_provider_.Load(Lang::En, ":/translations/tree_en.qm")) {
        QMessageBox::critical(this, "Error",
                              "Не удалось загрузить .qm словари.");
    }

    model_ = new TranslatableItemModel(GetCurrentProvider(), this);
    if (!model_->LoadFromJson(":/data/data.json")) {
        QMessageBox::critical(this, "Error",
                              "Не удалось загрузить data.json.");
    }

    // View
    view_ = new QTreeView(this);
    view_->setModel(model_);
    view_->setAlternatingRowColors(true);
    view_->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    view_->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    view_->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    view_->expandAll();

    // UI
    switch_lang_btn_ = new QPushButton(this);
    switch_provider_btn_ = new QPushButton(this);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(switch_lang_btn_);
    layout->addWidget(switch_provider_btn_);
    layout->addWidget(view_);
    setCentralWidget(central);

    connect(switch_lang_btn_, &QPushButton::clicked, this, &MainWindow::slotSwitchLanguage);
    connect(switch_provider_btn_, &QPushButton::clicked, this, &MainWindow::slotSwitchProvider);

    UpdateButtonText();

    resize(800, 400);
    setWindowTitle(QStringLiteral("Translatable Tree"));
}

ITranslationProvider *MainWindow::GetCurrentProvider() {
    if (is_qt_provider_) {
        return &qt_provider_;
    }
    return &json_provider_;
}

void MainWindow::slotSwitchLanguage() {
    lang_ = (lang_ == Lang::Ru) ? Lang::En : Lang::Ru;
    model_->SetLanguage(lang_);
    UpdateButtonText();
}

void MainWindow::slotSwitchProvider() {
    is_qt_provider_ = !is_qt_provider_;
    model_->SetProvider(GetCurrentProvider());
    UpdateButtonText();
}

void MainWindow::UpdateButtonText() {
    switch_lang_btn_->setText(lang_ == Lang::Ru
        ? QStringLiteral("Переключить на EN")
        : QStringLiteral("Switch to RU"));

    const QString source = is_qt_provider_
        ? QStringLiteral(".qm")
        : QStringLiteral(".json");

    switch_provider_btn_->setText(lang_ == Lang::Ru
        ? "Источник: " + source
        : "Source: " + source);
}
