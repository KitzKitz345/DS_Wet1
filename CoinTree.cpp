//
// Created by Nitzan on 06/05/2018.
//

#include <cstdlib>
#include "CoinTree.h"
#include "PlayerTree.h"


void CoinTree::getScoreBoard(Tree<Player, Pair>* coin_tree, int **players, int *numOfPlayers){
    int n = coin_tree->getSize();
    Player** player_arr = new Player*[n];
    coin_tree->inorder(player_arr);
    *players = (int*)malloc(n*sizeof(int));
    for (int i=0; i < n; i++){
        *((*players)+i) = (*(player_arr+i))->getPlayerId();
    }
    delete player_arr;
}