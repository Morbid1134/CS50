#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    const int players = 2;
    const int char_values[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                                 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    // Keep track of current highest scoring player
    int highest_scoring_player;

    // Keep track of current players score and previous players score
    int scores[2] = {0, 0};

    int ties = 0;

    for (int i = 0; i < players; i++)
    {
        // set current score to 0
        scores[1] = 0;

        // get current players word
        string current_word = get_string("Player %i: ", (i + 1));

        // iterate over each character in current word
        for (int j = 0, l = strlen(current_word); j < l; j++)
        {
            // lowercase current character in current_word
            current_word[j] = tolower(current_word[j]);

            // If current character is between a-z then add its score to scores index 1
            if (current_word[j] >= 'a' && current_word[j] <= 'z')
            {
                scores[1] += char_values[(current_word[j] - 'a')];
            }
        }

        // move current players score to index 0 if it is larger than index 0
        if (scores[1] > scores[0])
        {
            scores[0] = scores[1];
            scores[1] = 0;
            highest_scoring_player = (i + 1);
        }
        else if (scores[1] == scores[0])
        {
            // If both scores are then increase number of ties found
            ties++;
        }
    }
    // If ties + 1 (bc n people can only have n-1 ties) is == #players then everyone has tied
    if ((ties + 1) == players)
    {
        printf("Tie!\n");
    }
    // Otherwise, highest_scoring_player won
    else
    {
        printf("Player %i wins!\n", highest_scoring_player);
    }
}
