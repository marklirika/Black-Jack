#include "gamebar.h"

#include <QCoreApplication>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include <QMenuBar>

Gamebar::Gamebar(BJgame* game, QWidget* parent) : QWidget(parent), game(game) {
    initButtons();
    setBackground();
    setupGamebar();
}

Gamebar::~Gamebar() {
    game = nullptr;
    mainLayout->removeItem(spacer);
    mainLayout->removeItem(leftHelperLayout);
    delete leftHelperLayout;
    leftHelperLayout = nullptr;
    mainLayout->removeItem(centralHelperLayout);
    delete centralHelperLayout;
    centralHelperLayout = nullptr;
    delete mainLayout;
}

void Gamebar::setBackground() {
    backgroundLabel->lower();
    backgroundLabel->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/blackjack_table.png"));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, parentWidget()->width(), parentWidget()->height());
}
void Gamebar::initButtons() {
    backgroundLabel = new QLabel(parentWidget());

    spacer = new QSpacerItem(parentWidget()->width(), 0, QSizePolicy::Maximum, QSizePolicy::Fixed);

    mainLayout = new QHBoxLayout();
    centralHelperLayout = new QVBoxLayout();
    leftHelperLayout = new QHBoxLayout();

    menuButton = new QPushButton("Menu", this);
    restartButton = new QPushButton("Restart", this);
    betButton = new QPushButton("Bet", this);
    spinbox = new QSpinBox(this);
    drawCardButton = new QPushButton("Draw", this);
    finishButton = new QPushButton("Finish", this);
    playAgainButton = new QPushButton("Play again", this);

    hostScoreBar = new QLabel(this);
    dealerScoreBar = new QLabel(this);
    winnerBar = new QLabel(this);
    balance = new QLabel(this);
}

void Gamebar::setupGamebar() {
    menuButton->setFixedSize(Gamebar::parentWidget()->height() / 10, parentWidget()->height() / 10);
    restartButton->setFixedSize(parentWidget()->height() / 10, parentWidget()->height() / 10);
    spinbox->setSingleStep(10);
    spinbox->setMinimum(10);
    spinbox->setMaximum(game->getBank());

    hostScoreBar->setStyleSheet("color: white;");
    dealerScoreBar->setStyleSheet("color: white");
    balance->setText(QString("BALANCE: %1").arg(game->getHost().bank));
    balance->setStyleSheet("color: white");

    playAgainButton->hide();
    drawCardButton->hide();
    finishButton->hide();
    balance->move(parentWidget()->width() / 2.3, 0);

    connect(menuButton, &QPushButton::clicked, this, &Gamebar::menuButtonClicked);
    connect(drawCardButton, &QPushButton::clicked, [=]() {
        game->getDeck().deal(1, game->getHost());
        game->scoreHost();
        setHostScoreBar();
        if (game->getHost().score < 21) {
            this->showMatchTable();
        }
        resize();
    });
    connect(finishButton, &QPushButton::clicked, [&]() {
        game->finishMatch();
    });
    connect(playAgainButton, &QPushButton::clicked, this, &Gamebar::restart);
    connect(spinbox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), game, &BJgame::setBet);
    connect(betButton, &QPushButton::clicked, this, &Gamebar::betButtonClicked);

    addToCentralWidget({betButton, spinbox});
    leftHelperLayout->addWidget(restartButton, Qt::AlignRight);

    mainLayout->setAlignment(Qt::AlignBottom);
    mainLayout->addWidget(menuButton, Qt::AlignBottom);
    mainLayout->addItem(spacer);
    mainLayout->addLayout(centralHelperLayout);
    mainLayout->addItem(spacer);
    mainLayout->addLayout(leftHelperLayout);
    setLayout(mainLayout);
}

