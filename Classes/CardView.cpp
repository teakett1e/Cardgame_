#include "CardView.h"

USING_NS_CC;

CardView* CardView::createWithModel(std::shared_ptr<CardModel> model) {
    CardView* ret = new (std::nothrow) CardView();
    if (ret && ret->initWithModel(model)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::initWithModel(std::shared_ptr<CardModel> model) {
    _model = model;


    this->init();

    this->setScale(0.5f);

    this->setAnchorPoint(Vec2(0.5f, 0.5f));

    updateTexture();


    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->setContentSize(Size(120, 160)); 
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->setScale(0.5f);
    this->setPosition(_model->getInitialPosition());
    return true;
}

bool CardView::onTouchBegan(Touch* touch, Event* event) {
    Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
    Size s = this->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);

    if (rect.containsPoint(locationInNode)) {
        if (_clickCallback) {
            _clickCallback(this);
        }
        return true;
    }
    return false;
}

void CardView::setClickCallback(const std::function<void(CardView*)>& callback) {
    _clickCallback = callback;
}

std::shared_ptr<CardModel> CardView::getModel() const {
    return _model;
}

void CardView::updateTexture() {
    this->setTexture("");
    this->removeAllChildren();
    if (!_model) return;

    this->removeAllChildren(); 

    if (_model->isFaceUp()) {
        int face = _model->getCardValue(); 
        std::string faceStr = std::to_string(face);

        CardSuitType suit = _model->getSuit();
        std::string color = (suit == CardSuitType::HEARTS || suit == CardSuitType::DIAMONDS)
            ? "red" : "black";

        std::string path = "res/number/big_" + color + "_" + faceStr + ".png";
        this->setTexture(path);
    }
    else {
       
        auto drawNode = DrawNode::create();
        drawNode->drawSolidRect(Vec2(0, 0), Vec2(120, 160), Color4F(0.4f, 0.4f, 0.4f, 1.0f));
        this->addChild(drawNode);

        this->setTexture(""); 
        this->setContentSize(Size(120, 160));
    }

    this->setScale(0.5f);
}
