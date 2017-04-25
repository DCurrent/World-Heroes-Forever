# DC Random
Generate random values in OpenBOR script.

Load this library into your module projects to enable controllable random number generation. 

## Installation

1. Download and unzip dc_vars folder into your data/scripts folder.
1. #include data/scripts/dc_random/main.c into any other script you would like to add random number functionality to.
1. Open config.h to modify default values used in the library.

## Use Cases

Get current lower boundry for number generation.
```c
int i = dc_random_get_lower_bound();
```

Get current upper boundry.
```c
int i = dc_random_get_upper_bound();
```

Set a new upper boundry. Returns 1 if successful.
```c
int i = {int};
int result;

result = dc_random_set_upper_bound(i);
```

Set a new lower boundry. Returns 1 if successful.
```c
int i = {int};
int result;

result = dc_random_set_lower_bound(i);
```

Generate a random integer between lower and upper boundry. If you do not set upper and lower boundries, default values will be used.
```c
int i = dc_random_int();
```
