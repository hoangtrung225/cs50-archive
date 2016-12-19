/**
 * compare-1.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Compares two strings.
 *
 * Demonstrates strings as pointers to characters.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // get line of text
    printf("Say something: ");
    char* s = GetString();
 
    // get another line of text
    printf("Say something: ");
    char* t = GetString();
 
    // try to compare strings
    if (s != NULL && t != NULL)
    {
        if (strcmp(s, t) == 0)
        {
            printf("You typed the same thing!\n");
        }
        else
        {
            printf("You typed different things!\n");
        }
    }
}
