#include <stack>

#ifndef ASSIGN4_INTEGRATED

#include "util.hpp"
#include "player.hpp"

#endif

namespace uno {
    Player::Player(std::string name) : name(std::move(name)) {}

    std::string Player::to_string() {
        std::string res = this->name + ": ";
        std::stack<const Card *> handStack;

        for (const Card *card: this->hand) {
            handStack.push(card);
        }

        res += stack_to_string(handStack);

        return res;
    }

    std::string Player::getName() {
        return name;
    }
}
