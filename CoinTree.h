//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_COINTREE_H
#define CODE_COINTREE_H

#include "PlayerTree.h"

class Pair {
    int id;
    int coin;

public:
    explicit Pair (int id, int coin);
    ~Pair() = default;
    Pair(const Pair& p) = delete;
    bool operator==(const Pair& p) const;
    bool operator>(const Pair& p) const;
/*  bool operator<(const Pair& p) const;       is needed??*/

};

namespace CoinTree{
    void getScoreBoard(Tree<Player, Pair>* coin_tree, int **players, int *numOfPlayers);
    void insertPlayerByCoin(Tree<Player, Pair>* coin_tree, Pair& key, Player& player);
    void removePlayer(Tree<Player, Pair>* coin_tree, int playerId, int coins);
    void deleteTree(Tree<Player, Pair>* coin_tree);
}


/*
unitePlayerTrees
maybe exceptions*/

#endif //CODE_COINTREE_H
