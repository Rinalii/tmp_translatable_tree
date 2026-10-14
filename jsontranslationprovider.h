#ifndef JSONTRANSLATIONPROVIDER_H
#define JSONTRANSLATIONPROVIDER_H

#include <QHash>
#include "itranslationprovider.h"

// Чтение словарей из JSON-файлов.
// Ожидаемый формат: { "key": "перевод", ... }
class JsonTranslationProvider : public ITranslationProvider {
public:
    JsonTranslationProvider() = default;

    // Загрузить словарь для языка. Возвращает false при ошибке чтения/парсинга.
    bool Load(Lang lang, const QString &path);

    QString Translate(const QString &key, Lang lang) const override;

private:
    QHash<QString, QString> ru_;
    QHash<QString, QString> en_;
};

#endif // JSONTRANSLATIONPROVIDER_H
