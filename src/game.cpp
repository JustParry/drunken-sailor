// "game.cpp" will handle most in-game logic
// Includes necessary libraries
#include "game.h"
#include <iostream>
#include <algorithm>
#include <random>

// shuffles deck
void shuffleDeck(std::vector<std::string>& deck) {
    std::random_device rd;
    // I hate mersenne twister 19937, why so specific???
    std::mt19937 g(rd());
    // this allows for shuffling the deck given random seed given by function above
    std::shuffle(deck.begin(), deck.end(), g);
    std::cout << "Shuffled deck." << std::endl;
}

// deals one card from the deck to the hand
void hit(std::vector<std::string>& deck, std::vector<std::string>& hand, int& ace) {
    std::string card = deck.back();
    // remove the last card from the deck and add it to the hand
    deck.pop_back();
    hand.push_back(card);
    // check if the card is an ace
    std::cout << card << std::endl;
    if (card.find("A") != std::string::npos) {
        ace ++;    
    }

    // tells user the card has been dealt
}

// splits hand if possible
std::vector<std::string>& split(std::vector<std::string>& hand, int& bet, int& aces1, int& aces2) {
    // check if the player can split
    std::vector<char> v1(hand[0].begin(), hand[0].end());
    std::vector<char> v2(hand[1].begin(), hand[1].end());
    if (hand.size() == 2 && v1[0] == v2[0]) {
        std::vector<std::string> newHand;
        // create a new hand for the split
        newHand.push_back(hand.back());
        hand.pop_back();
        
        // checks if the cards are both aces
        if (hand[0] == "A") {
            aces1 -= 1;
            aces2 += 1;
        }

        // double the bet for the new hand
        bet *= 2;

        std::cout << "Split hand. New bet: " << bet << std::endl;
        return newHand;
    }
    
    // returns why they can't split (in case they skipped the rules)
    else {
        std::cout << "Cannot split unless cards are the same value." << std::endl;
    }
}

// checks if the player wins or loses
bool checkWin(std::vector<std::string>& dealerHand, std::vector<std::string>& playerHand) {
    // check if the player wins or loses
    int playerScore = 0;
    int dealerScore = 0;
    int playerAces = 0;
    int dealerAces = 0;
    // calculate the score for the player
    for (const auto& card : playerHand) {
        if (card.find("A") != std::string::npos) {
            playerScore += 11;
            playerAces += 1;
        } else if (card.find("K") || card.find("Q") || card.find("J") != std::string::npos) {
            playerScore += 10;
        } else {
            playerScore += std::stoi(card);
        }
    }

    // calculate the score for the dealer
    for (const auto& card : dealerHand) {
        if (card.find("A") != std::string::npos) {
            dealerScore += 11;
            dealerAces += 1;
        } else if (card.find("K") || card.find("Q") || card.find("J") != std::string::npos) {
            dealerScore += 10;
        } else {
            dealerScore += std::stoi(card);
        }
    }
    for (int i = 0; i < playerAces; i++) {
        if (playerScore > 21) {
            playerScore -= 10;
        }
    }
    for (int i = 0; i < dealerAces; i++) {
        if (dealerScore > 21) {
            dealerScore -= 10;
        }
    }
    // check if the player wins or loses
    if (checkBust(playerHand)) {
        std::cout << "Player busts. Dealer wins." << std::endl;
        return false;
    } else if (checkBust(dealerHand)) {
        std::cout << "Dealer busts. Player wins." << std::endl;
        return true;
    } else if (playerScore > dealerScore) {
        std::cout << "Player wins." << std::endl;
        return true;
    }else if (playerScore < dealerScore) {
        std::cout << "Dealer wins." << std::endl;
        return false;
    } else {
        std::cout << "Dealer wins on ties." << std::endl;
        return false;
    }
}

// checks if the player (or dealer) busts
bool checkBust(std::vector<std::string>& hand) {
    int score = 0;
    int savedAces = 0;
    // calculate the score for the hand
    for (const auto& card : hand) {
        if (card.find("A") != std::string::npos) {
            score += 11;
            savedAces+= 1;
        }
        else if (card.find("K") || card.find("Q") || card.find("J") != std::string::npos) {
            score += 10;
        } else {
            // convert the card to an integer and add it to the score
            std::vector<char> v(card.begin(), card.end());
            std::string num(v[0], v[1]);
            score += std::stoi(num);
        }
    }

    // check if the hand busts
    if (score > 21 && savedAces <= 0) {
        std::cout << "Hand busts." << std::endl;
        return true;
    }
    else if (score > 21 && savedAces > 0) {
        // if the hand busts, check if there are any aces
        // if there are, subtract 10 from the score for each ace
        for (int i = 0; i < savedAces; i++) {
            score -= 10;
            if (score <= 21) {
                return false;
            }
        }
        if (score > 21) {
            std::cout << "Hand busts." << std::endl;
            return true;
        }
    }
    return false;
}

// Note: The above code is made based only on personal experience and knowledge.
// there are very different versions of this very popular game.
// The code is not guaranteed to be correct or complete.
// The code is not guaranteed to be free of bugs or errors.
// The code is not guaranteed to be free of security vulnerabilities.
// With all of this said, please feel free to use this code as reference for anything
// you may need, and make sure to link this github under the credits of your project.