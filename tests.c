#include <string.h>
#include <math.h>
#include "structures.h"
#include "ui.c"

void test_transaction_validation() {
    printf("Testing 'transaction_validation':\n");
    struct Transaction test;
    ///Test1: valid data
    test.date.day = 18;
    test.date.month = 10;
    test.date.year = 2008;
    strcpy(test.description, "test case 1");
    test.amount = 16.59;
    strcpy(test.type, "income");
    if(transaction_validation(test))
        printf("\tTest case 1 passed.\n");
    else
        printf("\tTest case 1 failed!\n");
    ///Test2: invalid date
    test.date.day = 32;
    test.date.month = 15;
    test.date.year = 1750;
    strcpy(test.description, "test case 2");
    test.amount = 16.59;
    strcpy(test.type, "income");
    if(!transaction_validation(test))
        printf("\tTest case 2 passed.\n");
    else
        printf("\tTest case 2 failed!\n");
    ///Test3: invalid amount
    test.date.day = 18;
    test.date.month = 10;
    test.date.year = 2008;
    strcpy(test.description, "test case 3");
    test.amount = -117;
    strcpy(test.type, "income");
    if(!transaction_validation(test))
        printf("\tTest case 3 passed.\n");
    else
        printf("\tTest case 3 failed!\n");
    ///Test4: invalid type
    test.date.day = 18;
    test.date.month = 10;
    test.date.year = 2008;
    strcpy(test.description, "test case 4");
    test.amount = 16.59;
    strcpy(test.type, "ExPeNsE");
    if(!transaction_validation(test))
        printf("\tTest case 4 passed.\n");
    else
        printf("\tTest case 4 failed!\n");
}

void test_record_transaction() {
    printf("Testing 'record_transaction':\n");
    struct Transaction Test[10];
    struct Transaction test;
    int counter = 0;
    ///Test1: valid data
    test.date.day = 18;
    test.date.month = 10;
    test.date.year = 2008;
    strcpy(test.description, "test case 1");
    test.amount = 16.59;
    strcpy(test.type, "income");
    record_transaction(Test, test, &counter);
    if(counter == 1 && Test[1].date.day == 18 && Test[1].date.month == 10 &&
        Test[1].date.year == 2008 && strcmp(Test[1].description, "test case 1") == 0 &&
        abs(Test[1].amount - 16.59) < 0.1 && strcmp(Test[1].type, "income") == 0)
        printf("\tTest case 1 passed.\n");
    else
        printf("\tTest case 1 failed!\n");
    ///Test2: invalid data
    test.date.day = 32;
    test.date.month = 15;
    test.date.year = 1750;
    strcpy(test.description, "test case 2");
    test.amount = 16.59;
    strcpy(test.type, "income");
    record_transaction(Test, test, &counter);
    if(counter == 1)
        printf("\tTest case 2 passed.\n");
    else
        printf("\tTest case 2 failed!\n");
}

void test_calculate_balance() {
    printf("Testing 'calculate_balance':\n");
    struct Transaction Test[10];
    struct Transaction test;
    int counter = 0;
    ///Test1: empty struct
    if(abs(calculate_balance(Test, counter) - 0) < 0.1)
        printf("\tTest case 1 passed.\n");
    else
        printf("\tTest case 1 failed!\n");
    ///Test2: 3 transactions
    test.date.day = 18;
    test.date.month = 10;
    test.date.year = 2008;
    strcpy(test.description, "test case 2");
    test.amount = 16.59;
    strcpy(test.type, "income");
    record_transaction(Test, test, &counter);

    test.date.day = 18;
    test.date.month = 10;
    test.date.year = 2008;
    strcpy(test.description, "test case 2");
    test.amount = 18.98;
    strcpy(test.type, "expense");
    record_transaction(Test, test, &counter);

    test.date.day = 18;
    test.date.month = 10;
    test.date.year = 2008;
    strcpy(test.description, "test case 2");
    test.amount = 14.76;
    strcpy(test.type, "income");
    record_transaction(Test, test, &counter);

    if(abs(calculate_balance(Test, counter) - 12.37) < 0.1)
        printf("\tTest case 2 passed.\n");
    else
        printf("\tTest case 2 failed!\n");
}

void test_save_load_data() {
    printf("Testing 'save_data' and 'load_data':\n");
    struct Transaction Test[10];
    struct Transaction test;
    int counter = 0;

    test.date.day = 18;
    test.date.month = 10;
    test.date.year = 2008;
    strcpy(test.description, "test case 1");
    test.amount = 16.59;
    strcpy(test.type, "income");
    record_transaction(Test, test, &counter);

    save_data(Test, counter, "report.txt");
    load_data(Test, &counter, "report.txt");

    if(counter == 2 && Test[2].date.day == 18 && Test[2].date.month == 10 &&
        Test[2].date.year == 2008 && strcmp(Test[2].description, "test case 1") == 0 &&
        abs(Test[1].amount - 16.59) < 0.1 && strcmp(Test[1].type, "income") == 0)
        printf("\tTest case 1 passed.\n");
    else
        printf("\tTest case 1 failed!\n");
}

void run_tests() {
    test_transaction_validation();
    test_record_transaction();
    test_calculate_balance();
    test_save_load_data();
}
