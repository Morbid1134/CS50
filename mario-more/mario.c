#include <cs50.h>
#include <stdio.h>

void print_s_n_times(string s, int n);

int main(void)
{
    int h = 0;
    do
    {
        h = get_int("Height of Pyramid: ");
    }
    while (h < 1 || h > 8);

    // Iterate over each row (r)
    for (int r = 1; r != (h + 1); r++)
    {
        print_s_n_times(" ", (h - r));
        print_s_n_times("#", r);
        printf("  ");
        print_s_n_times("#", r);
        printf("\n");
    }
}

void print_s_n_times(string s, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", s);
    }
}
