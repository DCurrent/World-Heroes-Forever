#include "data/scripts/dc_drawmethod/settings.h"
#include "data/scripts/dc_vars/main.c"

// Set drawmethod on or off.
void dc_drawmethod_set_enabled(void ent, int value)
{
    // Catch bad arguments here.
    if(typeof(value) != DC_DRAWMETHOD_VARTYPE_INTEGER)
    {
        log("error: dc_drawmethod_set_enabled(void ent, int value): {value} argument is invalid.");
        return;
    }

    changedrawmethod(ent, "enabled", value);
}

// Set drawmethod tint mode.
void dc_drawmethod_set_tint_mode(void ent, int value)
{
    // Catch bad arguments here.
    if(typeof(value) != DC_DRAWMETHOD_VARTYPE_INTEGER)
    {
        log("error: dc_drawmethod_tint_mode(void ent, int value): {value} argument is invalid.");
        return;
    }

    changedrawmethod(ent, "tintmode", value);
}

// Set drawmethod tint color.
void dc_drawmethod_set_tint_color(void ent, int rgb_r, int rgb_g, int rgb_b)
{
    int rgb_final = 0;    // Final RGB result.

    // Catch bad arguments here.
    if(typeof(rgb_r) != DC_DRAWMETHOD_VARTYPE_INTEGER || rgb_r < DC_DRAWMETHOD_RGB_MIN || rgb_r > DC_DRAWMETHOD_RGB_MAX
        || typeof(rgb_g) != DC_DRAWMETHOD_VARTYPE_INTEGER || rgb_g < DC_DRAWMETHOD_RGB_MIN || rgb_g > DC_DRAWMETHOD_RGB_MAX
        || typeof(rgb_b) != DC_DRAWMETHOD_VARTYPE_INTEGER || rgb_b < DC_DRAWMETHOD_RGB_MIN || rgb_b > DC_DRAWMETHOD_RGB_MAX)
    {
        log("error: dc_drawmethod_set_tint_color(void ent, int rgb_r, int rgb_g, int_rgb_b): One or more {rgb} arguments are invalid.");
        return;
    }

    // Get RGB code needed for OpenBOR.
    rgb_final = rgbcolor(rgb_r, rgb_g, rgb_b);

    changedrawmethod(ent, "tintcolor", rgb_final);
}

// Set drawmethod map.
void dc_drawmethod_set_map(void ent, int index)
{
    int pal_max = 0; // Number of palettes entity has loaded.

    // Get the entity's max map index.
    pal_max     = getentityproperty(ent, "mapcount");

    // If the index is not an integer value, it's probably
    // empty or accidently given a non integer value.
    // We'll return without setting value.
    if(typeof(index) != DC_VARS_TYPE_INTEGER
       || index > pal_max
       || index < 0)
    {
        log("Error: dc_drawmethod_set_map(void ent, int index): {index} must be an integer matching one of the entitiy's available map indexes.");
        return;
    }

    changedrawmethod(ent, "remap", index);
}

