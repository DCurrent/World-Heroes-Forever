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
}
