#include "translatableitemmodel.h"
#include "itemroles.h"
#include "itranslationprovider.h"
#include "treeloader.h"

TranslatableItemModel::TranslatableItemModel(ITranslationProvider &provider,
                                             QObject *parent)
    : QStandardItemModel(parent)
    , provider_(provider) {
    setColumnCount(3);
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

void TranslatableItemModel::BuildTree() {
    removeRows(0, rowCount());

    // col0 - ключ, col1/col2 - сырые значения (не переводятся)
    auto make_row =  [](const QString &key,
                       const QString &v1,
                       const QString &v2) -> QList<QStandardItem *> {
        auto *c0 = new QStandardItem;
        if (!key.isEmpty()) {
            c0->setData(key, role(ItemRoles::KeyRole));
        }
        auto *c1 = new QStandardItem(v1);
        auto *c2 = new QStandardItem(v2);

        // «Сырые» значения тоже сохраняем в ValueRole — пригодится,
        // если позже захочется отделить отображение от данных.
        c1->setData(v1, role(ItemRoles::ValueRole));
        c2->setData(v2, role(ItemRoles::ValueRole));

        return {c0, c1, c2};
    };

    // заполняем данными
    auto top_row = make_row("subaddress", "", "");
    QStandardItem *subaddress = top_row[0];
    appendRow(top_row);

    subaddress->appendRow(make_row("roll",    "0x0", "0.00'"));
    subaddress->appendRow(make_row("pitch",   "0x0", "0.00'"));
    subaddress->appendRow(make_row("heading", "0x0", "0.00'"));

    auto validity_row = make_row("validity", "0x0", "");
    QStandardItem *validity = validity_row[0];
    subaddress->appendRow(validity_row);

    validity->appendRow(make_row("reserve",    "0x0", ""));
    validity->appendRow(make_row("heading_ok", "",    "0"));
    validity->appendRow(make_row("pitch_ok",   "",    "0"));
}

void TranslatableItemModel::TranslateKeyItem(QStandardItem *item) {
    if (!item) return;
    // Переводим ячейку, только если у неё есть ключ.
    const QString key = item->data(role(ItemRoles::KeyRole)).toString();

    if (!key.isEmpty()) {
        item->setText(provider_.Translate(key, lang_));
    }

    for (int r = 0; r < item->rowCount(); ++r) {
        for (int c = 0; c < columnCount(); ++c) {
            TranslateKeyItem(item->child(r, c));
        }
    }
}

void TranslatableItemModel::Translate() {
    // заголовки колонок
    setHeaderData(0, Qt::Horizontal, provider_.Translate("col_param", lang_));
    setHeaderData(1, Qt::Horizontal, provider_.Translate("col_pass_val",  lang_));
    setHeaderData(2, Qt::Horizontal, provider_.Translate("col_val2",  lang_));

    for (int r = 0; r < rowCount(); ++r) {
        for (int c = 0; c < columnCount(); ++c) {
            TranslateKeyItem(item(r, c));
        }
    }
}
