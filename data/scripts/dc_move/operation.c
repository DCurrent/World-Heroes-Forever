// External Dependencies
#include    "data/scripts/dc_vars/main.c"
#include    "data/scripts/dc_error/main.c"

// Internal library
#include    "data/scripts/dc_move/settings.h"
#import     "data/scripts/dc_move/velocity.c"
#import     "data/scripts/dc_move/members.c"

// Return true if disable time set by user. Clears timer
// if expired and not infinite.
int dc_move_disable_check()
{
    int result;         // Final result.
    int elapsed_time;   // Current elapsed time.
    int time_disable;   // Disable setting.

    // Get the disable time setting and current elapsed time.
    time_disable = dc_vars_get_global_int(DC_MOVE_VARKEY_DISABLE);
    elapsed_time = openborvariant("elapsed_time");


    // Is timer still active (greater than
    // current elapsed time) or infinite? if either
    // is true, than we return true. Elsewise
    // we should clear the timer and
    // do nothing. A default of false
    // will be returned instead.
    if(time_disable > elapsed_time
       || time_disable == DC_MOVE_TIME_INFINITE)
    {
        // Result will be true.
        result = DC_VARS_FLAG_TRUE;
    }
    else
    {
        // The timer is expired. Clear the timer variable
        // and return false.
        dc_vars_clear_global_var(DC_MOVE_VARKEY_DISABLE, time_disable);
        result = DC_VARS_FLAG_FALSE;
    }

    return result;
}

