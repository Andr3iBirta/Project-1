#include <string.h>
#include "structures.h"

_Bool transaction_validation(struct Transaction transaction) {
    /**
    Function that checks if all information about 'transaction' is valid
    returns '0' if False and '1' if True
    */
    if(transaction.date.day < 1 || transaction.date.day > 31)
        return 0;
    if(transaction.date.month < 1 || transaction.date.month > 12)
        return 0;
    if(transaction.date.year < 1900)
        return 0;
    if(transaction.amount < 0)
        return 0;
    if(strcmp(transaction.type, "income") && strcmp(transaction.type, "expense"))
        return 0;
    return 1;
}

_Bool in_time_period(struct Date date, struct Date start, struct Date end) {
    /**
    Function that checks if 'date' happens after 'start' and before 'end'
    returns '0' if False and '1' if True
    date = structure that represents a valid date
    start and end = structures that represents valid dates and 'start' is before 'end'
    */
    if(date.year < start.year || date.year > end.year)
        return 0;
    if(date.year == start.year)
    {
        if(date.month < start.month)
            return 0;
        if(date.month == start.month)
            if(date.day < start.day)
                return 0;
    }
    if(date.year == end.year)
    {
        if(date.month > end.month)
            return 0;
        if(date.month == end.month)
            if(date.day > end.day)
                return 0;
    }
    return 1;
}

_Bool time_period_validation(struct Date start, struct Date end) {
    /**
    Function that checks if 'start' and 'end' are valid dates and 'start' is before 'end'
    returns '0' if False and '1' if True
    */
    if(start.day < 1 || start.day > 31)
        return 0;
    if(start.month < 1 || start.month > 12)
        return 0;
    if(start.year < 1900)
        return 0;
    if(end.day < 1 || end.day > 31)
        return 0;
    if(end.month < 1 || end.month > 12)
        return 0;
    if(end.year < 1900)
        return 0;
    if(start.year > end.year)
        return 0;
    if(start.year == end.year)
    {
        if(start.month > end.month)
            return 0;
        if(start.month == end.month)
            if(start.day > end.day)
                return 0;
    }
    return 1;
}
