#ifndef ITEMROLES_H
#define ITEMROLES_H

#include <Qt>

/**
 * @file itemroles.h
 * @brief Пользовательские роли элементов модели
 */

/**
 * @brief Роль, в которой хранится ключ перевода
 *
 * В ячейке столбца 0 (столбец «Параметр») в этой роли лежит строка-ключ,
 * по которой @ref ITranslationProvider возвращает перевод для текущего языка.
 * Если роль не задана - ячейка считается непереводимой.
 */
inline constexpr int KeyRole = Qt::UserRole + 1;

#endif // ITEMROLES_H
