#include "window.h"

namespace BJ {
    window::window(QWidget* parent) : QMainWindow(parent) {
        ui.setupUi(this);

        game = new Game(this);
        gamebar = new Gamebar(game, this);

        menu = new MainMenu(this);
        menu->setEnabled(false);
        menu->hide();

        setupMusicLoop();
        setupSoundSource();

        connect(this, &window::setGameSkin, game, &Game::handleSetSkin);
        connect(game, &Game::setGamebarSkin, gamebar, &Gamebar::handleSetSkin);
        connect(game, &Game::finishMatchSignal, this, [=](Winner winner) {
            handleMatchEnding(winner);
            });
        connect(gamebar, &Gamebar::betButtonClicked, this, &window::handleBetButtonClicked);
        connect(gamebar, &Gamebar::menuButtonClicked, this, &window::handleMenuButtonClicked);

        connect(menu, &MainMenu::soundButtonClicked, this, &window::handleSoundButtonClicked);
        connect(menu, &MainMenu::faceButtonClicked, this, &window::handleFaceButtonClicked);
        connect(menu, &MainMenu::shirtButtonClicked, this, &window::handleShirtButtonClicked);
        connect(menu, &MainMenu::backButtonClicked, this, &window::handleBackButtonClicked);

        this->setCentralWidget(gamebar);
    }

    void window::setupSoundSource() {
        sound = new QMediaPlayer(this);
        soundOutput = new QAudioOutput(this);
        sound->setAudioOutput(soundOutput);
        sound->setSource(QString(QCoreApplication::applicationDirPath() + "/audio/card.mp3"));
        soundOutput->setVolume(50);
        connect(gamebar, &Gamebar::sound, sound, &QMediaPlayer::play);
    }

    void window::setupMusicLoop() {
        bkgndMusic = new QMediaPlayer(this);
        musicOutput = new QAudioOutput(this);
        bkgndMusic->setAudioOutput(musicOutput);
        bkgndMusic->setSource(QString(QCoreApplication::applicationDirPath() + "/audio/boat.mp3"));
        musicOutput->setVolume(50);
        bkgndMusic->play();
        connect(bkgndMusic, &QMediaPlayer::mediaStatusChanged, bkgndMusic, &QMediaPlayer::play);
    }

    void window::startMatch() {
        game->reset();
        game->getDeck().setup();
        gamebar->setupStartMatchWidget();
        game->setupMatch();
        game->scoreHost();
        gamebar->showHostScoreBar();
        if (game->getHost().score < 21) {
            gamebar->showMatchTable();
        }
    }

    void window::finishMatch(Winner& winner) {
        gamebar->setupEndMatchWidget();
        gamebar->showMatchTable();
        gamebar->revealDealerCards();
        gamebar->declareWinner(winner);
    }

    void window::showMenu() {
        menu->setEnabled(true);
        menu->show();
    }

    void window::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    gamebar->resize();
    menu->setFixedSize(this->width(), this->height());
}
} //namepace BJ
