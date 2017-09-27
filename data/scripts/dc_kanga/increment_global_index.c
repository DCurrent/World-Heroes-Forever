// Configuration.
#include "data/scripts/dc_kanga/config.h"

// Caskey, Damon V.
// 2016-10-27
//
// Increments to next available global palette.
int dc_kanga_increment_global_index()
{
    int index_current;    // Index of current global palette in use.
    int index_count;      // Number of global palettes available.

    // Get palette cap and palette in use.
    index_count     = openborvariant("numpalettes");
    index_current = openborvariant("current_palette");

    // If the current palette index is less than last palette
    // index available, then increment the global palette
    // one index.
    if(index_current < index_count)
    {
        index_current++;
        changepalette(index_current);
    }

    // Return the latest current index.
    return index_current;
}



