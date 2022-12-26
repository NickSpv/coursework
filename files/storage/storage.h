#pragma once

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>
#include <qjson-qt5/serializer.h>
#include <plan_item/plan_item.h>
#include <iostream>

class Storage
{
public:
  Storage();

  QVector<PlanItem> getItems();

public slots:
  void addItem(const PlanItem&);

private:
  QString path = "./data/items_list.json";

  QVector<PlanItem> items;

  void load();
  void save();
};

