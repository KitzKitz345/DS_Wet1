//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_CLANTREE_H
#define CODE_CLANTREE_H

#include "PlayerTree.h"
#include "Tree.h"
#include "Pair.h"

class Clan {
    int clan_id;
    Tree<Player,int>* players;
    Tree<Player,Pair>* players_by_coins;
    Player* best_player;

public:
    int getClanId() {

    }
    Player& getBestPlayer() {

    }
    void setBestPlayer() {

    }

    //addPlayerToClan

};

/*addClan
removeClan
uniteClanTrees
maybe exceptions*/

#endif //CODE_CLANTREE_H
