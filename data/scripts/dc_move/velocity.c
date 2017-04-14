// External Dependencies
#include    "data/scripts/dc_vars/main.c"
#include    "data/scripts/dc_error/main.c"

// Internal library
#include    "data/scripts/dc_move/settings.h"

// Adjust entity X axis velocity. Defaults to self if no
// valid entity is provided. Returns newly adjusted velocity.
float dc_move_adjust_velocity_x(void entity, float modifier)
{
    // Valid type flags.
    int     is_entity,
            is_float;

    // Velocity values.
    float   vel_x,
            vel_y,
            vel_z;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_adjust_velocity_x(void entity, float modifier)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_entity = dc_vars_is_entity(entity);

    if(is_entity == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Validate velocity value.
    is_float = dc_vars_is_float(modifier);

    if(is_float == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{Modifier} must be a valid floating point decimal.");
        dc_error_set_argument(modifier);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Get current velocities. OpenBOR script does not
    // allow setting just one velocity axis at a time, so we'll
    // get all current velocity values here and apply them along
    // with the one we wish to modify.
    vel_x = getentityproperty(entity, "xdir");
    vel_y = getentityproperty(entity, "tossv");
    vel_z = getentityproperty(entity, "zdir");

    // Apply our velocity modifier. All we need to do is
    // add the values together.
    vel_x += modifier;

    // Now we apply the velocities to target entity.
    changeentityproperty(entity, "velocity", vel_x, vel_z, vel_y);

    // Return the new velocity.
    return vel_x;
}

// Adjust entity Y axis velocity. Defaults to self if no
// valid entity is provided. Returns newly adjusted velocity.
float dc_move_adjust_velocity_y(void entity, float modifier)
{
    // Valid type flags.
    int     is_entity,
            is_float;

    // Velocity values.
    float   vel_x,
            vel_y,
            vel_z;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_adjust_velocity_y(void entity, float modifier)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_entity = dc_vars_is_entity(entity);

    if(is_entity == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Validate velocity value.
    is_float = dc_vars_is_float(modifier);

    if(is_float == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{Modifier} must be a valid floating point decimal.");
        dc_error_set_argument(modifier);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Get current velocities. OpenBOR script does not
    // allow setting just one velocity axis at a time, so we'll
    // get all current velocity values here and apply them along
    // with the one we wish to modify.
    vel_x = getentityproperty(entity, "xdir");
    vel_y = getentityproperty(entity, "tossv");
    vel_z = getentityproperty(entity, "zdir");

    // Apply our velocity modifier. All we need to do is
    // add the values together.
    vel_y += modifier;

    // Now we apply the velocities to target entity.
    changeentityproperty(entity, "velocity", vel_x, vel_z, vel_y);

    // Return new velocity.
    return vel_y;
}

// Adjust entity Z axis velocity. Defaults to self if no
// valid entity is provided. Returns newly adjusted velocity.
float dc_move_adjust_velocity_z(void entity, float modifier)
{
    // Valid type flags.
    int     is_entity,
            is_float;

    // Velocity values.
    float   vel_x,
            vel_y,
            vel_z;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_adjust_velocity_z(void entity, float modifier)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_entity = dc_vars_is_entity(entity);

    if(is_entity == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Validate velocity value.
    is_float = dc_vars_is_float(modifier);

    if(is_float == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{Modifier} must be a valid floating point decimal.");
        dc_error_set_argument(modifier);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Get current velocities. OpenBOR script does not
    // allow setting just one velocity axis at a time, so we'll
    // get all current velocity values here and apply them along
    // with the one we wish to modify.
    vel_x = getentityproperty(entity, "xdir");
    vel_y = getentityproperty(entity, "tossv");
    vel_z = getentityproperty(entity, "zdir");

    // Apply our velocity modifier. All we need to do is
    // add the values together.
    vel_z += modifier;

    // Now we apply the velocities to target entity.
    changeentityproperty(entity, "velocity", vel_x, vel_z, vel_y);

    // Return new velocity.
    return vel_z;
}

// Get entity X axis velocity.
float dc_move_get_velocity_x(void entity)
{
    // Valid type flags.
    int     is_entity;

    // Final result.
    float   result;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_get_velocity_x(void entity)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_entity = dc_vars_is_entity(entity);

    if(is_entity == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Get the velocity value.
    result = getentityproperty(entity, "xdir");

    // Return result.
    return result;
}

// Get entity Y axis velocity.
float dc_move_get_velocity_y(void entity)
{
    // Valid type flags.
    int     is_entity;

    // Final result.
    float   result;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_get_velocity_y(void entity)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_entity = dc_vars_is_entity(entity);

    if(is_entity == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Get the velocity value.
    result = getentityproperty(entity, "tossv");

    // Return result.
    return result;
}

// Get entity Z axis velocity.
float dc_move_get_velocity_z(void entity)
{
    // Valid type flags.
    int     is_entity;

    // Final result.
    float   result;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_get_velocity_z(void entity)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_entity = dc_vars_is_entity(entity);

    if(is_entity == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Get the velocity value.
    result = getentityproperty(entity, "zdir");

    // Return result.
    return result;
}

// Set entity X axis velocity.
int dc_move_set_velocity_x(void entity, float velocity)
{
    // Valid type flags.
    int     is_entity,
            is_float;

    // Velocity values.
    float   vel_x,
            vel_y,
            vel_z;

    // Get velocities values to apply. OpenBOR script does not
    // allow setting just one velocity axis at a time, so we'll
    // get all current velocity values here and apply them along
    // with the one we wish to modify.
    vel_x = velocity;
    vel_y = getentityproperty(entity, "tossv");
    vel_z = getentityproperty(entity, "zdir");

    // Now we apply the velocities to target entity.
    changeentityproperty(entity, "velocity", vel_x, vel_z, vel_y);

    return DC_VARS_FLAG_TRUE;
}

// Set entity Y axis velocity.
int dc_move_set_velocity_y(void entity, float velocity)
{
    // Valid type flags.
    int     is_entity,
            is_float;

    // Velocity values.
    float   vel_x,
            vel_y,
            vel_z;

    // Get velocities values to apply. OpenBOR script does not
    // allow setting just one velocity axis at a time, so we'll
    // get all current velocity values here and apply them along
    // with the one we wish to modify.
    vel_x = getentityproperty(entity, "xdir");
    vel_y = velocity;
    vel_z = getentityproperty(entity, "zdir");

    // Now we apply the velocities to target entity.
    changeentityproperty(entity, "velocity", vel_x, vel_z, vel_y);

    return DC_VARS_FLAG_TRUE;
}

// Set entity Z axis velocity.
int dc_move_set_velocity_z(void entity, float velocity)
{
    // Valid type flags.
    int     is_entity,
            is_float;

    // Velocity values.
    float   vel_x,
            vel_y,
            vel_z;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_set_velocity_z(void entity, float velocity)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_entity = dc_vars_is_entity(entity);

    if(is_entity == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate velocity value.
    is_float = dc_vars_is_float(velocity);

    if(is_float == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{velocity} must be a valid floating point decimal.");
        dc_error_set_argument(velocity);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Get velocities values to apply. OpenBOR script does not
    // allow setting just one velocity axis at a time, so we'll
    // get all current velocity values here and apply them along
    // with the one we wish to modify.
    vel_x = getentityproperty(entity, "xdir");
    vel_y = getentityproperty(entity, "tossv");
    vel_z = velocity;

    // Now we apply the velocities to target entity.
    changeentityproperty(entity, "velocity", vel_x, vel_z, vel_y);

    return DC_VARS_FLAG_TRUE;
}

// Set entity's Y axis using engine's default rules for
// jumping arcs.
int dc_move_toss(void entity, float velocity)
{
    // Valid type flags.
    int     is_entity,
            is_float;

    // Velocity values.
    float   vel_x,
            vel_y,
            vel_z;

    // Set function name for possible error trapping.
    dc_error_set_function("dc_move_toss(void entity, float velocity)");

    // Validate the entity. We want to make sure the pointer
    // is both valid and refers to an entity that actually exists.
    is_entity = dc_vars_is_entity(entity);

    if(is_entity == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{entity} must be a valid pointer for a currently existing entity.");
        dc_error_set_argument(entity);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate velocity value.
    is_float = dc_vars_is_float(velocity);

    if(is_float == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{velocity} must be a valid floating point decimal.");
        dc_error_set_argument(velocity);
        dc_error_alert();

        return DC_VARS_DEFAULT_FLOAT;
    }

    // Get velocities values to apply. OpenBOR script does not
    // allow setting just one velocity axis at a time, so we'll
    // get all current velocity values here and apply them along
    // with the one we wish to modify.
    vel_x = getentityproperty(entity, "xdir");
    vel_y = velocity;
    vel_z = getentityproperty(entity, "zdir");

    // Now we apply the velocities to target entity.
    changeentityproperty(entity, "velocity", vel_x, vel_z, vel_y);

    // Run the toss function.
    tossentity(entity, vel_y, vel_x, vel_z);

    return DC_VARS_FLAG_TRUE;
}
