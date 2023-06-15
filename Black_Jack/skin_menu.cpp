#include "skin_menu.h"

namespace BJ {
    void SkinMenu::mousePressEvent(QMouseEvent* event) {
        for(auto& kv : labelsInfo) {
            auto& stringInfo = kv.first;
            auto& label = kv.second;


            QRect rect = label->geometry();
            if (event->button() == Qt::LeftButton && rect.contains(event->pos()) ) {
                emit skinChoice(stringInfo);
            }
        }
    }

    SkinMenu::SkinMenu(QWidget* parent)
        : QDialog(parent) {
        setWindowTitle("Available skins");
        setModal(true);
    }

    void SkinMenu::populateWindow(const std::map<QString, QPixmap>& skins){
        QVBoxLayout * layout = new QVBoxLayout(this);
        int i = 1;
        for (auto& skin : skins) {
            auto& texturePath = skin.first;
            auto& texture = skin.second;
            QPixmap newPix = texture.scaled(QSize(180, 250), Qt::KeepAspectRatio);
            QLabel* label = new QLabel(this);
            label->setPixmap(newPix);
            label->setFixedSize(QSize(180, 250));
            label->move(180 * i, 250 * i);
            layout->addWidget(label);
            labelsInfo.insert(std::make_pair(texturePath, label));
            i++;
        }
        setLayout(layout);
    }
} //namepace BJ
