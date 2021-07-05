#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#define filename "file.dat"
#define replicaname "replica.dat"
#define design printf("\n=====================================================================================\n");
#define clear system("cls");
#define invalid printf("Invalid Input!\n");
#define anykey printf("\n\nPress Any key to Continue...");getch();

FILE *original, *replica;

typedef struct record{
   char employeeNumber[15];
   char employeeName[15];
   char statusCode[10];
   int hoursWorked;
   float basicPay;
   float basicRate;
   float deductions;
} record;

int count, selectLine;
void addRecord();
int answer();
int inputDealer(int process);
int digitErrorDealer(char *receive);
void viewRecord();
void headView();
float overtimeDeal(float number);
void updateRecord();
void updateData();
void updateInput();
void deleteRecord();
record list;

int main(){
    char choice;
    clear
    while(1){
        original = fopen(filename, "rb");
        while(1){
            clear
            printf("\t\tCompany ABC Record System"); design
            printf("Main Menu:\n1. Add Record\n2. View Record\n3. Update Datas\n4. Delete Record\n5. Exit"); design
            printf("Select Process: ");
            scanf(" %c", &choice);
            design
            if(original == NULL && (choice <= '1' || choice >= '5')) break;
            if(original != NULL){
                fseek(original, 0, SEEK_END);
                if(ftell(original)!=0) break;
                if(ftell(original)==0 && (choice <= '1' || choice >= '5'))break;
            }
            clear
            printf("There is no recorded list.\nAdd Record first!\n\n");
            anykey
        }
        fclose(original);
        switch(choice){
            case '1':
                addRecord();
                break;
            case '2':
                headView();
                viewRecord();
                break;
            case '3':
                updateRecord();
                break;
            case '4':
                deleteRecord();
                break;
            case '5':
                clear design printf("Thank you for using the Record System!\nYour session has now ended."); design
                return 0;
            default:
                clear invalid anykey
        }
    }
    return 0;
}

void addRecord(){
    do{
        //Setting Datas:
        for(int i = 0; i < 8; i++) 
            while(1){
                system("cls");
                printf("Add Record"); design
                if(inputDealer(i)) break;
            }     
        original = fopen(filename, "ab");
        fwrite(&list, sizeof(record), 1, original);
        fclose(original);
        clear design
        printf("Add Another Process?");
    }while(answer());
}

int answer(){
    char ans;
    while(1){
        printf("\nRepeat the Process? Y/N: ");
        scanf(" %c", &ans);
        if(ans == 'y' || ans == 'n' || ans == 'Y' || ans == 'N') break;
        system("cls");
        printf("Invalid Input!");
    }
    if(ans == 'y' || ans == 'Y') return 1;
    return 0;
}


int inputDealer(int process){
    char receive[15];
    switch(process){
        case 1:
            printf("Employee Number: ");
            for(int i = 0; i < 20; i++){
                list.employeeNumber[i] = getch();
                if(list.employeeNumber[i] == '\b'){
                    list.employeeNumber[0] = '\0';
                    return 0;
                }
                printf("%c", list.employeeNumber[i]);
                if(list.employeeNumber[i] == '\r'){
                    list.employeeNumber[i] = '\0';
                    break;
                }
            }
            if(strlen(list.employeeNumber) <= 15)  return 1;
            printf("\nUp to 15 Characters Only!");
            anykey
            return 0;
        case 2:
            printf("Employee Name: ");
            for(int i = 0; i < 20; i++){
                list.employeeName[i] = getch();
                if(list.employeeName[i] == '\b'){
                    list.employeeName[0] = '\0';
                    return 0;
                }
                printf("%c", list.employeeName[i]);
                if(list.employeeName[i] == '\r'){
                    list.employeeName[i] = '\0';
                    break;
                }
            }
            if(strlen(list.employeeName) <= 15)  return 1;
            printf("\nUp to 15 Characters Only!");
            anykey
            return 0;
        case 3:
            printf("C: Casual\nR: Regular\nStatus Code: ");
            list.statusCode[0] = getch();
            printf("%c", list.statusCode[0]);
            if(list.statusCode[0]=='r' || list.statusCode[0]=='R'){
                strcpy(list.statusCode, "Regular");
                return 1;
            }
            if(list.statusCode[0]=='c' || list.statusCode[0]=='C'){
                strcpy(list.statusCode, "Casual");
                return 1;
            }
            system("cls");
            printf("Invalid Input!\n");
            printf("R and C only!"); 
            anykey
            return 0;
        case 4:
            printf("Hours Worked: ");
            scanf("\n");
            gets(receive);
            if(digitErrorDealer(receive)) list.hoursWorked = (int)strtol(receive, NULL, 10);
            else return 0;
            if(list.hoursWorked > 0 && list.hoursWorked <= 1000) return 1;
            system("cls");
            printf("0 to 1000 Only!"); 
            anykey
            return 0;
        case 5:
            printf("Basic Pay: ");
            scanf("\n");
            gets(receive);
            if(digitErrorDealer(receive)) list.basicPay = (float)strtol(receive, NULL, 10);
            else return 0;
            if(list.basicPay > 0 && list.basicPay <= 1000000) return 1;
            system("cls");
            printf("0 to 1,000,000 Only!"); 
            anykey
            return 0;
        case 6:
            printf("Basic Rate: ");
            scanf("\n");
            gets(receive);
            if(digitErrorDealer(receive)) list.basicRate = (float)strtol(receive, NULL, 10);
            else return 0;
            if(list.basicRate > 0 && list.basicRate <= 1000) return 1;
            system("cls");
            printf("0 to 1,000 Only!"); 
            anykey
            return 0;
        case 7:
            printf("Deductions: ");
            scanf("\n");
            gets(receive);
            if(digitErrorDealer(receive)) list.deductions = (float)strtol(receive, NULL, 10);
            else return 0;
            if(list.deductions > 0 && list.deductions <= 100000) return 1;
            system("cls");
            printf("0 to 1,00,000 Only!"); 
            anykey
    }
}

