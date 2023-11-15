#include "structures.h"
#include "infrastructure.c"

void display_transactions(struct Transaction *transactions, int counter) {
    /**
    Functions that prints information about every transaction in 'transactions'
    in descending order
    */
    if(!counter) {
        printf("\nNo transactions have been recorded.\n");
        return;
    }
    printf("\n");
    for(int i = counter; i >= 1; i--)
    {
        printf("%2d)type: %s\n   date: %02d/%02d/%04d\n   description: %s\n   amount: %.2f$\n\n",
        counter - i + 1, get_type(transactions, i), get_date(transactions, i).day,
        get_date(transactions, i).month, get_date(transactions, i).year,
        get_description(transactions, i), get_amount(transactions, i));
    }
}

float calculate_balance(struct Transaction *transactions, int counter) {
    /**
    Functions that calculates and returns the current balance:
    the amount of every transaction is either added or subtracted from the total,
    depending on its type ('income' or 'expense')
    */
    float balance = 0;
    for(int i = 1; i <= counter; i++)
        if(strcmp(get_type(transactions, i), "income") == 0)
            balance += get_amount(transactions, i);
        else
            balance -= get_amount(transactions, i);
    return balance;
}

void data_report(struct Transaction *transactions, int counter, struct Date start, struct Date end) {
    /**
    Function that prints information about every transaction in 'transactions', sorted by type,
    transactions that happened in the 'start'-'end' time period
    */
    if(!counter) {
        printf("\nNo transactions have been recorded.\n");
        return;
    }
    ///flag to check if no transactions have been found
    _Bool found = 0;
    ///stores the indexes
    int k = 0;
    ///total money gained or spent
    float total = 0;
    
    printf("\n~income~\n\n");
    for(int i = counter; i >= 1; i--)
        if(in_time_period(get_date(transactions, i), start, end)) {
            found = 1;
            if(strcmp(get_type(transactions, i), "income") == 0)
            {
                printf("%2d)date: %02d/%02d/%04d\n   description: %s\n   amount: %.2f$\n",
                ++k, get_date(transactions, i).day, get_date(transactions, i).month,
                get_date(transactions, i).year, get_description(transactions, i),
                get_amount(transactions, i));

                total += get_amount(transactions, i);
            }
        }
    if(k)
        printf("\nTotal: %0.2f$\n", total);

    total = 0;
    k = 0;
    printf("\n~expenses~\n\n");
    for(int i = counter; i >= 1; i--)
        if(in_time_period(get_date(transactions, i), start, end)) {
            found = 1;
            if(strcmp(get_type(transactions, i), "expense") == 0)
            {
                printf("%2d)date: %02d/%02d/%04d\n   description: %s\n   amount: %.2f$\n",
                ++k, get_date(transactions, i).day, get_date(transactions, i).month,
                get_date(transactions, i).year, get_description(transactions, i),
                get_amount(transactions, i));

                total += get_amount(transactions, i);
            }
        }
    if(k)
        printf("\nTotal: %0.2f$\n", total);

    if(!found)
        printf("\nNo transactions have been found.\n");
}
