//
// Created by Nitzan on 12/05/2018.
//

#include "Oasis.h"
#include "Tree.h"

explicit Oasis::Oasis() : best_player(nullptr) {
    Tree<Player,int>* players = new Tree();
    this->players = players;
    Tree<Player,Pair>* players_by_coins = new Tree();
    this->players_by_coins = players_by_coins;
    Tree<Clan,int>* clans = new Tree();
    this->clans = clans;
}

void Oasis::insertPlayer(Player& player) {
    if (this->best_player == nullptr || (this->best_player->getChallenges() == 0 &&
        this->best_player->getPlayerId() > player.getPlayerId())){
        this->best_player = &player;
    }
    PlayerTree::insertPlayer(this->players, player);
    CoinTree::insertPlayerByCoin(this->players_by_coins, player);
}

void Oasis::addClan(int clanID){
    ClanTree::addClan(this->clans, clanID);
}

void Oasis::joinClan(int playerID, int clanID)
{
    Clan* clan = &(this->clans->find(clanID).getData());
    Player* player = &(this->players->find(playerID).getData());
    if (clan->getClanId() != clanID || player->getPlayerId() != playerID){
        throw Tree::DoesNotExist();
    }
    clan->joinClan(*player);
}

//need to add another check if the edited player is the best in the entire system
void Oasis::completeChallenge(int playerId, int coins) {
    CoinTree::removePlayer(this->players_by_coins, playerId, coins);
    PlayerTree::completeChallenge(this->players, playerId, coins);
    Player& player = this->players->find(playerId).getData(); // should be declared like that?
    CoinTree::insertPlayerByCoin(this->players_by_coins, player);
    Player* advanced_player = &(this->players->find(playerId).getData());
    Clan* clan_of_player = advanced_player->getClan();
    if (clan_of_player != nullptr){
        clan_of_player->completedChallenge(*advanced_player);
    }
}

void Oasis::getBestPlayer(int clanID, int *playerID){
    if (clanID < 0){
        if (this->best_player == nullptr){
            *playerID = -1;
        } else {
            *playerID = this->best_player->getPlayerId();
        }
    } else {
        Clan* clan = &(this->clans->find(clanID).getData());
        if (clan->getClanId() != clanID){
            throw Tree::DoesNotExist();
        }
        if (clan->getBestPlayer() == nullptr){
            *playerID = -1;
        } else {
            *playerID = clan->getBestPlayer();
        }
    }
}

void Oasis::getScoreboard(int clanID, int **players, int *numOfPlayers){
    if (clanID < 0){
        if (this->players_by_coins->getSize() == 0){
            *players = nullptr;
            *numOfPlayers = 0;
        } else {
            CoinTree::getScoreBoard(this->players_by_coins, players, numOfPlayers);
        }
    } else {
        Clan *clan = &(this->clans->find(clanID).getData());
        if (clan->getClanId() != clanID) {
            throw Tree::DoesNotExist();
        }
        if (clan->getBestPlayer() == nullptr) {
            players = nullptr;
            *numOfPlayers = 0;
        } else {
            clan->getScoreBoard(players, numOfPlayers);
        }
    }
}

void Oasis::uniteClans(int clanID1, int clanID2)
{
    ClanTree::uniteClans(this->clans, clanID1, clanID2);
}