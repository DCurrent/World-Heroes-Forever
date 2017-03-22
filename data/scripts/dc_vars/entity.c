// External Dependencies
#include    "data/scripts/dc_error/main.c"

// Package Files
#include    "data/scripts/dc_vars/settings.h"
#import     "data/scripts/dc_vars/validate.c"




// Clear an entity scope variable.
int dc_vars_clear_entity_var(void entity, void key)
{
    int is_pointer; // Valid type flag.
    int is_key;     // Valid key flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_clear_entity_var(void entity, void key)");

    // Validate the entity. It must be a valid pointer.
    is_pointer = dc_vars_is_key(entity);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        //log("\n Error: dc_vars_clear_entity_var(void entity, void key) ");
        //log("- {entity} must be a valid pointer.");

        log("\n");
        log("\n {entity}");
        log("\n -- Type: ");
        //log(dc_vars_type_to_string(typeof(entity)));
        log("\n -- Value: ");
        log(entity);

        log("\n");
        log("\n {key}");
        log("\n -- Type: ");
        //log(dc_vars_type_to_string(typeof(key)));
        log("\n -- Value: ");
        log(key);


        dc_error_set_message("{entity} must be a valid pointer.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    setentityvar(entity, key, NULL());

    return DC_VARS_FLAG_TRUE;
}

// Get an entity scope float.
float dc_vars_get_entity_float(void entity, void key)
{
    float   result = DC_VARS_DEFAULT_FLOAT, // Final result.
            temp;                           // Temp result.

    int is_pointer;                         // Valid type flag.
    int is_key;                             // Valid key flag.
    int is_float;                           // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_get_entity_float(void entity, void key)");

    // Validate the entity pointer. Unlike setting the variable, for getting
    // it's OK if the entity no longer exists, since it's quite possible for
    // an entity to be destroyed after an entity variable was set to it.
    is_pointer = dc_vars_is_pointer(entity);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return result;
    }

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
    temp = getentityvar(entity, key);

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

// Set an entity scope float.
int dc_vars_set_entity_float(void entity, void key, float value)
{
    int is_ent;     // Valid ent flag.
    int is_key;     // Valid key flag.
    int is_float;   // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_entity_float(void entity, void key, float value)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_ent = dc_vars_is_entity(entity);

    if(is_ent == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

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
    setentityvar(entity, key, value);

    return DC_VARS_FLAG_TRUE;
}

// Get an entity scope int.
int dc_vars_get_entity_int(void entity, void key)
{
    int   result = DC_VARS_DEFAULT_INTEGER, // Final result.
            temp;                           // Temp result.

    int is_pointer;                         // Valid type flag.
    int is_key;                             // Valid key flag.
    int is_int;                           // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_get_entity_int(void entity, void key)");

    // Validate the entity pointer. Unlike setting the variable, for getting
    // it's OK if the entity no longer exists, since it's quite possible for
    // an entity to be destroyed after an entity variable was set to it.
    is_pointer = dc_vars_is_pointer(entity);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return result;
    }

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
    temp = getentityvar(entity, key);

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

// Set an entity scope int.
int dc_vars_set_entity_int(void entity, void key, int value)
{
    int is_ent;     // Valid ent flag.
    int is_key;     // Valid key flag.
    int is_int;   // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_entity_int(void entity, void key, int value)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_ent = dc_vars_is_entity(entity);

    if(is_ent == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

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
    setentityvar(entity, key, value);

    return DC_VARS_FLAG_TRUE;
}

// Get an entity scope pointer.
int dc_vars_get_entity_pointer(void entity, void key)
{
    void   result = DC_VARS_DEFAULT_POINTER,    // Final result.
            temp;                               // Temp result.

    int is_pointer;                             // Valid type flag.
    int is_key;                                 // Valid key flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_get_entity_pointer(void entity, void key)");

    // Validate the entity pointer. Unlike setting the variable, for getting
    // it's OK if the entity no longer exists, since it's quite possible for
    // an entity to be destroyed after an entity variable was set to it.
    is_pointer = dc_vars_is_pointer(entity);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return result;
    }

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
    temp = getentityvar(entity, key);

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

// Set an entity scope pointer.
int dc_vars_set_entity_pointer(void entity, void key, int value)
{
    int is_ent;     // Valid ent flag.
    int is_key;     // Valid key flag.
    int is_pointer; // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_entity_pointer(void entity, void key, int value)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_ent = dc_vars_is_entity(entity);

    if(is_ent == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

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
    setentityvar(entity, key, value);

    return DC_VARS_FLAG_TRUE;
}

// Get an entity scope string.
void dc_vars_get_entity_string(void entity, void key)
{
    void   result = DC_VARS_DEFAULT_STRING,     // Final result.
            temp;                               // Temp result.

    int is_pointer;                             // Valid type flag.
    int is_key;                                 // Valid key flag.
    int is_string;                             // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_get_entity_string(void entity, void key)");

    // Validate the entity pointer. Unlike setting the variable, for getting
    // it's OK if the entity no longer exists, since it's quite possible for
    // an entity to be destroyed after an entity variable was set to it.
    is_string = dc_vars_is_string(entity);

    if(is_string == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return result;
    }

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
    temp = getentityvar(entity, key);

    // If the temp value is the right type, apply it to
    // result. Otherwise the the value is probably empty
    // or an invalid type managed to slip through. In that
    // case, we'll just leave the result to its default value.
    is_string = dc_vars_is_string(temp);

    if(is_string == DC_VARS_FLAG_TRUE)
    {
        result = temp;
    }

    // Return the value.
    return result;
}

// Set an entity scope string.
int dc_vars_set_entity_string(void entity, void key, int value)
{
    int is_ent;     // Valid ent flag.
    int is_key;     // Valid key flag.
    int is_string; // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_entity_string(void entity, void key, int value)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_ent = dc_vars_is_entity(entity);

    if(is_ent == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

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
    setentityvar(entity, key, value);

    return DC_VARS_FLAG_TRUE;
}
