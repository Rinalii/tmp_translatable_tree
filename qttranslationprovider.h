#ifndef QTTRANSLATIONPROVIDER_H
#define QTTRANSLATIONPROVIDER_H

#include "itranslationprovider.h"

#include <QHash>
class QTranslator;

// Перевод с (QTranslator + .qm)
// ключи совпадают с ключами, которые хранятся в KeyRole модели
class QtTranslationProvider : public ITranslationProvider {
public:
    QtTranslationProvider() = default;
    ~QtTranslationProvider() override;

    bool Load(Lang lang, const QString &path);

    QString Translate(const QString &key, Lang lang) const override;
private:
    // Отдельный QTranslator на каждый язык
    QHash<int, QTranslator*> translators_;
};

#endif // QTTRANSLATIONPROVIDER_H
