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
