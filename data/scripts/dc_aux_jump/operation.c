#include "data/scripts/dc_aux_jump/settings.h"

// Script var accessors
void dc_aux_jump_get_entity()
{
    return getscriptvar(DC_AUX_JUMP_VAR_KEY_ENTITY);
}

int dc_aux_jump_get_key_hold()
{
    return getscriptvar(DC_AUX_JUMP_VAR_KEY_KEY_HOLD);
}

int dc_aux_jump_get_key_press()
{
    return getscriptvar(DC_AUX_JUMP_VAR_KEY_KEY_PRESS);
}

float dc_aux_jump_get_max_height()
{
    return getscriptvar(DC_AUX_JUMP_VAR_KEY_MAX_HEIGHT);
}

// Script var mutators
void dc_aux_jump_set_entity(void value)
{
    int vartype = NULL();

    vartype = typeof(value);

    // Catch bad arguments here.
    if(vartype != DC_AUX_JUMP_VT_POINTER
       && vartype != DC_AUX_JUMP_VT_EMPTY)
    {
        log("\n\n error: dc_aux_jump_set_entity(void value): {value} argument is an invalid type. Pointer is required.");
        return;
    }

    setscriptvar(DC_AUX_JUMP_VAR_KEY_ENTITY, value);
}

void dc_aux_jump_set_key_hold(int value)
{
    int vartype = NULL();

    vartype = typeof(value);

    // Catch bad arguments here.
    if(vartype != DC_AUX_JUMP_VT_INTEGER)
    {
        log("\n\n error: dc_aux_jump_set_key_hold(int value): {value} argument is an invalid type. Integer is required.");
        return;
    }

    setscriptvar(DC_AUX_JUMP_VAR_KEY_KEY_HOLD, value);
}

void dc_aux_jump_set_key_press(int value)
{
    int vartype = NULL();

    vartype = typeof(value);

    // Catch bad arguments here.
    if(vartype != DC_AUX_JUMP_VT_INTEGER)
    {
        log("\n\n error: dc_aux_jump_set_key_press(int value): {value} argument is an invalid type. Integer is required.");
        return;
    }

    setscriptvar(DC_AUX_JUMP_VAR_KEY_KEY_PRESS, value);
}

void dc_aux_jump_set_max_height(float value)
{
    int vartype = NULL();

    vartype = typeof(value);

    // Catch bad arguments here.
    if(vartype != DC_AUX_JUMP_VT_FLOAT
       && vartype != DC_AUX_JUMP_VT_INTEGER)
    {
        log("\n\n error: dc_aux_jump_set_max_height(float value): {value} argument is an invalid type. Floating decimal or integer is required.");
        return;
    }

    setscriptvar(DC_AUX_JUMP_VAR_KEY_MAX_HEIGHT, value);
}

void dc_aux_jump_set_disable_time(int value)
{
    int vartype = NULL();

    vartype = typeof(value);

    // Catch bad arguments here.
    if(vartype != DC_AUX_JUMP_VT_INTEGER
       || vartype != DC_AUX_JUMP_VT_EMPTY)
    {
        log("\n\n error: dc_aux_jump_set_disable_time(float value): {value} argument has invalid type. Integer or empty (NULL) value required.");
        return;
    }

    setindexedvar(DC_AUX_JUMP_VAR_KEY_DISABLE, value);
}

// Return true if disable time set by user. Clears timer
// if expired and not infinite.
int dc_aux_jump_disable_check()
{
    int result          = DC_AUX_JUMP_FLAG_FALSE;
    int elapsed_time    = DC_AUX_JUMP_DEFAULT_INT;
    int time_disable    = DC_AUX_JUMP_DEFAULT_INT;
    int vartype         = DC_AUX_JUMP_DEFAULT_INT;

    time_disable = getindexedvar(DC_AUX_JUMP_VAR_KEY_DISABLE);

    vartype = typeof(time_disable);

    // Does time have any valid integer value?
    if(vartype == DC_AUX_JUMP_VT_INTEGER)
    {
        // Is timer still active (greater than
        // current elapsed time) or infinite? if either
        // is true, than we return true. Elsewise
        // we should clear the timer and
        // do nothing. A default of false
        // will be returned instead.
        if(time_disable > elapsed_time
           || time_disable != DC_AUX_JUMP_TIME_INFINITE)
        {
            // Result will be true.
            result = DC_AUX_JUMP_FLAG_TRUE;
        }
        else
        {
            time_disable = NULL();

            setindexedvar(DC_AUX_JUMP_VAR_KEY_DISABLE, time_disable);
        }
    }

    return result;
}

