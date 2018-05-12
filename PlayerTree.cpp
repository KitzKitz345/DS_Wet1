//
// Created by Nitzan on 06/05/2018.
//

#include "PlayerTree.h"

explicit Player::Player(int id, int coins, int challenges, int clan_id) : player_id(id),
                        coins(coins), challenges (challenges), clan_id(clan_id) {}

int Player::getPlayerId() {
    return this->player_id;
}

int Player::getCoins() {
    return this->coins;
}

int Player::getChallenges() {
    return this->challenges;
}

int Player::getClanId() {
    return this->clan_id;
}

void Player::setClanId(int new_id) {
    this->clan_id = new_id;
}

void Player::addCoins(int coins) {
    this->coins += coins;
}

void Player::incChallenges() {
    this->challenges++;
}

void PlayerTree::insertPlayer (Tree<Player, int>* player_tree, Player& player) {
    int player_id = player.getPlayerId();
    player_tree->insert(player_id,player);
}