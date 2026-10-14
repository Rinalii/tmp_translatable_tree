#pragma once

#include <QMainWindow>
#include "jsontranslationprovider.h"

class TranslatableItemModel;
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
    void UpdateButtonText();

    QTreeView *view_ = nullptr;
    TranslatableItemModel *model_ = nullptr;
    JsonTranslationProvider provider_;
    QPushButton *switch_lang_btn_ = nullptr;
    Lang lang_ = Lang::Ru;
};
