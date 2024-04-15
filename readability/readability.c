#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Get corpus to check its readability level
    string corpus = get_string("Text: ");

    // Initialize number of words, sentences, and letters
    int words = 1; // Assume at least 1 word in text
    int sentences = 0;
    int letters = 0;

    // Iterate over each character of the string
    for (int i = 0, l = strlen(corpus); i < l; i++)
    {
        // Set current lowercase character (prevent repeated indexing)
        char cc = tolower(corpus[i]);

        // If current character is a space then assume new word
        if (cc == ' ')
        {
            words++;
        }
        // If current character is . ? or ! then assume new sentence
        else if (cc == '.' || cc == '?' || cc == '!')
        {
            sentences++;
        }
        // Otherwise, if character tolower is >= 'a' and is <= 'z' then assume new letter
        else if (cc >= 'a' && cc <= 'z')
        {
            letters++;
        }
    }
    // L
    // Average number of letters per word is total letter divide total words
    // Average number of letters per 100 words is above times 100
    float L = (letters / (float) words) * 100.0;

    // S
    // Average number of sentences per word is total sentences divide total words
    // Average number of sentences per 100 words is above times 100
    float S = (sentences / (float) words) * 100.0;

    // Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // if index is < 1 the write "Before Grade 1"
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    // else if index is > 16 then write "Grade 16+"
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    // else write "Grade %i", index
    else
    {
        printf("Grade %i\n", index);
    }
}
