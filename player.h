#ifndef player_d
#define player_d

#include "avl.h"

namespace hw1 {

class Player {

    int id;
    int score;
	int clanID;

    public:
    Player(int id,int score, int ClandID) : id(id), score(score),
		clanID(clanID) {}

    int getID();

    int getScore();

	int getClanID();

    ~Player() = default;


    class Comp_by_score {
	public:
	bool operator() (Player *p1, Player *p2) {
		if (p1->score == p2->score) {
			return (p1->id < p2->id);
		}		
	    return (p1->score > p2->score);
    	}
    };

};


} // end namespace
#endif
