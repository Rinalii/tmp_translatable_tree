#include "treeloader.h"
#include "itemroles.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QStandardItem>

namespace {

// Рекурсивно строит строку (3 ячейки) и всех её потомков
QList<QStandardItem *> BuildRow(const QJsonObject &node) {
    auto *c0 = new QStandardItem;
    const QString key = node.value("key").toString();
    if (!key.isEmpty()) {
        c0->setData(key, KeyRole);
    }

    const QString v1 = node.value("pass_val").toString();
    const QString v2 = node.value("value").toString();

    auto *c1 = new QStandardItem(v1);
    auto *c2 = new QStandardItem(v2);

    const QJsonArray children = node.value("children").toArray();
    for (const QJsonValue &cv : children) {
        if (!cv.isObject()) continue;
        c0->appendRow(BuildRow(cv.toObject()));
    }

    return {c0, c1, c2};
}

} // namespace

bool TreeLoader::LoadInto(QStandardItemModel *model, const QString &path) {
    if (!model) return false;

    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) return false;

    QJsonParseError err{};
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) return false;

    const QJsonObject root = doc.object();
    const QJsonArray nodes = root.value("nodes").toArray();

    model->removeRows(0, model->rowCount());
    for (const QJsonValue &nv : nodes) {
        if (!nv.isObject()) continue;
        model->appendRow(BuildRow(nv.toObject()));
    }
    return true;
}
