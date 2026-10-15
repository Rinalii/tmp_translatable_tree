#pragma once

#include <QMainWindow>
#include "jsontranslationprovider.h"
#include "qttranslationprovider.h"

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
    void slotSwitchProvider();

private:
    void UpdateButtonText();

    ITranslationProvider *GetCurrentProvider();

    QTreeView *view_ = nullptr;
    TranslatableItemModel *model_ = nullptr;

    JsonTranslationProvider json_provider_;
    QtTranslationProvider   qt_provider_;
    bool is_qt_provider_ = false;

    QPushButton *switch_lang_btn_ = nullptr;
    QPushButton *switch_provider_btn_ = nullptr;
    Lang lang_ = Lang::Ru;
};
