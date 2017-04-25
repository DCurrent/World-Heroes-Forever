#include "data/scripts/dc_sundown/config.h"


// Increments to next available global palette.
int dc_sundown_global_increment()
{
    int palette_current;    // Index of current global palette in use.
    int palette_cap;        // Number of global palettes available.

    // Get palette cap and palette in use.
    palette_cap     = openborvariant("numpalettes");
    palette_current = openborvariant("current_palette");

    // If the current palette index is less than last palette
    // index available, then increment the global palette
    // one index.
    if(palette_current < palette_cap)
    {
        palette_current++;
        changepalette(palette_current);
    }

    // Return the latest current index.
    return palette_current;
}



