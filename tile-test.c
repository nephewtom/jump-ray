#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TILEMAP_SIZE_X 16
#define TILEMAP_SIZE_Y 12
#define TILE_PIXELS 16

typedef uint8_t Tilemap[TILEMAP_SIZE_Y][TILEMAP_SIZE_X + 1];

Tilemap staticMap = {
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
};

Tilemap oneMap = {
  "uno ############",
  "#              #",
  "#      #       #",
  "#     ##       #",
  "#    # #       #",
  "#      #       #",
  "#      #       #",
  "#      #       #",
  "#      #       #",
  "#      #       #",
  "#              #",
  "################",
};

Tilemap twoMap = {
  "dos ############",
  "#              #",
  "#     ####     #",
  "#    #    #    #",
  "#        #     #",
  "#       #      #",
  "#      #       #",
  "#     #        #",
  "#    #         #",
  "#    ######    #",
  "#              #",
  "################",
};

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
void insertLevelInTilemap(Tilemap* destArray, size_t i, const Tilemap* src) {
  memcpy(&destArray[i], src, sizeof(Tilemap));  // Copy into the correct index
}

// Function to print a specific Tilemap from an allocated array
void printTilemap(const Tilemap* tilemaps, size_t i) {
  for (int row = 0; row < TILEMAP_SIZE_Y; row++) {
    printf("%s\n", tilemaps[i][row]);  // Print the specific tilemap
  }
}

// Function to free the allocated array of Tilemaps
void freeTilemaps(Tilemap* tilemaps) {
  free(tilemaps);
}


int main() {
  
  printTilemap(&staticMap, 0);

  size_t numTilemaps = 3;
  Tilemap* screenTilemaps = allocateTilemaps(numTilemaps);

  uint8_t *tilemaps = (uint8_t*) screenTilemaps;
   
  // Copy LEVEL1 and LEVEL2 into the allocated array
  insertLevelInTilemap(screenTilemaps, 0, &oneMap);
  insertLevelInTilemap(screenTilemaps, 1, &twoMap);

  for (size_t i=0; i < numTilemaps; i++) {
    
    printf("Tilemap %llu:\n", i);
    printTilemap(screenTilemaps, i);
  }

  return 0;
}
