// CardModel.cpp
#include "CardModel.h"
#include <algorithm>

CardModel::CardModel(CardFaceType face, CardSuitType suit, bool faceUp)
    : _face(face), _suit(suit), _faceUp(faceUp) {
    // 不处理贴图
}


CardFaceType CardModel::getFace() const {
    return _face;
}

CardSuitType CardModel::getSuit() const {
    return _suit;
}

bool CardModel::isFaceUp() const {
    return _faceUp;
}

void CardModel::setFaceUp(bool faceUp) {
    _faceUp = faceUp;
}

int CardModel::getCardValue() const {
    int raw = static_cast<int>(_face);
    return raw + 1; 
}


void CardModel::addCoveringCard(std::shared_ptr<CardModel> card) {
    _coveringCards.push_back(card);
}

void CardModel::removeCoveringCard(std::shared_ptr<CardModel> card) {
    _coveringCards.erase(std::remove_if(_coveringCards.begin(), _coveringCards.end(),
        [&](const std::weak_ptr<CardModel>& w) {
            return w.lock() == card;
        }), _coveringCards.end());
}

bool CardModel::isCovered() const {
    for (const auto& w : _coveringCards) {
        if (w.lock()) return true;
    }
    return false;
}