// Main auxiliary jump function. Checks entity for Wall, edge, obstacle,
// and double jumping animations, evaluates usability based on
// status and environment, and executes as necessary. Returns
// the animation set, or DC_AUX_JUMP_FLAG_FALSE if none.
int dc_aux_jump_execute(){

    void    ent             = DC_AUX_JUMP_DEFAULT_POINTER;    // Entity controlled by player index.
    int     key_press       = DC_AUX_JUMP_DEFAULT_INT;        // Key press triggering event.
	int     key_hold        = DC_AUX_JUMP_DEFAULT_INT;        // Keys currently held when event was triggered.
	int     direction       = DC_AUX_JUMP_DIRECTION_RIGHT;    // Current facing.
	int     cmd_direction   = DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_NEUTRAL;  // Current directional command hold from player in relation to entity's facing.
	float   position_y      = DC_AUX_JUMP_DEFAULT_FLOAT;      // Entity position, Y axis.
	float   position_height = DC_AUX_JUMP_DEFAULT_FLOAT;      // Entity height from base.
	int     animation_id    = DC_AUX_JUMP_DEFAULT_INT;        // Current animation.
	int     animation_valid = DC_AUX_JUMP_FLAG_FALSE;         // Flag indicating entity has an animation.
    float   edge_x          = DC_AUX_JUMP_DEFAULT_FLOAT;      // Edge check position, X axis.
    int     wall_x          = DC_AUX_JUMP_DEFAULT_INT;        // Wall check position, X axis.
    int     obstacle_x      = DC_AUX_JUMP_DEFAULT_INT;        // Obstacle check position, X axis.
    int     animation_set   = DC_AUX_JUMP_DEFAULT_INT;        // Animation to perform.
    float   position_x_set  = DC_AUX_JUMP_DEFAULT_FLOAT;      // Position to set, X axis.
    float   maximum_height  = DC_AUX_JUMP_MAXIMUM_HEIGHT;     // Maximum height to allow auxiliary jumps.
    int     vartype         = DC_AUX_JUMP_VT_EMPTY;           // Variable type.

	// Target entity.
	ent             = dc_aux_jump_get_entity();
    vartype         = typeof(ent);

    // Get current key press and any keys being held.
    key_hold        = dc_aux_jump_get_key_hold();
    key_press       = dc_aux_jump_get_key_press();

	// Is this a jump key press and a valid entity pointer?
	if(key_press & DC_AUX_JUMP_KEY_JUMP
        && vartype == DC_AUX_JUMP_VT_POINTER)
	{
	    // Let's get the entity properties we'll need.
	    animation_id    = getentityproperty(ent, "animationid");
	    direction       = getentityproperty(ent, "direction");
	    position_y      = getentityproperty(ent, "y");

        // Now let's see if there is a temporary maximum height set.
        // If not, we use the default.
        maximum_height  = dc_aux_jump_get_max_height();
        vartype         = typeof(maximum_height);

        if(vartype != DC_AUX_JUMP_VT_FLOAT
           && vartype != DC_AUX_JUMP_VT_INTEGER)
        {
            maximum_height = DC_AUX_JUMP_MAXIMUM_HEIGHT;
        }

        // If current Y position is beyond maximum height, then
        // exit. We don't want to do anything else.
        if(position_y > maximum_height)
        {
            // was triggered. Return false.
            return DC_AUX_JUMP_FLAG_FALSE;
        }

		// Is entity in a valid jumping animation and within maximum
        // vertical distance from base?
		if(animation_id == DC_AUX_JUMP_ANI_JUMP
            || animation_id == DC_AUX_JUMP_ANI_JUMP_WALK
            || animation_id == DC_AUX_JUMP_ANI_JUMP_RUN
            || animation_id == DC_AUX_JUMP_ANI_JUMP_WALL
            || animation_id == DC_AUX_JUMP_ANI_JUMP_EDGE
            || animation_id == DC_AUX_JUMP_ANI_JUMP_OBJECT
            || animation_id == DC_AUX_JUMP_ANI_JUMP_DOUBLE_BACK
            || animation_id == DC_AUX_JUMP_ANI_JUMP_DOUBLE_FORWARD
            || animation_id == DC_AUX_JUMP_ANI_JUMP_DOUBLE_NEUTRAL)
		{

            // We'll need to get the x position of any possible walls
            // or edges within range of our alternate jump animations.
            edge_x      = dc_aux_jump_find_edge_x(ent, DC_AUX_JUMP_ANI_JUMP_EDGE_START);
            wall_x      = dc_aux_jump_find_wall_x(ent, DC_AUX_JUMP_ANI_JUMP_WALL_START);
            obstacle_x  = dc_aux_jump_find_obstacle_x(ent, DC_AUX_JUMP_ANI_JUMP_OBJECT_START);

            if(obstacle_x)
            {
                // prepare animation.
                animation_set   = DC_AUX_JUMP_ANI_JUMP_OBJECT_START;

                // Face away from obstacle.
                dc_aux_jump_face_away(ent, obstacle_x);

            }
            else if(wall_x)
            {
                // Prepare animation.
                animation_set   = DC_AUX_JUMP_ANI_JUMP_WALL_START;

                // Face away from wall.
                dc_aux_jump_face_away(ent, wall_x);

            }
            else if(edge_x)
            {
                // prepare animation.
                animation_set   = DC_AUX_JUMP_ANI_JUMP_EDGE_START;

                // Face away from edge.
                dc_aux_jump_face_away(ent, edge_x);
            }

		}

		// Double jump.

        // If no wall or edge jump has been set up,
        // entity in a valid jumping animation (excluding double jumps,
        // then let's try a double jump.
		if((animation_id == DC_AUX_JUMP_ANI_JUMP
            || animation_id == DC_AUX_JUMP_ANI_JUMP_WALK
            || animation_id == DC_AUX_JUMP_ANI_JUMP_RUN
            || animation_id == DC_AUX_JUMP_ANI_JUMP_WALL
            || animation_id == DC_AUX_JUMP_ANI_JUMP_EDGE
            || animation_id == DC_AUX_JUMP_ANI_JUMP_OBJECT)
            && animation_set == DC_AUX_JUMP_FLAG_FALSE)
        {
            // Which horizontal direction command is player sending?
            cmd_direction   = dc_aux_jump_aux_command_direction(ent, key_hold);

            // Let's decide which double jump animation to use based
            // on player's horizontal direction command.
            switch(cmd_direction)
            {
                // No direction at all.
                default:
                case DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_NEUTRAL:

                    animation_set = DC_AUX_JUMP_ANI_JUMP_DOUBLE_NEUTRAL;
                    break;

                // Backward.
                case DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_BACK:

                    animation_set = DC_AUX_JUMP_ANI_JUMP_DOUBLE_BACK;
                    break;

                // Forward.
                case DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_FORWARD:

                    animation_set = DC_AUX_JUMP_ANI_JUMP_DOUBLE_FORWARD;
                    break;
            }
        }

		// Did we set up an alternate jump of any kind? If so let's take care of the details here.
        if(animation_set && animation_set)
        {
            // Does entity have the selected animation?
            animation_valid = getentityproperty(ent, "animvalid", animation_set);

            if(animation_valid == DC_AUX_JUMP_FLAG_TRUE)
            {
                // Now we need to stop all current velocity.
                changeentityproperty(ent, "velocity", 0, 0, 0);

                // Set the animation. We don't want to change any AI flags here,
                // so we're just going to use the changeentityproperty method.
                changeentityproperty(ent, "animation", animation_set);

                // We are finished, so return animation ID and exit the function.
                return animation_set;
            }
        }
	}

	// If we made it all the way here, then no special jump action
	// was triggered. Return false.
	return DC_AUX_JUMP_FLAG_FALSE;
}

