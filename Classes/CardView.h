#pragma once

#include "cocos2d.h"
#include "CardModel.h"
#include <functional>

class CardView : public cocos2d::Sprite {
public:
    static CardView* createWithModel(std::shared_ptr<CardModel> model);

    void updateTexture(); 
    void setClickCallback(const std::function<void(CardView*)>& callback);

    std::shared_ptr<CardModel> getModel() const;

private:
    std::shared_ptr<CardModel> _model;
    std::function<void(CardView*)> _clickCallback;

    bool initWithModel(std::shared_ptr<CardModel> model);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
};
