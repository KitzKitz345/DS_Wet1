//
// Created by Nitzan on 06/05/2018.
//

#include <cstdlib>
#include "ClanTree.h"
#include "PlayerTree.h"
#include "CoinTree.h"

Clan::Clan(int id): clan_id(id), players(nullptr), players_by_coins(nullptr),
                             best_player(nullptr){
    this->players = new Tree<Player, int>();
    this->players_by_coins = new Tree<Player, Pair>();
}

Clan::~Clan(){
    delete players;
    delete players_by_coins;
}

int Clan::getClanId() {
    return this->clan_id;
}

Player* Clan::getBestPlayer() {
    return this->best_player;
}

int Clan::getSize(){
    return this->players->getSize();
}

void Clan::getPlayers(Player** player_arr){
    this->players->inorder(player_arr);
}

void Clan::joinClan(Player &new_player) {
    if (new_player.getClan() != nullptr){
        throw ClanTree::AlreadyInClan();
    }
    if (this->best_player == nullptr){
        this->best_player = &new_player;
    } else if (new_player.getChallenges() > this->best_player->getChallenges()){
        this->best_player = &new_player;
    } else if(new_player.getChallenges() == this->best_player->getChallenges()){
        if (new_player.getPlayerId() < this->best_player->getPlayerId()){
            this->best_player = &new_player;
        }
    }
    Pair* pair_key = new Pair(new_player.getPlayerId(), new_player.getCoins());
    new_player.setClan(this);
    PlayerTree::insertPlayer(&(this->players), new_player);
    CoinTree::insertPlayerByCoin(&(this->players_by_coins), *pair_key, new_player);
}

void Clan::getScoreBoard(int **players, int *numOfPlayers){
    if (this->players == nullptr){
        *players = nullptr;
        *numOfPlayers = 0;
        return;
    }
    CoinTree::getScoreBoard(this->players_by_coins, players, numOfPlayers);
}

void Clan::completedChallenge(Player& player){
    if (player.getChallenges() >= this->best_player->getChallenges()){
        if (player.getPlayerId() < this->best_player->getPlayerId()){
            this->best_player = &player;
        }
    }
}


void ClanTree::addClan(Tree<Clan, int>** clan_tree, int id){
    Clan* new_clan = new Clan(id);
    int* key = new int(id);
    (*clan_tree) = (*clan_tree)->insert(*key, *new_clan);
}

void Clan::insertPlayerToClanCoins(Pair& key, Player& player){
    CoinTree::insertPlayerByCoin(&(this->players_by_coins), key, player);
}

void Clan::removePlayerFromClanCoins(Player& player){
    CoinTree::removePlayer(&(this->players_by_coins), player.getPlayerId(), player.getCoins());
}

void ClanTree::uniteClans(Tree<Clan, int>** clan_tree, int id1, int id2){
    Clan* clan1 = &((*clan_tree)->find(id1).getData());
    Clan* clan2 = &((*clan_tree)->find(id2).getData());
    if (clan1->getClanId() != id1 || clan2->getClanId() != id2){
        throw Tree<Clan, int>::DoesNotExist();
    }
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
        (*(player_arr+i))->setClan(nullptr);
        if ((*(player_arr+i))->getChallenges() != 0){
            to->joinClan(**(player_arr+i));
        }
    }
    delete player_arr;
    int id_to_remove = from->getClanId();
    (*clan_tree) = (*clan_tree)->remove(id_to_remove);
    delete from;
}

void ClanTree::deleteTree(Tree<Clan, int>* clan_tree) {
    clan_tree->deleteTree();
    delete clan_tree;
}



