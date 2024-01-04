#ifndef ASSIGN4_INTEGRATED

#include "game.hpp"
#include "card.hpp"

#endif

#include <utility>

namespace uno {
    Card::Card(std::string color) : color(std::move(color)) {}

    bool Card::is_available(const Game &game) const {
        if (game.discard.empty()) { return false; }

        const Card *top_card = game.discard.top();
        if (this->color == top_card->get_color() or this->get_point() == top_card->get_point()) {
            return true;
        }

        return false;
    }

    NumberCard::NumberCard(std::string color, int number) : Card(std::move(color)), number(number) {}

    std::string NumberCard::to_string() const {
        return std::to_string(number) + color;
    }

    const int NumberCard::get_point() const {
        return number;
    }


    void NumberCard::effect(Game &game) const {}

    SkipCard::SkipCard(std::string color) : Card(std::move(color)) {}

    std::string SkipCard::to_string() const {
        return "S" + color;
    }

    const int SkipCard::get_point() const {
        return 20;
    }

    void SkipCard::effect(Game &game) const {
        game.skip = true;
    }

    ReverseCard::ReverseCard(std::string color) : Card(std::move(color)) {}

    std::string ReverseCard::to_string() const {
        return "R" + color;
    }

    const int ReverseCard::get_point() const {
        return 30;
    }

    void ReverseCard::effect(Game &game) const {
        game.direction = (game.direction == -1 ? 1 : -1);
    }

    DrawTwoCard::DrawTwoCard(std::string color) : Card(std::move(color)) {}

    std::string DrawTwoCard::to_string() const {
        return "D" + color;
    }

    const int DrawTwoCard::get_point() const {
        return 40;
    }

    void DrawTwoCard::effect(Game &game) const {
        game.draw_two = true;
    }
}
