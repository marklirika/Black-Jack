#pragma once

// Custom
#include "game.h"

//Qt
#include <QCoreApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QMessageBox>
#include<QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QMenu>
#include <QMenuBar>
#include <QEventLoop>

namespace BJ {
    class BJwindow;

    class Gamebar : public QWidget {
        Q_OBJECT;

    public:
        explicit Gamebar(Game* game, QWidget* parent = nullptr);
        ~Gamebar();

        // rendering
        void showMatchTable();
        void resize();
        void revealDealerCards();
        void declareWinner(Winner& winner);

        void showHostScoreBar();
        void showDealerScoreBar();
        void hideScoreBar(QWidget* scoreBar);

        // logic
        void setupGamebar();
        void initButtons();
        void setBackground();

        void addToCentralWidget(std::vector<QWidget*> widgets);
        void removeFromCentralWidget(std::vector<QWidget*> widgets);

        void setupStartMatchWidget();
        void setupEndMatchWidget();
        void restart();

        void deleteObjects();

        const std::vector<QLabel*>& getHostHand() const { return hostCards; }
        const std::vector<QLabel*>& getDealerHand() const { return dealerCards; }
    signals:
        void betButtonClicked();
        void menuButtonClicked();
        void sound();

    public slots:
        void handleSetSkin();

    private:
        int hostCardIndex = 0;
        int dealerCardIndex = 0;

        Game* game;
        QTimer* timer;

        std::vector<QLabel*> hostCards;
        std::vector<QLabel*> dealerCards;

        QLabel* background;

        QHBoxLayout* mainLayout;
        QVBoxLayout* centralHelperLayout;
        QHBoxLayout* leftHelperLayout;
        QSpacerItem* spacer;

        QLabel* hostScoreBar;
        QLabel* dealerScoreBar;
        QLabel* balanceBar;
        QLabel* winnerBar;

        QSpinBox* spinbox;
        QPushButton* menuButton;
        QPushButton* restartButton;
        QPushButton* betButton;
        QPushButton* drawCardButton;
        QPushButton* finishButton;
        QPushButton* playAgainButton;
    };
} //namepace BJ


