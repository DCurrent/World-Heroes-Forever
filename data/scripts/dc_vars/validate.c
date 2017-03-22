#include    "data/scripts/dc_vars/settings.h"
#include    "data/scripts/dc_error/main.c"

// Return true if value is NULL() or empty.
int dc_vars_is_empty(void value)
{
    int type;
    int result;

    // Get variable type.
    type = typeof(value);

    // Evaluate type.
    if(type == DC_VARS_TYPE_EMPTY)
    {
        result = DC_VARS_FLAG_TRUE;
    }
    else
    {
        result = DC_VARS_FLAG_FALSE;
    }

    // Return result.
    return result;
}

// Return true if value is a valid entity pointer.
int dc_vars_is_entity(void entity)
{
    int is_pointer;
    int exists;

    // Is value a valid pointer?
    is_pointer = dc_vars_is_pointer(entity);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        return DC_VARS_FLAG_FALSE;
    }

    // OK, so we know the value is a pointer, but
    // does the entity actually exist? It's possible
    // that the entity is removed, but the pointer
    // is not.
    exists = getentityproperty(entity, "exists");

    if(exists == DC_VARS_FLAG_FALSE)
    {
        return DC_VARS_FLAG_FALSE;
    }

    // Return result.
    return DC_VARS_FLAG_TRUE;
}

// Return true if value is a floating decimal.
int dc_vars_is_float(float value)
{
    int type;
    int result;

    // Get variable type.
    type = typeof(value);

    // Evaluate type.
    if(type == DC_VARS_TYPE_FLOAT)
    {
        result = DC_VARS_FLAG_TRUE;
    }
    else
    {
        result = DC_VARS_FLAG_FALSE;
    }

    // Return result.
    return result;
}

// Return true if value is a whole integer.
int dc_vars_is_integer(int value)
{
    int type;
    int result;

    // Get variable type.
    type = typeof(value);

    // Evaluate type.
    if(type == DC_VARS_TYPE_INTEGER)
    {
        result = DC_VARS_FLAG_TRUE;
    }
    else
    {
        result = DC_VARS_FLAG_FALSE;
    }

    // Return result.
    return result;
}

// Return true if value can be used as a variable identifier key.
int dc_vars_is_key(void value)
{
    int type;
    int result;

    // Get variable type.
    type = typeof(value);

    // Evaluate type vs. valid choices.
    if(type == DC_VARS_TYPE_INTEGER
       || type == DC_VARS_TYPE_POINTER
       || type == DC_VARS_TYPE_STRING)
    {
        result = DC_VARS_FLAG_TRUE;
    }
    else
    {
        result = DC_VARS_FLAG_FALSE;
    }

    // Return result.
    return result;
}

// Return true if value is a valid integer or floating decimal.
int dc_vars_is_numeric(void value)
{
    int type;
    int result;

    // Get variable type.
    type = typeof(value);

    // Evaluate type vs. valid choices.
    if(type == DC_VARS_TYPE_FLOAT
       || type == DC_VARS_TYPE_INTEGER)
    {
        result = DC_VARS_FLAG_TRUE;
    }
    else
    {
        result = DC_VARS_FLAG_FALSE;
    }

    // Return result.
    return result;
}

// Return true if value is a pointer.
int dc_vars_is_pointer(void value)
{
    int type;
    int result;

    // Get variable type.
    type = typeof(value);

    // Evaluate type.
    if(type == DC_VARS_TYPE_POINTER)
    {
        result = DC_VARS_FLAG_TRUE;
    }
    else
    {
        result = DC_VARS_FLAG_FALSE;
    }

    // Return result.
    return result;
}

// Return true if value is a string.
int dc_vars_is_string(void value)
{
    int type;
    int result;

    // Get variable type.
    type = typeof(value);

    // Evaluate type.
    if(type == DC_VARS_TYPE_STRING)
    {
        result = DC_VARS_FLAG_TRUE;
    }
    else
    {
        result = DC_VARS_FLAG_FALSE;
    }

    // Return result.
    return result;
}
