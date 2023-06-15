#pragma once
// Custom
#include "ui_BJwindow.h"
#include "game.h"
#include "gamebar.h"
#include "main_menu.h"
#include "skin_menu.h"

// QT
#include <QtWidgets/QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include <QPixmap>
#include <QString>

// std
#include <map>

namespace BJ {
    class window : public QMainWindow
    {
        Q_OBJECT

    public:
        window(QWidget* parent = nullptr);

        void setupMusicLoop();
        void setupSoundSource();

        void startMatch();
        void finishMatch(Winner& winner);

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

        void handleMatchEnding(Winner& winner);

    protected:
        void resizeEvent(QResizeEvent* event) override;

    private:
        Game* game;
        Gamebar* gamebar;

        QAudioOutput* musicOutput;
        QAudioOutput* soundOutput;
        QMediaPlayer* bkgndMusic;
        QMediaPlayer* sound;

        MainMenu* menu;
        SkinMenu* skinMenu;
        Ui::BJwindow ui;

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
    };
} //namepace BJ
