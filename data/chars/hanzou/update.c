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

    settextobj(text_index, text_x, text_y += 10, text_font, text_z, "Path: " + path0001(entity));
    settextobj(++text_index, text_x, text_y += 10, text_font, text_z, "Path: " + path0002(entity));
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

    log("\n\n" + last);

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

    log("\n\n done");

}
