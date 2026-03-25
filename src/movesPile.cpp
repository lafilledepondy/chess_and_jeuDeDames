// ==============================================================================
// MOVESPILE 
// ==============================================================================

#include "movesPile.hpp"

std::string MovesPile::backMove() const {
    if (_history.empty()) return "";

    const MoveRecord& move = _history.top();
    return move.from.toString() + " -> " + move.to.toString();
}

bool MovesPile::empty() const {
    return size() == 0;
}

std::size_t MovesPile::size() const {
    return _history.size();
}

void MovesPile::clear() {
    while (!_history.empty()) {
        _history.pop();
    }
}

void MovesPile::push(const MoveRecord& move) {
    _history.push(move);
}

const MoveRecord& MovesPile::top() const {
    return _history.top();
}

MoveRecord MovesPile::pop() {
    MoveRecord move = _history.top();
    _history.pop();
    return move;
}

bool MovesPile::canUndo() const {
    return !_history.empty();
}