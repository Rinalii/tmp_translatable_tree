#pragma once

#include <QMainWindow>
#include "translations.h"

class QStandardItemModel;
class QStandardItem;
class QTreeView;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void slotSwitchLanguage();

private:
    void BuildTree();
    void TranslateKeyItem(QStandardItem *item);
    void Translate();

    QTreeView *view_ = nullptr;
    QStandardItemModel *model_ = nullptr;
    QPushButton *switch_lang_btn_ = nullptr;
    Lang lang_ = Lang::Ru;
};
