#include "clan.h"

namespace hw2 {

void Clan::addPlayer(int player_id, int score) {
	try {
		Player player(player_id, score, _id);
		_players_by_score.insertNode(player);
	} catch ( std::bad_alloc& ex ) {
		throw memoryAllocFailure();
	}
}

int Clan::getSize() {
	return 	_players_by_score.getSize();
}

int Clan::getStrongest(int k) {
	return _players_by_score.findGradeByIndex(k-1);
}

void Clan::setClanLost() {
	_can_fight = false ;
}

bool Clan::canFight() {
	return _can_fight ;
}

MinHeap<int>::Node* Clan::getMinHeapNode() {
	return _min_heap_node;
}


} // end namespace
