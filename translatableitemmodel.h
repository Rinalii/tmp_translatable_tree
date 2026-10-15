#ifndef TRANSLATABLEITEMMODEL_H
#define TRANSLATABLEITEMMODEL_H

#include <QStandardItemModel>
#include "itranslationprovider.h"

/**
 * @file translatableitemmodel.h
 * @brief Модель дерева с поддержкой переводов
 */

/**
 * @brief Модель дерева, поддерживающая смену языка и источника переводов
 *
 * Модель построена поверх @ref QStandardItemModel. В ячейке столбца 0
 * может храниться ключ перевода в роли @ref KeyRole. При вызове
 * @ref Translate (в конструкторе, при смене языка, при смене провайдера
 * или после загрузки данных) текст таких ячеек заменяется переводом
 *
 * @note Названия колонок (headerData) также переводятся
 */
class TranslatableItemModel : public QStandardItemModel {
    Q_OBJECT
public:

    /**
     * @brief Конструктор
     * @param provider Источник переводов. Не должен быть nullptr
     * @param parent   Родительский QObject
     */
    explicit TranslatableItemModel(ITranslationProvider *provider,
                                   QObject *parent = nullptr);

    /**
     * @brief Заменить источник переводов и обновить тексты
     * @param provider Новый источник переводов
     */
    void SetProvider(ITranslationProvider *provider);

    /**
     * @brief Сменить язык и обновить тексты
     * @param lang Новый язык. Если совпадает с текущим - ничего не делает
     */
    void SetLanguage(Lang lang);

    /**
     * @brief Текущий язык модели
     * @return Язык, установленный через @ref SetLanguage (по умолчанию — Ru)
     */
    Lang GetLanguage() const;

    /**
     * @brief Загрузить дерево из JSON-файла
     *
     * Формат описан в @ref TreeLoader. При успешной загрузке
     * автоматически вызывается @ref Translate
     *
     * @param path Путь к JSON-файлу (может быть ресурсом)
     * @return true при успехе, иначе false
     */
    bool LoadFromJson(const QString &path);

private:

    /**
     * @brief Рекурсивно обновить текст ячейки и её потомков
     *
     * Переводит ячейку, если у неё задана роль @ref KeyRole, затем
     * рекурсивно обрабатывает дочерние элементы столбца 0
     *
     * @param item Корневой элемент поддерева. Может быть nullptr
     */
    void TranslateKeyItem(QStandardItem *item);

    /**
     * @brief Обновить заголовки колонок и тексты всех ячеек
     */
    void Translate();

    ITranslationProvider *provider_ = nullptr; ///< Источник переводов
    Lang lang_ = Lang::Ru;                     ///< Текущий язык
};

#endif // TRANSLATABLEITEMMODEL_H
