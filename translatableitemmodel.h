#ifndef TRANSLATABLEITEMMODEL_H
#define TRANSLATABLEITEMMODEL_H

#include <QStandardItemModel>
#include "itranslationprovider.h"

class TranslatableItemModel : public QStandardItemModel {
    Q_OBJECT
public:
    explicit TranslatableItemModel(ITranslationProvider *provider,
                                   QObject *parent = nullptr);

    void SetProvider(ITranslationProvider *provider);
    void SetLanguage(Lang lang);
    Lang GetLanguage() const;

    // Загрузить данные из JSON-файла (структура дерева).
    bool LoadFromJson(const QString &path);

private:
    void BuildTree();
    // Рекурсивно обновляет текст всех ячеек, у которых задан KeyRole
    void TranslateKeyItem(QStandardItem *item);
    void Translate();

    ITranslationProvider *provider_ = nullptr;
    Lang lang_ = Lang::Ru;
};

#endif // TRANSLATABLEITEMMODEL_H
