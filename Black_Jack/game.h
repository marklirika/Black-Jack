#pragma once

// Custom
#include "game_structs.h"

// Qt
#include <QPixmap>
#include <QObject>
#include <QString>
#include <QCoreApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QMessageBox>

//std
#include <vector>

namespace BJ {
    class Game : public QObject {
        Q_OBJECT

    public:
        explicit Game(QObject* parent = nullptr);
        ~Game(){}

        void setupMatch();
        void scoreHost();
        void scoreDealer();
        void reset();
        void restart();
        void finishMatch();

        void setBet(int value);
        const int& getBank() const { return host.bank; }
        const int& getPot() const { return pot; }
        Player& getHost() { return host; }
        Player& getDealer() { return dealer; }
        Deck& getDeck() { return deck; }

    signals:
        void finishMatchSignal(Winner winner);
        void gameOverSignal();
        void setGamebarSkin();

    public slots:
        void handleSetSkin(const QString& text);

    private:
        int pot;

        Player host;
        Player dealer;
        Winner winner;

        Deck deck;
    };
} //namepace BJ
