#include "data/scripts/dc_vars/main.c"
#include "data/scripts/dc_d20/main.c"
#include "data/scripts/dc_drawmethod/main.c"

// You must include the auxiliary jumping system here
// to use its functions.
#include "data/scripts/dc_move/main.c"


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

    if(player_key_press & openborconstant("FLAG_START"))
    {
        if(!openborvariant("pause"))
        {
            setglobalvar("game_paused", 1);
        }
        else
        {
            setglobalvar("game_paused", NULL());
        }
    }

    // Here is where we will set up and execute the auxiliary jumping system.

    // Send the jumping system basic values it will need. Notice these
    // are the variables we populated above.
    dc_move_set_entity(player_entity);
    dc_move_set_key_hold(player_key_hold);
    dc_move_set_key_press(player_key_press);

    // Execute the aux jump function and get the result.
    aux_jump = dc_move_execute();

    // If an aux jump was triggered, let's clear the
    // Jump key. We don't HAVE to do this, and in some cases
    // might not want to. But unless you intend to use the
    // Jump key for other things in conjunction with the
    // auxiliary jumping system, it's a good idea.
    if(aux_jump != DC_VARS_FLAG_FALSE)
    {
        // Remove the jump command from key press.
        player_key_press = player_key_press - DC_MOVE_KEY_JUMP;

        // Apply the key press to player entity.
        changeplayerproperty(player_entity, "playkeys", player_key_press);
    }

    // Filestream testing
    int rnd;
    void target;
    char name,
        model,
        alias;

    if(player_key_hold & DC_MOVE_KEY_SPECIAL)
    {
        if(player_key_press & DC_MOVE_KEY_ATTACK_3)
        {
            //dc_vars_set_random_lower_bound(1);
            //dc_vars_set_random_upper_bound(10);

            setlocalvar(DC_D20_KEY_UPPER, 10);
            rnd = dc_d20_random_int();

            log("\n\n");
            log("Random: ");
            log(rnd);
            log("\n");

        }

        if(player_key_press & DC_MOVE_KEY_ATTACK_4)
        {
            target = getentityproperty(player_entity, "opponent");

            int test_loop;
            for(test_loop=0; test_loop < 3000; test_loop++)
            {
                setentityvar(target, "test_loop"+test_loop, test_loop);

                log("\n test_loop(" + test_loop + "): " + getentityvar(target, "test_loop"+test_loop));
            }


            model = getentityproperty(target, "model");
            alias = getentityproperty(target, "name");
            name = get_random_argument(model);

            log("\n\n");
            log("Model: ");
            log(model);
            log("\n");
            log("Alias: ");
            log(alias);
            log("\n");
            log("Random Name: ");
            log(name);
            log("\n");

            // Create array.
            void array_rows = array(2);
            void array_cols = array(5);

            // Set array element value (this works as our object property).
            set(array_cols, 0, "A Col 0");
            set(array_cols, 1, "A Col 1");
            set(array_cols, 2, "A Col 2");
            set(array_cols, 3, "A Col 3");
            set(array_cols, 4, "A Col 4");

            set(array_rows, "A", array_cols);

            void row = get(array_rows, "A");
            char col = get(row, 2);

            log("col 2: ");
            log(col);
            log("\n");


        }
    }

}

// Generate random argument from text database.
char get_random_argument(void key)
{
    int  is_argument;   // Valid value flag.
    int  random;        // Random name flag.
    int  filestream;    // Names text file index.
    void argument;      // Argument from filestream.
    char result;        // Final result.
    int  found;         // Finding flag.
    int  is_key;        // Valid key flag.

    // Current column position and
    // total column count.
    int  column_count,
        column_position;

    int  row_current,
        row_prev;

    // Set default for result.
    result = -1;

    // Verify valid key.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        return result;
    }

    // Get names text file index.
    filestream = getindexedvar("test_1");

    // File index empty and not a 0?
    if(!filestream && filestream != 0)
    {
        // Open Names file stream and store index.
        filestream = openfilestream("names.bin", 1);
        setindexedvar("test_1", filestream);
    }

    if(filestream == -1)
    {
        log("\n\n No load");
        return -1;
    }

    // Go first row of the filestream.
    setfilestreamposition(filestream, 0);

    // Get first column value, then continue on to each
    // subsequent row in the column until a match for key
    // is found or we reach the end of the file.
    argument = getfilestreamargument(filestream, 0, "string");

    while(argument != key)
    {
        // Record previous row cursor position. We need this to
        // know when we're at last row.
        row_prev = getfilestreamposition(filestream);

        // Move to next line and test for a value match.
        filestreamnextline(filestream);
        argument = getfilestreamargument(filestream, 0, "string");

        row_current = getfilestreamposition(filestream);

        // Filestreamnextline() does nothing if we're already at
        // last row. We can use that to detect when we're at the last row
        // here by comparing the row cursor before filestreamnextline()
        // call and after. If they are the same, we know we're at the
        // last row. Last rows must always be blank or contain a dummy value,
        // so if we got this far, then no match was found and there's no
        // reason to do anything else. We'll exit the function and return
        // a default value.
        if(row_prev == row_current)
        {
            return -1;
        }
    }

    // Now we will count the number
    // columns in the line by looping over each and looking for
    // an argument until no valid argument is found.

    // Initialize counter.
    column_position = 0;

    // Start loop.
    do
    {
        // Get value (if any) and increment counter.
        is_argument = getfilestreamargument(filestream, column_position, "string");
        column_position++;
    }
    while (is_argument);

    // Loop above stops when a blank column is detected. That means the
    // position is one over last argument, and since the position gets
    // another increment right after, we need to subtract two for
    // an accurate count.
    column_count = column_position - 2;

    // Now that we have a count of columns in this line,
    // we can use it as the upper bound for random
    // number generation. We'll set lower bound to one
    // since column 0 is the identifier.
    dc_vars_set_random_lower_bound(1);
    dc_vars_set_random_upper_bound(column_count);

    // Generate a random number. We'll use this number to chose
    // which column to get our value from.
    random = dc_vars_get_random_int();

    // We now have a random number corresponding to second
    // column (column 1) through maximum number of columns.
    // All we need to do is get argument from a column using
    // the random number.
    argument   = getfilestreamargument(filestream, random, "string");

    // changeentityproperty(entity, "name", alias);							//Asign new alias to model.

    // Copy the column argument to final result.
    result = argument;

    filestreamappend(filestream, "append_1", 1);
    filestreamappend(filestream, "append_2", 1);
    savefilestream(filestream, "names.bin");

    closefilestream(filestream);

    // Return final result.
    return result;
}





