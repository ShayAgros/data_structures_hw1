#include "avl.h"


namespace hw1 {

class Player {

    int id;
    int coins;


    // these fields will be of different types
    // but they need to have the player's clan id
    // and a point to it in the Clans AVL tree
    int clan;
    void* clah_pointer;


    public:
    Player(int id,int coins) : id(id) , coins(coins) {}
    
    ~Player() = default;


};


} // end namespace
