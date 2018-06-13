#ifndef player_d
#define player_d

#include "avl.h"

namespace hw1 {

class Player {

    int _id;
    int _score;
	int _clanID;

    public:
    Player(int _id,int _score, int ClandID) : _id(_id), _score(_score),
		_clanID(_clanID) {}

    int getID();

    int getScore();

	int getClanID();

    ~Player() = default;


    class CompareByScore {
	public:
	bool operator() (Player *p1, Player *p2) {
		if (p1->_score == p2->_score) {
			return (p1->_id < p2->_id);
		}		
	    return (p1->_score > p2->_score);
    	}
    };

	class CompareByID {
	public:
		bool operator() (Player *p1, Player *p2) {
			return (p1->_id < p2->_id);
		}
	};


};


} // end namespace
#endif
