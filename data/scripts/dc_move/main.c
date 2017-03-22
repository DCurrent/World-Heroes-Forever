// External Dependencies
#include    "data/scripts/dc_vars/main.c"
#include    "data/scripts/dc_error/main.c"

// Package files
#include    "data/scripts/dc_move/settings.h"
#import     "data/scripts/dc_move/members.c"
#import     "data/scripts/dc_move/operation.c"
#import     "data/scripts/dc_move/velocity.c"

/*
    dc_movement
    Caskey, Damon V.
    2016-05-08

    General velocity and movement controls. See included readme for details.

    ***Source License***

        By making use of all or part of this script package,
        you agree to the following license, including the
        retention of this license link itself.

        http://www.caskeys.com/dc/?p=5067

    ***Install***

        1. Add container folder folder to your data/scripts folder.
        2. #Include main.c from container folder in whatever script you
            would like to call the functions from.

        See the readme for specific details.

    ***External Dependencies***

        The following are other script packages this one requires
        to run. Make sure you have downloaded and installed them
        first. Otherwise this package will fail to work and likely
        cause the engine to report an error and shut down.

        dc_error
        dc_vars