void Gamebar::resize() {
    int width = parentWidget()->width();
    int height = parentWidget()->height();

    backgroundLabel->setFixedSize(width, height);

    menuButton->setFixedSize(height / 12, height / 12);
    restartButton->setFixedSize(height / 12, height / 12);


    for (auto& el : game->getHost().hand) {
        QPixmap pixmap = el.face;
        pixmap.scaled(QSize(width / 12 + 20, height / 8 + 16), Qt::KeepAspectRatio);
        el.face = pixmap;
        pixmap = el.shirt;
        pixmap.scaled(QSize(width / 12 + 20, height / 8 + 16), Qt::KeepAspectRatio);
        el.shirt = pixmap;
    }

    for (auto& el : game->getDealer().hand) {
        QPixmap pixmap = el.face;
        pixmap.scaled(QSize(width / 12 + 20, height / 8 + 16), Qt::KeepAspectRatio);
        el.face = pixmap;
        pixmap = el.shirt;
        pixmap.scaled(QSize(width / 12 + 20, height / 8 + 16), Qt::KeepAspectRatio);
        el.shirt = pixmap;
    }

    for (int i = 0; i < hostCards.size(); i++) {
        QPixmap pixmap = game->getHost().hand[i].face.scaled(QSize(width / 12 + 20, height / 8 + 16), Qt::KeepAspectRatio);
        hostCards[i]->move(pixmap.width() + pixmap.width() * i, height / 3);
        hostCards[i]->setPixmap(pixmap);
        hostCards[i]->setFixedSize(pixmap.size());
    }

    for (int i = 0; i < dealerCards.size(); i++) {
        QPixmap pixmap = game->getDealer().hand[i].face.scaled(QSize(width / 12 + 20, height / 8 + 16), Qt::KeepAspectRatio);
        dealerCards[i]->move(width - (2 * pixmap.width() + pixmap.width() * i), height / 3);
        dealerCards[i]->setPixmap(pixmap);
        dealerCards[i]->setFixedSize(pixmap.size());
    }

    if (winnerBar != nullptr) {
        QPixmap pixmap = winnerBar->pixmap().scaled(QSize(width / 2, height / 2), Qt::KeepAspectRatio);
        winnerBar->setPixmap(pixmap);
        winnerBar->setFixedSize(pixmap.size());
        winnerBar->move(width / 4, height / 2);
    }

    if (hostScoreBar != nullptr) {
        hostScoreBar->setFixedSize(width / 5, height / 4);
        hostScoreBar->move(width / 6, height / 3 + height / 9);
    }

    if (dealerScoreBar != nullptr) {
        dealerScoreBar->setFixedSize(width / 5, height / 4);
        dealerScoreBar->move(width - width / 6, height / 3 + height / 9);
    }

    if (balance != nullptr) {
        balance->move(width / 2.3, 0);
    }
}


void Gamebar::showMatchTable() {
    timer = new QTimer(this);
    timer->setInterval(150);
    hostCardIndex = hostCards.size();
    dealerCardIndex = dealerCards.size();
    auto& realHostHand = game->getHost().hand;
    auto& realDealerHand = game->getDealer().hand;
    QPixmap pixmap;

    for (int i = this->hostCards.size(); i < realHostHand.size(); i++) {
        QLabel* card = new QLabel(this);
        pixmap = realHostHand[i].face.scaled(
                    QSize(parentWidget()->width() / 12 + 20,
                           parentWidget()->height() / 8 + 16),
                     Qt::KeepAspectRatio);
        card->setPixmap(pixmap);
        card->setFixedSize(pixmap.size());
        hostCards.push_back(card);
    }

    for (int i = dealerCards.size(); i < realDealerHand.size(); i++) {
        QLabel* card = new QLabel(this);
        pixmap = realDealerHand[i].shirt.scaled(
                    QSize(parentWidget()->width() / 12 + 20,
                          parentWidget()->height() / 8 + 16),
                    Qt::KeepAspectRatio);
        card->setPixmap(pixmap);
        card->setFixedSize(pixmap.size());
        dealerCards.push_back(card);
    }

    connect(timer, &QTimer::timeout, [&]() {
        int width = parentWidget()->width();
        int height = parentWidget()->height();
        auto& realHostHand = game->getHost().hand;
        auto& realDealerHand = game->getDealer().hand;
        int i = hostCards.size() - 1;
        int pixmapWidth = realHostHand[i].shirt.scaled(
                    QSize(parentWidget()->width() / 12 + 20 + (parentWidget()->width() / 10),
                          parentWidget()->height() / 8 + 16),
                    Qt::KeepAspectRatio).width();

        if (hostCardIndex < realHostHand.size()) {
            QPoint startPosition(width / 2, 0);
            QPoint endPosition(pixmapWidth + pixmapWidth * hostCardIndex, height / 3);
            QPropertyAnimation* animation = new QPropertyAnimation(hostCards[hostCardIndex], "pos");
            animation->setDuration(500);
            animation->setStartValue(startPosition);
            animation->setEndValue(endPosition);

            QEasingCurve easingCurve(QEasingCurve::Linear);
            animation->setEasingCurve(easingCurve);
            hostCards[hostCardIndex]->show();
            animation->start();
            hostCardIndex++;
        }

        if (dealerCardIndex < realDealerHand.size()) {
            QPoint startPosition(width / 2, 0);
            QPoint endPosition(width - (2 * pixmapWidth + pixmapWidth * dealerCardIndex), height / 3);
            QPropertyAnimation* animation = new QPropertyAnimation(dealerCards[dealerCardIndex], "pos");
            animation->setDuration(500);
            animation->setStartValue(startPosition);
            animation->setEndValue(endPosition);
            QEasingCurve easingCurve(QEasingCurve::Linear);
            animation->setEasingCurve(easingCurve);
            dealerCards[dealerCardIndex]->show();
            animation->start();
            dealerCardIndex++;
        }
        emit sound();

        if (hostCardIndex == realHostHand.size() && dealerCardIndex == realDealerHand.size()) {
            timer->stop();
            drawCardButton->setEnabled(true);
            finishButton->setEnabled(true);
        }
        });
    drawCardButton->setEnabled(false);
    finishButton->setEnabled(false);
    timer->start();
}

