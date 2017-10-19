#ifndef DC_AFTERIMAGE

#define DC_AFTERIMAGE

#define DC_AFTERIMAGE_KEY_SPRITE        0
#define DC_AFTERIMAGE_KEY_POS_X         1
#define DC_AFTERIMAGE_KEY_POS_Y         2
#define DC_AFTERIMAGE_KEY_POS_Z         3
#define DC_AFTERIMAGE_KEY_POS_DIRECTION 4   // Direction
#define DC_AFTERIMAGE_KEY_POS_CD        5   // Tracker. To be removed.

#endif


int trailermax = 50; //total trailers the engine can handle
int trailerc = 8; // totally 5 trailer images for each character
int trailerd = 7; // delay to spawn next trailer, so trailer lasts for trailermax*trailerd
