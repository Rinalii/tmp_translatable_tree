#include "mainwindow.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QTreeView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // UI
    view_ = new QTreeView(this);
    model_ = new QStandardItemModel(this);
    model_->setColumnCount(3);
    view_->setModel(model_);
    view_->setAlternatingRowColors(true);
    view_->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    view_->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    view_->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    switch_lang_btn_ = new QPushButton(this);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(switch_lang_btn_);
    layout->addWidget(view_);
    setCentralWidget(central);

    connect(switch_lang_btn_, &QPushButton::clicked, this, &MainWindow::slotSwitchLanguage);

    BuildTree();
    Translate();

    resize(800, 400);
    setWindowTitle(QStringLiteral("Translatable Tree"));
}

void MainWindow::BuildTree() {
    model_->removeRows(0, model_->rowCount());

    // col0 - ключ, col1/col2 - сырые значения (не переводятся)
    auto make_row =  [](const QString &key,
                       const QString &v1,
                       const QString &v2) -> QList<QStandardItem *> {
                            auto *c0 = new QStandardItem;
                            c0->setData(key, Qt::UserRole);
                            auto *c1 = new QStandardItem(v1);
                            auto *c2 = new QStandardItem(v2);
                            return {c0, c1, c2};
                    };

    // заполняем данными
    auto top_row = make_row("subaddress", "", "");
    QStandardItem *subaddress = top_row[0];
    model_->appendRow(top_row);

    subaddress->appendRow(make_row("roll",    "0x0", "0.00'"));
    subaddress->appendRow(make_row("pitch",   "0x0", "0.00'"));
    subaddress->appendRow(make_row("heading", "0x0", "0.00'"));

    auto validity_row = make_row("validity", "0x0", "");
    QStandardItem *validity = validity_row[0];
    subaddress->appendRow(validity_row);

    validity->appendRow(make_row("reserve",    "0x0", ""));
    validity->appendRow(make_row("heading_ok", "",    "0"));
    validity->appendRow(make_row("pitch_ok",   "",    "0"));

    view_->expandAll();
}

// обновляем только колонку с ключами
void MainWindow::TranslateKeyItem(QStandardItem *item) {
    const QString key = item->data(Qt::UserRole).toString();
    if (!key.isEmpty()) {
        item->setText(tr_(key, lang_));
    }

    for (int r = 0; r < item->rowCount(); ++r) {
        if (auto *child = item->child(r, 0)) {
            TranslateKeyItem(child);
        }
    }
}

void MainWindow::Translate() {
    switch_lang_btn_->setText(lang_ == Lang::Ru ? "Переключить на EN" : "Switch to RU");

    // заголовки колонок
    model_->setHeaderData(0, Qt::Horizontal, tr_("col_param", lang_));
    model_->setHeaderData(1, Qt::Horizontal, tr_("col_pass_val",  lang_));
    model_->setHeaderData(2, Qt::Horizontal, tr_("col_val2",  lang_));

    for (int r = 0; r < model_->rowCount(); ++r) {
        if (auto *top = model_->item(r, 0)) {
            TranslateKeyItem(top);
        }
    }
}

void MainWindow::slotSwitchLanguage() {
    lang_ = (lang_ == Lang::Ru) ? Lang::En : Lang::Ru;
    Translate();
}
