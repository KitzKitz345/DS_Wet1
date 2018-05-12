//
// Created by Nitzan on 06/05/2018.
//

#include <cstdlib>
#include <new>
#include "CoinTree.h"
#include "PlayerTree.h"

explicit Pair::Pair(int id, int coin) : id(id), coin(coin){}

bool operator==(const Pair& p) const{
    return (this->id == p.id) && (this->coin == p.coin);
}

bool operator>(const Pair& p) const {
    return (this->coin > p.coin) || ((this->coin == p.coin) && (this->id < p.id));
}

void CoinTree::getScoreBoard(Tree<Player, Pair>* coin_tree, int **players, int *numOfPlayers){
    int n = coin_tree->getSize();
    Player** player_arr = new Player*[n];
    coin_tree->inorder(player_arr);
    *players = (int*)malloc(n*sizeof(int));
    if(*players == nullptr){
        throw std::bad_alloc();
    }
    for (int i=0; i < n; i++){
        *((*players)+i) = (*(player_arr+i))->getPlayerId();
    }
    delete player_arr;
}

void CoinTree::insertPlayerByCoin(Tree<Player, Pair>* coin_tree, Player& player) {
    Pair* p = new Pair(player.getPlayerId(), player.getCoins()); // should do delete?
    coin_tree->insert(*p, player);
}

void CoinTree::completeChallenge(Tree<Player, Pair>* coin_tree, int playerId, int coins) {
    Pair* p = new Pair(playerId, coins); // should do delete?
    Tree<Player, Pair>& node = coin_tree->find(*p); // should be &??
    Player& player = node.getData(); // should be &??
    coin_tree->remove(*p);
    coin_tree->insert(*p, player);
}