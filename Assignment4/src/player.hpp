#ifndef ASSIGN4_INTEGRATED
#pragma once
#endif

#include <string>
#include <utility>
#include <vector>

#ifndef ASSIGN4_INTEGRATED

#include "card.hpp"

#endif

namespace uno {

    class Player {
    private:
        /**
         * @brief The name of the player
         */
        std::string name;

        /**
         * @brief The cards in the player's hand
         */
        std::vector<const Card *> hand;

    public:
        /**
         * @brief Creates a new player with the given name
         * @param name The name of the player
         */
        explicit Player(std::string name);

        /**
         * @brief Get the player name
         * @return Player name string
         */
        std::string getName();

        /**
         * @brief Get the player name with their cards in hand
         * @return Player information string
         */
        std::string to_string();

        friend class Game;
    };
}
