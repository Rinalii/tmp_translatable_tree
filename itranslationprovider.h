#ifndef ITRANSLATIONPROVIDER_H
#define ITRANSLATIONPROVIDER_H

#include <QString>

enum class Lang { Ru, En };

// Источник переводов
class ITranslationProvider {
public:
    virtual ~ITranslationProvider() = default;

    // Вернуть перевод. Если ключа нет - вернуть сам ключ.
    virtual QString Translate(const QString &key, Lang lang) const = 0;
};

#endif // ITRANSLATIONPROVIDER_H
