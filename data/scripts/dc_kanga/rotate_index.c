// Configuration.
#include "data/scripts/dc_kanga/config.h"

// Caskey, Damon V.
// 2016-10-27
//
// Apply target entity's next map index in a continuous loop from
// first to last.
int dc_kanga_rotate_index()
{
    int index_current;  // Current palette in use.
    int index_count;    // Number of palettes entity has loaded.
    void target;        // Target entity.

    // Get target entity.
    target = getlocalvar(DC_KANGA_KEY_TARGET);

    // If the target entity is not valid, then exit.
    if(typeof(target) != openborconstant("VT_PTR")) return index_current;
    if(!getentityproperty(target, "exists")) return index_current;

    // Get number of maps loaded and the entity's current map index.
    index_count     = getentityproperty(target, "mapcount");
    index_current   = getentityproperty(target, "maps", "current");

    // Increment to next index.
    index_current++;

    // If we've passed up the last index, reset to 0.
    if(index_current > index_count)
    {
        index_current = 0;
    }

    // Apply the map index.
    changeentityproperty(target, "map", index_current);

    return index_current;
}
