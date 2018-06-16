#ifndef clan_d
#define clan_d

#include "avl.h"
#include "player.h"
#include "min_heap.h"

namespace hw1 {

typedef AvlTree<Player, Player::CompareByScore ,Player::GetScore > Players_Tree;

class Clan {
private:
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

	/* returns clan's size */
	int getSize();
	/* returns k players which have the
		* highest grades
		*/
	int getStrongest(int k);

	/*disables clan's ability to fight*/
	void setClanLost();

	/* checks it clan can fight.
		* returns 'true' if so
		*/
	bool canFight();

	/*
		Returns the node which represents this clan in the min heap of _can_fight_clans in oasis.
	*/
	MinHeap<int>::Node* getMinHeapNode();

	class memoryAllocFailure {};
};



} // end namespace
#endif
