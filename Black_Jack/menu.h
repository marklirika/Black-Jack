#pragma once

#include <QWidget>
#include <QPushButton>

class Menu : public QWidget {
    Q_OBJECT

public:
    Menu(QWidget* parent = 0);

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
