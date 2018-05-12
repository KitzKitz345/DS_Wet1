//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_PLAYERTREE_H
#define CODE_PLAYERTREE_H

#include "Tree.h"

class Player {
    int player_id;
    int coins;
    int challenges;
    int clan_id;

public:
    explicit Player(int id, int coins, int challenges, int clan_id);
    ~Player();
    Player(const Player& player) = delete;
    int getPlayerId();
    int getCoins();
    int getChallenges();
    int getClanId();
    void setClanId(int new_id);
    void addCoins(int coins);
    void incChallenges();
};

namespace PlayerTree {
    void insertPlayer(Tree<Player, int>* player_tree, Player& player);
    void completeChallenge(Tree<Player, int>* player_tree, int playerId, int coins);
}


/*
removePlayer
unitePlayerTrees
maybe exceptions*/

#endif //CODE_PLAYERTREE_H
