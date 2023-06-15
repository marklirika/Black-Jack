#include "game.h"

namespace BJ {
    Game::Game(QObject* parent)
        : QObject(parent),
        pot{ 10 },
        host{ 1000, 0, false, {} },
        dealer{ 0, 0, true, {} },
        winner{ UNKNOWN },
        deck{} { }

    void Game::setupMatch() {
        deck.deal(2, host);
        deck.deal(2, dealer);
    }

    void Game::finishMatch() {
        scoreDealer();
        if (((host.score < dealer.score) || host.score > 21) && (dealer.score <= 21)) {
            host.bank -= pot;
            if (host.bank < 10) {
                emit gameOverSignal();
                restart();
            }
            emit finishMatchSignal(DEALER);
        }
        else if ((host.score <= 21) && (dealer.score > 21 || host.score > dealer.score)) {
            host.bank += pot;
            emit finishMatchSignal(HOST);
        }
        else {
            emit finishMatchSignal(DRAW);
        }
    }

    void Game::restart() {
        host.bank = 1000;
    }

    void Game::scoreHost() {
        host.score = 0;
        int aceAmount = 0;
        for (auto& el : host.hand) {
            bool isAce = false;
            QStringList words = el.name.split("_");
            for(auto& word : words){
                if(word == "ace") isAce = true; break;
            }
            if (!isAce) {
                host.score += el.value;
            }
            else {
                aceAmount += 1;
            }
        }

        if (aceAmount > 0) {
            if (host.score + 11 + aceAmount - 1 <= 21) {
                host.score += 11 + aceAmount - 1;
            }
            else {
                host.score += aceAmount;
            }
        }

        if (host.score >= 21) {
            finishMatch();
        }
    }

    void Game::scoreDealer() {
        dealer.score = 0;
        int aceAmount = 0;
        for (auto& el : dealer.hand) {
            if (el.name != "Ace") {
                dealer.score += el.value;
            }
            else {
                aceAmount += 1;
            }
        }

        if (aceAmount > 0) {
            if (dealer.score + 11 + aceAmount - 1 <= 21) {
                dealer.score += 11 + aceAmount - 1;
            }
            else {
                dealer.score += aceAmount;
            }
        }

        if (dealer.score <= 16) {
            deck.deal(1, dealer);
            scoreDealer();
        }
    }

    void Game::setBet(int value) {
        pot = value;
    }

    void Game::reset() {
        this->host.score = 0;
        this->dealer.score = 0;
        this->dealer.cardsHidden = true;
        if (!host.hand.empty()) {
            host.hand.clear();
        }
        if (!dealer.hand.empty()) {
            dealer.hand.clear();
        }
        if (!deck.cards.empty()) {
            deck.cards.clear();
        }
    }

    void Game::handleSetSkin(const QString& info) {
    this->deck.skinPath = info;
    deck.setupCardsSkins();
    for(auto& card : host.hand) {
        QPixmap pixmap = QPixmap(info + card.name);
        qDebug() << info + card.name;
        card.face = pixmap;
        card.shirt = QPixmap(info + "shirt.png");
    }
    for(auto& card : dealer.hand) {
        QPixmap pixmap = QPixmap(info + card.name);
        card.face = pixmap;
        card.shirt = QPixmap(info + "shirt.png");
    }
    emit setGamebarSkin();
}
} //namepace BJ