// Face away from given position.
int dc_aux_jump_face_away(void ent, float target_x)
{

    int     result          = DC_AUX_JUMP_DIRECTION_RIGHT;  // Result and position entity is set to.
    float   position_x      = DC_AUX_JUMP_DEFAULT_FLOAT;    // Entity position, X axis.

	// Get X position.
	position_x      = getentityproperty(ent, "x");


    // Simple check. If we are to left of target x
    // position, then face left. Otherwise face right.
    if(position_x < target_x)
    {
        result = DC_AUX_JUMP_DIRECTION_LEFT;
    }
    else
    {
        result = DC_AUX_JUMP_DIRECTION_RIGHT;
    }

    // Apply direction result to entity.
    changeentityproperty(ent, "direction", result);

    //return result.
    return result;
}

// Return forward or backward key command in relation
// to entity's current facing.
int dc_aux_jump_aux_command_direction(void ent, int key_hold)
{
    int direction   = DC_AUX_JUMP_DEFAULT_INT;
    int result      = DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_NEUTRAL;

    // Get current facing.
    direction = getentityproperty(ent, "direction");

    // Run checks based on facing left or right.
    switch(direction)
    {
        // Facing left.
        case DC_AUX_JUMP_DIRECTION_LEFT:

            // Holding key left?
            if(key_hold & DC_AUX_JUMP_KEY_MOVE_LEFT)
            {
                // Then this is the "forward" key.
                result = DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_FORWARD;
            }
            // Holding key right?
            else if(key_hold & DC_AUX_JUMP_KEY_MOVE_RIGHT)
            {
                // Then this is the "back" key.
                result = DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_BACK;
            }

            break;

        // Facing right.
        default:
        case DC_AUX_JUMP_DIRECTION_RIGHT:

            // Holding key left?
            if(key_hold & DC_AUX_JUMP_KEY_MOVE_LEFT)
            {
                // Then this is the "back" key.
                result = DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_BACK;
            }
            // Holding key right?
            else if(key_hold & DC_AUX_JUMP_KEY_MOVE_RIGHT)
            {
                // Then this is the "forward" key.
                result = DC_AUX_JUMP_KEY_MOVE_HORIZONTAL_FORWARD;
            }

            break;

    }

    // Now return our results.
    return result;
}

