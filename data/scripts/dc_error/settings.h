
// Define flags. Leave these alone.
#ifndef DC_ERROR_DEFINE
#define DC_ERROR_DEFINE  1

#define DC_ERROR_TITLE                  ""                              // An overall title for errors. Mostly redundant.

#define DC_ERROR_FLAG_FALSE             0
#define DC_ERROR_FLAG_TRUE              1

#define DC_ERROR_ERROR_PRETEXT          "Error:"                        // Default error alert subtitle.
#define DC_ERROR_ERROR_MESSAGE          "See log for details."          // Default error alert closing.

#define DC_ERROR_VARKEY_ARGUMENT        "dc_error_arg"                  // Default argument value. Rarely used.
#define DC_ERROR_VARKEY_FUNCTION        "dc_error_fun"                  // Default function value. Rarely used.
#define DC_ERROR_VARKEY_MESSAGE         "dc_error_msg"                  // Default message value. Rarely used.

// OpenBOR variable types.
#define DC_ERROR_TYPE_EMPTY             openborconstant("VT_EMPTY")
#define DC_ERROR_TYPE_FLOAT             openborconstant("VT_DECIMAL")
#define DC_ERROR_TYPE_INTEGER           openborconstant("VT_INTEGER")
#define DC_ERROR_TYPE_POINTER           openborconstant("VT_PTR")
#define DC_ERROR_TYPE_STRING            openborconstant("VT_STR")

// Text box settings.
#define DC_ERROR_TEXTOBJ_FONT_BOLD      2                               // Font index for bold text.
#define DC_ERROR_TEXTOBJ_FONT_LABEL     3                               // Font index for titles and labels.
#define DC_ERROR_TEXTOBJ_FONT_NORMAL    1                               // Font index for normal message text.
#define DC_ERROR_TEXTOBJ_INDEX          0                               // Text object index used for on screen alert.
#define DC_ERROR_TEXTOBJ_POSITION_X     10                              // X position for top left corner of text alert.
#define DC_ERROR_TEXTOBJ_POSITION_Y     60                              // Y position for top left corner of text alert.
#define DC_ERROR_TEXTOBJ_POSITION_Z     -1                              // Z (depth/layer) position of text alert.
#define DC_ERROR_TEXTOBJ_TIME           1000                            // Time to display alert on screen.

#endif // DC_ERROR_DEFINE
