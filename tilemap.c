#define TILEMAP_SIZE_X 16
#define TILEMAP_SIZE_Y 12

// How wide and tall is each tile in pixels
#define TILE_PIXELS 16

// What happens when we get out of grid horizontally
#define OUTSIDE_TILE_HORIZONTAL TILE_FULL
// What happens when we get out of grid vertically
#define OUTSIDE_TILE_VERTICAL TILE_EMPTY

typedef enum { TILE_EMPTY = ' ', TILE_ZERO = '\0', TILE_FULL = '#' } Tile;

// Tilemap is a grid of tiles (`Tile` enums, stored as unsigned bytes).
// The '+ 1' is there for string null-termination, because
// we're defining the tilemaps with strings.
typedef uint8_t Tilemap[TILEMAP_SIZE_Y][TILEMAP_SIZE_X + 1];


// List of tilemaps for each screen in the level.
// Note: starts at the bottom, so it looks continuous
const Tilemap screenTilemaps[] = {
    {
        // Index zero is empty
        // This index is reserved for 'invalid tilemap'
    },
    {
        "################",
        "#              #",
        "# #### #### #  #",
        "# #    #    #  #",
        "# # ## # ## #  #",
        "# #  # #  #    #",
        "# #### #### #  #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#########      #",
    },
    {
        "#########      #",
        "#########    ###",
        "########      ##",
        "########      ##",
        "##########     #",
        "##########     #",
        "########      ##",
        "########      ##",
        "##########    ##",
        "######        ##",
        "###           ##",
        "###         ####",
    },
    {
        "###         ####",
        "###    ##   ####",
        "###         ####",
        "###          ###",
        "#####        ###",
        "###          ###",
        "#            ###",
        "##        ######",
        "##         #####",
        "##         #####",
        "######     #####",
        "#####      #####",
    },
    {
        "#####      #####",
        "###      #######",
        "##        ######",
        "##          ####",
        "######      ####",
        "######       ###",
        "######   #   ###",
        "#####    ##  ###",
        "#####        ###",
        "##           ###",
        "##        ######",
        "##    ##########",
    },
// Starting screen:
    {
        "##    ##########",
        "##            ##",
        "####          ##",
        "########       #",
        "#####          #",
        "##             #",
        "##       #######",
        "#        #######",
        "#         ######",
        "#####     ######",
        "#####     ######",
        "################",
    },
    {
        "##    ##########",
        "##            ##",
        "####          ##",
        "########       #",
        "#####          #",
        "##             #",
        "##            ##",
        "#            ###",
        "#           ####",
        "#          #####",
        "          ######",
        "################",
    },
};



// Empty level (reserved for invalid tilemap)
const Tilemap EMPTY = {
    
};

const Tilemap FINAL_SCREEN = {
    "################",
    "#              #",
    "# #### #### #  #",
    "# #    #    #  #",
    "# # ## # ## #  #",
    "# #  # #  #    #",
    "# #### #### #  #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#########      #",
};
const Tilemap LEVEL4 = {
    "#########      #",
    "#########    ###",
    "########      ##",
    "########      ##",
    "##########     #",
    "##########     #",
    "########      ##",
    "########      ##",
    "##########    ##",
    "######        ##",
    "###           ##",
    "###         ####",
};
const Tilemap LEVEL3 = {
    "###         ####",
    "###    ##   ####",
    "###         ####",
    "###          ###",
    "#####        ###",
    "###          ###",
    "#            ###",
    "##        ######",
    "##         #####",
    "##         #####",
    "######     #####",
    "#####      #####",
};
const Tilemap LEVEL2 = {
    "#####      #####",
    "###      #######",
    "##        ######",
    "##          ####",
    "######      ####",
    "######       ###",
    "######   #   ###",
    "#####    ##  ###",
    "#####        ###",
    "##           ###",
    "##        ######",
    "##    ##########",
};

