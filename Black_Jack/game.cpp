#include "BJ_game.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QMessageBox>

#include <iostream>
#include <algorithm>
#include <random>

BJgame::BJgame(QObject* parent)
    : QObject(parent),
    pot{ 10 },
    host{ 1000, 0 },
    dealer{ 0, 0 },
    winner{ UNKNOWN },
    deck{}
    {

}

void BJgame::setupMatch() {
    deck.deal(2, host);
    deck.deal(2, dealer);
}

void BJgame::restart() {
    host.bank = 1000;
}

void BJgame::finishMatch() {
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

void BJgame::scoreHost() {
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

void BJgame::scoreDealer() {
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

void BJgame::setBet(int value) {
    pot = value;
}

void BJgame::reset() {
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

void Deck::setup() { 
    if (!this->cards.empty()) {
        cards.clear();
    }
    setupCardsSkins();
    shuffle();
}

void Deck::setupCardsSkins() {
    if(!cards.empty()){
        cards.clear();
    }
    cards.push_back({ "ace_of_spades", 10, QPixmap(skinPath + "ace_of_spades.png") });
    cards.push_back({ "2_of_spades", 2, QPixmap(skinPath + "2_of_spades.png") });
    cards.push_back({ "3_of_spades", 3, QPixmap(skinPath + "3_of_spades.png") });
    cards.push_back({ "4_of_spades", 4, QPixmap(skinPath + "4_of_spades.png") });
    cards.push_back({ "5_of_spades", 5, QPixmap(skinPath + "5_of_spades.png") });
    cards.push_back({ "6_of_spades", 6, QPixmap(skinPath + "6_of_spades.png") });
    cards.push_back({ "7_of_spades", 7, QPixmap(skinPath + "7_of_spades.png") });
    cards.push_back({ "8_of_spades", 8, QPixmap(skinPath + "8_of_spades.png") });
    cards.push_back({ "9_of_spades", 9, QPixmap(skinPath + "9_of_spades.png") });
    cards.push_back({ "10_of_spades", 10, QPixmap(skinPath + "10_of_spades.png") });
    cards.push_back({ "jack_of_spades", 10, QPixmap(skinPath + "jack_of_spades.png") });
    cards.push_back({ "queen_of_spades", 10, QPixmap(skinPath + "queen_of_spades.png") });
    cards.push_back({ "king_of_spades", 10, QPixmap(skinPath + "king_of_spades.png") });

    cards.push_back({ "ace_of_hearts", 10, QPixmap(skinPath + "ace_of_hearts.png") });
    cards.push_back({ "2_of_hearts", 2, QPixmap(skinPath + "2_of_hearts.png") });
    cards.push_back({ "3_of_hearts", 3, QPixmap(skinPath + "3_of_hearts.png") });
    cards.push_back({ "4_of_hearts", 4, QPixmap(skinPath + "4_of_hearts.png") });
    cards.push_back({ "5_of_hearts", 5, QPixmap(skinPath + "5_of_hearts.png") });
    cards.push_back({ "6_of_hearts", 6, QPixmap(skinPath + "6_of_hearts.png") });
    cards.push_back({ "7_of_hearts", 7, QPixmap(skinPath + "7_of_hearts.png") });
    cards.push_back({ "8_of_hearts", 8, QPixmap(skinPath + "8_of_hearts.png") });
    cards.push_back({ "9_of_hearts", 9, QPixmap(skinPath + "9_of_hearts.png") });
    cards.push_back({ "10_of_hearts", 10, QPixmap(skinPath + "10_of_hearts.png") });
    cards.push_back({ "jack_of_hearts", 10, QPixmap(skinPath + "jack_of_hearts.png") });
    cards.push_back({ "queen_of_hearts", 10, QPixmap(skinPath + "queen_of_hearts.png") });
    cards.push_back({ "king_of_hearts", 10, QPixmap(skinPath + "king_of_hearts.png") });

    cards.push_back({ "ace_of_clubs", 10, QPixmap(skinPath + "ace_of_clubs.png") });
    cards.push_back({ "2_of_clubs", 2, QPixmap(skinPath + "2_of_clubs.png") });
    cards.push_back({ "3_of_clubs", 3, QPixmap(skinPath + "3_of_clubs.png") });
    cards.push_back({ "4_ of_clubs", 4, QPixmap(skinPath + "4_of_clubs.png") });
    cards.push_back({ "5_ of_clubs", 5, QPixmap(skinPath + "5_of_clubs.png") });
    cards.push_back({ "6_ of_clubs", 6, QPixmap(skinPath + "6_of_clubs.png") });
    cards.push_back({ "7_ of_clubs", 7, QPixmap(skinPath + "7_of_clubs.png") });
    cards.push_back({ "8_ of_clubs", 8, QPixmap(skinPath + "8_of_clubs.png") });
    cards.push_back({ "9_ of_clubs", 9, QPixmap(skinPath + "9_of_clubs.png") });
    cards.push_back({ "10_of_clubs", 10, QPixmap(skinPath + "10_of_clubs.png") });
    cards.push_back({ "jack_of_clubs", 10, QPixmap(skinPath + "jack_of_clubs.png") });
    cards.push_back({ "queen_of_clubs", 10, QPixmap(skinPath + "queen_of_clubs.png") });
    cards.push_back({ "king_of_clubs", 10, QPixmap(skinPath + "king_of_clubs.png") });

    cards.push_back({ "ace_of_diamonds", 10, QPixmap(skinPath + "ace_of_diamonds.png") });
    cards.push_back({ "2_of_diamonds", 2, QPixmap(skinPath + "2_of_diamonds.png") });
    cards.push_back({ "3_of_diamonds", 3, QPixmap(skinPath + "3_of_diamonds.png") });
    cards.push_back({ "4_of_diamonds", 4, QPixmap(skinPath + "4_of_diamonds.png") });
    cards.push_back({ "5_of_diamonds", 5, QPixmap(skinPath + "5_of_diamonds.png") });
    cards.push_back({ "6_of_diamonds", 6, QPixmap(skinPath + "6_of_diamonds.png") });
    cards.push_back({ "7_of_diamonds", 7, QPixmap(skinPath + "7_of_diamonds.png") });
    cards.push_back({ "8_of_diamonds", 8, QPixmap(skinPath + "8_of_diamonds.png") });
    cards.push_back({ "9_of_diamonds", 9, QPixmap(skinPath + "9_of_diamonds.png") });
    cards.push_back({ "10_of_diamonds", 10, QPixmap(skinPath + "10_of_diamonds.png") });
    cards.push_back({ "jack_of_diamonds", 10, QPixmap(skinPath + "jack_of_diamonds.png") });
    cards.push_back({ "queen_of_diamonds", 10, QPixmap(skinPath + "queen_of_diamonds.png") });
    cards.push_back({ "king_of_diamonds", 10, QPixmap(skinPath + "king_of_diamonds.png") });

    for (auto& card : cards) {
        card.shirt = QPixmap(skinPath + "shirt.png");
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(cards.begin(), cards.end(), gen);
}

void Deck::deal(int quantityOfCards, Player& player) {

    for (int i = 0; i < quantityOfCards; i++) {
        auto it = std::prev(this->cards.end());
        player.hand.push_back(*it);
        this->cards.pop_back();
    }
}

void BJgame::handleSetSkin(const QString& info) {
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
        qDebug() << info + card.name;
        card.face = pixmap;
        card.shirt = QPixmap(info + "shirt.png");
    }
    emit setGamebarSkin();
}
