#include "gamebar.h"

#define WIDTH 600
#define HEIGHT 420

namespace BJ {
    void Gamebar::showMatchTable() {
        timer = new QTimer(this);
        timer->setInterval(150);
        hostCardIndex = hostCards.size();
        dealerCardIndex = dealerCards.size();
        auto& realHostHand = game->getHost().hand;
        auto& realDealerHand = game->getDealer().hand;
        int width = parentWidget()->width();
        int height = parentWidget()->height();
        QPixmap pixmap;
        QSize pixmapSize = QSize(60 * (width / WIDTH), 90 * (height / HEIGHT));

        for (int i = this->hostCards.size(); i < realHostHand.size(); i++) {
            QLabel* card = new QLabel(this);
            pixmap = realHostHand[i].face.scaled(pixmapSize, Qt::KeepAspectRatio);
            card->setPixmap(pixmap);
            card->setFixedSize(pixmap.size());
            hostCards.push_back(card);
        }

        for (int i = dealerCards.size(); i < realDealerHand.size(); i++) {
            QLabel* card = new QLabel(this);
            pixmap = realDealerHand[i].shirt.scaled(pixmapSize, Qt::KeepAspectRatio);
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
            int pixmapWidth = 60 * (width / WIDTH);

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

    void Gamebar::revealDealerCards() {
        game->getDealer().cardsHidden = false;
        for (int i = 0; i < game->getDealer().hand.size(); i++) {
            dealerCards[i]->setPixmap(game->getDealer().hand[i].face.scaled(
                                          60 * (parentWidget()->width() / WIDTH), 90 * (parentWidget()->height() / HEIGHT)));
            dealerCards[i]->setFixedSize(60 * (parentWidget()->width() / WIDTH), 90 * (parentWidget()->height() / HEIGHT));
        }
        showDealerScoreBar();
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
        balanceBar->setText(QString("BALANCE: %1").arg(game->getHost().bank));
    }

    void Gamebar::resize() {
        int width = parentWidget()->width();
        int height = parentWidget()->height();
        background->setFixedSize(width, height);
        QSize newPixmapSize = QSize(60 * (width / WIDTH), 90 * (height / HEIGHT));
        QPixmap pixmap;

        menuButton->setFixedSize(height / 12, height / 12);
        restartButton->setFixedSize(height / 12, height / 12);

        for (auto& el : game->getHost().hand) {
            pixmap = el.face;
            pixmap.scaled(newPixmapSize, Qt::KeepAspectRatio);
            el.face = pixmap;
            pixmap = el.shirt;
            pixmap.scaled(newPixmapSize, Qt::KeepAspectRatio);
            el.shirt = pixmap;
        }

        for (auto& el : game->getDealer().hand) {
            pixmap = el.face;
            pixmap.scaled(newPixmapSize, Qt::KeepAspectRatio);
            el.face = pixmap;
            pixmap = el.shirt;
            pixmap.scaled(newPixmapSize, Qt::KeepAspectRatio);
            el.shirt = pixmap;
        }

        for (int i = 0; i < hostCards.size(); i++) {
            pixmap = game->getHost().hand[i].face;
            pixmap = pixmap.scaled(newPixmapSize, Qt::KeepAspectRatio);

            hostCards[i]->move(pixmap.width() * (i + 1), height / 3);
            hostCards[i]->setPixmap(pixmap);
            hostCards[i]->setFixedSize(pixmap.size());
        }

        for (int i = 0; i < dealerCards.size(); i++) {
            if (game->getDealer().cardsHidden) {
                pixmap = game->getDealer().hand[i].shirt;
            }
            else {
                pixmap = game->getDealer().hand[i].face;
            }
            pixmap = pixmap.scaled(newPixmapSize, Qt::KeepAspectRatio);
            dealerCards[i]->move(width - (pixmap.width() * (i + 2)), height / 3);
            dealerCards[i]->setPixmap(pixmap);
            dealerCards[i]->setFixedSize(pixmap.size());
        }

        if (winnerBar != nullptr) {
            pixmap = winnerBar->pixmap().scaled(QSize(width / 2, height / 2), Qt::KeepAspectRatio);
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

        if (balanceBar != nullptr) {
            balanceBar->move(width / 2.3, 0);
        }
    }

    void Gamebar::showHostScoreBar() {
        if (hostScoreBar == nullptr) {
            hostScoreBar = new QLabel(this);
        }
        hostScoreBar->setText(QString("%1").arg(game->getHost().score));
        hostScoreBar->setStyleSheet("color: white");
        hostScoreBar->setFixedSize(parentWidget()->width() / 5, parentWidget()->height() / 9);
        hostScoreBar->move(parentWidget()->width() / 6, parentWidget()->height() / 5);
        hostScoreBar->show();
    }

    void Gamebar::showDealerScoreBar() {
        if (dealerScoreBar == nullptr) {
            dealerScoreBar = new QLabel(this);
        }
        dealerScoreBar->setStyleSheet("color: white");
        dealerScoreBar->setText(QString("%1").arg(game->getDealer().score));
        dealerScoreBar->setFixedSize(parentWidget()->width() / 5, parentWidget()->height() / 9);
        dealerScoreBar->move(parentWidget()->width() - 200, parentWidget()->height() / 5);
        dealerScoreBar->show();
    }

    void Gamebar::hideScoreBar(QWidget* scoreBar) {
        scoreBar->hide();
    }
} // namespace BJ


