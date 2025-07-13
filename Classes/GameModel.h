// GameModel.h
#pragma once

#include "CardModel.h"
#include <vector>
#include <memory>
#include <stack>
#include <tuple>

class GameModel {
public:
    GameModel();

    void setPlayFieldCards(const std::vector<std::shared_ptr<CardModel>>& cards);
    void setStackCards(const std::vector<std::shared_ptr<CardModel>>& cards);
    void setBottomCard(std::shared_ptr<CardModel> card);

    const std::vector<std::shared_ptr<CardModel>>& getPlayFieldCards() const;
    const std::vector<std::shared_ptr<CardModel>>& getStackCards() const;
    std::shared_ptr<CardModel> popStackCard(); 
    std::shared_ptr<CardModel> getBottomCard() const;

    void pushUndoState(); 
    void popUndoState();

    bool isStackEmpty() const;

private:
    std::vector<std::shared_ptr<CardModel>> _playFieldCards;
    std::vector<std::shared_ptr<CardModel>> _stackCards;
    std::shared_ptr<CardModel> _bottomCard;


    std::stack<std::tuple<
        std::vector<std::shared_ptr<CardModel>>,
        std::vector<std::shared_ptr<CardModel>>,
        std::shared_ptr<CardModel>>> _undoStack;
};
