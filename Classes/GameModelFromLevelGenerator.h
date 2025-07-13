// GameModelFromLevelGenerator.h
#pragma once

#include "GameModel.h"
#include "LevelConfig.h"

class GameModelFromLevelGenerator {
public:

    static std::shared_ptr<GameModel> generate(const LevelConfig& config);
};
