// #include "data/scripts/traileru.c"

void main()
{
    afterimage_setup();
    draw_afterimage();
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
		if((anim == openborconstant("ANI_RUN")) || (anim == openborconstant("ANI_JUMP")))
		{
            spr = getentityproperty(ent, "sprite");
            x = getentityproperty(ent, "x");
            z = getentityproperty(ent, "z");
            a = getentityproperty(ent, "y");
            facing = getentityproperty(ent, "direction");

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

void draw_afterimage()
{
    // Previous draw method values.
    int dm_prev_alpha;
    int dm_prev_enabled;
    int dm_prev_flipx;

	int i, j, k;
	void spr;
	int facing, cd;
	float a, z, x;
	void map = getglobalvar("blahblah.map");

	float pos_draw_x;
	float pos_draw_y;
	float pos_draw_z;

	for(i=1; i<=trailermax; i++)
	{
		spr = getglobalvar("trailer"+i+".s");
		if(spr)
		{
			cd = getglobalvar("trailer"+i+".c");
			if(!cd)
			{
				setglobalvar("trailer"+i+".c", NULL());
				setglobalvar("trailer"+i+".s", NULL());
				setglobalvar("trailer"+i+".x", NULL());
				setglobalvar("trailer"+i+".z", NULL());
				setglobalvar("trailer"+i+".a", NULL());
			}
			else
			{
				if(openborvariant("game_paused")==0)
				{
					setglobalvar("trailer"+i+".c", cd-1);
				}
				x = getglobalvar("trailer"+i+".x");
				z = getglobalvar("trailer"+i+".z");
				a = getglobalvar("trailer"+i+".a");
				facing = getglobalvar("trailer"+i+".f");

				// Direct draw sprites use the global drawmethod, so
				// let's set up its attributes here. We'll also
				// need to get the drawmethods already in use
				// so we can reset them when we're done.
				dm_prev_alpha   = getdrawmethod(NULL(), "alpha");
                dm_prev_enabled = getdrawmethod(NULL(), "enabled");
                dm_prev_flipx   = getdrawmethod(NULL(), "flipx");

				changedrawmethod(NULL(), "enabled", 1);
				changedrawmethod(NULL(), "alpha", 1);

				// If facing left, let's flip the sprite.
				if(facing == openborconstant("DIRECTION_LEFT"))
                {
                    changedrawmethod(NULL(), "flipx", 1);
                }

                // Calculate final draw position for drawn sprite.
                pos_draw_x = x-openborvariant("xpos");
                pos_draw_y = (z-a-openborvariant("ypos"))-4;
                pos_draw_z = (z-1)-i;

				// Draw the sprite to screen.
				//drawsprite(spr, x-openborvariant("xpos"), z-a-openborvariant("ypos"), (z-1)-i, 0);
				drawsprite(spr, pos_draw_x, pos_draw_y, pos_draw_z, 0);

				// Reset the global drawmethod.
				changedrawmethod(NULL(), "enabled", dm_prev_enabled);
				changedrawmethod(NULL(), "flipx", dm_prev_flipx);
				changedrawmethod(NULL(), "alpha", dm_prev_alpha);
			}
		}
	}
}
