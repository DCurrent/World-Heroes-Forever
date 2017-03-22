#include "data/scripts/dc_sundown/config.h"

int dc_level_palette(int time_interval)
{
    int palette_current;    // Current level palette in use.
    int elapsed_current;    // Current gametime.
    int palette_cap;        // Number of level palettes available.
    int trigger;            // Time to perform next palette increment.

    // Get palette cap and palette in use.
    palette_cap     = openborvariant("numpalettes");
    palette_current = openborvariant("current_palette");

    // Get current and stored elapsed time.
    elapsed_current = openborvariant("elapsed_time");
    trigger    = getglobalvar(DC_LEVEL_PALETTE_KEY_ELAPSED_LAST);

    // If trigger time is empty, initialize 0
    // to enable logical math.
    if(!trigger)
    {
        trigger = 0;
    }

    // IF the current palette is less than last palette available,
    // we will then perform a time check to see if the current
    // palette should be incremented.
    if(palette_current < palette_cap)
    {
        // Has current time surpassed the set time? If so, we will
        // increment the level palette once, and then reset the trigger
        // time by adding current time plus our time interval
        // argument.
        if(elapsed_current >= trigger)
        {
            palette_current++;
            changepalette(palette_current);

            setglobalvar(DC_LEVEL_PALETTE_KEY_ELAPSED_LAST, elapsed_current + time_interval);
        }
    }
    else
    {
        // If we're already at last palette, there is nothing more
        // for our function to do. Makesure the global variable we
        // used is clear.
        setglobalvar(DC_LEVEL_PALETTE_KEY_ELAPSED_LAST, NULL());
    }

    // Return the current palette.
    return palette_current;
}
