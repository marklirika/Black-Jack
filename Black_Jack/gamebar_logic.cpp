#include "gamebar.h"


namespace BJ {
    Gamebar::Gamebar(Game* game, QWidget* parent) : QWidget(parent), game(game) {
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
        background->lower();
        background->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/blackjack_table.png"));
        background->setScaledContents(true);
        background->setGeometry(0, 0, parentWidget()->width(), parentWidget()->height());
    }

    void Gamebar::initButtons() {
        background = new QLabel(parentWidget());

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
        balanceBar = new QLabel(this);
    }

    void Gamebar::setupGamebar() {
        menuButton->setFixedSize(Gamebar::parentWidget()->height() / 10, parentWidget()->height() / 10);
        restartButton->setFixedSize(parentWidget()->height() / 10, parentWidget()->height() / 10);
        spinbox->setSingleStep(10);
        spinbox->setMinimum(10);
        spinbox->setMaximum(game->getBank());

        hostScoreBar->setStyleSheet("color: white;");
        dealerScoreBar->setStyleSheet("color: white");
        balanceBar->setText(QString("BALANCE: %1").arg(game->getHost().bank));
        balanceBar->setStyleSheet("color: white");

        playAgainButton->hide();
        drawCardButton->hide();
        finishButton->hide();
        balanceBar->move(parentWidget()->width() / 2.3, 0);

        connect(menuButton, &QPushButton::clicked, this, &Gamebar::menuButtonClicked);
        connect(drawCardButton, &QPushButton::clicked, [=]() {
            game->getDeck().deal(1, game->getHost());
            game->scoreHost();
            showHostScoreBar();
            if (game->getHost().score < 21) {
                this->showMatchTable();
            }
        });
        connect(finishButton, &QPushButton::clicked, [&]() {
            game->finishMatch();
        });
        connect(playAgainButton, &QPushButton::clicked, this, &Gamebar::restart);
        connect(spinbox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), game, &Game::setBet);
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
} //namepace BJ
