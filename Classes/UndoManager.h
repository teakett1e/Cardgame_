// UndoManager.h
#pragma once

#include "CardModel.h"
#include <vector>
#include <memory>
#include "cocos2d.h" 

struct UndoAction {
    std::shared_ptr<CardModel> fromCard;
    std::shared_ptr<CardModel> toCard;
    cocos2d::Vec2 fromPos;
    cocos2d::Vec2 toPos;
};

class UndoManager {
public:
    void recordAction(const UndoAction& action);
    bool hasUndo() const;
    UndoAction popUndo();

private:
    std::vector<UndoAction> _undoStack;
};
