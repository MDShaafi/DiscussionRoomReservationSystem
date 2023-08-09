//Discussion Room Reservation System
// - The discussion rooms will be available for booking from 8am to 7pm.
// - Each slot is one hour.
// - Students can manage their own booking.
// - Each student can book a maximum of 3 continuous slots in a day.

#include "ICP_HEADER.h"

void callMain();

int main() {
    printf("\n\n\n\n");
    //define variables
    char currentUser[20];
    int choice =0;
    int error=0;

    char username[20];
    char password[20];
    char fileName[20];

    int failSafe=9;
    int try=0;

    //start system
    initialise();
    printf("Press Enter to start");
    getchar();
    getchar();

    //login
    printf("--------------------------------------------\n");
    printf("|                LOGIN                     |\n");
    printf("--------------------------------------------\n");

    while(1)
    {
        strcpy(username," ");
        strcpy(password," ");
        printf("Enter username: ");
        scanf("%s", &username);
        printf("Enter password: ");
        scanf("%s", &password);

        error=0;
        error =authenticate(username, password);

        try++;
        if (try==failSafe) {
            printf("Too many tries");
            return -9;
        }

        if (error==0) {
            printf("Login successful!\n");            
            break;
        } else if(error==-1) {
            printf("Invalid username or password.\n");
            continue;
        } else {
            printf("Error Exit");
            return -1;
        }
        
    }
    //strcpy(currentUser,username);
    strcpy(fileName,"");

    //filleName stored
    strcpy(fileName,username);
    strcat(fileName, ".txt"); //add .txt to username to acess file

    //importOldData
    error=0;
    error = readFromFile(fileName,username);
    if (error!=0)
    {
        printf("Error reading file: %d",error);
        return -1;
    }
/*
    if (strcmp(fileName,username + ".txt") != 0) {
        strcat(fileName, ".txt");
    }
*/
    
    try=0;
    intro();
    printf("Date of booking: 01-08-2023\n");
    while (choice!=4)
    {
        //printf("File name: %s Username: %s\n",fileName,username);
        choice = menu();
        switch (choice)
        {
        case 1:
            viewAvailableSlot();
            
            getchar();
            
            break;
        
        case 2:
            bookNewSlot(username);
            
            break;

        case 3:
            editBookedSlot(username);
            
            getchar();
            
            break;

        case 4:
            storeToFile(fileName,username);
            return -1;
            break;

        case 5: //logout
            storeToFile(fileName,username);
            callMain();
            break;

        default:
            printf("Invalid input...");
            try++;
            if (try==failSafe) {
                printf("Too many tries");
                return -9;
            }
            break;
        }
        printf("Press Enter to proceed");
        getchar();
        printf("\n\n\n\n");
        //printf("File name: %s Username: %s\n",fileName,username);
    }
    printf("\n\n\n\n");
    
}

void callMain() {
    main();
}
