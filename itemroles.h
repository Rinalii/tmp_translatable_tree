#ifndef ITEMROLES_H
#define ITEMROLES_H

#include <Qt>

// Роли для ячеек модели дерева
// KeyRole   - переводимое значение
// ValueRole - "сырое" значение (не переводится)
enum class ItemRoles : int {
    KeyRole   = Qt::UserRole + 1,
    ValueRole = Qt::UserRole + 2,
};

// enum class -> int
inline int role(ItemRoles r) noexcept {
    return static_cast<int>(r);
}

#endif // ITEMROLES_H
