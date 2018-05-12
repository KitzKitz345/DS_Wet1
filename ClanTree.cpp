//
// Created by Nitzan on 06/05/2018.
//

#include <cstdlib>
#include <new>
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

void Clan::joinClan(Player &new_player) {
    if (new_player.getChallenges() > this->best_player->getChallenges()){
        this->best_player = &new_player;
    } else if(new_player.getChallenges() == this->best_player->getChallenges()){
        if (new_player.getPlayerId() < this->best_player->getPlayerId()){
            this->best_player = &new_player;
        }
    }
    int* id_key = new int(new_player.getPlayerId());
    this->players->insert(*id_key, new_player);
    this->players_by_coins->insert();
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
    Clan* new_clan = new Clan(id);
    clan_tree->insert(id, *new_clan);
}

void ClanTree::uniteClans(Tree<Clan, int>* clan_tree, int id1, int id2){

}



