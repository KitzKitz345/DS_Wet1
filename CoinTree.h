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
    operator ==
    operator >
    operator <

};

namespace CoinTree{
    void getScoreBoard(Tree<Player, Pair>* coin_tree, int **players, int *numOfPlayers);
}

/*insertPlayer (player already exists)
 *
removePlayer
unitePlayerTrees
maybe exceptions*/

#endif //CODE_COINTREE_H
