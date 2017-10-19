
// Import functions.
#include "data/scripts/dc_drawmethod/main.c"

#include "data/scripts/traileru.c"

void main(){

    void    ent         = NULL();   // Target entity pointer.
    int     ent_count   = 0;        // Entity count.
    int     i           = 0;        // Loop counter.

    // Get entity count.
    ent_count = openborvariant("ent_max");

    // Loop over each entity index.
    for(i=0; i<ent_count; i++)
    {
        // Get entity pointer.
		ent = getentity(i);

		// Execute tint effect on entity.
        //dc_drawmethod_auto_tint(ent);
    }

    draw_afterimage();
  }
