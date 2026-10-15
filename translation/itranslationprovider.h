#ifndef ITRANSLATIONPROVIDER_H
#define ITRANSLATIONPROVIDER_H

#include <QString>

/**
 * @file itranslationprovider.h
 * @brief Интерфейс источника переводов
 */

/**
 * @brief Поддерживаемые языки интерфейса
 */
enum class Lang { Ru, ///< Русский
                  En  ///< Английский
};

/**
 * @brief Абстрактный источник переводов
 *
 * Реализации могут читать переводы откуда угодно: JSON-файлы,
 * QTranslator + .qm, база данных и т.д. Модель
 * (@ref TranslatableItemModel) работает только через этот интерфейс
 * и не знает, откуда берётся строка
 */
class ITranslationProvider {
public:
    virtual ~ITranslationProvider() = default;

    /**
     * @brief Вернуть перевод для ключа на заданном языке
     *
     * @param key  Ключ перевода (см. @ref KeyRole)
     * @param lang Язык, на который нужно перевести
     * @return Переведённая строка. Если ключ не найден — возвращается key
     */
    virtual QString Translate(const QString &key, Lang lang) const = 0;
};

#endif // ITRANSLATIONPROVIDER_H
