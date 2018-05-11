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
    explicit Clan(int id);
    ~Clan();
    Clan(const Clan& clan) = delete;
    int getClanId();
    Player& getBestPlayer();
    void setBestPlayer();
    void joinClan(Player& new_player);
    void getScoreBoard(int **players, int *numOfPlayers);
};

//maybe exceptions

void addClan(Tree<Clan, int> clan_tree, int id);
void uniteClans(Tree<Clan, int> clan_tree, int id1, int id2);


#endif //CODE_CLANTREE_H
