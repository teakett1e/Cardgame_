// GameModelFromLevelGenerator.cpp
#include "GameModelFromLevelGenerator.h"
#include "CardModel.h"


std::shared_ptr<GameModel> GameModelFromLevelGenerator::generate(const LevelConfig& config) {
    auto gameModel = std::make_shared<GameModel>();

    std::vector<std::shared_ptr<CardModel>> playFieldCards;
    for (const auto& cfg : config.playFieldConfigs) {

        auto card = std::make_shared<CardModel>(cfg.face, cfg.suit);
        card->setInitialPosition(cfg.position); 
        card->setFaceUp(true);  

        playFieldCards.push_back(card);
    }

    std::vector<std::shared_ptr<CardModel>> stackCards;
    for (const auto& cfg : config.stackConfigs) {
        auto card = std::make_shared<CardModel>(cfg.face, cfg.suit);
        card->setInitialPosition(cfg.position);
        card->setFaceUp(false); 

        stackCards.push_back(card);
    }

    gameModel->setPlayFieldCards(playFieldCards);
    gameModel->setStackCards(stackCards);


    if (!stackCards.empty()) {
        auto bottomCard = stackCards.front();
        bottomCard->setFaceUp(true);
        bottomCard->setInitialPosition(cocos2d::Vec2(600, 400));
        gameModel->setBottomCard(bottomCard);
        stackCards.erase(stackCards.begin());
    }

    return gameModel;
}
