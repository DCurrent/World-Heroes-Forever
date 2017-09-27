#include "data/scripts/dc_kanga/main.c"

void main()
{

    void self = getlocalvar("self");

    setlocalvar(DC_KANGA_KEY_TARGET, self);

    dc_kanga_random_index();

}