const Tilemap TEST_LEVEL = {
    "##     #########",
    "####          ##",
    "######        ##",
    "#########      #",
    "###########    #",
    "##             #",
    "##            ##",
    "#           ####",
    "#         ######",
    "#       ########",
    "      ##########",
    "################",
};
const Tilemap START_SCREEN = {
    "##    ##########",
    "##            ##",
    "####          ##",
    "########       #",
    "#####          #",
    "##             #",
    "##       #######",
    "#        #######",
    "#         ######",
    "#####     ######",
    "#####     ######",
    "################",
};

const Tilemap FLAT_LEVEL = {
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#             ##",
    "#           ####",
    "#         ######",
    "        ########",
    "################",
};
const


Tile
tilemapGetTile(const Tilemap* tilemap, int x, int y)
{
    if (x < 0 || x >= TILEMAP_SIZE_X) return OUTSIDE_TILE_HORIZONTAL;
    if (y < 0 || y >= TILEMAP_SIZE_Y) return OUTSIDE_TILE_VERTICAL;
    return (Tile)(*tilemap)[y][x];
}

Tile
tilemapGetTileFullOutside(const Tilemap* tilemap, int x, int y)
{
    if (x < 0 || x >= TILEMAP_SIZE_X) return TILE_FULL;
    if (y < 0 || y >= TILEMAP_SIZE_Y) return TILE_FULL;
    return (Tile)(*tilemap)[y][x];
}

// Converts a center (vector) from world-space to screen-space.
// In world-space one unit is one tile in size, so coordinate [1, 1] means tile at this coordinate.
// On the other hand, in screen-space, one unit is a pixel. [1, 1] would just mean the pixel
// close to the upper left corner of the widnow.
Vector2
worldToScreen(const Vector2 worldSpacePos)
{
    return Vector2Scale(worldSpacePos, TILE_PIXELS);
}

bool
tilemapIsTileFull(const Tilemap* tilemap, int x, int y)
{
    const Tile tile = tilemapGetTile(tilemap, x, y);
    if (tile == TILE_EMPTY || tile == TILE_ZERO) return false;
    return true;
}

void printTile(void* v) {
    Tilemap* t = (Tilemap*)v;
    for (int i=0; i< TILEMAP_SIZE_X; i++) {
        for (int j=0; j< TILEMAP_SIZE_Y; j++) {
            printf("%c", (*t)[i][j]);
        }
        printf("\n");
    }
}

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


// Function to allocate memory for an array of n Tilemaps
Tilemap* allocateTilemaps(size_t n) {
    Tilemap* newTilemaps = malloc(n * sizeof(Tilemap));
    if (!newTilemaps) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return newTilemaps;
}

// Function to copy an existing Tilemap into the i-th index of the allocated array
void insertLevelInMap(const Tilemap* level, Tilemap* map, size_t pos) {
    memcpy(&map[pos], level, sizeof(Tilemap));  // Copy into the correct index
}

// Function to print a specific Tilemap from an allocated array
void printLevel(const Tilemap* tilemap, size_t i) {
    for (int row = 0; row < TILEMAP_SIZE_Y; row++) {
        printf("%s\n", tilemap[i][row]);  // Print the specific tilemap
    }
}

// Function to free the allocated array of Tilemaps
void freeTilemaps(Tilemap* tilemaps) {
    free(tilemaps);
}

Tilemap *mainTilemap;
size_t numOfLevels = 3;

Tilemap* createTilemap(size_t nLevels) {

  Tilemap* tilemap = allocateTilemaps(nLevels);

  insertLevelInMap(&LEVEL3, tilemap, 0);
  insertLevelInMap(&LEVEL2, tilemap, 1);
  insertLevelInMap(&FLAT_LEVEL, tilemap, 2);
  /* insertLevelInMap(&START_SCREEN, tilemap, 2); */

  return tilemap;
}

void printMap(Tilemap* tilemap) {
    for (size_t i=0; i<numOfLevels; i++) {
        printLevel(tilemap, i);
    }
}

Tilemap* reloadTilemap(size_t nLevels) {

  free(mainTilemap);
  mainTilemap = allocateTilemaps(nLevels);


  return mainTilemap;
}

