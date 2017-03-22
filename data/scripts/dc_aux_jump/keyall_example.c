#include "data/scripts/dc_vars/main.c"
#include "data/scripts/dc_drawmethod/main.c"

// You must include the auxiliary jumping system here
// to use its functions.
#include "data/scripts/dc_aux_jump/main.c"


void main()
{
	int p = getlocalvar("player");

	if(playerkeys(p, 1, "moveleft"))
	{
		setglobalvar("p"+p+"lastdir", 0);
	}
	else if(playerkeys(p, 1, "moveright"))
	{
		setglobalvar("p"+p+"lastdir", 1);
	}

    dc_effect_tint_debug_control();

    // Set up basic variables. You'll need most of these these for
    // for key triggered functions anyway.
    int     player_index        = NULL();
    void    player_entity       = NULL();
    int     aux_jump            = NULL();
    int     player_key_press    = NULL();
    int     player_key_hold     = NULL();
    int     aux_jump            = NULL();

    // Populate the variables.
    player_index        = getlocalvar("player");
    player_entity       = getplayerproperty(player_index, "entity");
    player_key_hold     = getplayerproperty(player_index, "keys");
    player_key_press    = getplayerproperty(player_index, "newkeys");


    // Here is where we will set up and execute the auxiliary jumping system.

    // Send the jumping system basic values it will need. Notice these
    // are the variables we populated above.
    dc_aux_jump_set_entity(player_entity);
    dc_aux_jump_set_key_hold(player_key_hold);
    dc_aux_jump_set_key_press(player_key_press);

    // Execute the aux jump function and get the result.
    aux_jump = dc_aux_jump_execute();

    // If an aux jump was triggered, let's clear the
    // Jump key. We don't HAVE to do this, and in some cases
    // might not want to. But unless you intend to use the
    // Jump key for other things in conjunction with the
    // auxiliary jumping system, it's a good idea.
    if(aux_jump != DC_AUX_JUMP_FLAG_FALSE)
    {
        // Remove the jump command from key press.
        player_key_press = player_key_press - DC_AUX_JUMP_KEY_JUMP;

        // Apply the key press to player entity.
        changeplayerproperty(player_entity, "playkeys", player_key_press);
    }

}



