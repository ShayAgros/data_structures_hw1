#ifndef clan_d
#define clan_d

#include "avl.h"
#include "player.h"
#include "min_heap.h"

namespace hw1 {

typedef AvlTree<Player, Player::CompareByScore> Players_Tree;

class Clan {

	int _id;
	bool _can_fight;
	Players_Tree _players_by_score;
	MinHeap<int>::Node* _min_heap_node;

public:

	Clan() : _id(0), _can_fight(true),
		_players_by_score(), _min_heap_node(NULL) {}

	Clan(int id, MinHeap<int>::Node* min_heap_node) : _id(id), _can_fight(true),
		_players_by_score(), _min_heap_node(min_heap_node) {}

	~Clan() {}

	void addPlayer(int player_id, int score);

	class memoryAllocFailure {};
};



} // end namespace
#endif
