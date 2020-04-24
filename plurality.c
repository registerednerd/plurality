#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

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
        printf("Index: %i, Name: %s, Votes: %i\n", i, candidates[i].name, candidates[i].votes);
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Determine highest vote count
    int high_score = candidates[0].votes;
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes > high_score)
        {
            high_score = candidates[i].votes;
        }
    }

    // determine how many people have high score
    int winner_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == high_score)
        {
            winner_count++;
        }
    }

    // populate array with winners
    int winner_index = 0;
    candidate winners[winner_count];
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == high_score)
        {
            winners[winner_index] = candidates[i];
            winner_index++;
        }
    }

    // print winners
    for (int i = 0; i < winner_count; i++)
    {
        printf("%s\n", winners[i].name);
    }
}