int digitErrorDealer( char *receive){
    for(int i = 0; i < strlen(receive); i++) 
        if(!isdigit(receive[i])){
            system("cls");
            printf("Not a digit!");
            anykey
            return 0;
        } 
    return 1;
}

void headView(){
    clear design
    printf("\t\t\t\t\tABC Company\n\t\t\t\t\tMakati City\n\n\t\t\t\t\t Payroll"); design
    printf("\nEmployee No.\tEmployee Name\tStatus  Basic Salary  Overtime Pay  Deductions  Net Pay\n\n");
}

void viewRecord(){
    clear
    float overTime;
    headView();
    original = fopen(filename, "rb");
    while(fread(&list, sizeof(record), 1, original) != (int)NULL){
        overTime = overtimeDeal(list.hoursWorked)*(1.5 * list.basicRate);
        printf("%s\t%s\t%s\t%0.2f\t  %0.2f   %0.2f   %0.2f\n", list.employeeNumber, list.employeeName, list.statusCode, list.basicPay, overTime, list.deductions, list.basicPay + overTime - list.deductions);
    }
    fclose(original); design
    anykey
}

float overtimeDeal(float number){
    if(number - 160 < 0) return 0;
    else return number - 160;
}

void updateRecord(){
    system("cls");
    while(1){
        original = fopen(filename, "rb"); design
        count = 0;
        //Process 1: Select Record
        for(int i = 0; fread(&list, sizeof(record), 1, original) != (int)NULL; i++, count++)
            printf("%d. %s\t%s\n",i+1, list.employeeNumber, list.employeeName);
        printf("%d. Exit Process\n\n", count+1);
        fclose(original); design
        printf("Select Record: ");
        scanf("%d", &selectLine);
        if(selectLine == count+1) main();
        if(selectLine > 0 && selectLine <= count) break;
        system("cls");
        printf("Invalid Choice!\n\n");
    }
    updateData();
}

void updateData(){
    int selectedData;
    system("cls");
    while(1){   
        original = fopen(filename, "rb"); design
        for(int i = 0; fread(&list, sizeof(record), 1, original) != (int)NULL; i++)
            if(i == selectLine-1){
                printf("1. Employee Number:\t%s\n2. Employee Name:\t%s\n3. Status Code:\t\t%s\n4. Hours Worked:\t%d\n5. Basic Pay:\t\t\t%0.2f\n6. Basic Rate:\t\t\t%0.2f\n7. Deductions:\t\t\t%0.2f\n8. Exit Process\n", list.employeeNumber, list.employeeName, list.statusCode, list.hoursWorked, list.basicPay, list.basicRate, list.deductions);
                break;
            }
        fclose(original); design
        printf("Choose Data to Update: ");
        scanf("%d", &selectedData);
        if(selectedData == 8) updateRecord();
        if(selectedData > 0 && selectedData < 8) break;
        system("cls");
        printf("Invalid Choice!\n\n");
    }
    updateInput(selectedData);
}

