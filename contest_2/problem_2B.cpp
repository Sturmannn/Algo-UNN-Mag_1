#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

struct Player {
    uint32_t efficiency;
    uint32_t number;
};

bool CompareEfficiencyPlayers(const Player& a, const Player& b) {
    return a.efficiency < b.efficiency;
}

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint32_t players_count = 0;
    std::cin >> players_count;

    std::vector<Player> players(players_count);

    for (size_t ind = 0; ind < players_count; ++ind) {
        players[ind].number = ind + 1;
        std::cin >> players[ind].efficiency;
    }

    if (players_count == 0) {
        return 0;
    }

    std::sort(players.begin(), players.end(), CompareEfficiencyPlayers);

    uint32_t left = 0;

    int32_t best_left = 0;
    int32_t best_right = -1;

    uint64_t current_sum = 0;
    uint64_t max_sum = 0;

    for (size_t rigth = 0; rigth < players_count; ++rigth) {
        current_sum += players[rigth].efficiency;

        while (left + 1 < rigth && static_cast<uint64_t>(players[rigth].efficiency) >
                                       static_cast<uint64_t>(players[left].efficiency) +
                                           static_cast<uint64_t>(players[left + 1].efficiency)) {
            current_sum -= players[left].efficiency;
            left++;
        }

        if (current_sum > max_sum) {
            best_left = left;
            best_right = rigth;
            max_sum = current_sum;
        }
    }

    std::cout << max_sum << '\n';

    std::vector<uint32_t> best_players;
    for (int32_t ind = best_left; ind <= best_right; ++ind) {
        best_players.push_back(players[ind].number);
    }

    std::sort(best_players.begin(), best_players.end());

    int32_t best_players_count = static_cast<int32_t>(best_players.size());
    for (int32_t ind = 0; ind < best_players_count; ++ind) {
        std::cout << best_players[ind] << (ind == best_players_count - 1 ? '\n' : ' ');
    }

    return 0;
}
