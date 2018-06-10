#include "clan.h"

namespace hw1 {

void Clan::addPlayer(Player *player) {
	try {
		_players_by_score.insertNode(player);
	} catch ( std::bad_alloc& ex ) {
		throw memoryAllocFailure();
	}
}


} // end namespace
