#include "safec.h"
// stdio include not needed because safec.h includes it

int main()
{
    s_print("Enter your name: ");
    char* name = s_input();
    if (name)
    {
        s_print_ln("Hello, %s!", name);
        free(name);
    }
    else
    {
        s_print_ln("Failed to read input.");
    }
    return 0;
}
