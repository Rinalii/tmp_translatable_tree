#include "translatableitemmodel.h"
#include "itemroles.h"
#include "itranslationprovider.h"
#include "treeloader.h"

TranslatableItemModel::TranslatableItemModel(ITranslationProvider *provider,
                                             QObject *parent)
    : QStandardItemModel(parent)
    , provider_(provider) {
    setColumnCount(3);
    Translate();
}

void TranslatableItemModel::SetProvider(ITranslationProvider *provider) {
    provider_ = provider;
    Translate();
}

void TranslatableItemModel::SetLanguage(Lang lang) {
    if (lang_ == lang) return;
    lang_ = lang;
    Translate();
}

Lang TranslatableItemModel::GetLanguage() const {
    return lang_;
}

bool TranslatableItemModel::LoadFromJson(const QString &path) {
    const bool ok = TreeLoader::LoadInto(this, path);
    if (ok) {
        Translate();
    }
    return ok;
}

void TranslatableItemModel::TranslateKeyItem(QStandardItem *item) {
    if (!item) return;
    // Переводим ячейку, только если у неё есть ключ.
    const QString key = item->data(KeyRole).toString();

    if (!key.isEmpty()) {
        item->setText(provider_->Translate(key, lang_));
    }

    for (int r = 0; r < item->rowCount(); ++r) {
        TranslateKeyItem(item->child(r, 0));
    }
}

void TranslatableItemModel::Translate() {
    // заголовки колонок
    setHeaderData(0, Qt::Horizontal, provider_->Translate("col_param", lang_));
    setHeaderData(1, Qt::Horizontal, provider_->Translate("col_pass_val",  lang_));
    setHeaderData(2, Qt::Horizontal, provider_->Translate("col_val2",  lang_));

    for (int r = 0; r < rowCount(); ++r) {
        TranslateKeyItem(item(r, 0));
    }
}
