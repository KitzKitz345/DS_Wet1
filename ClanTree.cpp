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

bool Clan::operator>(const Clan& p) const {
    if (this->getSize() > p.getSize()) {
        return true;
    } else if (this->getSize() == p.getSize()) {
        if (this->getClanId() < p.getClanId()) {
            return true;
        }
    }
    return false;
}

int Clan::getClanId() const{
    return this->clan_id;
}

Player* Clan::getBestPlayer() const{
    return this->best_player;
}

int Clan::getSize() const{
    return this->players->getSize();
}

void Clan::getPlayersById(Player** player_arr) const{
    this->players->inorder(player_arr);
}

void Clan::getPlayersByCoin(Player** player_arr) const{
    this->players_by_coins->inorder(player_arr);
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

void Clan::getScoreBoard(int **players, int *numOfPlayers) const{
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
    if (clan1 > clan2){
        to = clan1;
        from = clan2;
    } else {
        to = clan2;
        from = clan1;
    }
    int n_to = to->getSize();
    Player** to_player_player_arr = nullptr;
    Player** to_player_coin_arr = nullptr;
    if (n_to != 0){
        to_player_player_arr = new Player*[n_to];
        to_player_coin_arr = new Player*[n_to];
        try {
            to->getPlayersById(to_player_player_arr);
            to->getPlayersByCoin(to_player_coin_arr);
        } catch (std::exception& e) {
            delete[] to_player_player_arr;
            delete[] to_player_coin_arr;
            throw e;
        }
    }
    int n_from = from->getSize();
    Player** from_player_player_arr = nullptr;
    Player** from_player_coin_arr = nullptr;
    if (n_from != 0){
        from_player_player_arr = new Player*[n_from];
        from_player_coin_arr = new Player*[n_from];
        try {
            from->getPlayersById(from_player_player_arr);
            from->getPlayersByCoin(from_player_coin_arr);
        } catch (std::exception& e) {
            delete[] from_player_player_arr;
            delete[] from_player_coin_arr;
            delete[] to_player_player_arr;
            delete[] to_player_coin_arr;
            throw e;
        }
    }
    int* to_id_key = new int(to->getClanId());
    int* from_id_key = new int(from->getClanId());
    Tree<Clan, int>* current_root = (*clan_tree);
    (*clan_tree) = (*clan_tree)->remove(*to_id_key);
    if (current_root->getData().getClanId() == *to_id_key){
        delete current_root;
    }
    (*clan_tree) = (*clan_tree)->remove(*from_id_key);
    if (current_root->getData().getClanId() == *from_id_key){
        delete current_root;
    }
    delete from;
    delete from_id_key;
    Clan* new_empty_clan = new Clan(to->getClanId());
    delete to;
    ClanTree::addClan(clan_tree, *new_empty_clan, *to_id_key);
    for (int i=0, j=0; i<n_to, j<n_from;){
        //iterate over the coin player arrays
    }
    for (int i=0, j=0; i<n_to, j<n_from;){
        //iterate over the player arrays
    }
    delete[] from_player_player_arr;
    delete[] from_player_coin_arr;
    delete[] to_player_player_arr;
    delete[] to_player_coin_arr;
}

    /*
for(int i = 0; i < from_n; i++){
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
 */
    /*
for(int i = 0; i < n_to; i++){
    if ((*(to_player_arr+i))->getChallenges() == 0){
        to->removePlayerFromClanPlayersTree(**(to_player_arr+i));
        to->removePlayerFromClanCoins(**(to_player_arr+i));
    }
}
 */



void ClanTree::deleteTree(Tree<Clan, int>* clan_tree) {
    clan_tree->deleteTree(true);
    delete clan_tree;
}



