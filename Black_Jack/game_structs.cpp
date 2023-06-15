#include "game_structs.h"

#include <algorithm>
#include <random>

namespace BJ {
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
} //namepace BJ
