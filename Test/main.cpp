#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Player.h"
#include "IniParser.h"

int getPlayerChoice() {
    int choice;
    do {
        std::cout << "Enter your choice (0: Rock, 1: Paper, 2: Scissors): ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
    } while (choice < 0 || choice > 2);
    return choice;
}

std::string getChoiceName(int choice) {
    if (choice == 0) return "Rock";
    if (choice == 1) return "Paper";
    return "Scissors";
}

int main() {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Player player1;
    Player player2;

    std::unordered_map<std::string, std::string> config = parseIniFile("config.ini");

    player1.name = config["Player1"];
    player2.name = config["Player2"];

    player1.wins = 0;
    player1.losses = 0;
    player1.draws = 0;

    player2.wins = 0;
    player2.losses = 0;
    player2.draws = 0;

    int numRounds = std::stoi(config["NumRounds"]);

    std::ofstream outFile("results.txt");
    if (!outFile.is_open()) {
        std::cout << "Error: Unable to open results.txt" << std::endl;
        return 1;
    }

    outFile << player1.name << " vs. " << player2.name << std::endl;
    outFile << "------------------------------" << std::endl;

    for (int round = 1; round <= numRounds; ++round) {
        player1.choice = getPlayerChoice();
        player2.choice = std::rand() % 3;

        if (player1.choice == player2.choice) {
            player1.draws++;
            player2.draws++;
        }
        else if ((player1.choice + 1) % 3 == player2.choice) {
            player1.losses++;
            player2.wins++;
        }
        else {
            player1.wins++;
            player2.losses++;
        }

        outFile << "Round " << round << ": ";
        outFile << player1.name << " chose " << getChoiceName(player1.choice);
        outFile << ", " << player2.name << " chose " << getChoiceName(player2.choice);
        outFile << std::endl;
    }

    outFile << "------------------------------" << std::endl;
    outFile << "Results:" << std::endl;
    outFile << player1.name << " - Wins: " << player1.wins << " Losses: " << player1.losses << " Draws: " << player1.draws << std::endl;
    outFile << player2.name << " - Wins: " << player2.wins << " Losses: " << player2.losses << " Draws: " << player2.draws << std::endl;

    outFile.close();

    std::cout << "Results written to results.txt" << std::endl;

    return 0;
}
