#include "jsontranslationprovider.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

bool JsonTranslationProvider::Load(Lang lang, const QString &path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        return false;
    }

    const QByteArray raw = f.readAll();
    QJsonParseError err{};
    const QJsonDocument doc = QJsonDocument::fromJson(raw, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        return false;
    }

    const QJsonObject obj = doc.object();
    QHash<QString, QString> &target = (lang == Lang::Ru) ? ru_ : en_;
    target.clear();
    target.reserve(obj.size());
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        target.insert(it.key(), it.value().toString());
    }
    return true;
}

QString JsonTranslationProvider::Translate(const QString &key, Lang lang) const {
    const auto &dict = (lang == Lang::Ru) ? ru_ : en_;
    return dict.value(key, key);
}
