#pragma once
#include <QHash>
#include <QString>

enum class Lang { Ru, En };

// Ключи -> перевод
inline const QHash<QString, QString> ru = {
    // заголовки колонок
    {"col_param",       "Параметр"},
    {"col_pass_val",    "Переданные значения"},
    {"col_val2",        "Значения"},

    // узлы
    {"subaddress",      "Подадрес"},
    {"roll",            "Крен объекта"},
    {"pitch",           "Тангаж"},
    {"heading",         "Курс"},
    {"validity",        "Признаки достоверности данных"},
    {"reserve",         "[0-12] Резерв"},
    {"heading_ok",      "[13] Достоверность курса"},
    {"pitch_ok",        "[14] Достоверность тангажа"},
    };

inline const QHash<QString, QString> en = {
    {"col_param",       "Parameter"},
    {"col_pass_val",    "Passed values"},
    {"col_val2",        "Values"},

    {"subaddress",      "Subaddress"},
    {"roll",            "Object roll"},
    {"pitch",           "Pitch"},
    {"heading",         "Heading"},
    {"validity",        "Data validity flags"},
    {"reserve",         "[0-12] Reserve"},
    {"heading_ok",      "[13] Heading validity"},
    {"pitch_ok",        "[14] Pitch validity"},
    };

inline QString tr_(const QString &key, Lang lang) {
    const auto &dict = (lang == Lang::Ru) ? ru : en;
    return dict.value(key, key);
}
