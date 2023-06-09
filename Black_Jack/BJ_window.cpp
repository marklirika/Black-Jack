#include "BJ_window.h"
#include "gamebar.h"
#include "skin_menu.h"

#include <QMessageBox>


BJwindow::BJwindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    game = new BJgame(this);
    gamebar = new Gamebar(game, this);

    menu = new Menu(this);
    menu->setEnabled(false);
    menu->hide();

    setupMusicLoop();
    setupSound();

    connect(this, &BJwindow::setGameSkin, game, &BJgame::handleSetSkin);
    connect(game, &BJgame::setGamebarSkin, gamebar, &Gamebar::handleSetSkin);

    connect(gamebar, &Gamebar::betButtonClicked, this, &BJwindow::handleBetButtonClicked);
    connect(gamebar, &Gamebar::menuButtonClicked, this, &BJwindow::handleMenuButtonClicked);

    connect(menu, &Menu::soundButtonClicked, this, &BJwindow::handleSoundButtonClicked);
    connect(menu, &Menu::faceButtonClicked, this, &BJwindow::handleFaceButtonClicked);
    connect(menu, &Menu::shirtButtonClicked, this, &BJwindow::handleShirtButtonClicked);
    connect(menu, &Menu::backButtonClicked, this, &BJwindow::handleBackButtonClicked);

    connect(game, &BJgame::finishMatchSignal, this, [=](Winner winner) {
        finishMatch(winner);
        });
    this->setCentralWidget(gamebar);
}

void BJwindow::setupSound() {
    sound = new QMediaPlayer(this);
    audioOutput_2 = new QAudioOutput(this);
    sound->setAudioOutput(audioOutput_2);
    sound->setSource(QString(QCoreApplication::applicationDirPath() + "/audio/card.mp3"));
    audioOutput_2->setVolume(50);

    connect(gamebar, &Gamebar::sound, sound, &QMediaPlayer::play);
}

void BJwindow::setupMusicLoop() {
    bkgndMusic = new QMediaPlayer(this);
    audioOutput_1 = new QAudioOutput(this);
    bkgndMusic->setAudioOutput(audioOutput_1);
    bkgndMusic->setSource(QString(QCoreApplication::applicationDirPath() + "/audio/boat.mp3"));
    audioOutput_1->setVolume(50);
    bkgndMusic->play();
    connect(bkgndMusic, &QMediaPlayer::mediaStatusChanged, bkgndMusic, &QMediaPlayer::play);
}

void BJwindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    gamebar->resize();
    menu->setFixedSize(this->width(), this->height());
}

void BJwindow::handleBetButtonClicked() {
    start();
}

void BJwindow::start() {
    game->reset();
    game->getDeck().setup();
    gamebar->setupStartMatchWidget();
    game->setupMatch();
    game->scoreHost();
    gamebar->setHostScoreBar();
    if (game->getHost().score < 21) {
        gamebar->showMatchTable();
    }
    gamebar->resize();
}

void BJwindow::showMenu() {
    menu->setEnabled(true);
    menu->show();
}

void BJwindow::finishMatch(Winner& winner) {
    gamebar->setupEndMatchWidget();
    gamebar->showMatchTable();
    gamebar->revealDealerCards();
    gamebar->declareWinner(winner);
    gamebar->resize();
}

void BJwindow::handleMenuButtonClicked() {
    showMenu();
}

void BJwindow::handleSoundButtonClicked() {
    if (audioOutput_1->volume() == 0) {
        audioOutput_1->setVolume(50);
    }
    else {
        audioOutput_1->setVolume(0);
    }
}

void BJwindow::handleFaceButtonClicked(){
    skinMenu = new SkinMenu(this);
    connect(skinMenu, &SkinMenu::skinChoice, this, &BJwindow::handleSkinChoice);

    skinMenu->populateWindow(faceSkins);
    skinMenu->show();
}

void BJwindow::handleShirtButtonClicked() {
    skinMenu = new SkinMenu(this);
    connect(skinMenu, &SkinMenu::skinChoice, this, &BJwindow::handleSkinChoice);

    skinMenu->populateWindow(shirtSkins);
    skinMenu->show();
}

void BJwindow::handleBackButtonClicked() {
    menu->setEnabled(false);
    menu->hide();
    if(gamebar !=nullptr){
        gamebar->setEnabled(true);
    }
}

void BJwindow::handleSkinChoice(const QString& text) {
    emit setGameSkin(text);
}
