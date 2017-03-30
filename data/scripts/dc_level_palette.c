
#ifndef DC_LEVEL_PALETTE
#define DC_LEVEL_PALETTE 1

#define DC_LEVEL_PALETTE_KEY_ELAPSED_LAST "dc_level_palette_elapsed_time_last"

#endif

dc_level_palette(int time_interval, int pallette_cap)
{
    void ent                = NULL;
    int palette_current     = NULL;
    int elapsed_last        = NULL;
    int elapsed_current     = NULL;

    int palette_current = openborvariant("current_palette");

    // Get current and stored elapsed time.
    elapsed_current = openborvariant("elapsed_time");
    elapsed_last    = getlocalvar(DC_LEVEL_PALETTE_KEY_ELAPSED_LAST);

    // Validate elapsed time and reset if nessesary.
    if(!elapsed_last)
    {
        elapsed_last = elapsed_current;
    }

    if((elapsed_current - elapsed_last)  >= time_interval)
    {
        if(palette_current < palette_cap)
        {
            palette_current++;
            changepalette(palette_current);
        }
    }

    setlocalvar(DC_LEVEL_PALETTE_KEY_ELAPSED_LAST, elapsed_last);
}

