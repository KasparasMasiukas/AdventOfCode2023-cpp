#include "day07.h"

#include <sstream>
#include <regex>
#include <unordered_map>
#include <utility>

static bool jokerMode = false;

static std::unordered_map<char, int> cardStrength = {
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7},
    {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12}
};

static std::unordered_map<char, int> cardStrengthWithJoker = {
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7},
    {'T', 8}, {'J', -1}, {'Q', 10}, {'K', 11}, {'A', 12}
};


enum HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

long long findCount(const std::unordered_map<char, int> &cardCount, int count) {
    return std::count_if(cardCount.begin(), cardCount.end(),
                         [count](const auto &cardToCount) {
                             return count == cardToCount.second;
                         });
}

// Convert Jokers to the most common card in hand
std::string convertHandJokers(std::string hand) {
    std::unordered_map<char, int> cardCount;
    int maxCount = 0;
    char maxCard;
    for (const char card: hand) {
        const int count = ++cardCount[card];
        if (card != 'J' && count > maxCount) {
            maxCount = count;
            maxCard = card;
        }
    }
    if (maxCount > 0) {
        std::replace(hand.begin(), hand.end(), 'J', maxCard);
    }
    return hand;
}

HandType handToType(const std::string &originalHand) {
    std::unordered_map<char, int> cardCount;
    const std::string hand = jokerMode ? convertHandJokers(originalHand) : originalHand;
    for (const char card: hand) {
        cardCount[card]++;
    }
    if (findCount(cardCount, 5)) {
        return FIVE_OF_A_KIND;
    }
    if (findCount(cardCount, 4)) {
        return FOUR_OF_A_KIND;
    }
    if (findCount(cardCount, 3) && findCount(cardCount, 2)) {
        return FULL_HOUSE;
    }
    if (findCount(cardCount, 3)) {
        return THREE_OF_A_KIND;
    }
    if (findCount(cardCount, 2) == 2) {
        return TWO_PAIR;
    }
    if (findCount(cardCount, 2)) {
        return ONE_PAIR;
    }
    return HIGH_CARD;
}

class Hand {
public:
    Hand(std::string hand, const int bid) : hand(std::move(hand)), bid(bid), type(handToType(this->hand)) {
    }

    std::string hand;
    int bid;
    HandType type;

    bool operator<(const Hand &other) const {
        auto &cardStrengthMap = jokerMode ? cardStrengthWithJoker : cardStrength;
        if (type != other.type) {
            return type < other.type;
        }
        for (int i = 0; i < hand.length(); ++i) {
            const int thisCardStrength = cardStrengthMap[hand[i]];
            const int otherCardStrength = cardStrengthMap[other.hand[i]];
            if (thisCardStrength != otherCardStrength) {
                return thisCardStrength < otherCardStrength;
            }
        }
        return false;
    }
};

std::vector<Hand> parseAndSortHands(std::istream &input) {
    std::string hand;
    int bid;
    std::vector<Hand> hands;
    while (input >> hand >> bid) {
        hands.emplace_back(hand, bid);
    }
    std::sort(hands.begin(), hands.end());
    return hands;
}

std::string Day07::solveChallenge1(std::istream &input) {
    jokerMode = false;
    long long sum = 0;
    const std::vector<Hand> hands = parseAndSortHands(input);
    for (int i = 0; i < hands.size(); ++i) {
        const int rank = i + 1;
        sum += rank * hands[i].bid;
    }

    return std::to_string(sum);
}

std::string Day07::solveChallenge2(std::istream &input) {
    jokerMode = true;
    long long sum = 0;
    const std::vector<Hand> hands = parseAndSortHands(input);
    for (int i = 0; i < hands.size(); ++i) {
        const int rank = i + 1;
        sum += rank * hands[i].bid;
        std::cout << hands[i].hand << " " << hands[i].type << std::endl;
    }

    return std::to_string(sum);
}
