#include "qttranslationprovider.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QTranslator>

namespace {
constexpr const char *k_context = "Tree"; // контекст, совпадающий с .ts
}

QtTranslationProvider::~QtTranslationProvider() {
    for (QTranslator *t : translators_) {
        if (t) {
            QCoreApplication::removeTranslator(t);
            delete t;
        }
    }
    translators_.clear();
}

bool QtTranslationProvider::Load(Lang lang, const QString &path) {
    if (!QFileInfo::exists(path)) {
        return false;
    }

    auto *t = new QTranslator();
    if (!t->load(path)) {
        delete t;
        return false;
    }

    if (!QCoreApplication::installTranslator(t)) {
        delete t;
        return false;
    }

    const int lang_id = static_cast<int>(lang);
    auto it = translators_.find(lang_id);
    if (it != translators_.end()) { // удаляем устаревшую версию
        QCoreApplication::removeTranslator(it.value());
        delete it.value();
    }
    translators_[lang_id] = t;

    return true;
}

QString QtTranslationProvider::Translate(const QString &key, Lang lang) const {
    QTranslator *t = translators_.value(static_cast<int>(lang), nullptr);
    if (!t) {
        return key; // ничего не загружено - отдаём ключ
    }

    const QString translated = t->translate(k_context, key.toUtf8().constData());
    return translated.isEmpty() ? key : translated;
}
