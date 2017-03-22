// External Dependencies
#include    "data/scripts/dc_error/main.c"

// Package Files
#include    "data/scripts/dc_vars/settings.h"
#import     "data/scripts/dc_vars/validate.c"

// Clear an script scope variable.
int dc_vars_clear_local_var(void key)
{
    int is_key; // Valid key flag.

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_function("dc_vars_clear_local_var(void key)");
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    setscriptvar(key, NULL());

    return DC_VARS_FLAG_TRUE;
}

// Get an script scope float.
float dc_vars_get_local_float(void key)
{
    float   result = DC_VARS_DEFAULT_FLOAT, // Final result.
            temp;                           // Temp result.

    int is_key;                             // Valid key flag.
    int is_float;                           // Valid type flag.

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_function("dc_vars_get_local_float(void key)");
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return result;
    }

    // Get the variable.
    temp = getscriptvar(key);

    // If the temp value is the right type, apply it to
    // result. Otherwise the the value is probably empty
    // or an invalid type managed to slip through. In that
    // case, we'll just leave the result to its default value.
    is_float = dc_vars_is_float(temp);

    if(is_float == DC_VARS_FLAG_TRUE)
    {
        result = temp;
    }

    // Return the value.
    return result;
}

// Set an script scope float.
int dc_vars_set_local_float(void key, float value)
{
    int is_key;     // Valid key flag.
    int is_float;   // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_local_float(void key, float value)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate the value argument. It must be the proper type. If not,
    // we will return false without setting anything.
    is_float = dc_vars_is_float(value);

    if(is_float == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a floating decimal.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    setscriptvar(key, value);

    return DC_VARS_FLAG_TRUE;
}

// Get an script scope integer.
int dc_vars_get_local_int(void key)
{
    int result = DC_VARS_DEFAULT_INTEGER,   // Final result.
        temp;                               // Temp result.

    int is_key;                             // Valid key flag.
    int is_int;                             // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_get_local_int(void key)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return result;
    }

    // Get the variable.
    temp = getscriptvar(key);

    // If the temp value is the right type, apply it to
    // result. Otherwise the the value is probably empty
    // or an invalid type managed to slip through. In that
    // case, we'll just leave the result to its default value.
    is_int = dc_vars_is_integer(temp);

    if(is_int == DC_VARS_FLAG_TRUE)
    {
        result = temp;
    }

    // Return the value.
    return result;
}

// Set an script scope integer.
int dc_vars_set_local_int(void key, int value)
{
    int is_key; // Valid key flag.
    int is_int; // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_local_int(void key, int value)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate the value argument. It must be the proper type. If not,
    // we will return false without setting anything.
    is_int = dc_vars_is_integer(value);

    if(is_int == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a whole integer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    setscriptvar(key, value);

    return DC_VARS_FLAG_TRUE;
}

// Get an script scope pointer.
void dc_vars_get_local_pointer(void key)
{
    void    result = DC_VARS_DEFAULT_POINTER,   // Final result.
            temp;                               // Temp result.

    int is_key;                                 // Valid key flag.
    int is_pointer;                             // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_get_local_pointer(void key)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return result;
    }

    // Get the variable.
    temp = getscriptvar(key);

    // If the temp value is the right type, apply it to
    // result. Otherwise the the value is probably empty
    // or an invalid type managed to slip through. In that
    // case, we'll just leave the result to its default value.
    is_pointer = dc_vars_is_pointer(temp);

    if(is_pointer == DC_VARS_FLAG_TRUE)
    {
        result = temp;
    }

    // Return the value.
    return result;
}

// Set an script scope pointer.
int dc_vars_set_local_pointer(void key, void value)
{
    int is_key;     // Valid key flag.
    int is_pointer; // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_local_pointer(void key, void pointer)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate the value argument. It must be the proper type. If not,
    // we will return false without setting anything.
    is_pointer = dc_vars_is_pointer(value);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid pointer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    setscriptvar(key, value);

    return DC_VARS_FLAG_TRUE;
}

// Get an script scope string.
void dc_vars_get_local_string(void key)
{
    void    result = DC_VARS_DEFAULT_STRING,
            temp;

    int is_key;
    int is_string;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_get_local_string(void key)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return result;
    }

    // Get the variable.
    temp = getscriptvar(key);

    // If the temp value is the right type, apply it to
    // result. Otherwise the the value is probably empty
    // or an invalid type managed to slip through. In that
    // case, we'll just leave the result to its default value.
    is_string = dc_vars_is_string(result);

    if(is_string == DC_VARS_FLAG_TRUE)
    {
        result = temp;
    }

    // Return the value.
    return result;
}

// Set an script scope string.
int dc_vars_set_local_string(void key, int value)
{
    int is_key;     // Valid key flag.
    int is_string;  // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_local_string(void key, void string)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate the value argument. It must be the proper type. If not,
    // we will return false without setting anything.
    is_string = dc_vars_is_string(value);

    if(is_string == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid string.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    setscriptvar(key, value);

    return DC_VARS_FLAG_TRUE;
}
