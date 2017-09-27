#include "data/scripts/dc_eggball/main.c"
#include "data/scripts/dc_kanga/main.c"

void main()
{


    if (dc_eggball_interval(1))
    {
        dc_kanga_increment_global_index();
    }

    settextobj(2, 10, 70, 1, 999999994, "Palette: " + openborvariant("current_palette") + " of " + openborvariant("numpalettes"));
	settextobj(3, 10, 80, 1, 999999994, "Last: " + getlocalvar(DC_EGGBALL_LAST + 1));
	settextobj(4, 10, 90, 1, 999999994, "Time: " + openborvariant("elapsed_time"));
	//settextobj(5, 10, 100, 1, 999999994, "Sets: " + openborvariant("sets_count"));

    //debug();

}

void debug()
{
    int     text_index, text_x, text_y, text_z, text_font;
    int     set_current;
    int     level_current;
    void    set_handle;
    void    level_collection;
    void    level_handle;
    int     set_levels_count;
    int     set_prop_levels_count;
    void    set_prop_name;
    int     set_prop_levels_handle;
    int    level_prop_name;


    set_current     = openborvariant("current_set");
    level_current   = openborvariant("current_level");
    set_handle      = get_set_handle(set_current);

    //set_prop_levels_handle = openborconstant("SET_PROP_LEVELS_HANDLE");

    set_levels_count    = get_set_property(set_handle, openborconstant("SET_PROP_LEVELSET_COUNT"));
    set_prop_name       = get_set_property(set_handle, openborconstant("SET_PROP_NAME"));

    level_prop_name     = get_level_property(NULL(), openborconstant("LEVEL_PROP_NAME"));

    text_index  = 6;
    text_x      = 10;
    text_y      = 110;
    text_z      = 999999994;
    text_font   = 1;

	settextobj(text_index++, text_x, text_y += 10, text_font, text_z, "Current Set: " + set_current);
	settextobj(text_index++, text_x, text_y += 10, text_font, text_z, "Set Handle: " + set_handle);
	settextobj(text_index++, text_x, text_y += 10, text_font, text_z, "Set Name: " + set_prop_name);
	settextobj(text_index++, text_x, text_y += 10, text_font, text_z, "Set Levels Count: " + set_levels_count);
	settextobj(text_index++, text_x, text_y += 10, text_font, text_z, "Level Name: " + level_prop_name);
	//settextobj(9, 10, 140, 1, 999999994, "SET_PROP_LEVELS_HANDLE: " + set_prop_levels_handle);
	//settextobj(10, 10, 150, 1, 999999994, "Levels Count: " + levels_count);
}
