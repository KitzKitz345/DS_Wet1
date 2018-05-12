//
// Created by Nitzan on 12/05/2018.
//

#include "Oasis.h"

explicit Oasis::Oasis() : best_player(nullptr) {

}

void Oasis::insertPlayer(Player& player) {
    PlayerTree::insertPlayer(this->players, player);
    CoinTree::insertPlayerByCoin(this->players_by_coins, player);
}

void Oasis::completeChallenge(int playerId, int coins) {
    PlayerTree::completeChallenge(this->players, playerId, coins);
    CoinTree::completeChallenge(this->players_by_coins, playerId, coins);
}