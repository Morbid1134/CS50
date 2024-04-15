#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    // iterate over each candidate to see if exists
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate is who was voted for then add one vote
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            // return true since vote has been counted
            return true;
        }
    }
    // candidate did not exist, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // keep track of winner(s) and heighest known score
    string winners[candidate_count];
    int number_of_winners = 0;
    int heighest_score = 0;

    // iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidate has heighest known score then replace winners with candidate
        if (candidates[i].votes > heighest_score)
        {
            winners[0] = candidates[i].name;
            number_of_winners = 1;
            heighest_score = candidates[i].votes;
        }
        // else if candidate has equal score to heighest known score, add candidate to winners list
        else if (candidates[i].votes == heighest_score)
        {
            winners[number_of_winners] = candidates[i].name;
            number_of_winners += 1;
        }
    }
    // for candidate in winners list, print candidate name
    for (int i = 0; i < number_of_winners; i++)
    {
        printf("%s\n", winners[i]);
    }
    return;
}
