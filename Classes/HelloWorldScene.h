// HelloWorldScene.h
#pragma once

#include "cocos2d.h"

class GameController;

class HelloWorld : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

private:
    GameController* _gameController = nullptr;

};
