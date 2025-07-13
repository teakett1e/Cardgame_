#pragma once

#include "cocos2d.h"
#include <memory>
#include <unordered_map>
#include "GameModel.h"
#include "GameView.h"
#include "CardView.h"
#include "UndoManager.h"

class GameController {
public:
    GameController();

    void startGame(int levelId, GameView* gameView);
    void handleCardClick(CardView* cardView);
    void handleStackCardClick(CardView* cardView);
    void undoLastAction();

private:
    std::shared_ptr<GameModel> _gameModel;
    GameView* _gameView = nullptr;
    UndoManager _undoManager;

    std::unordered_map<CardModel*, CardView*> _modelToViewMap;

    bool canMatch(std::shared_ptr<CardModel> a, std::shared_ptr<CardModel> b);

    void rebuildModelToViewMap();
};
