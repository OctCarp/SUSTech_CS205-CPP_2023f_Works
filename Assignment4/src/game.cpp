#ifndef ASSIGN4_INTEGRATED

#include "util.hpp"
#include "game.hpp"

#endif

namespace uno {

    Game::Game(std::initializer_list<Player *> players) {
        size_t sz = players.size();
        if (sz < 2 || sz > 4) {
            throw std::invalid_argument("Invalid number of players");
        }
        this->players = players;
        this->playerNum = (int) sz;
    }

    inline int Game::get_next_player() const {
        if (direction == -1) {
            return (current_player_index == 0 ? playerNum - 1 : (current_player_index - 1));
        } else {
            return (current_player_index == playerNum - 1 ? 0 : (current_player_index + 1));
        }
    }

    void Game::setup() {
        skip = false;
        draw_two = false;

        draw.push(new NumberCard("B", 0));
        draw.push(new NumberCard("R", 0));
        for (int i = 0; i < 2; ++i) {
            for (int val = 1; val <= 9; ++val) {
                draw.push(new NumberCard("B", val));
                draw.push(new NumberCard("R", val));
            }
            draw.push(new SkipCard("B"));
            draw.push(new SkipCard("R"));
            draw.push(new ReverseCard("B"));
            draw.push(new ReverseCard("R"));
            draw.push(new DrawTwoCard("B"));
            draw.push(new DrawTwoCard("R"));
        }
        shuffle_stack(draw);

        std::default_random_engine e;
        std::uniform_int_distribution<int> u(0, this->playerNum - 1);
        e.seed(time(nullptr));
        this->current_player_index = u(e);

        for (int i = 0; i < 7; ++i) {
            for (int playerId = 0; playerId < playerNum; ++playerId) {
                players[playerId]->hand.push_back(get_top_draw_out());
            }
        }
        discard.push(get_top_draw_out());
        current_player_index = get_next_player();
    }

    bool Game::play() {
        Player *curPlayer = players[current_player_index];
        if (skip) {
            curPlayer->hand.push_back(get_top_draw_out());
            skip = false;
        } else {
            if (draw_two) {
                for (int i = 0; i < 2; ++i) {
                    curPlayer->hand.push_back(get_top_draw_out());
                }
                draw_two = false;
            } else {
                const Card *out = nullptr;
                for (auto it = curPlayer->hand.begin(); it != curPlayer->hand.end(); ++it) {
                    if ((*it)->is_available(*this)) {
                        out = *it;
                        curPlayer->hand.erase(it);
                        break;
                    }
                }

                if (out != nullptr) {
                    out->effect(*this);
                    discard.push(out);
                } else {
                    const Card *drawOut = this->get_top_draw_out();
                    curPlayer->hand.push_back(drawOut);
                }

                if (curPlayer->hand.empty()) {
                    current_player_index = get_next_player();
                    return true;
                }
            }
        }
        current_player_index = get_next_player();
        return false;
    }

    std::string Game::get_winner() const {
        Player *winner = nullptr;
        int score_sum = 0;
        for (Player *player: players) {
            if (player->hand.empty()) {
                winner = player;
                continue;
            }

            int player_score = 0;
            for (const Card *card: player->hand) {
                player_score += card->get_point();
            }
            score_sum += player_score;
        }

        if (winner == nullptr) {
            return "";
        }
        return winner->name + " (" + std::to_string(score_sum) + ")";
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        os << "Draw: " << stack_to_string(game.draw) << std::endl;
        os << "Discard: " << stack_to_string(game.discard) << std::endl;
        os << "Current: " << game.players[game.current_player_index]->getName() << std::endl;
        os << "Direction: " << (game.direction == -1 ? "Left" : "Right") << std::endl;
        for (Player *player: game.players) {
            os << player->to_string() << std::endl;
        }

        return os;
    }

    const Card *Game::get_top_draw_out() {
        if (draw.empty()) {
            const Card *top_discard = discard.top();
            discard.pop();

            swap(discard, draw);
            discard.push(top_discard);

            shuffle_stack(draw);
        }
        const Card *out = draw.top();
        draw.pop();

        return out;
    }
}

