#include "avl.h"


namespace hw1 {

class Oasis {

    AvlTree players_by_successe; // you need to get the name shorter. Needed to return player with most successes
    AvlTree players_by_id; // need shorter name, needed to check it player already exists in addPlayer
    AvlTree clans;


    public:


    /*  addPlayer:
     *  	need to add the player to players_by_id
     *  	add him\her to players_by_successes
     *  	and set his\her clan and coins to be 0
     *
     */

    /* addClan
     *	add clan to 'clans' tree
     */

    /* joinClan:
     * add player to clan. Clan holds AVL tree of players in it
     * this AVL tree is sorted by successes. Need to update
     * player's data (set his\her clan num and pointer to the new
     * clan and Node in 'clan' AVL tree
     *
     */


    /* completeChalange:
     * 	removes player from players_by_successe tree and players_by_id
     * 	and the clan's players' tree (player has a point to this tree)
     * 	tree, adds successes and points to the player and adds him\her
     * 	back to all trees. players_by_successe and clan's players'
     * 	trees are sorted by successes
     *
     */

    /* getBestPlayer
     * return left_most node in players_by_successes of in clan's
     * players' tree
     *
     */

    /* getScoreBoard:
     * maybe a clan needs one more tree that will be arranged by
     * score. Not difficult to implement it, but gonna cost us one
     * more AVL tree
     *
     */


};


} // end namespace
