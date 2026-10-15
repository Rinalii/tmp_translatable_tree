#ifndef JSONTRANSLATIONPROVIDER_H
#define JSONTRANSLATIONPROVIDER_H

#include <QHash>
#include "itranslationprovider.h"

/**
 * @file jsontranslationprovider.h
 * @brief Источник переводов на основе JSON-словарей
 */

/**
 * @brief Провайдер переводов, читающий словари из JSON-файлов
 *
 * Ожидаемый формат файла:
 * @code
 * {
 *   "col_param":    "Параметр",
 *   "col_pass_val": "Переданные значения",
 *   "col_val2":     "Значения"
 * }
 * @endcode
 *
 * Для каждого языка хранится отдельный словарь. Если ключ отсутствует,
 * @ref Translate возвращает сам ключ
 */
class JsonTranslationProvider : public ITranslationProvider {
public:
    JsonTranslationProvider() = default;

    /**
     * @brief Загрузить словарь для указанного языка
     *
     * Полностью заменяет ранее загруженный словарь для этого языка.
     *
     * @param lang Язык, для которого загружается словарь
     * @param path Путь к JSON-файлу (может быть ресурсом)
     * @return true при успешной загрузке и парсинге, иначе false
     */
    bool Load(Lang lang, const QString &path);

    /// @copydoc ITranslationProvider::Translate
    QString Translate(const QString &key, Lang lang) const override;

private:
    QHash<QString, QString> ru_; ///< Словарь для русского языка
    QHash<QString, QString> en_; ///< Словарь для английского языка
};

#endif // JSONTRANSLATIONPROVIDER_H
