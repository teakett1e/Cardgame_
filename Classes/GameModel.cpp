// GameModel.cpp
#include "GameModel.h"
#include <tuple>
#include <vector>
#include <memory>


GameModel::GameModel() {}

void GameModel::setPlayFieldCards(const std::vector<std::shared_ptr<CardModel>>& cards) {
    _playFieldCards = cards;
}

void GameModel::setStackCards(const std::vector<std::shared_ptr<CardModel>>& cards) {
    _stackCards = cards;
}

void GameModel::setBottomCard(std::shared_ptr<CardModel> card) {
    _bottomCard = card;
}

const std::vector<std::shared_ptr<CardModel>>& GameModel::getPlayFieldCards() const {
    return _playFieldCards;
}

const std::vector<std::shared_ptr<CardModel>>& GameModel::getStackCards() const {
    return _stackCards;
}

std::shared_ptr<CardModel> GameModel::getBottomCard() const {
    return _bottomCard;
}

void GameModel::pushUndoState() {
    _undoStack.push(std::make_tuple(_playFieldCards, _stackCards, _bottomCard));
}

void GameModel::popUndoState() {
    if (_undoStack.empty()) return;
    std::tie(_playFieldCards, _stackCards, _bottomCard) = _undoStack.top();
    _undoStack.pop();
}


std::shared_ptr<CardModel> GameModel::popStackCard() {
    if (_stackCards.empty()) return nullptr;
    auto card = _stackCards.front();
    _stackCards.erase(_stackCards.begin());
    return card;
}

bool GameModel::isStackEmpty() const {
    return _stackCards.empty();
}