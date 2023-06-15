#pragma once

// Qt
#include<QCoreApplication>
#include <QDialog>
#include <QLayout>
#include <QMouseEvent>
#include <QLabel>

// std
#include <map>

namespace BJ {
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
} //namepace BJ