void dc_drawmethod_auto_tint(void ent)
{
    // dc_drawmethod_auto_tint
    // License - http://www.caskeys.com/dc/?p=5067
    // Caskey, Damon V.
    // 2015-05-04
    //
    // Apply color tint for hit effects.

    float time_percentage   = 0.0;  // Calculated time percentage.
    int time_effect         = 0;    // The normal set time for an effect to expire.
    float time_remaining    = 0.0;  // Actuall time in seconds before an effect will expire.
    float time_current      = 0.0;  // The current engine time.
    float time_initial      = 0.0;  // Time an effect was applied.
    int   map_default       = 0;    // Remap entity was spawned into play with.
    int   animation         = 0;    // Animation ID currently in use.
    int   debug             = NULL();    // Debug mode.
    int   alpha             = 0;

    int rgb_r = 0,  // RGB color settings.
        rgb_g = 0,
        rgb_b = 0,
        tint_mode = DC_DRAWMETHOD_TRANSPARENCY_OFF;

    // Verify entity or exit.
    if(typeof(ent) != DC_DRAWMETHOD_VARTYPE_POINTER) return;
    if(!getentityproperty(ent, "exists")) return;

    // First lets turn drawmethod on. If we don't, nothing below will
    // work at all.
    dc_drawmethod_set_enabled(ent, DC_DRAWMETHOD_FLAG_ON);

    // For time controlled effects, we need to know
    // current time and the time an effect was first
    // applied.
    time_current    += openborvariant("elapsed_time");
    time_initial    += dc_vars_get_entity_float(ent, DC_DRAWMETHOD_VAR_KEY_TIME_INITIAL);

    // If entity is frozen, apply a freeze tint.
    if(getentityproperty(ent, "aiflag", "frozen") == DC_DRAWMETHOD_FLAG_ON)
    {
        // First we need to know how long the entity is meant to be frozen.
        time_effect = getentityproperty(ent, "freezetime");

        // Now let's see if we have a time when the freeze took place.
        // If not, this, entity was just frozen, so let's
        // record the time to an entity var.
        if(!time_initial)
        {
            time_initial = time_effect - time_current;
            dc_vars_set_entity_float(ent, DC_DRAWMETHOD_VAR_KEY_TIME_INITIAL, time_initial);
        }

        // How much time is left before freeze effect is set to expire?
        time_remaining  = time_effect - time_current;

        // Now let's find out want to know what % of the original
        // freeze time is left. Then we'll multiply that by
        // maximum intensity of color and apply it to blue
        // and green color setting.
        time_percentage = (time_remaining) / (time_initial);
        rgb_b = DC_DRAWMETHOD_FREEZE * time_percentage;

        // Make green same intensity as blue - this makes a much
        // stronger looking freeze effect than blue alone.
        rgb_g = rgb_b;

        // Unless fmap is set to -1, OpenBOR ALWAYS applies an fmap on frozen entities.
        // Since the default fmap is 0, that means entities without an fmap revert
        // back to their default palette. Obviously we don't we don't want that since
        // the whole point is to use dynamic tinting instead of a remap. To fix the
        // problem we'll get the map that entity was spawned into play with (ie. was
        // using before being set to an fmap), and force the engine to use it here.
        map_default = getentityproperty(ent, "mapdefault");
        dc_drawmethod_set_map(ent, map_default);

        // Set transparency mode for tint, and apply blue intensity based
        // on % of initial freeze time is left.
        dc_drawmethod_set_tint_mode(ent, DC_DRAWMETHOD_FREEZE_MODE);
        dc_drawmethod_set_tint_color(ent, DC_DRAWMETHOD_RGB_MIN, rgb_g, rgb_b);

        // No reason to do anything else, so exit the function.
        return;
    }


    // For most effects checking the animations will work, so
    // let's grab the current animation here.
    animation = getentityproperty(ent, "animationid");

    // In a burning animation? Then we'll apply burn tint.
    if(animation == openborconstant("ANI_BURN")
       || animation == openborconstant("ANI_BURNPAIN"))
    {
        // Set transparency mode for tint, and apply tint color.
        dc_drawmethod_set_tint_mode(ent, DC_DRAWMETHOD_BURN_MODE);
        dc_drawmethod_set_tint_color(ent, DC_DRAWMETHOD_BURN_RGB_R, DC_DRAWMETHOD_BURN_RGB_G, DC_DRAWMETHOD_BURN_RGB_B);

        // Nothing else to do, so exit the function.
        return;
    }

    // In a death animation?
    if(animation == openborconstant("ANI_DIE"))
    {
        // Set transparency mode for tint, and apply tint color.
        dc_drawmethod_set_tint_mode(ent, DC_DRAWMETHOD_KO_MODE);
        dc_drawmethod_set_tint_color(ent, DC_DRAWMETHOD_KO_RGB_R, DC_DRAWMETHOD_KO_RGB_G, DC_DRAWMETHOD_KO_RGB_B);

        // Nothing else to do, so exit the function.
        return;
    }

    ///////

    // If you want to add other tint effects, like shock, poison,
    // and so on, put them here. Use the burn example as a
    // template.

    ///////

    // If we got this far without exiting, there was no effect to apply.
    // Clear any previous tints and entity vars.
    dc_drawmethod_set_tint_color(ent, DC_DRAWMETHOD_FLAG_OFF, DC_DRAWMETHOD_FLAG_OFF, DC_DRAWMETHOD_FLAG_OFF);
    dc_drawmethod_set_tint_mode(ent, DC_DRAWMETHOD_FLAG_OFF);

    dc_vars_clear_entity_var(ent, DC_DRAWMETHOD_VAR_KEY_TIME_INITIAL);
}

