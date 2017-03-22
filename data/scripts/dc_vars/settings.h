
// Defined flags. Leave these be.
#ifndef DC_VARS_DEFINE
#define DC_VARS_DEFINE  1

// Basic true and false flags.
#define DC_VARS_FLAG_FALSE          0
#define DC_VARS_FLAG_TRUE           1

// Default values used for each variable type. You probably
// won't need to change these, but they are available for
// your convenience.
#define DC_VARS_DEFAULT_FLOAT       0.0
#define DC_VARS_DEFAULT_INTEGER     0
#define DC_VARS_DEFAULT_POINTER     NULL()
#define DC_VARS_DEFAULT_STRING      ""

// Array settings.
#define DC_VARS_DEFAULT_ARRAY_SIZE  1;


// Random local var keys.
#define DC_VARS_VARKEY_RND_LOWER    "dc_vars_vk_0"
#define DC_VARS_VARKEY_RND_UPPER    "dc_vars_vk_1"
#define DC_VARS_VARKEY_ARRAY        "dc_vars_vk_2"

// Variable types.
#define DC_VARS_TYPE_EMPTY      openborconstant("VT_EMPTY")
#define DC_VARS_TYPE_FLOAT      openborconstant("VT_DECIMAL")
#define DC_VARS_TYPE_INTEGER    openborconstant("VT_INTEGER")
#define DC_VARS_TYPE_POINTER    openborconstant("VT_PTR")
#define DC_VARS_TYPE_STRING     openborconstant("VT_STR")

#endif // DC_VARS_DEFINE