// Returns x position of closest wall within animation range.
int dc_aux_jump_find_wall_x(void ent, int animation_id)
{
    int result              = DC_AUX_JUMP_DEFAULT_INT;      // Final result.
    int animation_valid     = DC_AUX_JUMP_FLAG_FALSE;       // Animation exists flag.
    int check_x_min         = DC_AUX_JUMP_DEFAULT_INT;      // Checking minimum range.
    int check_x_max         = DC_AUX_JUMP_DEFAULT_INT;      // Checking maximum range.
    int check_y_min         = DC_AUX_JUMP_DEFAULT_INT;      // Checking minimum range.
    int check_y_max         = DC_AUX_JUMP_DEFAULT_INT;      // Checking maximum range.
    int check_z_min         = DC_AUX_JUMP_DEFAULT_INT;      // Checking minimum range.
    int check_z_max         = DC_AUX_JUMP_DEFAULT_INT;      // Checking maximum range.
    int wall_height         = DC_AUX_JUMP_DEFAULT_INT;      // Wall height.
    int wall_distance_old   = DC_AUX_JUMP_DEFAULT_INT;
    int wall_distance_new   = DC_AUX_JUMP_DEFAULT_INT;
    int direction           = DC_AUX_JUMP_DIRECTION_RIGHT;  // Current facing.
    int height              = DC_AUX_JUMP_DEFAULT_INT;      // height of wall found (if any).

    float position_x        = DC_AUX_JUMP_DEFAULT_FLOAT;
    float position_y        = DC_AUX_JUMP_DEFAULT_FLOAT;
    float position_z        = DC_AUX_JUMP_DEFAULT_FLOAT;

    int loop_x              = DC_AUX_JUMP_DEFAULT_INT;      // Loop counter.
    int loop_z              = DC_AUX_JUMP_DEFAULT_INT;      // Loop counter.

    // If this entity doesn't have the animation at all,
    // then exit. There's nothing else to do.
    animation_valid =  getentityproperty(ent, "animvalid", animation_id);

    if(animation_valid == DC_AUX_JUMP_FLAG_FALSE)
    {
        return result;
    }

    // Get current entity x position and direction.
    position_x  = getentityproperty(ent, "x");
    position_y  = getentityproperty(ent, "y");
    position_z  = getentityproperty(ent, "z");
    direction   = getentityproperty(ent, "direction");

    // Get X ranges of animation.
    check_x_min = getentityproperty(ent, "range", "xmin", animation_id);
    check_x_max = getentityproperty(ent, "range", "xmax", animation_id);
    check_y_min = getentityproperty(ent, "range", "amin", animation_id);
    check_y_max = getentityproperty(ent, "range", "amax", animation_id);
    check_z_min = getentityproperty(ent, "range", "zmin", animation_id);
    check_z_max = getentityproperty(ent, "range", "zmax", animation_id);

    // We're doing the range checking ourselves, so we'll need to
    // combine the range settings with current position. If facing
    // left, we'll need subtract for X. If facing right, then we'll
    // add. Y and Z are always added.

    if(direction == DC_AUX_JUMP_DIRECTION_LEFT)
    {
        check_x_min = position_x - check_x_min;
        check_x_max = position_x - check_x_max;
    }
    else
    {
        check_x_min += position_x;
        check_x_max += position_x;
    }

    check_y_min += position_y;
    check_y_max += position_y;

    check_z_min += position_z;
    check_z_max += position_z;

    // Loop through all possible X positions within
    // X axis range.
    for(loop_x = check_x_min; loop_x <= check_x_max; loop_x++)
    {
        // Now loop over each possible Z position within Z axis
        // range.
        for(loop_z = check_z_min; loop_z <= check_z_max; loop_z++)
        {
            // Get wall height (if any).
            height = checkwall(loop_x, loop_z);

            // Is the wall height within our vertical range?
            if(height >= check_y_min && height <= check_y_max)
            {
                // Has a wall X position been assigned?
                if(result)
                {
                    // Let's find out if this wall position X is closer
                    // to entity than the previous one.

                    wall_distance_old = result - position_x;
                    wall_distance_new = loop_x - position_x;

                    // Compare old to new. If new is closer, assign that as
                    // our wall position X.
                    if(wall_distance_new < wall_distance_old)
                    {
                        result = loop_x;
                    }
                }
                else
                {
                    // Assign wall position to our current check location.
                    result = loop_x;
                }
            }
        }
    }

    // return final result.
    return result;
}

