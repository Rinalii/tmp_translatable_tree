#ifndef TRANSLATABLEITEMMODEL_H
#define TRANSLATABLEITEMMODEL_H

#include <QStandardItemModel>
#include "translations.h"

class TranslatableItemModel : public QStandardItemModel {
    Q_OBJECT
public:
    TranslatableItemModel(QObject *parent = nullptr);

    void SetLanguage(Lang lang);
    Lang GetLanguage() const;

private:
    void BuildTree();
    // обновляем только колонку с ключами
    void TranslateKeyItem(QStandardItem *item);
    void Translate();

    Lang lang_ = Lang::Ru;
};

#endif // TRANSLATABLEITEMMODEL_H
