#include "GameController.h"
#include "GameModelFromLevelGenerator.h"
#include "LevelConfigLoader.h"

USING_NS_CC;

GameController::GameController() {}


void GameController::rebuildModelToViewMap() {
    _modelToViewMap.clear();
    for (auto child : _gameView->getChildren()) {
        auto cardView = dynamic_cast<CardView*>(child);
        if (cardView) {
            _modelToViewMap[cardView->getModel().get()] = cardView;
        }
    }
}

bool GameController::canMatch(std::shared_ptr<CardModel> a, std::shared_ptr<CardModel> b) {
    if (!a || !b) return false;
    int diff = abs(a->getCardValue() - b->getCardValue());
    return diff == 1;
}

void GameController::startGame(int levelId, GameView* gameView) {
    _gameView = gameView;

    auto config = LevelConfigLoader::loadFromJson("level_1.json");
    _gameModel = GameModelFromLevelGenerator::generate(config);

    _gameView->setCardClickCallback([this](CardView* view) {
        handleCardClick(view);
        });
    _gameView->setStackCardClickCallback([this](CardView* view) {
        handleStackCardClick(view);
        });

    _gameView->showGame(_gameModel);
    this->rebuildModelToViewMap(); 

    // 使用裸指针建立映射
    _modelToViewMap.clear();
    for (auto child : _gameView->getChildren()) {
        auto cardView = dynamic_cast<CardView*>(child);
        if (cardView && cardView->getModel()) {
            _modelToViewMap[cardView->getModel().get()] = cardView;
        }
    }

}

void GameController::handleCardClick(CardView* clickedView) {
    auto clickedModel = clickedView->getModel();
    if (!clickedModel || clickedModel->isCovered() || !clickedModel->isFaceUp()) return;

    auto bottomCard = _gameModel->getBottomCard();
    if (!bottomCard || !canMatch(clickedModel, bottomCard)) return;

    auto toView = _modelToViewMap[bottomCard.get()];
    if (!toView) {
        CCLOG("Error: toView not found in _modelToViewMap");
        return;
    }

    auto fromPos = clickedView->getPosition();
    auto toPos = toView->getPosition();
    CCLOG("Clicked card move to toPos: (%f, %f)", toPos.x, toPos.y);

    clickedView->runAction(Sequence::create(
        MoveTo::create(0.3f, toPos),
        CallFunc::create([=]() {
            _gameModel->setBottomCard(clickedModel);
            clickedModel->setFaceUp(true);
            clickedView->updateTexture();


            for (auto& card : _gameModel->getPlayFieldCards()) {
                card->removeCoveringCard(clickedModel);
            }


            _undoManager.recordAction({ clickedModel, bottomCard, fromPos, toPos });


            auto toViewNow = _modelToViewMap[clickedModel.get()];
            if (toViewNow) toViewNow->updateTexture();


            clickedView->removeFromParent();
            _modelToViewMap.erase(clickedModel.get());

            }),
        nullptr
                ));
}

void GameController::handleStackCardClick(CardView* clickedView) {
    if (_gameModel->isStackEmpty()) return;

    auto currentBottom = _gameModel->getBottomCard();
    auto newBottom = _gameModel->popStackCard();
    if (!newBottom) return;

    newBottom->setFaceUp(true);
    _gameModel->setBottomCard(newBottom);


    auto newBottomView = CardView::createWithModel(newBottom);
    newBottomView->setClickCallback([this](CardView* v) {
        handleCardClick(v);
        });
    _gameView->addChild(newBottomView);
    newBottomView->setPosition(newBottom->getInitialPosition());
    _modelToViewMap[newBottom.get()] = newBottomView;

    auto fromView = _modelToViewMap[newBottom.get()];
    auto toView = _modelToViewMap[currentBottom.get()];
    if (!fromView || !toView) {
        CCLOG("Error: fromView or toView not found in _modelToViewMap");
        return;
    }

    auto fromPos = fromView->getPosition();
    auto toPos = toView->getPosition();

    fromView->runAction(Sequence::create(
        MoveTo::create(0.3f, toPos),
        CallFunc::create([=]() {
            fromView->updateTexture();
            toView->updateTexture();

            _undoManager.recordAction({ newBottom, currentBottom, fromPos, toPos });

            _gameView->showGame(_gameModel);
            this->rebuildModelToViewMap(); 
            }),
        nullptr
                ));
}

void GameController::undoLastAction() {
    if (!_undoManager.hasUndo()) return;

    auto action = _undoManager.popUndo();
    _gameModel->setBottomCard(action.toCard);

    auto fromView = _modelToViewMap[action.fromCard.get()];
    auto toView = _modelToViewMap[action.toCard.get()];
    if (!fromView || !toView) {
        CCLOG("Error: undo fromView or toView not found in _modelToViewMap");
        return;
    }

    fromView->runAction(Sequence::create(
        MoveTo::create(0.3f, action.fromPos),
        CallFunc::create([=]() {
            fromView->updateTexture();
            toView->updateTexture();
            _gameView->showGame(_gameModel);
            this->rebuildModelToViewMap();
            }),
        nullptr
                ));
}
