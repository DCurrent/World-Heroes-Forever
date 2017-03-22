// External Dependencies
#include    "data/scripts/dc_error/main.c"

// Package Files
#include    "data/scripts/dc_vars/settings.h"
#import     "data/scripts/dc_vars/validate.c"
#import     "data/scripts/dc_vars/local.c"

// Return lower bound setting for random numbers.
int dc_vars_get_random_lower_bound()
{
    int result;

    result = dc_vars_get_local_int(DC_VARS_VARKEY_RND_LOWER);

    return result;
}

// Return upper bound setting for random numbers.
int dc_vars_get_random_upper_bound()
{
    int result;

    result = dc_vars_get_local_int(DC_VARS_VARKEY_RND_UPPER);

    return result;
}

// Set lower bound for random numbers.
int dc_vars_set_random_lower_bound(int value)
{
    int result;
    int is_set;

    // set the value, and record result.
    is_set = dc_vars_set_local_int(DC_VARS_VARKEY_RND_LOWER, value);

    if(is_set == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_function("dc_vars_set_random_lower_bound(float value)");
        dc_error_set_message("Unable to set. Check for log for type alerts.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    return DC_VARS_FLAG_TRUE;
}

// Set upper bound for random numbers.
int dc_vars_set_random_upper_bound(int value)
{
    int result;
    int is_set;

    // set the value, and record result.
    is_set = dc_vars_set_local_int(DC_VARS_VARKEY_RND_UPPER, value);

    if(is_set == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_function("dc_vars_set_random_upper_bound(float value)");
        dc_error_set_message("Unable to set. Check for log for type alerts.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    return DC_VARS_FLAG_TRUE;
}

// Generate random value of 0 to 100, or between
// upper and lower boundaries if set.
int dc_vars_get_random_int()
{
    int     result;
    int     lower_bound,
            upper_bound,
            mod;

    // Get upper and lower bound settings.
    lower_bound = dc_vars_get_random_lower_bound();
    upper_bound = dc_vars_get_random_upper_bound();

    // Default lower and upper bounds to 0 and
    // 100 respectively if there is no existing
    // setting in place.
    if(lower_bound == DC_VARS_DEFAULT_INTEGER)
    {
        lower_bound = 0;
    }

    if(upper_bound == DC_VARS_DEFAULT_INTEGER)
    {
        upper_bound = 100;
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
