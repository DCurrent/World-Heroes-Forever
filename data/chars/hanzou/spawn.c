#include "data/scripts/dc_kanga/main.c"

void main()
{

    void self = getlocalvar("self");

    setlocalvar(DC_KANGA_KEY_TARGET, self);

    dc_kanga_random_index();

    head_spawn();
}

void head_spawn(void target)
{
    void spawn;
    float target_pos_X;
    float target_pos_Y;
    float target_pos_Z;
    void target_table;  //target's current color table.


    if(!target)
    {
        target = getlocalvar("self");
    }

    target_pos_X    = getentityproperty(target, "x") - openborvariant("xpos");
    target_pos_Y    = getentityproperty(target, "z");
    target_pos_Z    = getentityproperty(target, "a");
    target_table    = getentityproperty(target, "colourmap");

    clearspawnentry();
    setspawnentry("name",   "hanzou_head");
    setspawnentry("alias",  "head");
    setspawnentry("map",    0);
	setspawnentry("coords", target_pos_X, target_pos_Y, target_pos_Z);
    spawn = spawn();
    clearspawnentry();

    log("spawn :" + spawn);

    changeentityproperty(spawn, "parent", target);

    bindentity(spawn, target, 0, 0, 0, openborconstant("DIRECTION_ADJUST_SAME"), 2);

}
