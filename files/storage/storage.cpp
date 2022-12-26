#include "storage.h"

Storage::Storage() {
  load();
}

void Storage::load() {
  std::cout << "LOAD\n";
  QFile file(path);
  if (file.open(QIODevice::ReadOnly)) {
    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
      std::cout << "fromJson failed: " << jsonError.errorString().toStdString()
                << std::endl;
      return;
    }
    if (document.isObject()) {
      QJsonObject jsonObj = document.object();
      for (auto item : items) {
        /*if (jsonObj.contains(item)) {
          QJsonObject obj = jsonObj.value(item).toObject();
          QStringList keys = obj.keys();
          for (auto key : keys) {
            auto value = obj.take(key);
            if (value.isDouble()) {
              int id = value.toInt();
              std::cout << key.toStdString() << " : " << id;
            } else if (value.isString()) {
              QString patch_svg = value.toString();
              std::cout << key.toStdString() << " : " << patch_svg.toStdString();
            }
          }
        }*/
      }
    }
  }
}

void Storage::save() {
  std::cout << "SAVE\n";
  QVariantList items_list;

  for (auto item : items) {
    QVariantMap item_map;
    item_map.insert("id", item.getId());
    item_map.insert("patch", item.getSvgPatch());
  }

  QJson::Serializer serializer;
  QByteArray json = serializer.serialize(items_list);

  QFile file(path);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
    QTextStream iStream(&file);
    iStream.setCodec("utf-8");
    iStream << json;
    file.close();
  } else {
    std::cout << "file open failed: " << path.toStdString() << std::endl;
  }
}

void Storage::addItem(const PlanItem &new_item) {
  items.append(new_item);
}

QVector<PlanItem> Storage::getItems() {
  return items;
}