// Get X position of screen edge if found within X range of
// animation.
int dc_aux_jump_find_edge_x(void ent, int animation)
{
    // ent: Entity to perform range check.
    // animation_id: Animation to get range settings from.

    int result              = DC_AUX_JUMP_FLAG_FALSE;   // Final result.
    int in_range            = DC_AUX_JUMP_FLAG_FALSE;   // Target in range.
    int animation_valid     = DC_AUX_JUMP_FLAG_FALSE;   // Animation exists flag.
    int scroll_x            = DC_AUX_JUMP_DEFAULT_INT;  // Screen scroll position.
    int far_x               = DC_AUX_JUMP_DEFAULT_INT;  // location of far screen edge.
    int vartype             = DC_AUX_JUMP_VT_EMPTY;     // Variable type.
    int anim_valid          = DC_AUX_JUMP_FLAG_FALSE;   // Valid animation?

    // Verify valid entity.
    vartype = typeof(ent);

    if(vartype != DC_AUX_JUMP_VT_POINTER)
    {
        return result;
    }

    // Verify animation was provided.
    vartype = typeof(animation);

    if(vartype != DC_AUX_JUMP_VT_INTEGER)
    {
        return result;
    }

    // Verify animation provided is valid.
    anim_valid = getentityproperty(ent, "animvalid", animation);

    if(anim_valid == DC_AUX_JUMP_FLAG_FALSE)
    {
        return result;
    }

    // Get current scroll position, far edge position
    // and entity x position.
    scroll_x    = openborvariant("xpos");
    far_x       = scroll_x + openborvariant("hResolution");

    in_range = dc_aux_jump_check_range_by_position(ent, animation, scroll_x);

    if(in_range == DC_AUX_JUMP_FLAG_TRUE)
    {
        // Just in case the scroll position hasn't moved at all
        // bust is still within range, return 1 instead of 0 so
        // evaluations won't fail.
        if(scroll_x == DC_AUX_JUMP_DEFAULT_FLOAT)
        {
            result = 1;
        }
        else
        {
            result = scroll_x;
        }

        return result;
    }

    // Same check, but this time for the far edge of screen.
    in_range = dc_aux_jump_check_range_by_position(ent, animation, far_x);

    if(in_range == DC_AUX_JUMP_FLAG_TRUE)
    {
        result = far_x;

        // Just in case the case the end result is still 0,
        // we'll adjust it to 1 so evaluations don't fail.
        if(result == DC_AUX_JUMP_DEFAULT_FLOAT)
        {
            result = 1;
        }

        return result;
    }

    // Return result (if we made it this far - it's false.
    return result;

}

