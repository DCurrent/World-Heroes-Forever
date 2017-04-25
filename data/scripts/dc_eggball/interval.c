#include "data/scripts/dc_eggball/config.h"

int dc_eggball_interval(void instance)
{
    int result;
    int elapsed_current;    // Current gametime.
    int interval;           // Time interval.
    int last_occurrence;    // Time of triggered instance.
    int difference;         // Time difference.

    // Populate in-line vars.
    result          = DC_EGGBALL_FLAG_FALSE;
    elapsed_current = openborvariant("elapsed_time");
    last_occurrence = getlocalvar(DC_EGGBALL_LAST + instance);
    interval        = getlocalvar(DC_EGGBALL_INTERVAL + instance);

    // If last occurrence is empty or
    // exceeds elapsed time then re-zero.
    if(!last_occurrence || last_occurrence > elapsed_current)
    {
        last_occurrence = 0;
    }

    // If no interval is set, then use default.
    if(typeof(interval) == openborconstant("VT_EMPTY"))
    {
        interval = DC_EGGBALL_DEFAULT_INTERVAL;
    }

    // Get difference between last_occurrence
    // and elapsed_current.
    difference = elapsed_current - last_occurrence;

    // Once difference is met, perform
    // action and record last occurrence
    // for the next cycle.
    if(difference >= interval)
    {
        result = DC_EGGBALL_FLAG_TRUE;
        setlocalvar(DC_EGGBALL_LAST + instance, elapsed_current);
    }

    return result;
}



