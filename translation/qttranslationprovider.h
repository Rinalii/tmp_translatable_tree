#ifndef QTTRANSLATIONPROVIDER_H
#define QTTRANSLATIONPROVIDER_H

#include "itranslationprovider.h"

#include <QHash>
class QTranslator;

/**
 * @file qttranslationprovider.h
 * @brief Источник переводов на основе QTranslator и .qm-файлов
 */

/**
 * @brief Провайдер переводов через QTranslator + .qm
 *
 * Ключи, хранимые в @ref KeyRole, должны совпадать с исходными строками
 * в .ts-файле. Контекст перевода задан константой @c k_context
 * и должен совпадать с контекстом в .ts
 *
 * Для каждого языка создаётся отдельный QTranslator, поэтому
 * переключение языка не требует повторной загрузки .qm
 */
class QtTranslationProvider : public ITranslationProvider {
public:
    QtTranslationProvider() = default;

    /**
     * @brief Освобождает все загруженные QTranslator
     */
    ~QtTranslationProvider() override;

    /**
     * @brief Загрузить .qm-файл для указанного языка
     *
     * Если для языка уже был загружен переводчик, он удаляется и
     * заменяется новым
     *
     * @param lang Язык, для которого загружается .qm
     * @param path Путь к .qm-файлу (может быть ресурсом)
     * @return true при успешной загрузке, иначе false
     */
    bool Load(Lang lang, const QString &path);

    /// @copydoc ITranslationProvider::Translate
    QString Translate(const QString &key, Lang lang) const override;

private:
    /// Отдельный QTranslator на каждый язык (ключ — int(Lang))
    QHash<int, QTranslator*> translators_;
};

#endif // QTTRANSLATIONPROVIDER_H
