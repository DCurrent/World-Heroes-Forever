#include "data/scripts/trailer.h"

void draw_afterimage()
{
	int i, j, k;
	void spr;
	int facing, cd;
	float a, z, x;
	void map = getglobalvar("blahblah.map");

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

				//setdrawmethod(NULL(), 1, 256, 256, facing, 0, 0, 6, 0, 0, 0, 0, 0, map);



				// Direct draw sprites use the global drawmethod, so
				// let's set up its attributes here.
				changedrawmethod(NULL(), "enabled", 1);
				changedrawmethod(NULL(), "alpha", 1);

				if(facing == openborconstant("DIRECTION_LEFT"))
                {
                    changedrawmethod(NULL(), "flipx", 1);
                }

				// Draw the sprite to screen.
				drawsprite(spr, x-openborvariant("xpos"), z-a-openborvariant("ypos"), (z-1)-i, 0);

				// Reset the global drawmethod.
				changedrawmethod(NULL(), "enabled", 0);
				changedrawmethod(NULL(), "flipx", 0);
				changedrawmethod(NULL(), "alpha", 0);
			}
		}
	}
}
