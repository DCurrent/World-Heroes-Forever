#ifndef DC_MOVE

    // *****Settings*****
    //
    // These are the settings you will use to configure the auxiliary
    // jumping system.

    // This is the maximum height the jumping system allows. Auxiliary
    // jump commands will be ignored until the entity falls back below maximum
    // height. This is to stop characters from climbing or jumping beyond the
    // design boundaries of your stage and possibly getting stuck. You can use
    // any value you like. Note you can temporarily override this setting by
    // using the DC_MOVE_set_max_height() command.
    #define DC_MOVE_MAXIMUM_HEIGHT              openborvariant("hResolution") * 1.25    // Maximum height to allow auxiliary jumps.

    // These are the auxiliary jumping animations. Settings here are module wide.
    // For example, whatever animation you set for double jumping here must be used
    // by every model you want to have double jumping capability. If a model does not
    // have one of these animations, then it simply does not have the associated
    // jumping capability. You can mix and match how you like. In other words, a model
    // might not have a wall jump, but could still have double jumping. Another model
    // might only have double jumping, and yet another might have everything.

    // Note that if you like you may also re-use animation definitions. For example, you
    // could define the same animation here for the start-up of obstacle jumping, wall
    // jumping, and edge jumping. Then adding that single animation to a model would
    // give it all those types of auxiliary jumping.
    #define DC_MOVE_ANI_JUMP_DOUBLE_NEUTRAL     openborconstant("ANI_FOLLOW42")     // Double jumping animation.
    #define DC_MOVE_ANI_JUMP_DOUBLE_BACK        openborconstant("ANI_FOLLOW44")     // Double jumping backward animation.
    #define DC_MOVE_ANI_JUMP_DOUBLE_FORWARD     openborconstant("ANI_FOLLOW43")     // Double jumping forward animation.
    #define DC_MOVE_ANI_JUMP_EDGE               openborconstant("ANI_FOLLOW41")     // Screen edge jumping animation.
    #define DC_MOVE_ANI_JUMP_EDGE_START         openborconstant("ANI_FOLLOW40")     // Screen edge prepping to jump animation. The range of this animation is used to detect screen edges
    #define DC_MOVE_ANI_JUMP_OBJECT             openborconstant("ANI_FOLLOW41")     // Obstacle jumping animation.
    #define DC_MOVE_ANI_JUMP_OBJECT_START       openborconstant("ANI_FOLLOW40")     // Obstacle prepping to jump animation. The range of this animation is used to detect objects.
    #define DC_MOVE_ANI_JUMP_WALL               openborconstant("ANI_FOLLOW41")     // Wall jump animation.
    #define DC_MOVE_ANI_JUMP_WALL_START         openborconstant("ANI_FOLLOW40")     // Wall prepping to jump animation.   The range of this animation is used to detect walls.

    //*****End User Settings.*****
    //
    // Leave the rest of these alone unless you really
    // know what you're doing.

    #define DC_MOVE                             1

    // Control flags
    #define DC_MOVE_TIME_INFINITE               -1                                  // True.

        // System direction flags.
    #define DC_MOVE_DIRECTION_LEFT	            0                                   // Left.
    #define DC_MOVE_DIRECTION_RIGHT             1                                   // Right.

    // Variable keys.
    #define DC_MOVE_VARKEY_DISABLE             "DC_MOVE_disable"               // Disable auxiliary jumping.
    #define DC_MOVE_VARKEY_ENTITY              "DC_MOVE_entity"                // Entity.
    #define DC_MOVE_VARKEY_KEY_HOLD            "DC_MOVE_hold"                  // Key hold.
    #define DC_MOVE_VARKEY_KEY_PRESS           "DC_MOVE_press"                 // Key press.
    #define DC_MOVE_VARKEY_MAX_HEIGHT          "DC_MOVE_max_height"            // Temporary maximum height.

    // System animations.
    #define DC_MOVE_ANI_JUMP                    openborconstant("ANI_JUMP")         // Jumping animation.
    #define DC_MOVE_ANI_JUMP_RUN                openborconstant("ANI_RUNJUMP")      // Running jump animation.
    #define DC_MOVE_ANI_JUMP_WALK               openborconstant("ANI_FORWARDJUMP")  // Moving jump animation.

    // Entity types.
    #define DC_MOVE_TYPE_OBSTACLE               openborconstant("TYPE_OBSTACLE")    // Obstacle.

    // System key flags.
    #define DC_MOVE_KEY_ATTACK                  openborconstant("FLAG_ATTACK")      // Attack 1.
    #define DC_MOVE_KEY_ATTACK_2                openborconstant("FLAG_ATTACK2")     // Attack 2.
    #define DC_MOVE_KEY_ATTACK_3                openborconstant("FLAG_ATTACK3")     // Attack 3.
    #define DC_MOVE_KEY_ATTACK_4                openborconstant("FLAG_ATTACK4")     // Attack 4.
    #define DC_MOVE_KEY_ESCAPE                  openborconstant("FLAG_ESC")         // Escape.
    #define DC_MOVE_KEY_JUMP                    openborconstant("FLAG_JUMP")        // Jump.
    #define DC_MOVE_KEY_MOVE_LEFT               openborconstant("FLAG_MOVELEFT")    // Left.
    #define DC_MOVE_KEY_MOVE_RIGHT              openborconstant("FLAG_MOVERIGHT")   // Right.
    #define DC_MOVE_KEY_SCREENSHOT              openborconstant("FLAG_SCREENSHOT")  // Screen shot.
    #define DC_MOVE_KEY_SPECIAL                 openborconstant("FLAG_SPECIAL")     // Special.

    // Forward/Backward command status in relation to facing.
    #define DC_MOVE_KEY_MOVE_HORIZONTAL_BACK    1                                   // Back.
    #define DC_MOVE_KEY_MOVE_HORIZONTAL_FORWARD 2                                   // Forward.
    #define DC_MOVE_KEY_MOVE_HORIZONTAL_NEUTRAL 3                                   // None.

#endif