// Returns x position of first obstacle in range of animation.
int dc_aux_jump_find_obstacle_x(void ent, int animation_id){

    int     result          = DC_AUX_JUMP_DEFAULT_INT;          // Final result.
    int     animation_valid = DC_AUX_JUMP_FLAG_FALSE;           // Animation exists flag.
    float   target_x        = DC_AUX_JUMP_DEFAULT_FLOAT;        // Position of entity on X axis.
    float   target_y        = DC_AUX_JUMP_DEFAULT_FLOAT;        // Position of entity on Y axis.
    float   target_z        = DC_AUX_JUMP_DEFAULT_FLOAT;        // Position of entity on Z axis.
    int     target_h        = DC_AUX_JUMP_DEFAULT_INT;          // Target's height setting.
    void    target          = DC_AUX_JUMP_DEFAULT_POINTER;      // Target entity pointer.
    int     target_count    = DC_AUX_JUMP_DEFAULT_INT;          // Target Entity count.
    int     i               = DC_AUX_JUMP_DEFAULT_INT;          // Loop counter.
    int     in_range        = DC_AUX_JUMP_FLAG_FALSE;           // Target in range?
    int     type            = DC_AUX_JUMP_TYPE_OBSTACLE;        // Type of entity.

    // If this entity doesn't have the animation at all,
    // then exit. There's nothing else to do.
    animation_valid =  getentityproperty(ent, "animvalid", animation_id);

    if(animation_valid == DC_AUX_JUMP_FLAG_FALSE)
    {
        return result;
    }

    // Get entity count.
    target_count = openborvariant("ent_max");

    // Loop over each entity index.
    for(i=0; i<target_count; i++)
    {
        // Get entity pointer.
		target = getentity(i);

        target_x = getentityproperty(target, "x");
        target_y = getentityproperty(target, "y");
        target_z = getentityproperty(target, "z");
        target_h = getentityproperty(target, "height");

        // Add height to target's Y position.
        target_y += target_h;

	    // Is the target in range and an obstacle?

	    in_range    = dc_aux_jump_check_range_by_position(ent, animation_id, target_x, target_y, target_z);

	    type        = getentityproperty(target, "type");

	    if(in_range == DC_AUX_JUMP_FLAG_TRUE && type == DC_AUX_JUMP_TYPE_OBSTACLE)
        {
            // Get the current target x positon, then exit loop.
            result = getentityproperty(target, "x");
            break;
        }

    }
    return result;

}

