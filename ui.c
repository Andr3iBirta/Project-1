#include <string.h>
#include "structures.h"

struct Transaction ui_record_transaction() {
    /**
    Function that reads the day, month, year, description, amount and type
    of a transaction
    */
    struct Transaction transaction;
    printf("Enter the date(dd/mm/yyyy): ");
    scanf("%d/%d/%d", &transaction.date.day, &transaction.date.month, &transaction.date.year);

    printf("Enter the description: ");
    while(getchar() != '\n'); ///clears the buffer
    fgets(transaction.description, 251, stdin); ///reads a multi-word string
    ///deletes the 'endline' character from the end of the string
    if(transaction.description[strlen(transaction.description) - 1] == '\n')
        transaction.description[strlen(transaction.description) - 1] = '\0';

    printf("Enter the amount: ");
    if(scanf("%f", &transaction.amount) != 1)
        transaction.amount = -1; ///if a non-float input is entered, it is marked as invalid

    printf("Enter the type: ");
    scanf("%s", transaction.type);
    return transaction;
}

struct Date ui_data_report(char* type) {
    /**
    Function that reads a date of the specified type (start or end)
    */
    struct Date date;
    if(strcmp(type, "start") == 0 || strcmp(type, "end") == 0)
    {
        printf("\nEnter the %s date: ", type);
        scanf("%d/%d/%d", &date.day, &date.month, &date.year);
    }
    else
        printf("\nUnknown type.\n");
    return date;
}

void main_menu() {
    printf("    +-------------------+\n    | Budget calculator |\n    +-------------------+\n");
    printf(" 1 - Record new transaction\n");
    printf(" 2 - Print transaction history\n");
    printf(" 3 - Calculate account balance\n");
    printf(" 4 - Data report\n");
    printf(" 5 - Load data\n");
    printf(" 6 - Save data\n");
    printf(" 7 - Exit the application\n");
}

void run_menu() {
    ///array that will contain the transactions
    struct Transaction trn[1025];
    ///number of transactions recorded and user command
    int counter = 0, cmd;
    ///this is where the transactions are saved between sessions
    char *filename = "report.txt";
    ///an infinite loop keeps displaying the menu
    while(1) {
        main_menu();
        printf("\nEnter a command: ");
        scanf("%d", &cmd);
        switch(cmd) {
            case 1:
            {
                struct Transaction transaction = ui_record_transaction();
                record_transaction(trn, transaction, &counter);
                break;
            }
            case 2:
            {
                display_transactions(trn, counter);
                break;
            }
            case 3:
            {
                printf("\nThe account balance stands at: %.2f$\n", calculate_balance(trn, counter));
                break;
            }
            case 4:
            {
                struct Date start = ui_data_report("start");
                struct Date end = ui_data_report("end");
                if(time_period_validation(start, end))
                    data_report(trn, counter, start, end);
                else
                    printf("\nInvalid data.\n");
                break;
            }
            case 5:
            {
                load_data(trn, &counter, filename);
                break;
            }
            case 6:
            {
                save_data(trn, counter, filename);
                break;
            }
            case 7:
                break;
            default:
                printf("\nInvalid command!\n");
        }
        ///exits the menu
        if(cmd == 7)
        {
            printf("\nExit successful.\n");
            break;
        }
        ///clears the buffer
        while(getchar() != '\n');
        ///clears the screen so the menu runs smoothly
        getchar();
        system("cls");
    }
}
