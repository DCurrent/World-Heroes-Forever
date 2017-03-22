#ifndef DC_PALETTE_ROTATE
#define DC_PALETTE_ROTATE 1

// Variable types
#define DC_PALETTE_ROTATE_VT_POINTER    openborconstant("VT_PTR")       // Pointer variable type.

#endif

int dc_palette_rotate(void ent)
{

    int pal_current;    // Current palette in use.
    int pal_max;        // Number of palettes entity has loaded.

    // If target entity is not provided, default to calling entity.
    if(typeof(ent) != DC_PALETTE_ROTATE_VT_POINTER)
    {
        ent = getlocalvar("self");
    }

    // Get number of maps loaded and the entity's current map index.
    pal_max     = getentityproperty(ent, "mapcount");
    pal_current = getentityproperty(ent, "maps", "current");

    // Increment palette map to next index.
    pal_current++;

    // If we've passed up the last palette index, reset to 0.
    if(pal_current > pal_max)
    {
        pal_current = 0;
    }

    // Apply the map index.
    changeentityproperty(ent, "map", pal_current);

    return pal_current;
}
