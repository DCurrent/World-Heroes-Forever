
#ifndef DC_LEVEL_PALETTE
#define DC_LEVEL_PALETTE 1

#define DC_LEVEL_PALETTE_KEY_ELAPSED_LAST "dc_level_palette_elapsed_time_last"

// Variable types
#define DC_LEVEL_VT_EMPTY                  openborconstant("VT_EMPTY")     // Empty (NULL) variable type.
#define DC_LEVEL_VT_FLOAT                  openborconstant("VT_DECIMAL")   // Float variable type.
#define DC_LEVEL_VT_INTEGER                openborconstant("VT_INTEGER")   // Integer variable type.
#define DC_LEVEL_VT_POINTER                openborconstant("VT_PTR")       // Pointer variable type.

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
    elapsed_last    = getindexedvar(DC_LEVEL_PALETTE_KEY_ELAPSED_LAST);

    // Make sure elapsed last is an interger value. Set to 0 otherwise.
    if(typeof(elpased_last) != DC_LEVEL_VT_INTEGER)
    {
        elapsed_last = 0;
    }

    if(elapsed_last >= time_interval)
    {
        if(palette_current < palette_cap)
        {
            palette_cap++;
            changepalette(palette_cap);
        }
    }

    setindexedvar(DC_LEVEL_PALETTE_KEY_ELAPSED_LAST, elapsed_last);
}
