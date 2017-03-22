#ifndef DC_HP_FLOAT

#define DC_HP_FLOAT 1

#define DC_HP_FLOAT_FONT                2   // Font for text display.
#define DC_HP_FLOAT_CAYDENCE            "%" // Add on string for HP display.

#define DC_HP_FLOAT_POSITION_BASE_X     10  // Starting X position of text.
#define DC_HP_FLOAT_POSITION_BASE_Y     80  // Starting Y position of text.

#define DC_HP_FLOAT_POSITION_FACTOR_Y   20  // Amount to adjust position of each player text compared to previous.

#define DC_HP_FLOAT_VARTYPE_POINTER     openborconstant("VT_PTR")

#endif // DC_HP_FLOAT

void dc_hp_float()
{

    void    entity;         // Player entity.
    char    result;         // Final result to display on screen.
    int     var_type;       // Variable type.
    int     hp_percentage;  // HP percentage result.
    int     hp_current;     // Current HP.
    int     hp_max;         // Maximum HP.
    int     i;              // Loop counter.
    int     player_max;     // Maximum available players.
    int     position_adj_y; // Position adjustment, Y axis.
    int     position_y;     // Final position, Y axis.

    // Get currently allowed number of players.
    player_max = openborvariant("max_players");

    // Loop through each player index, from 0 to max.
    for(i = 0; i < player_max; i++)
    {
        // Adjust position for display by multiplying
        // factor with loop counter, and adding result
        // to base.
        position_adj_y  = i * DC_HP_FLOAT_POSITION_FACTOR_Y;
        position_y      = position_adj_y + DC_HP_FLOAT_POSITION_BASE_Y;

        // Get player entity.
        entity = getplayerproperty(i, "entity");

        // Verify the entity var is a valid pointer.
        var_type = typeof(entity);

        if(var_type == DC_HP_FLOAT_VARTYPE_POINTER)
        {
            // Get hp and HP max.
            hp_current  = getentityproperty(entity, "health");
            hp_max      = getentityproperty(entity, "maxhealth");

            // Calculate a percentage value.
            hp_percentage = hp_current * 100 / hp_max;

            // Combine calculation with string add ons.
            result = hp_percentage + DC_HP_FLOAT_CAYDENCE;

            // Draw result to the screen.
            drawstring(DC_HP_FLOAT_POSITION_BASE_X, position_y, DC_HP_FLOAT_FONT, result);
        }
    }
}
