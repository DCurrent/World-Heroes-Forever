
//#define ZOOM_SWI 6			//6

#ifndef DC_INSET

#define DC_INSET    1

#define KEY_SCREEN          "key_screen"
#define KEY_BACKGROUND      "key_background"
#define SCREEN_BACKGROUND   "data/levels/usa4/screen00.gif"

#endif // DC_INSET

void get_screen()
{
    void screen;
    int  x;
    int  y;
    int  background_sprite;

    x = openborvariant("hresolution");
    y = openborvariant("vresolution");

    // Get current screen.
    screen = getlocalvar(KEY_SCREEN);

    // If no screen is set up,
    // initialize it here.
    if(!screen)
    {
        // Load the background sprite for our screen.
        background_sprite = loadsprite(SCREEN_BACKGROUND);

        // Allocate screen and use it to populate
        // the screen variable, then populate
        // background variable.
        screen = allocscreen(x, y);
        setlocalvar(KEY_SCREEN, screen);
        setlocalvar(KEY_BACKGROUND, background_sprite);
    }

    return screen;
}


void main()
{
	//if(getglobalvar("game_paused")){return;}else{}
	void count=getscriptvar(2);
	void current_time=openborvariant("elapsed_time");
	if(!count){
		count=current_time;
		setscriptvar(2, current_time);
	}else{}
	void scr = get_screen();



	int maxz    = openborvariant("PLAYER_MAX_Z");
	int min_z   = openborconstant("MIN_INT");

	//min_z = 135;

	//if(openborvariant("game_paused"))return;
	if(current_time - count>1) //12
	{
		clearscreen(scr);
		drawspriteq(scr, 0, min_z, maxz, 0, 0);
		setscriptvar(2, current_time);
	}
	//Set drawMethod
	changedrawmethod(NULL(),"reset",1);
	changedrawmethod(NULL(),"enabled",1);
	//changedrawmethod(NULL(),"scalex",43);
	//changedrawmethod(NULL(),"scaley",52);

	changedrawmethod(NULL(),"scalex",54);
	changedrawmethod(NULL(),"scaley",54);

	//Draw the resized customized screen to main screen.
	float x = openborvariant("xpos") + 35;
	float y = 33;

	void self = getlocalvar("self");

	x = getentityproperty(self, "x") - x;
	y = getentityproperty(self, "y") + getentityproperty(self, "base") - 22;

	drawscreen(scr,x,-y,135);
	//changedrawmethod(NULL(),"scalex",256);
	//changedrawmethod(NULL(),"scaley",328);
	//changedrawmethod(NULL(),"alpha",2);
	//drawsprite(getscriptvar(1),x,y,2);
	changedrawmethod(NULL(),"enabled", 0);

    //settextobj(0, 10, 50, 1, 999999994, openborvariant("PLAYER_MIN_Z"));
	//settextobj(1, 10, 60, 1, 999999994, min_z);
	//settextobj(2, 10, 70, 1, 999999994, openborconstant("MIN_INT"));
	//settextobj(3, 10, 80, 1, 999999994, openborvariant("pause"));
	settextobj(2, 10, 70, 1, 999999994, "x: " + x);
	settextobj(3, 10, 80, 1, 999999994, "y: " + y);
	settextobj(4, 10, 90, 1, 999999994, openborvariant("elapsed_time"));


}
void clear()
{
	void scr = getindexedvar(0);
	if(scr){
		free(scr);
		free(getscriptvar(1));
	}
}
