#include "player.h"

namespace hw1 {

    void* Player::getClan() {
	return clan_pointer;
    }


    void Player::setClan(void *clan){
	clan_pointer = clan;
    }

    void Player::addCoins(int new_coins) {
	this->coins += new_coins;	
	this->num_of_challenges ++;
    }


} // end namespace
