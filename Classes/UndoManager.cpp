// UndoManager.cpp
#include "UndoManager.h"

void UndoManager::recordAction(const UndoAction& action) {
    _undoStack.push_back(action);
}

bool UndoManager::hasUndo() const {
    return !_undoStack.empty();
}

UndoAction UndoManager::popUndo() {
    auto action = _undoStack.back();
    _undoStack.pop_back();
    return action;
}
