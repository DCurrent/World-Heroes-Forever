void main()
{
    if(openborvariant("in_selectscreen")==1) return;

    void entity = getlocalvar("self");

    int     text_index, text_x, text_y, text_z, text_font;

    text_index  = 6;
    text_x      = 10;
    text_y      = 110;
    text_z      = 999999994;
    text_font   = 1;

    //settextobj(text_index, text_x, text_y += 10, text_font, text_z, "Path: " + path0001(entity));
    //settextobj(++text_index, text_x, text_y += 10, text_font, text_z, "Path: " + path0002(entity));

    afterimage_setup();
}

char path0002(void vEnt)
{

    /*
    path0001
    06182010
    Damon V. Caskey

    Return entity path (without filename). Pretty suboptimal with a while
    loop, but does the job given OpenBOR's limited string manipulation.
    */

    char    cPath   = getentityproperty(vEnt, "path");			//Sample string.
	char    cStr;
    int     i       = strlength(cPath);

    int last = strinlast(cPath, "/");

    //return strleft(cPath, last);

    //log("\n\n" + last);

}

char path0001(void vEnt)
{

    /*
    path0001
    06182010
    Damon V. Caskey

    Return entity path (without filename). Pretty suboptimal with a while
    loop, but does the job given OpenBOR's limited string manipulation.
    */

    char    cPath   = getentityproperty(vEnt, "path");			//Sample string.
	char    cStr;
    int     i       = strlength(cPath);

    do
    {
        cStr = strright(cPath, i--);

        log("\n" + cStr);
    }
    while (strinfirst(cStr, "/") == -1);

    return strleft(cPath, i+1);

    //log("\n\n done");

}

#include "data/scripts/trailer.h"

void afterimage_setup()
{
	int i, j, k;
	void spr;
	int facing, cd;
	float a, z, x;

	void ent = getlocalvar("self");
	int anim = getentityproperty(ent, "animationid");
	void map;
	int elapsed_time = openborvariant("elapsed_time");

	if(anim == openborconstant("ANI_WALK")){ map = getentityproperty(ent, "colourtable", 2);}
	if(anim == openborconstant("ANI_JUMP")){ map = getentityproperty(ent, "colourtable", 0);}
	setglobalvar("blahblah.map", map);


	if(elapsed_time%trailerd==0)
	{
		if((anim == openborconstant("ANI_WALK")) || (anim == openborconstant("ANI_JUMP")))
		{
            spr = getentityproperty(ent, "sprite");
            x = getentityproperty(ent, "x");
            z = getentityproperty(ent, "z");
            a = getentityproperty(ent, "a");
            facing = !getentityproperty(ent, "direction");

            for(k=1; k<=trailermax; k++) //find an empty trailer slot
            {
                if(getglobalvar("trailer"+k+".s")==NULL())
                {
                    setglobalvar("trailer"+k+".s", spr);
                    setglobalvar("trailer"+k+".x", x);
                    setglobalvar("trailer"+k+".z", z);
                    setglobalvar("trailer"+k+".a", a);
                    setglobalvar("trailer"+k+".f", facing);
                    setglobalvar("trailer"+k+".c", trailerc*trailerd);
                    break;
                }
            }
        }
	}
}

