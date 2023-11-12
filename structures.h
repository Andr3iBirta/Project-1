#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

struct Date {
    int day, month, year;
}date;

struct Transaction {
    struct Date date;
    char description[251], type[10];
    float amount;
};

#endif // STRUCTURES_H_INCLUDED
