//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_CLANTREE_H
#define CODE_CLANTREE_H

#include "Tree.h"
#include "PlayerTree.h"
#include "CoinTree.h"

class Clan {
    int clan_id;
    Tree<Player,int>* players;
    Tree<Player,Pair>* players_by_coins;
    Player* best_player;

public:
    explicit Clan(int id);
    ~Clan();
    Clan(const Clan& clan) = delete;
    int getClanId();
    int getBestPlayer();
    int getSize();
    void getPlayers(Player** player_arr);
    void joinClan(Player& new_player);
    void removePlayerFromClanCoins(Player& player);
    void insertPlayerToClanCoins(Pair& key, Player& player);
    void getScoreBoard(int **players, int *numOfPlayers);
    void completedChallenge(Player& player);
};

//maybe exceptions
//class aaa : public std::exception {};

namespace ClanTree{

    class AlreadyInClan : public std::exception {};

    void addClan(Tree<Clan, int>* clan_tree, int id);
    void uniteClans(Tree<Clan, int>* clan_tree, int id1, int id2);
    void deleteTree(Tree<Clan, int>* clan_tree);
}




#endif //CODE_CLANTREE_H
