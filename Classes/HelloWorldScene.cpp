#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "GameController.h"
#include "GameView.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    return HelloWorld::create();
}

bool HelloWorld::init() {
    if (!Scene::init()) return false;

    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1080, 2080, ResolutionPolicy::FIXED_WIDTH);

    auto bgColor = LayerColor::create(Color4B(34, 139, 34, 255)); // 深绿背景
    this->addChild(bgColor, -1);


    auto gameView = GameView::create();
    this->addChild(gameView);


    _gameController = new GameController();
    _gameController->startGame(1, gameView);


    auto undoItem = MenuItemLabel::create(
        Label::createWithSystemFont("Undo", "Arial", 64),
        [=](Ref*) {
            if (_gameController) {
                _gameController->undoLastAction();
            }
        }
    );
    undoItem->setPosition(Vec2(1000, 150));
    auto menu = Menu::create(undoItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    auto testSprite = Sprite::create("res/card_general.png");
    testSprite->setPosition(Vec2(540, 1000)); 
    this->addChild(testSprite);

    return true;
}

