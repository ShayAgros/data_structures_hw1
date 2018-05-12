#include "player.h"

namespace hw1 {

    void* Player::getClan() {
		return clan_pointer;
    }


    void Player::setClan(void *clan){
		clan_pointer = clan;
    }


} // end namespace