// Perform a manual range check vs. given coordinates.
// Performs identical function to check_range, but against
// a manually designated set of position coordinates.
int dc_aux_jump_check_range_by_position(void ent, int animation, float target_x, float target_y, float target_z, float target_base)
{
    int     result          = DC_AUX_JUMP_FLAG_FALSE;       // Result to return.
    int     direction       = DC_AUX_JUMP_DIRECTION_LEFT;   // Direction of entity.
    int     range_b_min     = DC_AUX_JUMP_DEFAULT_INT;
    int     range_b_max     = DC_AUX_JUMP_DEFAULT_INT;
    int     range_x_min     = DC_AUX_JUMP_DEFAULT_INT;
    int     range_x_max     = DC_AUX_JUMP_DEFAULT_INT;
    int     range_y_min     = DC_AUX_JUMP_DEFAULT_INT;
    int     range_y_max     = DC_AUX_JUMP_DEFAULT_INT;
    int     range_z_min     = DC_AUX_JUMP_DEFAULT_INT;
    int     range_z_max     = DC_AUX_JUMP_DEFAULT_INT;
    float   position_x      = DC_AUX_JUMP_DEFAULT_FLOAT;    // Entity position, X axis.
    float   position_y      = DC_AUX_JUMP_DEFAULT_FLOAT;    // Entity position, Y axis.
    float   position_z      = DC_AUX_JUMP_DEFAULT_FLOAT;    // Entity position, Z axis.
    int     position_base   = DC_AUX_JUMP_DEFAULT_INT;      // Entity position, base.
    int     vartype         = DC_AUX_JUMP_VT_EMPTY;         // Variable type.
    int     anim_valid      = DC_AUX_JUMP_FLAG_FALSE;       // Valid animation?

    // Verify valid entity.
    vartype = typeof(ent);

    if(vartype != DC_AUX_JUMP_VT_POINTER)
    {
        return result;
    }

    // Verify animation was provided.
    vartype = typeof(animation);

    if(vartype != DC_AUX_JUMP_VT_INTEGER)
    {
        return result;
    }

    // Verify animation provided is valid.
    anim_valid = getentityproperty(ent, "animvalid", animation);

    if(anim_valid == DC_AUX_JUMP_FLAG_FALSE)
    {
        return result;
    }

    // If a target position base is given, evaluate base range.
    vartype = typeof(target_base);

    if(vartype == DC_AUX_JUMP_VT_FLOAT
       || vartype == DC_AUX_JUMP_VT_INTEGER)
    {

        range_b_min = getentityproperty(ent, "range", "bmin", animation);
        range_b_max = getentityproperty(ent, "range", "bmax", animation);

        position_base  = getentityproperty(ent, "base");

        // If the target position falls within range, set
        // result to true. Otherwise set result to
        // false and return immediately since there's no
        // point in running any more evaluations.

        if((target_base - position_base) >= range_b_min
		  && (target_base - position_base) <= range_b_max)
        {
            result = DC_AUX_JUMP_FLAG_TRUE;
        }
        else
        {
            result = DC_AUX_JUMP_FLAG_FALSE;
            return result;
        }
    }


    // If a target position X is given, evaluate X range.
    vartype = typeof(target_x);

    if(vartype == DC_AUX_JUMP_VT_FLOAT
       || vartype == DC_AUX_JUMP_VT_INTEGER)
    {
        // Get X range, position and direction.
        range_x_min = getentityproperty(ent, "range", "xmin", animation);
        range_x_max = getentityproperty(ent, "range", "xmax", animation);
        direction   = getentityproperty(ent, "direction");
        position_x  = getentityproperty(ent, "x");

        // X range calculation differs if facing right or left.
        if(direction == DC_AUX_JUMP_DIRECTION_RIGHT)
        {
            // If the target position falls within range, set
            // result to true. Otherwise set result to
            // false and return immediately since there's no
            // point in running any more evaluations.
            if(target_x >= position_x + range_x_min
                && target_x <= position_x + range_x_max)
            {
                result = DC_AUX_JUMP_FLAG_TRUE;
            }
            else
            {
                result = DC_AUX_JUMP_FLAG_FALSE;
                return result;
            }
        }
        else
        {
            // If the target position falls within range, set
            // result to true. Otherwise set result to
            // false and return immediately since there's no
            // point in running any more evaluations.
            if(target_x <= position_x - range_x_min
                && target_x >= position_x - range_x_max)
            {
                result = DC_AUX_JUMP_FLAG_TRUE;
            }
            else
            {
                result = DC_AUX_JUMP_FLAG_FALSE;
                return result;
            }
        }
    }

    // If a target position Y is given, evaluate Y range.
    vartype = typeof(target_y);

    if(vartype == DC_AUX_JUMP_VT_FLOAT
       || vartype == DC_AUX_JUMP_VT_INTEGER)
    {
        range_y_min = getentityproperty(ent, "range", "amin", animation);
        range_y_max = getentityproperty(ent, "range", "amax", animation);

        position_y  = getentityproperty(ent, "y");

        // If the target position falls within range, set
        // result to true. Otherwise set result to
        // false and return immediately since there's no
        // point in running any more evaluations.
        if((target_y - position_y) >= range_y_min
		  && (target_y - position_y) <= range_y_max)
        {
            result = DC_AUX_JUMP_FLAG_TRUE;
        }
        else
        {
            result = DC_AUX_JUMP_FLAG_FALSE;
            return result;
        }
    }

    // If a target position Z is given, evaluate Z range.
    vartype = typeof(target_z);

    if(vartype == DC_AUX_JUMP_VT_FLOAT
       || vartype == DC_AUX_JUMP_VT_INTEGER)
    {
        range_z_min = getentityproperty(ent, "range", "zmin", animation);
        range_z_max = getentityproperty(ent, "range", "zmax", animation);

        position_z  = getentityproperty(ent, "z");

        // If the target position falls within range, set
        // result to true. Otherwise set result to
        // false and return immediately since there's no
        // point in running any more evaluations.

        if((target_z - position_z) >= range_z_min
		  && (target_z - position_z) <= range_z_max)
        {
            result = DC_AUX_JUMP_FLAG_TRUE;
        }
        else
        {
            result = DC_AUX_JUMP_FLAG_FALSE;
            return result;
        }
    }

    return result;
}
