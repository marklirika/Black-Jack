#pragma once
#include "ui_BJwindow.h"
#include "BJ_game.h"
#include "gamebar.h"
#include "menu.h"
#include "skin_menu.h"

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QPixmap>
#include <QLabel>
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QMap>

#include <map>
class BJwindow : public QMainWindow
{
    Q_OBJECT

public:
    BJwindow(QWidget* parent = nullptr);

    void setupMusicLoop();
    void setupSound();

    void start();

    void showMenu();
signals:
    void setGameSkin(const QString& text);

public slots:
    void handleBetButtonClicked();
    void handleMenuButtonClicked();

    void handleSoundButtonClicked();
    void handleFaceButtonClicked();
    void handleShirtButtonClicked();
    void handleBackButtonClicked();

    void handleSkinChoice(const QString& info);

    void finishMatch(Winner& winner);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    BJgame* game;
    Gamebar* gamebar;

    QAudioOutput* audioOutput_1;
    QAudioOutput* audioOutput_2;
    QMediaPlayer* bkgndMusic;
    QMediaPlayer* sound;

    const std::map<QString, QPixmap> faceSkins {
        { QString(QCoreApplication::applicationDirPath() + "/images/cardset_1/"),
                 QPixmap(QCoreApplication::applicationDirPath() + "/images/cardset_1/ace_of_spades.png")},
        { QString(QCoreApplication::applicationDirPath() + "/images/cardset_2/"),
                 QPixmap(QCoreApplication::applicationDirPath() + "/images/cardset_2/ace_of_spades.png")} };

    const std::map<QString, QPixmap> shirtSkins {
        { QString(QCoreApplication::applicationDirPath() + "/images/cardset_1/"),
            QPixmap(QCoreApplication::applicationDirPath() + "/images/cardset_1/shirt.png") },
        { QString(QCoreApplication::applicationDirPath() + "/images/cardset_2/"),
                    QPixmap(QCoreApplication::applicationDirPath() + "/images/cardset_2/shirt.png") } };
    Menu* menu;
    SkinMenu* skinMenu;
    Ui::BJwindow ui;
};

