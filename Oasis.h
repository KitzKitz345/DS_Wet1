//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_OASIS_H
#define CODE_OASIS_H

#include "PlayerTree.h"
#include "ClanTree.h"
#include "CoinTree.h"

class Oasis {
    Tree<Player,int>* players;
    Tree<Clan,int>* clans;
    Tree<Player,Pair>* players_by_coins;
    Player* best_player;

public:
    explicit Oasis(); //need to finish constructor
    ~Oasis(); // need to finish destructor
    Oasis(const Oasis& oasis) = delete;
    Tree<Player,int>* getPlayersTree();
    Tree<Player,Pair>* getCoinTree();
    void addClan(int clanID);
};

namespace OasisFuncs {
    void insertPlayer(Oasis* oasis, Player& player);
}

#endif //CODE_OASIS_H
