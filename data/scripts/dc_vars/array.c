// External Dependencies
#include    "data/scripts/dc_error/main.c"

// Package Files
#include    "data/scripts/dc_vars/settings.h"
#import     "data/scripts/dc_vars/validate.c"
#import     "data/scripts/dc_vars/local.c"

// Create an array and return its handle.
void dc_vars_create_array()
{
    void result;    // Final result.

    result = array(DC_VARS_DEFAULT_ARRAY_SIZE);

    return result;
}

// Delete all array elements and free the array handle.
void dc_vars_destroy_array()
{
    void    array;  // Array handle.
    int     cursor; // Array cursor.

    array = dc_vars_get_array_handle();

    // Iterate all elements and clear them.
    reset(array);

	do
    {
        // Clear element.
		set(array, key, NULL());

        // Move to next element.
		cursor = next(array);

	} while(cursor);

	// Destroy array.
	free(array);
}

// Get current array handle.
void dc_vars_get_array_handle()
{
    int result;     // Final result.

    // Set the array handle.
    result = dc_vars_get_local_pointer(DC_VARS_VARKEY_ARRAY);

    // Return result.
    return result;
}

// Assign an array handle to work with.
int dc_vars_set_array_handle(void value)
{
    int result;     // Final result.
    int is_pointer; // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_array_handle(void value)");

    // Validate the value argument. It must be the proper type. If not,
    // we will return false without setting anything.
    is_pointer = dc_vars_is_pointer(value);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid array handle.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Set the array handle.
    result = dc_vars_set_local_pointer(DC_VARS_VARKEY_ARRAY, value);

    // Return result.
    return result;
}

// Set value of array element.
int dc_vars_set_array_element(void key, void value)
{
    void    array;      // Array handle.
    int     is_key;     // Valid key flag.
    int     is_pointer; // Valid type flag.

    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_set_array_element(void key, void pointer)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate the value argument. It must be the proper type. If not,
    // we will return false without setting anything.
    is_pointer = dc_vars_is_pointer(value);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid pointer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Get array handle.
    array = dc_vars_get_array_handle();

    // Set the variable.
    set(array, key, value);

    return DC_VARS_FLAG_TRUE;
}

int dc_vars_get_array_size()
{
    void    array;  // Array handle.
    int     result; // Final result.

    // Get array handle.
    array = dc_vars_array_get_handle();

    // Get array size.
    result = size(array);

    // Return result.
    return result;
}

// Insert a new element directly after key.
int dc_vars_insert_array_element(void key, void value)
{
    int     is_key;     // Valid key flag.
    int     is_pointer; // Valid type flag.
    int     cursor;     // Array cursor.

    // Current key and value in array loop.
    void    key_temp,
            value_temp;

    // Current and temp array handles.
    void    array,
            array_temp;

    // Sizes of arrays.
    int size,
        size_temp;


    // Set function name for possible error trapping.
    dc_error_set_function("dc_vars_insert_array_element(void key, void pointer)");

    // Validate the key. It must be a usable as an identifier.
    is_key = dc_vars_is_key(key);

    if(is_key == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{key} must be a valid integer, pointer, or string.");
        dc_error_set_argument(key);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Validate the value argument. It must be the proper type. If not,
    // we will return false without setting anything.
    is_pointer = dc_vars_is_pointer(value);

    if(is_pointer == DC_VARS_FLAG_FALSE)
    {
        dc_error_set_message("{value} must be a valid pointer.");
        dc_error_set_argument(value);
        dc_error_alert();

        return DC_VARS_FLAG_FALSE;
    }

    // Get array handle as temp.
    array_temp = dc_vars_get_array_handle();

    // Get size of temp array.
    size_temp = size(array_temp);

    // Now create a new array one element larger than
    // temp. This will be our finished array.
    size    = size_temp + 1;
    array   = array(size);

    // Now we need to iterate through the temp array
    // and copy each element to our final array, but
    // with new element inserted immediately after the
    // specified key.
    reset(array_temp);

	do
    {
        key_temp    = key();
        value_temp  = value();

        // Clear element.
		set(array, key_temp, value_temp);

        // Move to next element.
		cursor = next(array);

        if(key == key_temp)
        {
            // Clear element.
            set(array, key, value_temp);
        }

	} while(cursor);




    // Set the variable.
    set(array, key, value);

    return DC_VARS_FLAG_TRUE;
}

// Return numeric position of array element
// matching specified key.
int dc_get_key_position(void key)
{
    int counter;
    int is_key;
    void array;

    array = dc_vars_get_array_handle();

    ///////////////// Working Here ////////////////////////////

}

int main()
{
    int array[100], position, count, size, value;

    printf("Enter number of elements in array\n");
    scanf("%d", &size);

    printf("Enter %d elements\n", size);

    for (count = 0; count < size; count++)
    	scanf("%d", &array[count]);

    printf("Enter the location where you wish to insert an element\n");
    scanf("%d", &position);

    printf("Enter the value to insert\n");
    scanf("%d", &value);

    for (count = size - 1; count >= position - 1; count--)
		array[count+1] = array[count];


    array[position-1] = value;

    printf("Resultant array is\n");

    for (count = 0; count <= size; count++)
		printf("%d\n", array[count]);

    return 0;
}