// Main auxiliary jump function. Checks entity for Wall, edge, obstacle,
// and double jumping animations, evaluates usability based on
// status and environment, and executes as necessary. Returns
// the animation set, or DC_VARS_FLAG_FALSE if none.
int dc_move_execute(){

    void    ent;                // Entity controlled by player index.
    int     key_press;          // Key press triggering event.
	int     key_hold;           // Keys currently held when event was triggered.
	int     direction;          // Current facing.
	int     cmd_direction;      // Current directional command hold from player in relation to entity's facing.
	float   position_y;         // Entity position, Y axis.
	float   position_height;    // Entity height from base.
	int     animation_id;       // Current animation.
	int     animation_valid;    // Flag indicating entity has an animation.
    float   edge_x;             // Edge check position, X axis.
    int     wall_x;             // Wall check position, X axis.
    int     obstacle_x;         // Obstacle check position, X axis.
    int     animation_set;      // Animation to perform.
    float   position_x_set;     // Position to set, X axis.
    float   maximum_height;     // Maximum height to allow auxiliary jumps.

    // Set defaults we need.
    animation_set = DC_VARS_FLAG_FALSE;

	// Target entity.
	ent             = dc_move_get_entity();

    // Get current key press and any keys being held.
    key_hold        = dc_move_get_key_hold();
    key_press       = dc_move_get_key_press();

	// Is this a jump key press and a valid entity pointer?
	if(key_press & DC_MOVE_KEY_JUMP)
	{
	    // Let's get the entity properties we'll need.
	    animation_id    = getentityproperty(ent, "animationid");
	    direction       = getentityproperty(ent, "direction");
	    position_y      = getentityproperty(ent, "y");

        // Now let's see if there is a temporary maximum height set.
        // If not, we use the default.
        maximum_height  = dc_move_get_max_height();

        // If current Y position is beyond maximum height, then
        // exit. We don't want to do anything else.
        if(position_y > maximum_height)
        {
            // was triggered. Return false.
            return DC_VARS_FLAG_FALSE;
        }

		// Is entity in a valid jumping animation and within maximum
        // vertical distance from base?
		if(animation_id == DC_MOVE_ANI_JUMP
            || animation_id == DC_MOVE_ANI_JUMP_WALK
            || animation_id == DC_MOVE_ANI_JUMP_RUN
            || animation_id == DC_MOVE_ANI_JUMP_WALL
            || animation_id == DC_MOVE_ANI_JUMP_EDGE
            || animation_id == DC_MOVE_ANI_JUMP_OBJECT
            || animation_id == DC_MOVE_ANI_JUMP_DOUBLE_BACK
            || animation_id == DC_MOVE_ANI_JUMP_DOUBLE_FORWARD
            || animation_id == DC_MOVE_ANI_JUMP_DOUBLE_NEUTRAL)
		{

            // We'll need to get the x position of any possible walls
            // or edges within range of our alternate jump animations.
            edge_x      = dc_move_find_edge_x(ent, DC_MOVE_ANI_JUMP_EDGE_START);
            wall_x      = dc_move_find_wall_x(ent, DC_MOVE_ANI_JUMP_WALL_START);
            obstacle_x  = dc_move_find_obstacle_x(ent, DC_MOVE_ANI_JUMP_OBJECT_START);

            if(obstacle_x)
            {
                // prepare animation.
                animation_set   = DC_MOVE_ANI_JUMP_OBJECT_START;

                // Face away from obstacle.
                dc_move_face_away(ent, obstacle_x);

            }
            else if(wall_x)
            {
                // Prepare animation.
                animation_set   = DC_MOVE_ANI_JUMP_WALL_START;

                // Face away from wall.
                dc_move_face_away(ent, wall_x);

            }
            else if(edge_x)
            {
                // prepare animation.
                animation_set   = DC_MOVE_ANI_JUMP_EDGE_START;

                // Face away from edge.
                dc_move_face_away(ent, edge_x);
            }

		}

		// Double jump.

        // If no wall or edge jump has been set up,
        // entity in a valid jumping animation (excluding double jumps,
        // then let's try a double jump.
		if((animation_id == DC_MOVE_ANI_JUMP
            || animation_id == DC_MOVE_ANI_JUMP_WALK
            || animation_id == DC_MOVE_ANI_JUMP_RUN
            || animation_id == DC_MOVE_ANI_JUMP_WALL
            || animation_id == DC_MOVE_ANI_JUMP_EDGE
            || animation_id == DC_MOVE_ANI_JUMP_OBJECT)
            && animation_set == DC_VARS_FLAG_FALSE)
        {
            // Which horizontal direction command is player sending?
            cmd_direction   = dc_move_command_direction(ent, key_hold);

            // Let's decide which double jump animation to use based
            // on player's horizontal direction command.
            switch(cmd_direction)
            {
                // No direction at all.
                default:
                case DC_MOVE_KEY_MOVE_HORIZONTAL_NEUTRAL:

                    animation_set = DC_MOVE_ANI_JUMP_DOUBLE_NEUTRAL;
                    break;

                // Backward.
                case DC_MOVE_KEY_MOVE_HORIZONTAL_BACK:

                    animation_set = DC_MOVE_ANI_JUMP_DOUBLE_BACK;
                    break;

                // Forward.
                case DC_MOVE_KEY_MOVE_HORIZONTAL_FORWARD:

                    animation_set = DC_MOVE_ANI_JUMP_DOUBLE_FORWARD;
                    break;
            }
        }

		// Did we set up an alternate jump of any kind? If so let's take care of the details here.
        if(animation_set && animation_set)
        {
            // Does entity have the selected animation?
            animation_valid = getentityproperty(ent, "animvalid", animation_set);

            if(animation_valid == DC_VARS_FLAG_TRUE)
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
	return DC_VARS_FLAG_FALSE;
}

// Face away from given position.
int dc_move_face_away(void ent, float target_x)
{

    int     result;     // Final result.
    float   position_x; // Entity position, X axis.

	// Get X position.
	position_x      = getentityproperty(ent, "x");


    // Simple check. If we are to left of target x
    // position, then face left. Otherwise face right.
    if(position_x < target_x)
    {
        result = DC_MOVE_DIRECTION_LEFT;
    }
    else
    {
        result = DC_MOVE_DIRECTION_RIGHT;
    }

    // Apply direction result to entity.
    changeentityproperty(ent, "direction", result);

    //return result.
    return result;
}

// Return forward or backward key command in relation
// to entity's current facing.
int dc_move_command_direction(void ent, int key_hold)
{
    int direction;  // Current direction.
    int result;     // Final result.

    // Set default result.
    result = DC_MOVE_KEY_MOVE_HORIZONTAL_NEUTRAL;

    // Get current facing.
    direction = getentityproperty(ent, "direction");

    // Run checks based on facing left or right.
    switch(direction)
    {
        // Facing left.
        case DC_MOVE_DIRECTION_LEFT:

            // Holding key left?
            if(key_hold & DC_MOVE_KEY_MOVE_LEFT)
            {
                // Then this is the "forward" key.
                result = DC_MOVE_KEY_MOVE_HORIZONTAL_FORWARD;
            }
            // Holding key right?
            else if(key_hold & DC_MOVE_KEY_MOVE_RIGHT)
            {
                // Then this is the "back" key.
                result = DC_MOVE_KEY_MOVE_HORIZONTAL_BACK;
            }

            break;

        // Facing right.
        default:
        case DC_MOVE_DIRECTION_RIGHT:

            // Holding key left?
            if(key_hold & DC_MOVE_KEY_MOVE_LEFT)
            {
                // Then this is the "back" key.
                result = DC_MOVE_KEY_MOVE_HORIZONTAL_BACK;
            }
            // Holding key right?
            else if(key_hold & DC_MOVE_KEY_MOVE_RIGHT)
            {
                // Then this is the "forward" key.
                result = DC_MOVE_KEY_MOVE_HORIZONTAL_FORWARD;
            }

            break;

    }

    // Now return our results.
    return result;
}

// Returns x position of closest wall within animation range.
int dc_move_find_wall_x(void ent, int animation_id)
{
    int result;             // Final result.
    int animation_valid;    // Animation exists flag.

    // Checking ranges, minimum and
    // maximum.
    int check_x_min,        // Checking minimum range.
        check_x_max,        // Checking maximum range.
        check_y_min,        // Checking minimum range.
        check_y_max,        // Checking maximum range.
        check_z_min,        // Checking minimum range.
        check_z_max;        // Checking maximum range.

    int wall_distance_old;  // Wall distance located in loop.
    int wall_distance_new;  // A new wall distance to compare against old for proximity.
    int direction;          // Current facing.
    int height;             // height of wall found (if any).

    // Entity current position.
    float position_x,
        position_y,
        position_z;

    // Loop counters.
    int loop_x,
        loop_z;

    // Set defaults.
    result = DC_VARS_FLAG_FALSE;

    // If this entity doesn't have the animation at all,
    // then exit. There's nothing else to do.
    animation_valid =  getentityproperty(ent, "animvalid", animation_id);

    if(animation_valid == DC_VARS_FLAG_FALSE)
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

    if(direction == DC_MOVE_DIRECTION_LEFT)
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
int dc_move_find_edge_x(void ent, int animation)
{
    // ent: Entity to perform range check.
    // animation_id: Animation to get range settings from.

    int result;             // Final result.
    int in_range;           // Target in range.
    int animation_valid;    // Animation exists flag.
    int scroll_x;           // Screen scroll position.
    int far_x;              // location of far screen edge.
    int vartype;            // Variable type.
    int anim_valid;         // Valid animation?

    // Valid type flags
    int is_ent,             // Entity.
        is_int;             // Whole integer.

    // Set default result.
    result = DC_VARS_FLAG_FALSE;

    // Verify valid entity.
    is_ent = dc_vars_is_entity(ent);

    if(is_ent == DC_VARS_FLAG_FALSE)
    {
        return result;
    }

    // Verify animation was provided.
    is_int =  typeof(animation);

    if(is_int == DC_VARS_FLAG_FALSE)
    {
        return result;
    }

    // Verify animation provided is valid.
    anim_valid = getentityproperty(ent, "animvalid", animation);

    if(anim_valid == DC_VARS_FLAG_FALSE)
    {
        return result;
    }

    // Get current scroll position, far edge position
    // and entity x position.
    scroll_x    = openborvariant("xpos");
    far_x       = scroll_x + openborvariant("hResolution");

    in_range = dc_move_check_range_by_position(ent, animation, scroll_x);

    if(in_range == DC_VARS_FLAG_TRUE)
    {
        // Just in case the scroll position hasn't moved at all
        // bust is still within range, return 1 instead of 0 so
        // evaluations won't fail.
        if(scroll_x == DC_VARS_DEFAULT_FLOAT)
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
    in_range = dc_move_check_range_by_position(ent, animation, far_x);

    if(in_range == DC_VARS_FLAG_TRUE)
    {
        result = far_x;

        // Just in case the case the end result is still 0,
        // we'll adjust it to 1 so evaluations don't fail.
        if(result == DC_VARS_DEFAULT_FLOAT)
        {
            result = 1;
        }

        return result;
    }

    // Return result (if we made it this far - it's false.
    return result;

}

// Returns x position of first obstacle in range of animation.
int dc_move_find_obstacle_x(void ent, int animation){

    int     result;             // Final result.

    // Target entity position.
    float   target_x,
            target_y,
            target_z;

    int     target_h;           // Target's height setting.
    void    target;             // Target entity pointer.
    int     target_count;       // Target Entity count.
    int     i;                  // Loop counter.
    int     in_range;           // Target in range?
    int     type;               // Type of entity.

    int     anim_valid;         // Valid animation?

    // Valid type flags
    int     is_ent,             // Entity.
            is_int;             // Whole integer.

    // Set default result.
    result = DC_VARS_FLAG_FALSE;

    // Verify valid entity.
    is_ent = dc_vars_is_entity(ent);

    if(is_ent == DC_VARS_FLAG_FALSE)
    {
        return result;
    }

    // Verify animation was provided.
    is_int =  typeof(animation);

    if(is_int == DC_VARS_FLAG_FALSE)
    {
        return result;
    }

    // Verify animation provided is valid.
    anim_valid = getentityproperty(ent, "animvalid", animation);

    if(anim_valid == DC_VARS_FLAG_FALSE)
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

	    in_range    = dc_move_check_range_by_position(ent, animation, target_x, target_y, target_z);

	    type        = getentityproperty(target, "type");

	    if(in_range == DC_VARS_FLAG_TRUE && type == DC_MOVE_TYPE_OBSTACLE)
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
int dc_move_check_range_by_position(void ent, int animation, float target_x, float target_y, float target_z, float target_base)
{
    int     result;     // Final result.

    // Type flags.
    int     is_num,     // Numeric.
            is_int,     // Whole integer.
            is_ent;     // Entity.

    // Range settings of entity.
    int     range_b_min,
            range_b_max,
            range_x_min,
            range_x_max,
            range_y_min,
            range_y_max,
            range_z_min,
            range_z_max;

    // Entity current position.
    float   position_x,
            position_y,
            position_z;

    int     position_base;  // Entity position, base.
    int     direction;      // Entity direction.
    int     vartype;        // Variable type.
    int     anim_valid;     // Valid animation?

    // Default result to false value.
    result = DC_VARS_FLAG_FALSE;

    // Verify valid entity.
    is_ent = dc_vars_is_entity(ent);

    if(is_ent == DC_VARS_FLAG_FALSE)
    {
        return result;
    }

    // Verify animation was provided.
    is_int = dc_vars_is_integer(animation);

    if(is_int == DC_VARS_FLAG_FALSE)
    {
        return result;
    }

    // Verify animation provided is valid.
    anim_valid = getentityproperty(ent, "animvalid", animation);

    if(anim_valid == DC_VARS_FLAG_FALSE)
    {
        return result;

    }

    // If a target position base is given, evaluate base range.
    is_num = dc_vars_is_numeric(target_base);

    if(is_num == DC_VARS_FLAG_TRUE)
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
            result = DC_VARS_FLAG_TRUE;
        }
        else
        {
            result = DC_VARS_FLAG_FALSE;
            return result;
        }
    }


    // If a target position X is given, evaluate X range.
    is_num = dc_vars_is_numeric(target_x);

    if(is_num == DC_VARS_FLAG_TRUE)
    {
        // Get X range, position and direction.
        range_x_min = getentityproperty(ent, "range", "xmin", animation);
        range_x_max = getentityproperty(ent, "range", "xmax", animation);
        direction   = getentityproperty(ent, "direction");
        position_x  = getentityproperty(ent, "x");

        // X range calculation differs if facing right or left.
        if(direction == DC_MOVE_DIRECTION_RIGHT)
        {
            // If the target position falls within range, set
            // result to true. Otherwise set result to
            // false and return immediately since there's no
            // point in running any more evaluations.
            if(target_x >= position_x + range_x_min
                && target_x <= position_x + range_x_max)
            {
                result = DC_VARS_FLAG_TRUE;
            }
            else
            {
                result = DC_VARS_FLAG_FALSE;
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
                result = DC_VARS_FLAG_TRUE;
            }
            else
            {
                result = DC_VARS_FLAG_FALSE;
                return result;
            }
        }
    }

    // If a target position Y is given, evaluate Y range.
    is_num = dc_vars_is_numeric(target_y);

    if(is_num == DC_VARS_FLAG_TRUE)
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
            result = DC_VARS_FLAG_TRUE;
        }
        else
        {
            result = DC_VARS_FLAG_FALSE;
            return result;
        }
    }

    // If a target position Z is given, evaluate Z range.
    is_num = dc_vars_is_numeric(target_z);

    if(is_num == DC_VARS_FLAG_TRUE)
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
            result = DC_VARS_FLAG_TRUE;
        }
        else
        {
            result = DC_VARS_FLAG_FALSE;
            return result;
        }
    }

    return result;
}
