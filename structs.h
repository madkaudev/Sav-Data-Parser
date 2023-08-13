/**
 * Defines a structure that represents a Pokemon.
*/
typedef struct pokemon {
    char pokedexIndex;          //Offset: 0x00
    char type1;                 //Offset: 0x05
    char type2;                 //Offset: 0x06 
    char heldItem;              //Offset: 0x07
    char moveIndexes[4];        //Offset: 0x08
    short evData[5];            //Offset: 0x11
    short ivData;               //Offset: 0x1B
    char level;                 //Offset: 0x21
    short stats[5];             //Offset: 0x22
};

/**
 * Defines a structure that represents a Pokemon party.
*/
typedef struct party {
    char numPokemon;            //Offset: 0x2F2C
    struct pokemon mons[6];     //Offset: 0x2F34
    char nicknames[6][10];      //Offset: 0x307E
};

/**
 * Defines a structure that represents the data associated with a player.
*/
typedef struct player {
    char playerName[7];         //Offset: 0x2598
    char money[3];              //Offset: 0x25F3
    char badges;                //Offset: 0x2602
    short playerID;             //Offset: 0x2605
    char currentMapID;          //Offset: 0x260A
    struct party playerParty;   //Offset: 0x2F2C    
};
