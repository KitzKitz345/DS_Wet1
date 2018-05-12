//
// Created by Nitzan on 12/05/2018.
//

#include <new>
#include "library1.h"
#include "Oasis.h"
#include "CoinTree.h"
#include "PlayerTree.h"
#include "exception"

StatusType addPlayer(void *DS, int playerID, int initialCoins) {
    if (DS == nullptr || playerID <= 0 || initialCoins < 0) {
        return INVALID_INPUT;
    }
    //need to check if players tree is null?
    try {
        Player* new_player = new Player(playerID,initialCoins,0,-1);
        ((Oasis*)DS)->insertPlayer(*new_player);
    } catch (Tree::AlreadyExist& e){
        return FAILURE;
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch (std::exception& e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType addClan(void *DS, int clanID){
    if (DS == nullptr || clanID <= 0){
        return INVALID_INPUT;
    }
    try{
        ((Oasis*)DS)->addClan(clanID);
    } catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    } catch (Tree::AlreadyExist& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType joinClan(void *DS, int playerID, int clanID){
    if (DS == nullptr || playerID <= 0 || clanID <= 0){
        return INVALID_INPUT;
    }
    try {
        ((Oasis*)DS)->joinClan(playerID, clanID);
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch (Tree::AlreadyExist& e){
        return FAILURE;
    } catch (ClanTree::AlreadyInClan& e){
        return FAILURE;
    }
    return SUCCESS;
}

//should divide into to funcs like addplayer?
StatusType completeChallange(void *DS, int playerID, int coins) {
    if (DS == nullptr || playerID <= 0 || coins < 0) {
        return INVALID_INPUT;
    }
    try {
        ((Oasis*)DS)->completeChallenge(playerID, coins);
    } catch (Tree::DoesNotExist& e) {
        return FAILURE;
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    } catch (std::exception& e) {
        return FAILURE;
    }
    return SUCCESS;
}

/* Description:   Joins two clans, leaving the players with no comlpeted challanges out of the new clan.
 * Input:         DS - A pointer to the data structure.
 *                clanID1 - ID of the first clan.
 *		          clanID2 - ID of the second clan.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, or if clanID1<=0, or if clanID2<=0
 *                FAILURE - If clanID1 or clanID2 are not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType uniteClans(void *DS, int clanID1, int clanID2)
{

}