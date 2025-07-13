// GameView.cpp
#include "GameView.h"

USING_NS_CC;

bool GameView::init() {
    if (!Node::init()) return false;
    return true;
}



void GameView::setCardClickCallback(const std::function<void(CardView*)>& callback) {
    _onCardClick = callback;
}


void GameView::setStackCardClickCallback(const std::function<void(CardView*)>& callback) {
    _onStackCardClick = callback;
}

void GameView::showGame(const std::shared_ptr<GameModel>& gameModel) {
    CCLOG("Show game called");
    this->removeAllChildren();


    // 主牌区
    for (const auto& card : gameModel->getPlayFieldCards()) {
        CCLOG("Card face=%d, suit=%d", (int)card->getFace(), (int)card->getSuit());

        auto view = CardView::createWithModel(card);
        view->setClickCallback(_onCardClick);
        view->setPosition(card->getInitialPosition());
        this->addChild(view);
        view->setPosition(Vec2(random(200, 900), random(1000, 1400)));
    }

    if (auto bottomCard = gameModel->getBottomCard()) {
        auto view = CardView::createWithModel(bottomCard);
        view->setClickCallback(_onCardClick);
        view->setPosition(bottomCard->getInitialPosition());

        this->addChild(view);
    }


    if (!gameModel->isStackEmpty()) {
        auto topStackCard = gameModel->getStackCards().front();
        auto view = CardView::createWithModel(topStackCard);
        view->setPosition(Vec2(300, 300));
        view->setClickCallback(_onStackCardClick);
        this->addChild(view);
    }
}

