#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Player {
    std::string name;
    int wins;
    int losses;
    int draws;
    int choice; // 0: Rock, 1: Paper, 2: Scissors
};

#endif // PLAYER_H
