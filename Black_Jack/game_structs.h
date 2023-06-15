#include <QCoreApplication>
#include <QString>
#include <QPixmap>

namespace BJ {
    struct Card {
        QString name;
        int value;
        QPixmap face;
        QPixmap shirt;
    };

    struct Player {
        int bank;
        int score;
        bool cardsHidden;
        std::vector<Card> hand;
    };

    struct Deck {
        void setup();
        void setupCardsSkins();

        void shuffle();
        void deal(int quantityOfCards, Player& player);

        void setCardPath(const QString& path);
        void setSkins(const QString&path);

        QString skinPath = QString(QCoreApplication::applicationDirPath() + "/images/cardset_1/");
        std::vector<Card> cards;
    };

    enum Winner {
        HOST,
        DEALER,
        DRAW,
        UNKNOWN
    };
} //namepace BJ
