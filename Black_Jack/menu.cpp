#include "menu.h"
#include <QVBoxLayout>
#include <QPushButton>

Menu::Menu(QWidget* parent)
    : QWidget(parent) {

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);

    soundButton = new QPushButton("Sound", this);
    soundButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    faceButton = new QPushButton("Choose Face Card Skin", this);
    faceButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    shirtButton = new QPushButton("Choose Shirt", this);
    shirtButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    backButton = new QPushButton("Back", this);
    backButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(soundButton, &QPushButton::clicked, this, &Menu::soundButtonClicked);
    connect(faceButton, &QPushButton::clicked, this, &Menu::faceButtonClicked);
    connect(shirtButton, &QPushButton::clicked, this, &Menu::shirtButtonClicked);
    connect(backButton, &QPushButton::clicked, this, &Menu::backButtonClicked);

    vbox->addWidget(soundButton);
    vbox->addWidget(faceButton);
    vbox->addWidget(shirtButton);
    vbox->addWidget(backButton);

    setLayout(vbox);
}
