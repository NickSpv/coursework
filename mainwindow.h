#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QGraphicsLineItem>
#include <QInputDialog>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRect>
#include <plan/plan.h>
#include <my_view.h>
#include <iostream>
#include <QSizeF>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void pressScene(QPointF);
  void moveScene(QPointF);
  void releaseScene(QPointF);

  void createNewPlan();
  void savePlanToImage();
  void save();
  void load();
  void on_toolButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_5_clicked();

private:
  Ui::MainWindow *ui;
  Plan *plan;
  QGraphicsLineItem *current_item;
  int id_item;
  QPointF start_position;
};
