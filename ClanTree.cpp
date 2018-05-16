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
    PlayerTree::deleteTree(this->players, false);
    this->players = nullptr;
    CoinTree::deleteTree(this->players_by_coins, false);
    this->players_by_coins = nullptr;
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

void Clan::joinClan(Player &new_player, Pair& pair_key, int& id_key) {
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
    new_player.setClan(this);
    PlayerTree::insertPlayer(&(this->players), new_player, id_key);
    CoinTree::insertPlayerByCoin(&(this->players_by_coins), new_player, pair_key);
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
    if (player.getChallenges() > this->best_player->getChallenges()) {
        this->best_player = &player;
    } else if (player.getChallenges() == this->best_player->getChallenges()){
        if (player.getPlayerId() < this->best_player->getPlayerId()){
            this->best_player = &player;
        }
    }
}


void ClanTree::addClan(Tree<Clan, int>** clan_tree, Clan& clan, int& key){
    (*clan_tree) = (*clan_tree)->insert(key, clan);
}

void Clan::insertPlayerToClanCoins(Pair& key, Player& player){
    CoinTree::insertPlayerByCoin(&(this->players_by_coins), player, key);
}

void Clan::removePlayerFromClanPlayersTree(Player& player){
    PlayerTree::removePlayer(&(this->players), player.getPlayerId());
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
    int n_to = to->getSize();
    if (n_to != 0){
        Player** to_player_arr = new Player*[n_to];
        try {
            to->getPlayers(to_player_arr);
            for(int i = 0; i < n_to; i++){
                if ((*(to_player_arr+i))->getChallenges() == 0){
                    to->removePlayerFromClanPlayersTree(**(to_player_arr+i));
                    to->removePlayerFromClanCoins(**(to_player_arr+i));
                }
            }
        } catch (std::exception& e) {
            delete[] to_player_arr;
            throw e;
        }
        delete[] to_player_arr;
    }
    int n = from->getSize();
    int* id_to_remove = new int(from->getClanId());
    try {
        if(n != 0){
            Player** player_arr = new Player*[n];
            try {
                from->getPlayers(player_arr);
                for(int i = 0; i < n; i++){
                    (*(player_arr+i))->setClan(nullptr);
                    if ((*(player_arr+i))->getChallenges() != 0){
                        int* id_key = new int((*(player_arr+i))->getPlayerId());
                        Pair* pair_key =  new Pair((*(player_arr+i))->getPlayerId(), (*(player_arr+i))
                                ->getCoins());
                        try {
                            to->joinClan(**(player_arr+i), *pair_key, *id_key);
                        } catch (std::exception& e) {
                            delete id_key;
                            delete pair_key;
                            throw e;
                        }
                    }
                }
                delete[] player_arr;
            } catch (std::exception& e) {
                delete[] player_arr;
                throw e;
            }

        }
        Tree<Clan, int>* current_root = (*clan_tree);
        (*clan_tree) = (*clan_tree)->remove(*id_to_remove);
        if (current_root->getData().getClanId() == *id_to_remove){
            delete current_root;
        }
    } catch (std::exception& e) {
        delete id_to_remove;
        throw e;
    }
    delete id_to_remove;
    /*if (from->getSize() != 0) {
        delete from;
    }*/
    delete from;
}

void ClanTree::deleteTree(Tree<Clan, int>* clan_tree) {
    clan_tree->deleteTree(true);
    delete clan_tree;
}



