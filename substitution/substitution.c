#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // If no arguments or more than 2 argument (not equal to 2 arguements), return error
    if (argc != 2)
    {
        printf("Usage: ./substitution [key]\n");
        return 1;
    }

    // else, if key is not 26 characters, return error
    // `else` is unneccesary due to early exits
    if (strlen(argv[1]) != 26)
    {
        printf("Key must be 26 characters\n");
        return 1;
    }

    // else, go over each character
    for (int i = 0, l = strlen(argv[1]); i < l; i++)
    {
        // set current character
        char cc = argv[1][i];

        // if current character in key is not an alphabetic character then exit early
        if (isalpha(cc) == false)
        {
            printf("Key must contain only alphabetical characters\n");
            return 1;
        }

        // check if current character is in key more than once
        int matches = 0;
        for (int j = 0; j < l; j++)
        {
            if (tolower(cc) == tolower(argv[1][j]))
            {
                matches++;
            }
        }
        if (matches > 1)
        {
            printf("A character should only appear once in the key\n");
            return 1;
        }
    }

    // Ask for plaintext to encrypt
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    // Loop through each character in plaintext
    for (int i = 0, l = strlen(plaintext); i < l; i++)
    {
        // Get current character
        char cc = plaintext[i];

        // if character is alphabetical then encrypt it
        if (isalpha(cc))
        {
            // If character is lowercase than index is cc - 'a'
            if (islower(cc))
            {
                // print substitute letter with key
                printf("%c", tolower(argv[1][(cc - 'a')]));
            }
            else
            // If character is not lowercase than index is cc - 'A'
            {
                printf("%c", toupper(argv[1][(cc - 'A')]));
            }
        }
        // else, print it naturally
        else
        {
            printf("%c", cc);
        }
    }
    printf("\n");
}
