#include <cs50.h>
#include <stdio.h>

// Function calls
int card_length(long card_no);
void checker(long ccno, int length);
bool checksum(long ccno);

// Main
int main(void)
{
    long ccno = get_long("Enter credit card number: ");
    int length = card_length(ccno);
    while (length != 13 && length != 15 && length != 16)
    {
        ccno = get_long("Please enter only AMEX, VISA or MASTERCARD: ");
        length = card_length(ccno);
    }
    if (checksum(ccno))
    {
        checker(ccno, length);
    }
}

// Checksum function definiton
bool checksum(long ccno)
{
    long c = 100;
    long k;
    int s1 = 0;
    int s2 = 0;
    do
    {
        k = ((ccno % c - ccno % (c / 10)) / (c / 10)) * 2;
        s1 += k % 10 + (k % 100 - k % 10) / 10;
        c *= 100;
    }
    while ((ccno * 10) / c > 0);

    c = 10;
    do
    {
        k = (ccno % c - ccno % (c / 10)) / (c / 10);
        s2 += k;
        c *= 100;
    }
    while ((ccno * 10) / c > 0);

    int check_sum = s1 + s2;
    if (check_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        printf("INVALID\n");
        return false;
    }
}

// Result function definiton
void checker(long ccno, int length)
{
    long r = ((ccno - ccno % 100000000000000) / 100000000000000);
    if (length == 15 && (((ccno - ccno % 10000000000000) / 10000000000000) == 34 ||
                         ((ccno - ccno % 10000000000000) / 10000000000000) == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (r == 51 || r == 52 || r == 53 || 5 == 54 || r == 55))
    {
        printf("MASTERCARD\n");
    }
    else if (length == 13 && ((ccno - ccno % 1000000000000) / 1000000000000) == 4)
    {
        printf("VISA\n");
    }
    else if (length == 16 && ((ccno - ccno % 1000000000000000) / 1000000000000000) == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Length of card definition
int card_length(long card_no)
{
    int c = 0;
    long ccno_p = card_no;
    long p;
    do
    {
        p = ccno_p / 10;
        ccno_p = p;
        c++;
    }
    while (p > 0);
    return c;
}
