// LevelConfig.h
#pragma once
#include "CardModel.h"
#include "cocos2d.h"
#include <vector>

struct CardConfig {
    CardFaceType face;
    CardSuitType suit;
    cocos2d::Vec2 position;
};

class LevelConfig {
public:
    std::vector<CardConfig> playFieldConfigs;
    std::vector<CardConfig> stackConfigs;
    cocos2d::Vec2 position; 
};
