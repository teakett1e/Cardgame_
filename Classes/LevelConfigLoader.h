#pragma once

#include "LevelConfig.h"
#include <string>

class LevelConfigLoader {
public:
    static LevelConfig loadFromJson(const std::string& path);
};
