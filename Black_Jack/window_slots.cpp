#include "window.h"

namespace BJ {
    void window::handleBetButtonClicked() {
        startMatch();
    }

    void window::handleMenuButtonClicked() {
        showMenu();
    }

    void window::handleSoundButtonClicked() {
        if (musicOutput->volume() == 0) {
            musicOutput->setVolume(50);
        }
        else {
            musicOutput->setVolume(0);
        }
    }

    void window::handleFaceButtonClicked(){
        skinMenu = new SkinMenu(this);
        connect(skinMenu, &SkinMenu::skinChoice, this, &window::handleSkinChoice);

        skinMenu->populateWindow(faceSkins);
        skinMenu->show();
    }

    void window::handleShirtButtonClicked() {
        skinMenu = new SkinMenu(this);
        connect(skinMenu, &SkinMenu::skinChoice, this, &window::handleSkinChoice);

        skinMenu->populateWindow(shirtSkins);
        skinMenu->show();
    }

    void window::handleBackButtonClicked() {
        menu->setEnabled(false);
        menu->hide();
        if(gamebar !=nullptr){
            gamebar->setEnabled(true);
        }
    }

    void window::handleSkinChoice(const QString& text) {
        emit setGameSkin(text);
    }

    void window::handleMatchEnding(Winner& winner) {
    finishMatch(winner);
}
} //namepace BJ
