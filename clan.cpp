#include "clan.h"

namespace hw1 {

void Clan::addPlayer(int player_id, int score) {
	try {
		Player player(player_id, score, _id);
		_players_by_score.insertNode(player);
	} catch ( std::bad_alloc& ex ) {
		throw memoryAllocFailure();
	}
}


} // end namespace
