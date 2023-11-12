#include "structures.h"
#include "validation.c"

///getter functions enable easier access to information about a transaction
struct Date get_date(struct Transaction *transactions, int index) {
    return transactions[index].date;
}
char* get_description(struct Transaction *transactions, int index) {
    return transactions[index].description;
}
float get_amount(struct Transaction *transactions, int index) {
    return transactions[index].amount;
}
char* get_type(struct Transaction *transactions, int index) {
    return transactions[index].type;
}

///setter functions enable modifying information about a transaction
void set_date(struct Transaction *transactions, int index, int new_day, int new_month, int new_year) {
    transactions[index].date.day = new_day;
    transactions[index].date.month = new_month;
    transactions[index].date.year = new_year;
}
void set_description(struct Transaction *transactions, int index, char* new_description) {
    strcpy(transactions[index].description , new_description);
}
void set_amount(struct Transaction *transactions, int index, float new_amount) {
    transactions[index].amount = new_amount;
}
void set_type(struct Transaction *transactions, int index, char* new_type) {
    strcpy(transactions[index].type, new_type);
}

void record_transaction(struct Transaction *transactions, struct Transaction new_transaction, int *counter) {
    /**
    Function that validates a new transaction and attempts to add it to the array
    *transactions = variable that points to an array of transactions
    new_transaction = transaction
    counter = integer that represents the current number of recorded transactions
    */
    if(transaction_validation(new_transaction))
    {
        (*counter)++;
        transactions[(*counter)] = new_transaction;
        printf("\nTransaction recorded successfully.\n");
    }
    else
        printf("\nInvalid data!\n\nThe transaction could not be recorded.\n");
}

void save_data(struct Transaction *transactions, int counter, char *filename) {
    /**
    Function that attempts to save information about every transaction
    in 'transactions', in 'filename'
    *transactions = variable that points to an array of transactions
    counter = integer that represents the current number of recorded transactions
    *filename = string that represents the name of the file currently in use
    */
    ///opens the file for the purpose of writing
    FILE *file = fopen(filename, "w");

    ///placeholders that ensure ease of access and code-readability
    int day, month, year;
    float amount;
    char description[251], type[10];

    ///cycles through every transaction
    for(int i = 1; i <= counter; i++) {
        day = get_date(transactions, i).day;
        month = get_date(transactions, i).month;
        year = get_date(transactions, i).year;
        amount = get_amount(transactions, i);
        strcpy(description, get_description(transactions, i));
        strcpy(type, get_type(transactions, i));

        ///saves a new transaction in the file
        fprintf(file, "%d/%d/%d %s\n %s %.2f\n", day, month, year, description, type, amount);
    }
    ///checks if any transactions have been recorded
    if(!counter)
        printf("\nNo data to be saved.\n");
    else
        printf("\nData saved successfully.\n");
    ///closes the file for further use
    fclose(file);
}

void load_data(struct Transaction *transactions, int *counter, char *filename) {
    /**
    Function that attempts to load information from 'filename' about
    every transaction in 'transactions'
    *transactions = variable that points to an array of transactions
    counter = integer that represents the current number of recorded transactions
    *filename = string that represents the name of the file currently in use
    */
    ///opens the file for the purpose of reading
    FILE *file = fopen(filename, "r");

    ///placeholders that ensure ease of access and code-readability
    int day, month, year;
    float amount;
    char description[251], type[10];
    float old_counter = (*counter);

    ///cycles through every transaction
    while (fscanf(file, "%d/%d/%d %[^\n] %s %f", &day, &month, &year, description, type, &amount) == 6) {
        (*counter)++;
        set_date(transactions, (*counter), day, month, year);
        set_description(transactions, (*counter), description);
        set_type(transactions, (*counter), type);
        set_amount(transactions, (*counter), amount);
    }
    ///checks if any transactions have been saved
    if((*counter) == old_counter)
        printf("\nCannot load from an empty file.\n");
    else
        printf("\nData loaded successfully.\n");
    ///closes the file for further use
    fclose(file);
}

