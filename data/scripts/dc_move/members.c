// External Dependencies
#include    "data/scripts/dc_vars/main.c"
#include    "data/scripts/dc_error/main.c"

// Internal library
#include    "data/scripts/dc_move/settings.h"
#import     "data/scripts/dc_move/velocity.c"

// Accessors
void dc_move_get_entity()
{
    return dc_vars_get_local_pointer(DC_MOVE_VARKEY_ENTITY);
}

int dc_move_get_key_hold()
{
    int result;

    result = dc_vars_get_local_int(DC_MOVE_VARKEY_KEY_HOLD);

    return result;
}

int dc_move_get_key_press()
{
    return dc_vars_get_local_int(DC_MOVE_VARKEY_KEY_PRESS);
}

float dc_move_get_max_height()
{
    float result;

    result = dc_vars_get_local_float(DC_MOVE_VARKEY_MAX_HEIGHT);

    // If there was no setting, then use
    // the default.
    if(result == 0.0)
    {
        result = DC_MOVE_MAXIMUM_HEIGHT;
    }

    return result;
}

// Mutators
int dc_move_set_entity(void value)
{
    int is_ent; // Valid type flag.
    int result; // Final result.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_set_entity(void value)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_ent = dc_vars_is_entity(value);

    if(is_ent == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    result = dc_vars_set_local_pointer(DC_MOVE_VARKEY_ENTITY, value);

    // Return result of operation. Should be true if
    // we made it this far.
    return result;
}

int dc_move_set_key_hold(int value)
{
    int is_int; // Valid type flag.
    int result; // Final result.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_set_key_hold(void value)");

    // Validate the integer.
    is_int = dc_vars_is_integer(value);

    if(is_int == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid whole integer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    result = dc_vars_set_local_int(DC_MOVE_VARKEY_KEY_HOLD, value);

    return result;
}

int dc_move_set_key_press(int value)
{
    int is_int; // Valid type flag.
    int result; // Final result.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_set_key_press(void value)");

    // Validate the integer.
    is_int = dc_vars_is_integer(value);

    if(is_int == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid whole integer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    result = dc_vars_set_local_int(DC_MOVE_VARKEY_KEY_PRESS, value);

    return result;
}

int dc_move_set_max_height(float value)
{
    int is_num; // Valid type flag.
    int result; // Final result.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_set_max_height(float value)");

    // Validate the integer.
    is_num = dc_vars_is_numeric(value);

    if(is_num == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid floating decimal or whole integer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    result = dc_vars_set_local_int(DC_MOVE_VARKEY_MAX_HEIGHT, value);

    return result;
}

int dc_move_set_disable_time(int value)
{
    int is_int;     // Valid type flag.
    int is_empty;   // Valid type flag.
    int result;     // Final result.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_set_disable_time(int value)");

    // Validate the integer.
    is_int = dc_vars_is_integer(value);

    if(is_int == DC_VARS_FLAG_FALSE
       && is_empty == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be NULL() or a whole integer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the variable.
    result = dc_vars_set_local_int(DC_MOVE_VARKEY_DISABLE, value);

    return result;

}
