#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

namespace BJ {
    class MainMenu : public QWidget {
        Q_OBJECT

    public:
        MainMenu(QWidget* parent = 0);

    signals:
        void soundButtonClicked();
        void faceButtonClicked();
        void shirtButtonClicked();
        void backButtonClicked();

    private:
        QPushButton* soundButton;
        QPushButton* faceButton;
        QPushButton* shirtButton;
        QPushButton* backButton;
    };
} //namepace BJ
