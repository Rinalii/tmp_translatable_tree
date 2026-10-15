#ifndef TREELOADER_H
#define TREELOADER_H

#include <QString>
class QStandardItemModel;

/**
 * @file treeloader.h
 * @brief Загрузчик дерева из JSON в QStandardItemModel
 */

/**
 * @brief Утилита для построения дерева @ref QStandardItem из JSON-файла
 *
 * Ожидаемый формат файла:
 * @code
 * {
 *   "nodes": [
 *     {
 *       "key":      "param_roll",
 *       "pass_val": "0x0",
 *       "value":    "0.00'",
 *       "children": [
 *         { "key": "param_roll_1", "pass_val": "0x0", "value": "0" }
 *       ]
 *     }
 *   ]
 * }
 * @endcode
 */
class TreeLoader {
public:

    /**
     * @brief Загрузить дерево из файла в модель
     *
     * Предварительно очищает модель
     *
     * @param model Модель, в которую загружается дерево. Не должна быть nullptr
     * @param path  Путь к JSON-файлу (может быть ресурсом)
     * @return true при успешной загрузке, иначе false
     */
    static bool LoadInto(QStandardItemModel *model, const QString &path);
};

#endif // TREELOADER_H
