#include "LevelConfigLoader.h"
#include "json/document.h"  // 使用 rapidjson
#include "cocos2d.h"

USING_NS_CC;
using namespace rapidjson;

static CardFaceType parseFace(int val) {
    return static_cast<CardFaceType>(val);
}

static CardSuitType parseSuit(int val) {
    return static_cast<CardSuitType>(val);
}

LevelConfig LevelConfigLoader::loadFromJson(const std::string& path) {
    LevelConfig config;

    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    std::string jsonData = FileUtils::getInstance()->getStringFromFile(fullPath);

    CCLOG("Load JSON from: %s", fullPath.c_str());
    CCLOG("JSON content: %s", jsonData.c_str());

    Document doc;
    doc.Parse(jsonData.c_str());
    if (doc.HasParseError()) {
        CCLOG("JSON parse error: %s", path.c_str());
        return config;
    }

    // 读取主牌堆
    const auto& playfield = doc["Playfield"];
    for (SizeType i = 0; i < playfield.Size(); ++i) {
        const auto& obj = playfield[i];
        CardConfig cc;
        cc.face = parseFace(obj["CardFace"].GetInt());
        cc.suit = parseSuit(obj["CardSuit"].GetInt());
        cc.position = Vec2(obj["Position"]["x"].GetFloat(), obj["Position"]["y"].GetFloat());
        config.playFieldConfigs.push_back(cc);
    }

    // 读取备用堆
    const auto& stack = doc["Stack"];
    for (SizeType i = 0; i < stack.Size(); ++i) {
        const auto& obj = stack[i];
        CardConfig cc;
        cc.face = parseFace(obj["CardFace"].GetInt());
        cc.suit = parseSuit(obj["CardSuit"].GetInt());
        cc.position = Vec2(obj["Position"]["x"].GetFloat(), obj["Position"]["y"].GetFloat());
        config.stackConfigs.push_back(cc);
    }

    return config;
}
