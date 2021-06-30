#include<stdlib.h>
#include<stdio.h>
#define filename "file.dat"
#define replicaname "replica.dat"
#define design1 printf("\n====================================================================================\n");
#define clear system("cls");
#define invalid printf("Invalid Input!\n");

FILE *original, *replica;

struct record{
   char employeeNumber[15];
   char employeeName[15];
   char statusCode;
   int hoursWorked;
   float basicPay;
   float basicRate;
   float deductions;
};

struct record list;
void headView();
void addRecord();
void viewRecord();
void updateRecord();
void deleteRecord();

int main(){
    int choice;
        clear
    while(1){
        original = fopen(filename, "r");
        while(1){
            printf("\t\tCompany ABC Record System"); design1
            printf("Main Menu:\n1. Add Record\n2. View Record\n3. Update Datas\n4. Delete Record\n5. Exit"); design1
            printf("Select Process: ");
            scanf("%d", &choice);
            design1
            if(original==NULL && choice > 1 && choice < 5){
                clear printf("There is no record in the system. Add some record first to proceed.\n\n");
                continue;
            }
            if(choice > 0 && choice <= 5)break;
            clear invalid
        }
        fclose(original);
        switch(choice){
            case 1:
                // addRecord();
                break;
            case 2:
                headView();
                // viewRecord();
                break;
            case 3:
                // updateRecord();
                break;
            case 4:
                // deleteRecord();
                break;
            case 5:
                clear design1 printf("Thank you for using the Record System!\nYour session has now ended."); design1
                return 0;
        }
        clear
    }

    return 0;
}

void headView(){
    clear design1
    printf("\t\t\tABC Company\n\t\t\tMakati City\n\n\t\t\tPayroll");
    printf("\nEmployee No.  Employee Name  Status  Basic Salary  Overtime Pay  Deductions  Net Pay\n");
}
