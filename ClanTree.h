//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_CLANTREE_H
#define CODE_CLANTREE_H

#include "PlayerTree.h"
#include "Tree.h"
#include "CoinTree.h"

class Clan {
    int clan_id;
    Tree<Player,int>* players;
    Tree<Player,Pair>* players_by_coins;
    Player* best_player;

public:
    explicit Clan(int id);
    ~Clan() = default;
    Clan(const Clan& clan) = delete;
    int getClanId();
    int getBestPlayer();
    int getSize();
    void getPlayers(Player** player_arr);
    void joinClan(Player& new_player);
    void getScoreBoard(int **players, int *numOfPlayers);
};

//maybe exceptions
//class aaa : public std::exception {};

namespace ClanTree{
    void addClan(Tree<Clan, int>* clan_tree, int id);
    void uniteClans(Tree<Clan, int>* clan_tree, int id1, int id2);
}




#endif //CODE_CLANTREE_H
