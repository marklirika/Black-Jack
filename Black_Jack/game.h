#pragma once
#include <QPixmap>
#include <QObject>
#include <QString>
#include <QCoreApplication>

#include <vector>

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

class BJgame : public QObject {
    Q_OBJECT

public:
    explicit BJgame(QObject* parent = nullptr);
    ~BJgame(){}

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

