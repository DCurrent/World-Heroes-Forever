#ifndef DC_DRAWMETHOD_DEFINED

    // These are core functionality constants. Unless
    // you know what you're doing, leave them alone.
    #define     DC_DRAWMETHOD_DEFINED                   1

    #define     DC_DRAWMETHOD_FLAG_OFF                  0
    #define     DC_DRAWMETHOD_FLAG_ON                   1

    #define     DC_DRAWMETHOD_VAR_KEY_DEBUG_FLAG        "dc_drawmethod_0"
    #define     DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_BLUE    "dc_drawmethod_1"
    #define     DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_GREEN   "dc_drawmethod_2"
    #define     DC_DRAWMETHOD_VAR_KEY_DEBUG_RGB_RED     "dc_drawmethod_3"
    #define     DC_DRAWMETHOD_VAR_KEY_DEBUG_TINT_MODE   "dc_drawmethod_4"
    #define     DC_DRAWMETHOD_VAR_KEY_TIME_INITIAL      "dc_drawmethod_5"


    #define     DC_DRAWMETHOD_TRANSPARENCY_OFF          0
    #define     DC_DRAWMETHOD_TRANSPARENCY_ALPHA        1
    #define     DC_DRAWMETHOD_TRANSPARENCY_NEGATIVE     2
    #define     DC_DRAWMETHOD_TRANSPARENCY_OVERLAY      3
    #define     DC_DRAWMETHOD_TRANSPARENCY_HARDLIGHT    4
    #define     DC_DRAWMETHOD_TRANSPARENCY_DODGE        5
    #define     DC_DRAWMETHOD_TRANSPARENCY_AVERAGE      6

    #define     DC_DRAWMETHOD_KEY_STATE_HOLD            0
    #define     DC_DRAWMETHOD_KEY_STATE_PRESS           1
    #define     DC_DRAWMETHOD_KEY_STATE_RELEASE         2
    // Key flags
    #define     DC_DRAWMETHOD_KEY_ATTACK_1              openborconstant("FLAG_ATTACK")
    #define     DC_DRAWMETHOD_KEY_ATTACK_2              openborconstant("FLAG_ATTACK2")
    #define     DC_DRAWMETHOD_KEY_ATTACK_3              openborconstant("FLAG_ATTACK3")
    #define     DC_DRAWMETHOD_KEY_ATTACK_4              openborconstant("FLAG_ATTACK4")
    #define     DC_DRAWMETHOD_KEY_ESCAPE                openborconstant("FLAG_ESC")
    #define     DC_DRAWMETHOD_KEY_MOVE_DOWN             openborconstant("FLAG_MOVEDOWN")
    #define     DC_DRAWMETHOD_KEY_MOVE_UP               openborconstant("FLAG_MOVEUP")

    #define     DC_DRAWMETHOD_RGB_MIN                   0
    #define     DC_DRAWMETHOD_RGB_MAX                   255



    // Variable types.
    #define     DC_DRAWMETHOD_VARTYPE_INTEGER   openborconstant("VT_INTEGER")
    #define     DC_DRAWMETHOD_VARTYPE_POINTER   openborconstant("VT_PTR")


    // The various settings go here so we can keep them
    // all in one place. Feel free to play around with them.
    #define     DC_DRAWMETHOD_BURN_RGB_R                DC_DRAWMETHOD_RGB_MAX       // Burn color Red RGB setting.
    #define     DC_DRAWMETHOD_BURN_RGB_G                102                         // Burn color Green RGB setting.
    #define     DC_DRAWMETHOD_BURN_RGB_B                DC_DRAWMETHOD_RGB_MIN       // Burn color Blue RGB setting.
    #define     DC_DRAWMETHOD_BURN_MODE                 DC_DRAWMETHOD_TRANSPARENCY_ALPHA       // Burn tint alpha mode

    #define     DC_DRAWMETHOD_FREEZE                    255                                    // Freze color (maximum blue intensity).
    #define     DC_DRAWMETHOD_FREEZE_MODE               DC_DRAWMETHOD_TRANSPARENCY_ALPHA       // Freeze tint alpha mode.

    #define     DC_DRAWMETHOD_KO_RGB_R                  220                                    // KO color RGB Red setting.
    #define     DC_DRAWMETHOD_KO_RGB_G                  220                                    // KO color RGB Green setting.
    #define     DC_DRAWMETHOD_KO_RGB_B                  220                                    // KO color RGB Blue setting.
    #define     DC_DRAWMETHOD_KO_MODE                   DC_DRAWMETHOD_TRANSPARENCY_AVERAGE     // KO tint alpha mode.

#endif
