// Package Files
#include    "data/scripts/dc_d20/config.h"

// Generate random value between
// upper and lower boundaries.
int dc_d20_random_int()
{
    int     result;
    int     lower_bound,
            upper_bound,
            mod;

    // Get upper and lower bound settings.
    lower_bound = getlocalvar(DC_D20_KEY_LOWER);
    upper_bound = getlocalvar(DC_D20_KEY_UPPER);

    // Default lower and upper bounds if there is no existing
    // setting in place.
    if(typeof(lower_bound) == openborconstant("VT_EMPTY"))
    {
        lower_bound = DC_D20_DEFAULT_LOWER;
    }

    if(typeof(upper_bound) == openborconstant("VT_EMPTY"))
    {
        upper_bound = DC_D20_DEFAULT_UPPER;
    }

    // OpenBOR's random generator is a bit odd,
    // so we'll need to do some math work to get
    // usable values.

    // Find difference between desired min and max,
    // then add 1 to create random seed.
    mod = (upper_bound - lower_bound) + 1;

    // Generate random number.
    result  = rand()%mod;

    // If resulting random number is negative, convert to positive.
    if (result < 0)
    {
        result = result * -1;
    }

    // Add minimum for final result.
    result = result + lower_bound;

    // Return final result.
    return result;
}
