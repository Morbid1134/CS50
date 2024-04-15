#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool if_card_length(long card, long length);
int n_digits_at_i(long card, long n, long index);
bool validate_card(long card, long length);

int main(void)
{
    long cardNumber = get_long("Check Card Validity: ");

    // If card length is 13 and First digit is 4, VISA
    if (if_card_length(cardNumber, 13) && n_digits_at_i(cardNumber, 1, 13) == 4 &&
        validate_card(cardNumber, 13))
    {
        printf("VISA\n");
    }
    // Else If card length is 15 and First 2 digits are 34 and 37, American Express
    else if (if_card_length(cardNumber, 15) &&
             (n_digits_at_i(cardNumber, 2, 15) == 34 || n_digits_at_i(cardNumber, 2, 15) == 37) &&
             validate_card(cardNumber, 16))
    {
        printf("AMEX\n");
    }

    // Else If card length is 16 and First 2 digits are 51–55, MasterCard
    else if (if_card_length(cardNumber, 16) &&
             (n_digits_at_i(cardNumber, 2, 16) == 51 || n_digits_at_i(cardNumber, 2, 15) == 52 ||
              n_digits_at_i(cardNumber, 2, 15) == 53 || n_digits_at_i(cardNumber, 2, 15) == 54 ||
              n_digits_at_i(cardNumber, 2, 15) == 55) &&
             validate_card(cardNumber, 16))
    {
        printf("MASTERCARD\n");
    }
    // If card length is 16 and First digit is 4, VISA
    else if (if_card_length(cardNumber, 16) && n_digits_at_i(cardNumber, 1, 16) == 4 &&
             validate_card(cardNumber, 16))
    {
        printf("VISA\n");
    }
    // Else, card is INVALID
    else
    {
        printf("INVALID\n");
    }
}

bool if_card_length(long card, long length)
{
    return (card > pow(10, (length - 1)) && card < pow(10, length));
}

int n_digits_at_i(long card, long n, long index)
{
    return ((int) (card / pow(10, index - (1 * n))) % (int) pow(10, n));
}

bool validate_card(long card, long length)
{
    long evenSum = 0;
    long oddSum = 0;
    for (int i = 1; i < (length + 1); i++)
    {
        // If this is odd, add it to oddSum
        int current_n = card - (floor(card / 10) * 10);

        if ((i % 2) != 0)
        {
            oddSum += current_n;
        }
        // Else number is even
        else
        {
            // multiple number by 2
            long temp = current_n * 2;

            // add the number in the ones place to evenSum
            evenSum += temp - (floor(temp / 10) * 10);

            // add number in tens place to evenSum
            evenSum += floor(temp / 10);
        }
        card = floor(card / 10);
    }
    // Return true (successful validation) if sum of evenSum and oddSum can be cleanly divide by 10
    if (((oddSum + evenSum) % 10) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
