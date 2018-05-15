/********************************************************
 * 	The Main class which handle all operations in this
 * 	homework
 *	This class ASSUMES argument integrety
 */

#include "avl.h"
#include "player.h"
#include "clan.h"


namespace hw1 {

class Oasis {

    AvlTree<Player*,Player::Comp_by_id> players_by_id;
    AvlTree<Player*,Player::Comp_by_coins> players_by_coins;
    Player* best_player;
    AvlTree<Clan*, Clan::Comp_by_id> clans;



    public:

    	Oasis() : players_by_id(), players_by_coins(), best_player(NULL),
		clans() {}

	~Oasis();
    	/* adds a player to the all_players
	 * tree and updates best_player if it isn't defined
	 * (can happen only if we add the first player)
	 *
	 * @playerID - the new players ID
	 * @initialCoins - players starting coins
	 *
	 * Exceptions:
	 * 	memoryAllocFailure - memory alloc failure
	 * 	playerExist - player already exists
	 */
	void addPlayer(int playerID,int initialCoins);

	/* adds clan to 'clans' tree
	 * @clanID - the new clan's id	
	 *
	 * Exceptions:
	 * 	memoryAllocFailure - memory alloc failure
	 * 	clanExists - clan already exists
	 */
	void addClan(int clanID);

	/* adds clan to 'clans' tree
	* @clanID - the new clan's id
	* //TODO - add comments
	* Exceptions:
	* 	memoryAllocFailure - memory alloc failure
	* 	clanExists - clan already exists
	*/
	void addClan(int clanID, Players_Tree& players_tree, Player* best_player);

	//TODO - add comments
	void removeClan(int clanID);

	/* adds a player to clan.
	 * @playerID - the player to be added the clan
	 * @clanID - the clan's id
	 *
	 * Exceptions:
	 * 	memoryAllocFailure - memory alloc failure
	 *	clanOrPlayerDoesntExist - no clan or player with this
	 *							id
	 *	playerAlreadyHasClan - player already has a different
	 *							clan
	 */
	void joinClan(int playerID, int clanID);

	/* We add coins to the player whose id is
	 * playerID
	 * @coins - the number of coins we want to add
	 *
	 * Exceptions:
	 * 	memoryAllocFailure - memory alloc failure
	 *	clanOrPlayerDoesntExist - there is no player
	 *				by this id
	 */
	void completeChallenge(int playerID,int coins);

	/* Unite two clans.
	* @clanID1 -
	* @clanID2 - 
	*
	* Exceptions:
	*/
	//TODO - fix comments
	void uniteClans(int clan_id1, int clan_id2);


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
    void getBestPlayer(int clanID, int *playerID);

    /* getScoreBoard:
     * maybe a clan needs one more tree that will be arranged by
     * score. Not difficult to implement it, but gonna cost us one
     * more AVL tree
     *
     */
	 void getScoreboard(int clanID, int **players, int *numOfPlayers);

/* TODO: check whether you need 'clanDoesntExist' and 'playerDoesntExist'*/
    class playerExist{};
    class playerDoesntExist{};
    class clanExists{};
    class clanDoesntExist{};
    class clanOrPlayerDoesntExist{};
    class playerAlreadyHasClan{};
    class memoryAllocFailure{};
	class InvalidInput {};

	private:
		// Sorts two arrays into one array
		// Parameters->
		//			*first_array - the first array to sort
		//			*size_first = the size of the first array
		//			*second_array - the second array to sort
		//			*size_second = the size of the second array
		// Returns ->
		//			A sorted array made of the two given arrays.
		//TODO - fix comments.
		static Player** mergeArraysWithChallenges(Player** first_array,
			int size_first, Player** second_array, int size_second,
			int* merged_array_size);
}; // class oasis


} // end namespace
