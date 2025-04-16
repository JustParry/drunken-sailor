// This is the file to run the game from.
// Please feel free to use this code as reference for anything
// If you find any errors or bugs, please let me know.

// Includes necessary libraries
#include "game.h"
#include <iostream>
#include <vector>
#include<string>

// Deck of cards
std::vector<std::string> old_deck = {
    "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH", "AH",
    "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD", "AD",
    "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC", "AC",
    "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS", "AS"
};

// Variables
std::vector<std::string> playerHand = {};
std::vector<std::string> dealerHand = {};
std::vector<std::string> splitHand = {};    
int playerAces = 0;
int splitAces = 0;
int dealerAces = 0;
int dealerScore = 0;
int main() {
    // introduces the game!
    char answer;
    std::cout << "Welcome to Blackjack!\nWould you like to hear the rules? (Y/N)" << std::endl;
    std::cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        std::cout << "1. The goal is to get as close to 21 as possible without going over." << std::endl;
        std::cout << "2. Face cards are worth 10, Aces can be worth 1 or 11." << std::endl;
        std::cout << "3. You can hit (take another card), stand (keep your current hand), ";
        std::cout << "double down (double your bet and take one more card, then stand), or split (if you have two of the same card, can only split ONCE)." << std::endl;
        std::cout << "4. The dealer must hit until they reach 17." << std::endl;
        std::cout << "5. If you bust (go over 21), you lose." << std::endl;
        std::cout << "6. If the dealer busts, you win." << std::endl;
        std::cout << "7. If you and the dealer have the same score, it's a push (no one wins)." << std::endl;
        std::cout << "You start with $50. No bet can go under $1 or have decimals in it." << std::endl;
        std::cout << "Try to get a high score, good luck!\n\n" << std::endl;
    }

    // Sets up the game appropriately
    int bet{0};
    std::vector<std::string> playerHand;
    std::vector<std::string> dealerHand;
    std::vector<std::string> splitHand;
    std::vector<std::string> deck;
    bool gameRunning = true;
    bool playerTurn = false;
    bool playerBusted = false;
    bool dealerBusted = false;
    bool playerWin = false;
    int playerFunds = 50;


    // Main game loop
    while (gameRunning) {
        // Resets the hands and aces
        playerHand.clear();
        dealerHand.clear();
        splitHand.clear();    
        playerAces = 0;
        splitAces = 0;
        dealerAces = 0;
        dealerScore = 0;

        // Shows wallet as well as other options
        std::cout << "You have $" << playerFunds << ". How much would you like to bet? (any integer 1 - " << playerFunds << ")" << std::endl;
        std::cout << "Enter 0 to quit. " << std::endl;
        std::cin >> bet;
        if (bet == 0) {
            std::cout << "Thanks for playing!" << std::endl;
            gameRunning = false;
            continue;
        }
        else if (bet < 1 || bet > playerFunds) {
            std::cout << "Invalid bet. Please enter a valid amount." << std::endl;
            continue;
        }
        playerFunds -= bet;
        std::cout << "You bet $" << bet << "." << std::endl;
        playerTurn = true;
        
        // Shuffles the deck
        deck = old_deck;
        shuffleDeck(deck);

        // deals two cards to the player and dealer
        hit(deck, playerHand, playerAces);
        hit(deck, playerHand, playerAces);
        hit(deck, dealerHand, playerAces);
        hit(deck, dealerHand, playerAces);

        // Starts player's turn
        while (playerTurn) {
            if (checkBust(playerHand)) {
                std::cout << "You busted! Dealer wins." << std::endl;
                playerBusted = true;
                playerTurn = false;
                break;
            }
            std::cout << "Your hand: ";
            for (const auto& card : playerHand) {
                std::cout << card << " ";
            }
            std::cout << std::endl;
            std::cout << "Dealer's Hand: ";
            for (const auto& card : dealerHand) {
                std::cout << card << " ";
            }
            std::cout << std::endl;
            std::cout << "Would you like to hit (H), stand (S), double down (D), split (P), or quit (Q)? ";
            std::cin >> answer;
            switch(answer) {
                case 'H':
                case 'h':
                    hit(deck, playerHand, playerAces);
                    break;

                case 'S':
                case 's':
                    playerTurn = false;
                    break;

                case 'D':
                case 'd':
                    if (playerFunds < bet) {
                        std::cout << "Not enough funds to double down." << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Doubling down." << std::endl;
                        playerFunds -= bet;
                        bet *= 2;
                        hit(deck, playerHand, playerAces);
                        playerTurn = false;
                        break;
                    }

                case 'P':
                case 'p':
                    if (playerFunds < bet) {
                        std::cout << "Not enough funds to split." << std::endl;
                        break;
                    }

                    // I don't want to rewrite everything... note to self: complete complex things first
                    else {
                        std::cout << "Splitting hand." << std::endl;
                        playerFunds -= bet;
                        splitHand = split(playerHand, bet, playerAces, splitAces);
                        
                        while (playerTurn) {
                            if (checkBust(splitHand)) {
                                std::cout << "Split hand busted! Dealer wins." << std::endl;
                                playerTurn = false;
                            }
                            std::cout << "Your split hand: ";
                            for (const auto& card : splitHand) {
                                std::cout << card << " ";
                            }
                            std::cout << std::endl;
                            std::cout << "Would you like to hit (H), or stand (S)? ";
                            std::cin >> answer;
                            switch(answer) {
                                case 'H':
                                case 'h':
                                    hit(deck, splitHand, splitAces);
                                    break;
                                case 'S':
                                case 's':
                                    playerTurn = false;
                                    break;
                                default:
                                    std::cout << "Invalid option. Please enter H, or S." << std::endl;
                                    break;
                            }
                        }
                        playerTurn = true;
                    }
                    break;
                case 'Q':
                case 'q':
                    std::cout << "Thanks for playing!" << std::endl;
                    gameRunning = false;
                    playerTurn = false;
                    break;
                default:
                    std::cout << "Invalid option. Please enter H, S, D, P, or Q." << std::endl;
                    break;
            }
        }

        // Dealer's turn
        if (!playerBusted) {
            while (!checkBust(dealerHand)) {
                std::cout << "Dealer's hand: ";
                for (const auto& card : dealerHand) {
                    std::cout << card << " ";
                }
                std::cout << std::endl;
                if (dealerScore < 17) {
                    hit(deck, dealerHand, dealerAces);
                
                }
                else {
                    std::cout << "Dealer stands." << std::endl;
                    break;
                }
            }
        }

        // Sees who wins!!!
        if (checkWin(dealerHand, playerHand)) {
            std::cout << "You win!" << std::endl;
            playerFunds += bet * 2;
        } 
        else {
            std::cout << "Dealer wins!" << std::endl;
        }
    }
}
