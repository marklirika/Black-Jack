#ifndef GAMEBAR_H
#define GAMEBAR_H
#include "BJ_game.h"

#include<QTimer>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QMenu>

#include <iostream>
#include <memory>

class BJwindow;

class Gamebar : public QWidget {
    Q_OBJECT;

public:
    explicit Gamebar(BJgame* game, QWidget* parent = nullptr);
    ~Gamebar();

    void setupGamebar();
    void setBackground();
    void initButtons();

    void showMatchTable();

    void addToCentralWidget(std::vector<QWidget*> widgets);
    void removeFromCentralWidget(std::vector<QWidget*> widgets);

    void showScoreBar(QWidget* scoreBar);
    void hideScoreBar(QWidget* scoreBar);
    void setHostScoreBar();
    void setDealerScoreBar();

    void revealDealerCards();
    void declareWinner(Winner& winner);
    const std::vector<QLabel*>& getHostHand() const { return hostCards; }
    const std::vector<QLabel*>& getDealerHand() const { return dealerCards; }

    void setupStartMatchWidget();
    void setupEndMatchWidget();

    void showMenu();
    void resize();

    void restart();
    void deleteObjects();

signals:
    void betButtonClicked();
    void menuButtonClicked();
    void sound();

public slots:
    void handleSetSkin();

private:
    int hostCardIndex = 0;
    int dealerCardIndex = 0;

    BJgame* game;
    QTimer* timer;

    std::vector<QLabel*> hostCards;
    std::vector<QLabel*> dealerCards;

    QLabel* backgroundLabel;

    QHBoxLayout* mainLayout;
    QVBoxLayout* centralHelperLayout;
    QHBoxLayout* leftHelperLayout;
    QSpacerItem* spacer;

    QLabel* hostScoreBar;
    QLabel* dealerScoreBar;
    QLabel* balance;
    QLabel* winnerBar;

    QSpinBox* spinbox;

    QPushButton* menuButton;
    QPushButton* restartButton;
    QPushButton* betButton;
    QPushButton* drawCardButton;
    QPushButton* finishButton;
    QPushButton* playAgainButton;
};
#endif // GAMEBAR_H


