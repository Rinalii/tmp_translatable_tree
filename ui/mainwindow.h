#pragma once

#include <QMainWindow>
#include "jsontranslationprovider.h"
#include "qttranslationprovider.h"

/**
 * @file mainwindow.h
 * @brief Главное окно демонстрационного приложения
 */

class TranslatableItemModel;
class QTreeView;
class QPushButton;

/**
 * @brief Главное окно: дерево с переводом + кнопки переключения языка/источника
 *
 * Окно хранит два источника переводов (@ref JsonTranslationProvider и
 * @ref QtTranslationProvider) и позволяет переключаться между ними и
 * между языками «на лету». Текущий провайдер передаётся в модель через
 * @ref TranslatableItemModel::SetProvider
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    /**
     * @brief Конструктор. Загружает словари, данные и настраивает UI
     * @param parent Родительский виджет
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:

    /**
     * @brief Переключить язык (Ru или En) и обновить модель и подписи кнопок
     */
    void slotSwitchLanguage();

    /**
     * @brief Переключить источник переводов (.json или .qm) и обновить модель
     */
    void slotSwitchProvider();

private:

    /**
     * @brief Обновить тексты кнопок в соответствии с текущим языком и источником
     */
    void UpdateButtonText();

    /**
     * @brief Вернуть указатель на текущий источник переводов
     * @return Указатель на json_provider_ или qt_provider_ в зависимости
     *         от значения @ref is_qt_provider_
     */
    ITranslationProvider *GetCurrentProvider();

    QTreeView *view_ = nullptr;                     ///< Представление дерева
    TranslatableItemModel *model_ = nullptr;        ///< Модель дерева

    JsonTranslationProvider json_provider_;         ///< Источник переводов из JSON
    QtTranslationProvider   qt_provider_;           ///< Источник переводов из .qm
    bool is_qt_provider_ = false;                   ///< true - используется .qm

    QPushButton *switch_lang_btn_ = nullptr;        ///< Кнопка смены языка
    QPushButton *switch_provider_btn_ = nullptr;    ///< Кнопка смены источника
    Lang lang_ = Lang::Ru;                          ///< Текущий язык
};