void updateInput(int selectedData){
    original = fopen(filename, "rb");
    replica = fopen(replicaname, "wb");
    for(int i = 0; fread(&list, sizeof(record), 1, original) != (int)NULL; i++){
        if(i == selectLine-1){
            switch(selectedData){
                case 1:
                    do{
                        system("cls");
                        printf("Current Data\n Employee Number: %s\n", list.employeeNumber);  design
                    }while(!inputDealer(selectedData));
                    break;
                case 2:
                    do{
                        system("cls");
                        printf("Current Data\n Employee Name: %s\n", list.employeeName);  design
                    }while(!inputDealer(selectedData));
                    break;
                case 3:
                    do{
                        system("cls");
                        printf("Current Data\n Status Code: %s\n", list.statusCode); design
                    }while(!inputDealer(selectedData));
                    break;
                case 4:
                    do{
                        system("cls");
                        printf("Current Data\n Hours Worked: %d\n", list.hoursWorked); design
                    }while(!inputDealer(selectedData));
                    break;
                case 5:
                    do{
                        system("cls");
                        printf("Current Data\n Basic Pay: %0.2f\n", list.basicPay); design
                    }while(!inputDealer(selectedData));
                    break;
                case 6:
                    do{
                        system("cls");
                        printf("Current Data\n Basic Rate: %0.2f\n", list.basicRate); design
                    }while(!inputDealer(selectedData));
                    break;
                case 7:
                    do{
                        system("cls");
                        printf("Current Data\nDeductions: %0.2f\n", list.deductions); design
                    }while(!inputDealer(selectedData));
            }
            fwrite(&list, sizeof(record), 1, replica);
            continue;
        }
        fwrite(&list, sizeof(record), 1, replica);
    }
    fclose(replica);
    fclose(original);
    //Deletes the existing outdated file.dat
    system("cls");
    if(remove(filename)){
        perror("File Deletion Failed!\nSuggestion: Open the Editor in Admin\n");
        anykey
    } 
    //Rename the Replica to Original
    if(rename(replicaname, filename)){
        system("cls");
        perror("File Rename Failed!\nCopying the content of Replica to the Original Instead...\n");
        anykey
        original = fopen(filename, "wb");
        replica = fopen(replicaname, "rb");
        for(int i = 0; fread(&list, sizeof(record), 1, replica) != (int)NULL; i++)
            fwrite(&list, sizeof(record), 1, original);
        fclose(replica);
        fclose(original);
    } 
    updateData();
}


void deleteRecord(){
    system("cls");
    while(1){
        original = fopen(filename, "rb"); design
        count = 0;
        //Process 1: Select Record
        printf("Here are the Available Records: \n");
        for(int i = 0; fread(&list, sizeof(record), 1, original) != (int)NULL; i++, count++)
            printf("%d. %s\t%s\n", i+1, list.employeeNumber, list.employeeName);
        printf("%d. Exit Process\n\n", count+1);
        fclose(original); design
        printf("Select Record to Delete: ");
        scanf("%d", &selectLine);
        if(selectLine == count+1) return;
        if(selectLine > 0 && selectLine <= count) break;
        system("cls");
        printf("Invalid Choice!\n\n");
    }
    system("cls");
    replica = fopen(replicaname, "wb");
    original = fopen(filename, "rb");
    for(int i = 0; fread(&list, sizeof(record), 1, original) != (int)NULL; i++){
        if(i == selectLine-1) continue;
        fwrite(&list, sizeof(record), 1, replica);
    }
    fclose(original);
    fclose(replica);
    //Deletes the existing outdated file.dat
    if(remove(filename)){
        system("cls");
        perror("File Deletion Failed!\nSuggestion: Open the Editor in Admin\n");
        anykey
    } 
    //Rename the Replica to Original
    if(rename(replicaname, filename)){
        system("cls");
        perror("File Rename Failed!\nCopying the content of Replica to the Original Instead...\n");
        anykey
        original = fopen(filename, "wb");
        replica = fopen(replicaname, "rb");
        //Copy Every Lines in Replica to Original
        for(int i = 0; fread(&list, sizeof(record), 1, replica) != (int)NULL; i++)
            fwrite(&list, sizeof(record), 1, original);
        fclose(replica);
        fclose(original);
    }
    system("cls");
    //Process 2: Show The Updated Datas
    original = fopen(filename, "rb"); design
    printf("Here's the updated record: \n");
    //Print Every Line in Original File
    for(int i = 0; fread(&list, sizeof(record), 1, original) != (int)NULL; i++)
        printf(" %d. %s\t%s\n", i+1, list.employeeNumber, list.employeeName);
    anykey
    fclose(original); design
    deleteRecord();
}