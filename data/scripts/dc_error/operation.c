#include "data/scripts/dc_error/settings.h"

void dc_error_set_argument(void value)
{
    setscriptvar(DC_ERROR_VARKEY_ARGUMENT, value);
}

void dc_error_set_function(void value)
{
    setscriptvar(DC_ERROR_VARKEY_FUNCTION, value);
}

void dc_error_set_message(void value)
{
    setscriptvar(DC_ERROR_VARKEY_MESSAGE, value);
}

void dc_error_alert()
{
    int text_index      = DC_ERROR_TEXTOBJ_INDEX;
    int text_name_pos_x = 0;                        // X position of function name.
    int text_msg_pos_y  = 0;                        // Y position of error message.
    int string_width    = 0;                        // Alert pretext width.
    int time            = 0;
    int type;
    void type_str;                                  // Variable type (as string).

    void function       = "";                       // Function name text.
    void message        = "";                       // Descriptive error message to user.
    void argument       = NULL();                   // Function argument (if relevant).

    // Acquire the error output text.
    argument    = getscriptvar(DC_ERROR_VARKEY_ARGUMENT);
    function    = getscriptvar(DC_ERROR_VARKEY_FUNCTION);
    message     = getscriptvar(DC_ERROR_VARKEY_MESSAGE);

    if(openborvariant("in_level")== DC_ERROR_FLAG_TRUE)
    {
        time = openborvariant("elapsed_time") + DC_ERROR_TEXTOBJ_TIME;

        // Establish text objects.
        // -Alert.
        settextobj(text_index,
            DC_ERROR_TEXTOBJ_POSITION_X,
            DC_ERROR_TEXTOBJ_POSITION_Y,
            DC_ERROR_TEXTOBJ_FONT_BOLD,
            DC_ERROR_TEXTOBJ_POSITION_Z,
            DC_ERROR_ERROR_PRETEXT,
            time);

        // - Label.
        // -- Increment text object index.
        text_index++;
        text_msg_pos_y = DC_ERROR_TEXTOBJ_POSITION_Y + 20;

        settextobj(text_index,
            DC_ERROR_TEXTOBJ_POSITION_X + 15,
            text_msg_pos_y,
            DC_ERROR_TEXTOBJ_FONT_NORMAL,
            DC_ERROR_TEXTOBJ_POSITION_Z,
            function,
            time);

        // -Error message.
        text_index++;
        text_msg_pos_y += 10;

        settextobj(text_index,
            DC_ERROR_TEXTOBJ_POSITION_X + 15,
            text_msg_pos_y,
            DC_ERROR_TEXTOBJ_FONT_NORMAL,
            DC_ERROR_TEXTOBJ_POSITION_Z,
            DC_ERROR_ERROR_MESSAGE,
            time);

    }

    // Now send an alert to the log.
    log("\n\n");
    log(DC_ERROR_ERROR_PRETEXT);
    log(function);
    log("\n");
    log(message);

    // If an argument is given, then let's add its value
    // and type to the log.
    if(argument)
    {
        // Get the argument type as a string.
        type = dc_error_get_type_as_string(argument);

        log("\n");
        log("Argument value: ");
        log(argument);
        log("\n");
        log("Argument Type: ");
        log(type_str);
        log("\n");
    }

    log("\n");
}

// Return the type of variable as a string.
void dc_error_get_type_as_string(void value)
{
    int  type;
    void result;

    type = typeof(value);

    // Can't use switch statements with openborcosntant(),
    // so we'll have to settle for an ugly if block.
    if(type == DC_ERROR_TYPE_EMPTY)
    {
        result = "Empty";
    }
    else if(type == DC_ERROR_TYPE_FLOAT)
    {
        result = "Floating decimal";
    }
    else if(type == DC_ERROR_TYPE_INTEGER)
    {
        result = "Integer";
    }
    else if(type == DC_ERROR_TYPE_POINTER)
    {
        result = "Pointer";
    }
    else if(type == DC_ERROR_TYPE_STRING)
    {
        result = "String";
    }
    else
    {
        result = "Unknown";
    }

    return result;
}

