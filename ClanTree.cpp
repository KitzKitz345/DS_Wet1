//
// Created by Nitzan on 06/05/2018.
//

#include <cstdlib>
#include "ClanTree.h"
#include "CoinTree.h"

explicit Clan::Clan(int id): clan_id(id), players(nullptr), players_by_coins(nullptr),
                             best_player(nullptr){

}

int Clan::getClanId() {
    return this->clan_id;
}

int Clan::getBestPlayer() {
    return this->best_player->getPlayerId();
}

int Clan::getSize(){
    return this->players->getSize();
}

void Clan::getPlayers(Player** player_arr){
    this->players->inorder(player_arr);
}

void Clan::joinClan(Player &new_player) {
    if (new_player.getClanId() == -1){
        throw ClanTree::AlreadyInClan();
    }
    if (new_player.getChallenges() > this->best_player->getChallenges()){
        this->best_player = &new_player;
    } else if(new_player.getChallenges() == this->best_player->getChallenges()){
        if (new_player.getPlayerId() < this->best_player->getPlayerId()){
            this->best_player = &new_player;
        }
    }
    int* id_key = new int(new_player.getPlayerId());
    new_player.setClanId(this->clan_id);
    PlayerTree::insertPlayer(this->players, new_player);
    CoinTree::insertPlayerByCoin(this->players_by_coins, new_player);
}

void Clan::getScoreBoard(int **players, int *numOfPlayers){
    if (this->players == nullptr){
        players = nullptr;
        *numOfPlayers = 0;
        return;
    }
    CoinTree::getScoreBoard(this->players_by_coins, players, numOfPlayers);
}

void ClanTree::addClan(Tree<Clan, int>* clan_tree, int id){
    if (clan_tree->find(id).getData().getClanId() == id){
        throw Tree::AlreadyExist();
    }
    Clan* new_clan = new Clan(id);
    clan_tree->insert(id, *new_clan);
}

void ClanTree::uniteClans(Tree<Clan, int>* clan_tree, int id1, int id2){
    Clan* clan1 = &(clan_tree->find(id1).getData());
    Clan* clan2 = &(clan_tree->find(id2).getData());
    Clan* to = nullptr;
    Clan* from = nullptr;
    if (clan1->getSize() > clan2->getSize()){
        to = clan1;
        from = clan2;
    } else if (clan1->getSize() < clan2->getSize()){
        to = clan2;
        from = clan1;
    } else {
        if(id1 < id2){
          to = clan1;
          from = clan2;
        } else {
            to = clan2;
            from = clan1;
        }
    }
    int n = from->getSize();
    Player** player_arr = new Player*[n];
    from->getPlayers(player_arr);
    for(int i = 0; i < n; i++){
        (*(player_arr+i))->setClanId(-1);
        if ((*(player_arr+i))->getChallenges() != 0){
            to->joinClan(**(player_arr+i));
        }
    }
    delete player_arr;
    int id_to_remove = from->getClanId();
    clan_tree->remove(id_to_remove);
    delete from;
}



