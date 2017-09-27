// Configuration.
#include "data/scripts/dc_kanga/config.h"

// Caskey, Damon V.
// 2016-09-27
//
// Apply random map index to target entity, avoiding
// hidden map range. Returns map index applied.
int dc_kanga_random_index()
{
    int map_count;              // Number of maps the entity has.
    int map_hidden_lower;       // Hidden maps range (lower boundary).
    int map_hidden_lower_vt;    // Hidden maps range, variable type (lower boundary).
    int map_hidden_upper;       // Hidden maps range (upper boundary).
    int map_hidden_upper_vt;    // Hidden maps range, variable type (upper boundary).
    int result;                 // Map to apply and return as final result.
    void target;                // Target entity.

    // Get target entity.
    target = getlocalvar(DC_KANGA_KEY_TARGET);

    // If the target entity is not valid, then exit.
    if(typeof(target) != openborconstant("VT_PTR")) return result;
    if(!getentityproperty(target, "exists")) return result;

    // Get map attributes.
    map_count           = getentityproperty(target, "mapcount");
    map_hidden_lower    = getentityproperty(target, "hmapl");
    map_hidden_upper    = getentityproperty(target, "hmapu");

    // Set range for random number generator.
    setlocalvar(DC_D20_KEY_LOWER, 0);
    setlocalvar(DC_D20_KEY_UPPER, map_count);

    // Generate random map value.
    result = dc_d20_random_int();

    // Get variable type of hidden ranges. This is so we
    // can verify there are hidden ranges. You can't just
    // a simple (!map_hidden_upper) because the range might
    // exist but have value of 0.
    map_hidden_lower_vt = typeof(map_hidden_lower);
    map_hidden_upper_vt = typeof(map_hidden_upper);

    // Do we have valid hidden map values?
    if(map_hidden_lower_vt != openborconstant("VT_EMPTY") && map_hidden_lower_vt != openborconstant("VT_EMPTY"))
    {
        // If the random map value falls within hidden range,
        // generate a new value.
        while(result >= map_hidden_lower && result <= map_hidden_upper)
        {
           result = dc_d20_random_int();
        }
    }

    // Apply the map value to target entity.
    changeentityproperty(target, "map", result);

    // Return result.
    return result;
}