void Gamebar::addToCentralWidget(std::vector<QWidget*> widgets) {
    for (auto& widget : widgets) {
        widget->setVisible(true);
        widget->setEnabled(true);
        centralHelperLayout->addWidget(widget);
    }
}

void Gamebar::removeFromCentralWidget(std::vector<QWidget*> widgets) {
    for (auto& widget : widgets) {
        widget->setVisible(false);
        widget->setEnabled(false);
        centralHelperLayout->removeWidget(widget);
    }
}

void Gamebar::hideScoreBar(QWidget* scoreBar) {
    scoreBar->hide();
}

void Gamebar::setHostScoreBar() {
    if (hostScoreBar == nullptr) {
        hostScoreBar = new QLabel(this);
    }
    hostScoreBar->setText(QString("%1").arg(game->getHost().score));
    hostScoreBar->setStyleSheet("color: white");
    hostScoreBar->setFixedSize(parentWidget()->width() / 5, parentWidget()->height() / 9);
    hostScoreBar->move(parentWidget()->width() / 6, parentWidget()->height() / 5);
    hostScoreBar->show();
}

void Gamebar::setDealerScoreBar() {
    if (dealerScoreBar == nullptr) {
        dealerScoreBar = new QLabel(this);
    }
    dealerScoreBar->setStyleSheet("color: white");
    dealerScoreBar->setText(QString("%1").arg(game->getDealer().score));
    dealerScoreBar->setFixedSize(parentWidget()->width() / 5, parentWidget()->height() / 9);
    dealerScoreBar->move(parentWidget()->width() - 200, parentWidget()->height() / 5);
    dealerScoreBar->show();
}

void Gamebar::revealDealerCards() {
    game->getDealer().cardsHidden = false;
    for (int i = 0; i < game->getDealer().hand.size(); i++) {
        dealerCards[i]->setPixmap(game->getDealer().hand[i].face.scaled(
            QSize(game->getDealer().hand[i].face.width() * (parentWidget()->width() / 600),
                  game->getDealer().hand[i].face.height() * (parentWidget()->height() / 400)), Qt::KeepAspectRatio));
    }
    setDealerScoreBar();
}

void Gamebar::declareWinner(Winner& winner) {
    if (winnerBar == nullptr) {
        winnerBar = new QLabel(this);
    }
    QString path;
    switch (winner) {
        case HOST: {
            path = QString(QCoreApplication::applicationDirPath() + "/images/win.png");
            break;
        }
        case DEALER: {
            path = QString(QCoreApplication::applicationDirPath() + "/images/lose.png");
            break;
        }
        case DRAW: {
            path = QString(QCoreApplication::applicationDirPath() + "/images/draw.png");
            break;
        }
    }
    QPixmap texture(path);
    winnerBar->setPixmap(texture);
    winnerBar->setFixedSize(texture.size());
    winnerBar->move(parentWidget()->width() / 3, parentWidget()->height() / 2);
    winnerBar->show();
    balance->setText(QString("BALANCE: %1").arg(game->getHost().bank));
}

void Gamebar::setupStartMatchWidget() {
    hostCardIndex = 0;
    dealerCardIndex = 0;
    removeFromCentralWidget({ betButton, spinbox });
    addToCentralWidget({ drawCardButton, finishButton });
}

void Gamebar::setupEndMatchWidget() {
    removeFromCentralWidget({ drawCardButton, finishButton });
    addToCentralWidget({ playAgainButton });
}

void Gamebar::restart() {
    if (dealerCards.empty() || hostCards.empty() || winnerBar != nullptr || hostScoreBar != nullptr || dealerScoreBar != nullptr) {
        deleteObjects();
    }
    removeFromCentralWidget({ playAgainButton });
    addToCentralWidget({ betButton, spinbox });
    hostCardIndex = 0;
    dealerCardIndex = 0;
    spinbox->setMaximum(1000);
}

void Gamebar::deleteObjects() {
    for (auto& card : hostCards) {
        delete card;
    }
    for (auto& card : dealerCards) {
        delete card;
    }

    hostCards.clear();
    dealerCards.clear();
    delete winnerBar;
    winnerBar = nullptr;
    delete hostScoreBar;
    hostScoreBar = nullptr;
    delete dealerScoreBar;
    dealerScoreBar = nullptr;
}

void Gamebar::handleSetSkin() {
    resize();
}

