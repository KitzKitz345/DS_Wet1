//
// Created by Nitzan on 12/05/2018.
//

#include "library1.h"
#include "Oasis.h"
#include "CoinTree.h"
#include "PlayerTree.h"

StatusType addPlayer(void *DS, int playerID, int initialCoins) {
    if (DS == nullptr || playerID <= 0 || initialCoins < 0) {
        return INVALID_INPUT;
    }
    //need to check if players tree is null?
    //should we cancel the get funcs and add proper funcs in oasis.cpp?
    try {
        Player* new_player = new Player(playerID,initialCoins,0,-1);
        PlayerTree::insertPlayer(((Oasis*)DS)->getPlayersTree(), *new_player);
        CoinTree::insertPlayerByCoin(((Oasis*)DS)->getCoinTree(), *new_player);
    } catch (Tree::AlreadyExist& e){
        return FAILURE;
    } catch (std::exception& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

//should divide into to funcs like addplayer?
StatusType completeChallange(void *DS, int playerID, int coins) {
    if (DS == nullptr || playerID <= 0 || coins < 0) {
        return INVALID_INPUT;
    }
    //need to add get data func in tree.h
    try {
        Tree<Player,int>* node = ((Oasis*)DS)->getPlayersTree()->find(playerID);
        Player* player = node->data;
        player->addCoins(coins);
        player->incChallenges();
    } catch (Tree::DoesNotExist& e) {
        return FAILURE;
    } catch (std::exception& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}