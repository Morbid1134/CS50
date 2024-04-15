#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_loop(int target, int looper);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // for every candidate in election, check if that candidate is current name
    for (int i = 0; i < candidate_count; i++)
    {
        // if the ith candidate is current voted for candidate
        if (strcasecmp(candidates[i], name) == 0)
        {
            // add candidate to ranks as the `rank` position
            // rank[index] is showing the index ranked (0th ranked) candidate. It would return the
            // candidates index in candidates[]. to see this voters 3rd candidate of choice input
            // ranks[2] and to see the name cooresponding to the returned int then do
            // candidates[ranks[2]]
            ranks[rank] = i;
            // return true that vote was valid
            return true;
        }
    }
    // If no mathing candidate to voters input then return false (candidate doesn't exist)
    // also set rank to -1 to indicate invalid vote
    ranks[rank] = -1;
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // loop over candidates in ranks (which is number of candidates)
    for (int i = 0; i < candidate_count; i++)
    {
        // if current vote is invalid (-1) then skip
        if (ranks[i] == -1)
        {
            return;
        }
        // otherwise, vote is valid
        // for each pair after and including the current candidate in ranks
        for (int j = (i + 1); j < candidate_count; j++)
        {
            // check if second candidate is valid to the pair
            if (ranks[j] != -1)
            {
                // count that candidate i is ranked higher than candidate j
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // keep track of pairs found
    pair_count = 0;

    // for every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // check the pairings for every candidate after current which is i
        for (int j = (i + 1); j < candidate_count; j++)
        {
            // initialize current pair
            pair current_pair;

            // if candidate i is prefered to candidate j then add pair to pairs array
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    current_pair.winner = i;
                    current_pair.loser = j;
                }
                else
                {
                    current_pair.winner = j;
                    current_pair.loser = i;
                }
                // add pair to pairs array
                pairs[pair_count] = current_pair;
                // increase number of pairs found
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    // for every pair in pairs array
    for (int i = 0; i < pair_count; i++)
    {
        // keep track if we make any changes to array
        bool action;

        // loop over every pair in pair array -1 (since second to last pair checks last pair)
        for (int j = 0; j < (pair_count - 1); j++)
        {
            action = false;

            // get current pairs preference
            int current_pair = preferences[pairs[j].winner][pairs[j].loser];
            // get index of next pairs winner
            int next_pair = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            // if next pair preference is stronger than the current pairs
            // swap pairs
            if (next_pair > current_pair)
            {
                // temporarily store stronger pair
                pair temp = pairs[j + 1];
                // set second position equal to weaker pair
                pairs[j + 1] = pairs[j];
                // set first position with stronger pair
                pairs[j] = temp;
                // note that we did make changes
                action = true;
            }
        }
        // if no changes occured then array is sorted
        if (action == false)
        {
            return;
        }
        // repeat again since array is not sorted (possibly could add recursion)
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // for pair in pairs
    for (int i = 0; i < pair_count; i++)
    {
        //  if adding this arrow does not create a loop
        if (is_loop(pairs[i].winner, pairs[i].loser) == false)
        {
            // create arrow from pair winner (w) to pair loser (l)
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // if locked[i][j] returns true then i points to j but also j has arrow pointing to it
    // loop over every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;
        // for every candidate
        for (int j = 0; j < candidate_count; j++)
        {
            // if jth candidate has an arrow pointing at ith candidate
            if (locked[j][i])
            {
                source = false;
            }
        }
        // if current candidate is source, print as winner and exit early
        if (source == true)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

bool is_loop(int target, int looper)
{
    // if looper is target return true (it is a loop)
    if (target == looper)
    {
        return true;
    }
    // for every candidate
    int loopers[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        // check if looper points to candidate
        if (locked[looper][i] == true)
        {
            // knowing there is another looper, check if looper loops
            if (is_loop(target, i))
            {
                // if looper is in fact a loop then return true (it is a loop).
                return true;
            }
        }
    }
    // after checking all arrows for potential loopers and none were target/loops, return false (this path is not a loop).
    return false;
}
