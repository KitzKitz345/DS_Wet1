//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_PLAYERTREE_H
#define CODE_PLAYERTREE_H

#include "Tree.h"
#include "ClanTree.h"

class Player {
    int player_id;
    int coins;
    int challenges;
    Clan* clan;

public:
    explicit Player (int id, int coins, int challenges, Clan* clan) : player_id(id), coins(coins),
             challenges (challenges), clan(nullptr){}

    ~Player();

    Player(const Player& player) = delete;

    int getPlayerId() {
        return this->player_id;
    }
    int getCoins() {
        return this->coins;
    }
    int getChallenges() {
        return this->challenges;
    }
    Clan* getClan() {
        return this->clan;
    }
    void addCoins(int coins) {
        this->coins += coins;
    }
    void incChallenges() {
        this->challenges++;
    }
};

//should new_player tree needs *?
void addPlayer (Tree<Player, int>* player_tree, int player_id, int coins) {
    Player* new_player = new Player(player_id,coins,0,nullptr);
    player_tree->insert(player_id,*new_player);
}

/*
removePlayer
unitePlayerTrees
maybe exceptions*/

#endif //CODE_PLAYERTREE_H
