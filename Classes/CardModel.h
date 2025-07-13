// CardModel.h
#pragma once

#include <vector>
#include <memory>
#include "cocos2d.h"

enum class CardSuitType {
    NONE = -1,
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
    NUM_TYPES
};

enum class CardFaceType {
    NONE = -1,
    TWO, THREE, FOUR, FIVE, SIX, SEVEN,
    EIGHT, NINE, TEN,
    NUM_TYPES
};


class CardModel {
public:
    CardModel(CardFaceType face, CardSuitType suit, bool faceUp = true);

    CardFaceType getFace() const;
    CardSuitType getSuit() const;
    bool isFaceUp() const;
    void setFaceUp(bool faceUp);

    int getCardValue() const;  


    void addCoveringCard(std::shared_ptr<CardModel> card);   
    void removeCoveringCard(std::shared_ptr<CardModel> card);
    bool isCovered() const;

    void setInitialPosition(const cocos2d::Vec2& pos) { _initialPosition = pos; }
    cocos2d::Vec2 getInitialPosition() const { return _initialPosition; }

private:
    CardFaceType _face;
    CardSuitType _suit;
    bool _faceUp;


    std::vector<std::weak_ptr<CardModel>> _coveringCards;
    cocos2d::Vec2 _initialPosition;
};
