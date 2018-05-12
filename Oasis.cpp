//
// Created by Nitzan on 12/05/2018.
//

#include "Oasis.h"

explicit Oasis::Oasis() : best_player(nullptr) {

}

void Oasis::insertPlayer(Player& player) {
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

void Oasis::completeChallenge(int playerId, int coins) {
    PlayerTree::completeChallenge(this->players, playerId, coins);
    CoinTree::completeChallenge(this->players_by_coins, playerId, coins);
}