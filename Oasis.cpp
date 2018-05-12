//
// Created by Nitzan on 12/05/2018.
//

#include "Oasis.h"

explicit Oasis::Oasis() : best_player(nullptr) {

}

Tree<Player,int>* Oasis::getPlayersTree () {
    return this->(*players);
}
Tree<Player,Pair>* Oasis::getCoinTree () {
    return this->(*players_by_coins);
};

