#ifndef TREELOADER_H
#define TREELOADER_H

#include <QString>
class QStandardItemModel;

// Строит дерево QStandardItem из JSON-файла
// Ожидаемый формат описан в data/data.json
class TreeLoader {
public:
    // Загрузить дерево из path в model
    static bool LoadInto(QStandardItemModel *model, const QString &path);
};

#endif // TREELOADER_H
