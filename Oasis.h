//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_OASIS_H
#define CODE_OASIS_H

#include "PlayerTree.h"
#include "ClanTree.h"
#include "Pair.h"
#include "CoinTree.h"

class Oasis {
    Tree<Player,int>* players;
    Tree<Clan,int>* clans;
    Tree<Player,Pair>* players_by_coins;
    Player* best_player;

public:

};

#endif //CODE_OASIS_H
