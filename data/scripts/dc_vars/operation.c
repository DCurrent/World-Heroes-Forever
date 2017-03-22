// External Dependencies
#include    "data/scripts/dc_error/main.c"

// Package Files
#include    "data/scripts/dc_vars/settings.h"
#import     "data/scripts/dc_vars/validate.c"

// Convert whole integer to floating decimal.
float dc_vars_int_to_float(int value)
{
    int     valid;
    float   result = DC_VARS_DEFAULT_FLOAT;

    // Validate argument type.
    valid = dc_vars_is_integer(value);

    if(valid == DC_VARS_FLAG_FALSE)
    {
        // The argument is invalid. So we'll send an alert and exit the function.

        dc_error_set_function("dc_vars_int_to_float(int value)");
        dc_error_set_message("{value} is not a valid integer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return result;
    }

    // Add a floating decimal of 0.0 to force conversion of
    // value to a decimal type.
    result = value + 0.0;

    // Return result.
    return result;
}

// Return the type of variable as a string.
void dc_vars_type_to_string(int type)
{
    char result;

    // Can't use switch statements with openborcosntant(),
    // so we'll have to settle for an ugly if block.
    if(type == DC_ERROR_TYPE_EMPTY)
    {
        result = "empty";
    }
    else if(type == DC_ERROR_TYPE_FLOAT)
    {
        result = "floating decimal";
    }
    else if(type == DC_ERROR_TYPE_INTEGER)
    {
        result = "integer";
    }
    else if(type == DC_ERROR_TYPE_POINTER)
    {
        result = "pointer";
    }
    else if(type == DC_ERROR_TYPE_STRING)
    {
        result = "string";
    }
    else
    {
        result = "unknown";
    }

    return result;
}
