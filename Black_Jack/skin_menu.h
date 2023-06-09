#pragma once

#include <QDialog>
#include <QLayout>
#include <QMouseEvent>
#include <QLabel>
#include<QCoreApplication>

#include <map>

class SkinMenu :
    public QDialog
{
    Q_OBJECT

public:
    SkinMenu(QWidget* parent = nullptr);

    void mousePressEvent(QMouseEvent* event) override;

    void populateWindow(const std::map<QString, QPixmap>& skins);

signals:
    void skinChoice(const QString& info);

private:
    std::map<QString, QLabel*> labelsInfo;
};

