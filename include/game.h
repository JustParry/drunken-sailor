#ifndef GAME_H
#define GAME_H

// Includes necessary libraries
#include <string>
#include <vector>

//shuffles deck
void shuffleDeck(std::vector<std::string>& deck);

// deals cards
void hit(std::vector<std::string>& deck, std::vector<std::string>& hand, int& ace);

// checks if the player can split, then splits if able
std::vector<std::string>& split(std::vector<std::string>& hand, int& bet, int&aces1, int&aces2);


// checks if the player wins or loses
bool checkWin(std::vector<std::string>& dealerHand, std::vector<std::string>& playerHand);

// checks if the player (or dealer) busts
bool checkBust(std::vector<std::string>& hand);
#endif