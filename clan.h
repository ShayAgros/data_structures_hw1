#ifndef clan_d
#define clan_d

#include "avl.h"
#include "player.h"
#include "min_heap.h"

namespace hw1 {

typedef AvlTree<Player*, Player::Comp_by_score> Players_Tree;

class Clan {

	int id;
	bool _can_fight;
	Players_Tree _players_by_score;
	MinHeap<int>::Node* _min_heap_node;
	Clan* _next;

public:
	Clan(int id) : id(id), _can_fight(true),
		_players_by_score(), _min_heap_node(NULL), _next(NULL) {}

	~Clan() {}

	void addPlayer(Player *player);

	class memoryAllocFailure {};
};





} // end namespace
#endif
