// GameView.h
#pragma once

#include "cocos2d.h"
#include "GameModel.h"
#include "CardView.h"

class GameView : public cocos2d::Node {
public:
    CREATE_FUNC(GameView);

    void showGame(const std::shared_ptr<GameModel>& gameModel);
    void setCardClickCallback(const std::function<void(CardView*)>& callback);
    void setStackCardClickCallback(const std::function<void(CardView*)>& callback);

private:
    std::function<void(CardView*)> _onCardClick;
    std::function<void(CardView*)> _onStackCardClick;

    bool init() override;
};
