#ifndef player_d
#define player_d

#include "avl.h"

namespace hw1 {

class Player {

    int _id;
    int _score;
    int _clan_id;

    public:
    Player(int id,int score, int clan_id) : _id(id), _score(score),
		_clan_id(clan_id) {}

    int getID();

    int getScore();

    int getClanID();

    ~Player() = default;


    class CompareByScore {
	public:
	bool operator() (const Player& p1, const Player& p2) {
		if (p1._score == p2._score) {
			return (p1._id < p2._id);
		}		
		return (p1._score > p2._score);
	}
    };

    class CompareByID {
    public:
	bool operator() (Player *p1, Player *p2) {
		return (p1->_id < p2->_id);
	}
    };

    class GetScore {
    public:
	bool operator() (Player *p1) {
		return p1->getScore();
	}
    };

};


} // end namespace
#endif