void dc_effect_tint_debug_control()
{
    int     player_index    = getlocalvar("player");
    int     debug           = DC_DRAWMETHOD_FLAG_OFF;
    int     key_press       = DC_DRAWMETHOD_FLAG_OFF;
	int     key_hold        = DC_DRAWMETHOD_FLAG_OFF;
	int     value           = 0;
    int     mode            = 0;

    // Get current key press and any keys being held.
    key_hold        = getplayerproperty(player_index, "keys");
    key_press       = getplayerproperty(player_index, "newkeys");

    // Get stored debug flag.
	debug           = dc_vars_get_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_FLAG);

    // if holding escape, then use Up/Down presses
    // to toggle debugging mode.
    if(key_hold & DC_DRAWMETHOD_KEY_ESCAPE)
    {
        debug = dc_vars_get_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_FLAG);

        debug = dc_effect_tint_spinner(debug, DC_DRAWMETHOD_FLAG_OFF, DC_DRAWMETHOD_FLAG_ON);

        dc_vars_set_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_FLAG, debug);
    }

    // If debugging mode is on, then we're going to use Bitwise ANDs to
    // see if certain keys are held. If they are, then pressing Up/Down
    // key presses will adjust associated values. As coded, each item has
    // an independent evaluation. This is to allow more than one value to
    // be adjusted at once, depending on limits of the input device.
    if(debug == DC_DRAWMETHOD_FLAG_ON)
    {
        // Tinting transparency mode.
        if(key_hold & DC_DRAWMETHOD_KEY_ATTACK_1)
        {
            // Get orginal value.
            mode    = dc_vars_get_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_TINT_MODE);

            // Adjust value based on key press and limits.
            mode    = dc_effect_tint_spinner(mode, 0, 6);

            // Save value.
            dc_vars_set_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_TINT_MODE, mode);
        }

        // RGB Red value.
        if(key_hold & DC_DRAWMETHOD_KEY_ATTACK_2)
        {
            // Get orginal value.
            value    = dc_vars_get_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_RED);

            // Adjust value based on key press and limits.
            value    = dc_effect_tint_spinner(value, 0, 255);

            // Save value.
            dc_vars_set_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_RED, value);
        }

        // RGB Green value.
        if(key_hold & DC_DRAWMETHOD_KEY_ATTACK_3)
        {
            // Get orginal value.
            value    = dc_vars_get_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_GREEN);

            // Adjust value based on key press and limits.
            value    = dc_effect_tint_spinner(value, 0, 255);

            // Save value.
            dc_vars_set_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_GREEN, value);
        }

        // RGB Blue Value.
        if(key_hold & DC_DRAWMETHOD_KEY_ATTACK_4)
        {
            // Get orginal value.
            value    = dc_vars_get_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_BLUE);

            // Adjust value based on key press and limits.
            value    = dc_effect_tint_spinner(value, 0, 255);

            // Save value.
            dc_vars_set_global_int(DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_BLUE, value);
        }
    }
}

// Simulate spinner control increments with looping.
int dc_effect_tint_spinner(int value, int lower_limit, int upper_limit)
{
    int     player_index    = NULL();   // Which player triggered key event.
    int     key_press       = NULL();   // Keypress

    // Get player index and key press.
    player_index    = getlocalvar("player");
    key_press       = getplayerproperty(player_index, "newkeys");

    // Use a Bitwise AND to find out if the Up or Down key
    // is pressed and increment or decrement the value
    // accordingly.
    if(key_press & DC_DRAWMETHOD_KEY_MOVE_UP)
    {
        value++;
    }
    else if(key_press & DC_DRAWMETHOD_KEY_MOVE_DOWN)
    {
        value--;
    }

    // Now let's make sure the value is in bounds.
    // If not, we'll loop it.
    if(value > upper_limit)
    {
        value = lower_limit;
    }
    else if(value < lower_limit)
    {
        value = upper_limit;
    }

    // Return the final value.
    return value;
}
