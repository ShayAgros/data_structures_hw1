#ifndef clan_d
#define clan_d

#include "avl.h"
#include "player.h"
#include "min_heap.h"

namespace hw1 {

typedef AvlTree<Player*, Player::Comp_by_score> Players_Tree;

class Clan {

	int _id;
	bool _can_fight;
	Players_Tree _players_by_score;
	MinHeap<int>::Node* _min_heap_node;

public:
	Clan(int _id) : _id(_id), _can_fight(true),
		_players_by_score(), _min_heap_node(NULL) {}

	~Clan() {}

	void addPlayer(Player *player);

	class memoryAllocFailure {};
};



} // end namespace
#endif
