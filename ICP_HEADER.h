#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char studentID[8];
} Reservation;

typedef struct {
    int roomNumber;
    int slotNumber;
    Reservation* currentReservation; // pointer to the current reservation for this room
} Room;

//Room room[8][11]; //Made an array of Room a global variable
Room rooms[8][11]; //Made an array of booked Room a global variable

//int createReservation(char studentID[], int roomNumber, int slotNumber); //completed
//int createReservationBookedRoom(char studentID[], int roomNumber, int slotNumber); //completed
Room* findRoom(int roomNumer, int slotNumber); //why does this exist ??
void initialise(); //completed
//int bookedRoomInitialise(); //why does this exist ??
void intro(); //completed
int menu(); //completed
int viewAvailableSlot(); //completed
int bookNewSlot(char studentID[]); //completed
int editBookedSlot(char studentID[]); //completed
int editBookedSlotView(char studentID[]); //completed
int editBookedSlotEdit(char studentID[]); //working
int editBookedSlotCancel(char studentID[]); //completed
//Reservation* createReservation(char ID[]);//completed
int createReservation(char ID[], int roomNumber, int slotNumber);
int authenticate(char username[], char password[]);
int readFromFile(char fileName[],char username[]);
int checkOrCreateFile(char fileName[],char username[]);
int storeToFile(char fileName[],char username[]);
int buildLogin();
int StoreBooking(char studentID[]);


void intro()  //completed
{
    printf("--------------------------------------------\n");
    printf("|           Welcome to APU                 |\n");
    printf("|   Discussion Room Reservation System     |\n");
    printf("|------------------------------------------|\n");
}

int menu()  //completed
{
    printf("--------------------------------------------\n");
    printf("|                 MENU                     |\n");
    printf("|------------------------------------------|\n");
    printf("| 1) View available slot                   |\n");
    printf("| 2) Book new slot                         |\n");
    printf("| 3) View / Edit / Cancel Existing Booking |\n");
    printf("| 4) EXIT                                  |\n");
    printf("| 5) Logout                                |\n");
    printf("|------------------------------------------|\n");
    printf("|      ENTER OPTION:                       |\n");
    printf("--------------------------------------------\n\n");

    int choice = 0;
    scanf("%d",&choice);

    if (choice==0)
    {
        printf("Error: Choice not stored!!");
        return -1; //Choice not stored
    }
    
    

    return choice;
}

int viewAvailableSlot() //choice 1 //completed
{
    printf("--------------------------------------------\n");
    printf("|            AVAILABLE SLOTS               |\n");
    printf("--------------------------------------------\n");

    for (int i = 0; i < 8; i++)
    {
        printf("--------------------------------------------\n");
        printf("|                ROOM %d                    |\n",(i+1));
        printf("--------------------------------------------\n");
        for (int j = 0; j < 11; j++)
        {
            if (rooms[i][j].currentReservation==NULL)
            {
                printf("  Slot %d: %d:00 - %d:00                    \n",(j+1),(j+8),(j+9));
            } 
        }
    }
    printf("--------------------------------------------\n\n");
    return 0;
}

int bookNewSlot(char studentID[]) //choice 2 //completed
{
    int localroomNumber =0;
    int localSlotNumber=0;  
    int error =0;  
    
    getchar();
    
    printf("--------------------------------------------\n");
    printf("|             BOOK NEW SLOTS               |\n");
    printf("|------------------------------------------|\n");
    printf("| Enter Room Number:                       |\n");
    printf("--------------------------------------------\n");
    
    scanf("%d",&localroomNumber);
    getchar();
    
    if (localroomNumber<1||localroomNumber>8) 
    {
        printf("Invalid choice");
        return -1;
    }
    
    localroomNumber--; 

    printf("--------------------------------------------\n");
    printf("| Enter Slot Number:                       |\n");
    printf("--------------------------------------------\n");
    
    
    scanf("%d",&localSlotNumber);
    getchar();
    
    if (localSlotNumber<1||localSlotNumber>11) 
    {
        printf("Invalid choice");
        return -1;
    }

    localSlotNumber--;

    error = createReservation(studentID,localroomNumber,localSlotNumber);
    if (error!=0)
    {
        return -1;
    }
    

    printf("--------------------------------------------\n");
    printf("| SUDESSFULLY BOOKED A SLOT                |\n");
    printf("--------------------------------------------\n");
    
    return 0; //Sucess

}

int editBookedSlot(char studentID[]) //choice 3 //completed
{ 
    int choice =0;
    getchar();
    
    
    printf("--------------------------------------------\n");
    printf("|   VIEW / EDIT / CANCEL EXISTING BOOKING  |\n");
    printf("|------------------------------------------|\n");
    printf("| 1) View existing booking                 |\n");
    printf("| 2) Edit existing booking                 |\n");
    printf("| 3) Cancel existing booking               |\n");
    printf("|------------------------------------------|\n");
    printf("|      ENTER OPTION:                       |\n");
    printf("--------------------------------------------\n\n");
    
    scanf("%d",&choice);
    getchar();
    
    switch (choice)
    {
    case 1:
        editBookedSlotView(studentID);
        break;
    
    case 2:
        editBookedSlotEdit(studentID);
        break;

    case 3:
        editBookedSlotCancel(studentID);
        break;
    
    default:
        printf("Invalid entry");
        break;
    }

    getchar();
    return 0;

}

int editBookedSlotView(char username[]) //choice 3-1 //completed
{
    char student_ID[20];
    strcpy(student_ID,username);
    printf("--------------------------------------------\n");
    printf("|             BOOKED SLOTS                 |\n");
    printf("--------------------------------------------\n");

    for (int i = 0; i < 8; i++)
    {
        printf("--------------------------------------------\n");
        printf("|                ROOM %d                    |\n",(i+1));
        printf("--------------------------------------------\n");
        for (int j = 0; j < 11; j++)
        {
            if (rooms[i][j].currentReservation != NULL)
            {
                strcpy(student_ID,rooms[i][j].currentReservation->studentID);
                printf("  %s : Slot %d: %d:00 - %d:00                    \n",student_ID,(j+1),(j+8),(j+9));
            } 
        }
    }
    printf("--------------------------------------------\n\n");
    return 0;
}

int editBookedSlotCancel(char student_ID[]) //choice 3-3 //completed
{
    int localRoomNumber=0;
    int localSlotNumber=0;

    printf("--------------------------------------------\n");
    printf("|  WHICH BOOKED SLOTS DO U WANT TO CANCEL  |\n");
    printf("--------------------------------------------\n");

    printf("|------------------------------------------|\n");
    printf("| Enter Room Number:                       |\n");
    printf("--------------------------------------------\n");

    scanf("%d",&localRoomNumber);
    getchar();

    if (localRoomNumber<1||localRoomNumber>8) 
    {
        printf("Invalid choice");
        return -1;
    }
    
    localRoomNumber--; 

    printf("--------------------------------------------\n");
    printf("| Enter Slot Number:                       |\n");
    printf("--------------------------------------------\n");

    scanf("%d",&localSlotNumber);
    getchar();

    if (localSlotNumber<1||localSlotNumber>11) 
    {
        printf("Invalid choice");
        return -1;
    }

    localSlotNumber--;

    if (rooms[localRoomNumber][localSlotNumber].currentReservation == NULL) {
        printf("Slot not booked");
        return -1; // Slot not booked
    }

    if (strcmp(rooms[localRoomNumber][localSlotNumber].currentReservation->studentID,student_ID)!=0)
    {
        printf("Slot booked by somebody else");
        return -2;
    }
    

    rooms[localRoomNumber][localSlotNumber].currentReservation=NULL;
    free(rooms[localRoomNumber][localSlotNumber].currentReservation);

    if (rooms[localRoomNumber][localSlotNumber].currentReservation) {
        printf("Error deleting memory");
        return -2; // Error deleting memory
    }

    printf("--------------------------------------------\n");
    printf("| BOOKING CANCELLED SUCCESSFULLY           |\n");
    printf("--------------------------------------------\n");

    return 0;//Sucess
    
}

int editBookedSlotEdit(char student_ID[]) //choice 3-2 //completed
{
    
    int oldRoomNumber=0;
    int oldSlotNumber=0;
    int newRoomNumber=0;
    int newSlotNumber=0;
    int choice=0;
    int error =0;

    printf("--------------------------------------------\n");
    printf("|  WHICH BOOKED SLOTS DO U WANT TO CHANGE? |\n");
    printf("--------------------------------------------\n");

    printf("|------------------------------------------|\n");
    printf("| Enter Old Room Number:                   |\n");
    printf("--------------------------------------------\n");
    
    scanf("%d",&oldRoomNumber);
    getchar();
    
    if (oldRoomNumber<1||oldRoomNumber>8) 
    {
        printf("Invalid choice");
        return -1;
    }
    
    oldRoomNumber--; 

    printf("--------------------------------------------\n");
    printf("| Enter Old Slot Number:                    |\n");
    printf("--------------------------------------------\n");
    
    
    scanf("%d",&oldSlotNumber);
    getchar();
    
    if (oldSlotNumber<1||oldSlotNumber>11) 
    {
        printf("Invalid choice");
        return -1;
    }

    oldSlotNumber--;

    if (rooms[oldRoomNumber][oldSlotNumber].currentReservation == NULL) {
        printf("Slot not booked");
        return -1; // Slot not booked
    }

    if (strcmp(rooms[oldRoomNumber][oldSlotNumber].currentReservation->studentID,student_ID)!=0)
    {
        printf("Slot booked by somebody else");
        return -2;
    }

    printf("--------------------------------------------\n");
    printf("|  CHANGE ROOM NUMBER AND/OR SLOT NUMBER   |\n");
    printf("|------------------------------------------|\n");
    printf("| 1) Change only Room Number               |\n");
    printf("| 2) Change only Slot Number               |\n");
    printf("| 3) Change both                           |\n");
    printf("|------------------------------------------|\n");
    printf("|      ENTER OPTION:                       |\n");
    printf("--------------------------------------------\n\n");

    scanf("%d",&choice);
    getchar();

    switch (choice)
    {
    case 1:

        printf("--------------------------------------------\n");
        printf("| Enter New Room Number:                   |\n");
        printf("--------------------------------------------\n");
        
        scanf("%d",&newRoomNumber);
        getchar();
        
        if (newRoomNumber<1||newRoomNumber>8) 
        {
            printf("Invalid choice");
            return -1;
        }
        
        newRoomNumber--;
        newSlotNumber = oldSlotNumber;
        
        error = createReservation(student_ID,newRoomNumber,newSlotNumber);
        if (error!=0)
        {
            return -1;
        }

        printf("--------------------------------------------\n");
        printf("| BOOKING EDITED SUCCESSFULLY              |\n");
        printf("--------------------------------------------\n");

        break;
    
    case 2:

        printf("--------------------------------------------\n");
        printf("| Enter New Slot Number:                    |\n");
        printf("--------------------------------------------\n");
        
        scanf("%d",&newSlotNumber);
        getchar();
        
        if (newSlotNumber<1||newSlotNumber>11) 
        {
            printf("Invalid choice");
            return -1;
        }
        
        newSlotNumber--;
        newRoomNumber = oldRoomNumber;
        
        error = createReservation(student_ID,newRoomNumber,newSlotNumber);
        if (error!=0)
        {
            return -1;
        }

        printf("--------------------------------------------\n");
        printf("| BOOKING EDITED SUCCESSFULLY              |\n");
        printf("--------------------------------------------\n");

        break;
    
    case 3:

        printf("--------------------------------------------\n");
        printf("| Enter New Room Number:                    |\n");
        printf("--------------------------------------------\n");
        
        scanf("%d",&newRoomNumber);
        getchar();
        
        if (newRoomNumber<1||newRoomNumber>8) 
        {
            printf("Invalid choice");
            return -1;
        }
        
        newRoomNumber--;

        printf("--------------------------------------------\n");
        printf("| Enter New Slot Number:                    |\n");
        printf("--------------------------------------------\n");
        
        scanf("%d",&newSlotNumber);
        getchar();
        
        if (newSlotNumber<1||newSlotNumber>11) 
        {
            printf("Invalid choice");
            return -1;
        }
        
        newSlotNumber--;
        
        error = createReservation(student_ID,newRoomNumber,newSlotNumber);
        if (error!=0)
        {
            return -1;
        }

        printf("--------------------------------------------\n");
        printf("| BOOKING EDITED SUCCESSFULLY              |\n");
        printf("--------------------------------------------\n");

        break;

    default:
        printf("Invalid entry");
        break;
    }

    rooms[oldRoomNumber][oldSlotNumber].currentReservation=NULL;
    free(rooms[oldRoomNumber][oldSlotNumber].currentReservation);

    if (rooms[oldRoomNumber][oldSlotNumber].currentReservation) {
        printf("Error deleting memory");
        return -2; // Error deleting memory
    }

    return 0;

}

int createReservation(char ID[], int roomNumber, int slotNumber) //completed 
{
    
    if (rooms[roomNumber][slotNumber].currentReservation != NULL) {
        printf("Slot already booked");
        return -1; // Slot already booked
    }
    
    
    
    Reservation* localReservation = NULL;
    
    localReservation = malloc(sizeof(Reservation));
    
    if (localReservation==NULL) {
        printf("Error allocating memory");
        return -2; // Error allocating memory
    }
    
    localReservation->studentID[0] = '\0';  
    
    strcpy(localReservation->studentID,ID);
    
    rooms[roomNumber][slotNumber].currentReservation = localReservation;

    return 0; // Success
}

void initialise()  //completed
{ 
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            rooms[i][j].roomNumber = i+1;
            rooms[i][j].slotNumber = j;
            rooms[i][j].currentReservation = NULL;
        }
    }
    buildLogin();
}

int authenticate(char username[], char password[]) //completed
{

    FILE* fp = fopen("login.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return -2;
    }
    
    char line[100];
    while (fgets(line, 100, fp) != NULL) {
        
        line[strcspn(line, "\n")] = 0;

        char* fileUsername = strtok(line, " ");
        char* filePassword = strtok(NULL, " ");

        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(fp);
            printf("Authenticated\n");
            return 0;
        }
    }

    fclose(fp);
    return -1;
}

int readFromFile(char fileName[],char username[]) //completed
{
    int error=0;
    char student_ID[8] ;
    strcpy(student_ID,username);
    

    FILE* fp = fopen("login.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return -2;
    }
    
    char line1[100];
    while (fgets(line1, 100, fp) != NULL) {
        //printf("Entered while loop\n");
            
        line1[strcspn(line1, "\n")] = 0;

        char* fileUsername = strtok(line1, " ");

        if (strcmp(fileUsername + strlen(fileUsername) - 4, ".txt") != 0) {
            strcpy(student_ID,fileUsername);
            strcat(fileUsername, ".txt");
        } else {
            int sizeOfFileName = strlen(fileUsername);
            for(int i=1;i<5;i++) {
                fileUsername[sizeOfFileName-i] = '\0';
            }
        }

        //printf("\n\nSTudentID: %s\n\n",student_ID);

        error = checkOrCreateFile(fileUsername,student_ID); //if file dont have create file
        if (error!=0) {
            return -1;
        }


        FILE* fp1 = fopen(fileUsername, "r");
        if (fp1 == NULL) {
            printf("Error: Could not open file.\n");
            return -2;
        }
        

        char line2[10];
        while (fgets(line2, 10, fp1) != NULL) 
        {
            //printf("Entered while loop\n");
            
            line2[strcspn(line2, "\n")] = 0;

            char* roomNumberStr = strtok(line2, " ");
            char* slotNumberStr = strtok(NULL, " ");
            

            int roomNumber = atoi(roomNumberStr);
            int slotNumber = atoi(slotNumberStr);
            //printf("Room Number: %d\n",roomNumber);
            //printf("Slot Number: %d\n",slotNumber);

            if ((roomNumber>-1 && roomNumber<8) && (slotNumber>-1 && slotNumber<11)) 
            {
                //printf("entered if statement\n");
                error=0;
                error = createReservation(student_ID,roomNumber,slotNumber);
                //printf("Created Reservation\n");
                
                if (error!=0) {
                    printf("Error cxreating Reservation");
                    return -3;
                }
                
                printf("Created reservation\n\n\n\n");
            }
            
            

        } 
        //printf("closed file\n");
        fclose(fp1);
          // printf("Exited while loop");

    }
    //printf("Exited while loop");
    
    fclose(fp);
    
    return 0;
}

int checkOrCreateFile(char fileName[],char username[]) //completed
{
    if (strcmp(fileName + strlen(fileName) - 4, ".txt") != 0) {
        strcat(fileName, ".txt");
    }
    
    // Check if the file already exists
    if (access(fileName, F_OK) == 0) {
        //printf("File already exists.\n");
        return 0;
    }

    // If the file doesn't exist, create it
    FILE *fp = fopen(fileName, "w");

    if (fp == NULL) {
        printf("Failed to create file.\n");
        return -1;
    }

    
    fclose(fp);

    //printf("File created successfully.\n");
    return 0;
}

int storeToFile(char fileName[],char username[]) {
    int error=0;
    char student_ID[8] ;
    strcpy(student_ID,username);
    

    
    if (strcmp(fileName + strlen(fileName) - 4, ".txt") != 0) {
        strcat(fileName, ".txt");
    }

    

    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("Failed to create file.\n");
        return -1;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            //strcpyy(username, rooms[i][j].currentReservation->studentID);
            if (rooms[i][j].currentReservation!=NULL)
            {
                if (strcmp(rooms[i][j].currentReservation->studentID,student_ID)==0){
                    fprintf(fp, "%d %d\n", (i), (j));
                    printf("Stored %d %d in %s w fileName %s\n",i,j,student_ID,fileName);
                }
                free(rooms[i][j].currentReservation);
                rooms[i][j].currentReservation = NULL;
                printf("Room freed\n");
            } 
        }
    }

    fclose(fp);

    printf("Data stored to file.\n");
    return 0;
}

int buildLogin() {
    FILE* fp = fopen("login.txt", "w");
    if (fp == NULL) {
        printf("Error: Failed to open file for writing.\n");
        return 1;
    }

    fprintf(fp, "admin password\n");
    fprintf(fp, "student password\n");
    fprintf(fp, "TP072262 mdshaafi\n");
    fprintf(fp, "mdshaafi qwerty\n");

    fclose(fp);
    printf("Data written to file.\n");
    return 0;
}



/*

int StoreBooking(char* username) {
    checkOrCreateFile("record.txt",username);

    int error=0;
    char student_ID[8] ;
    strcpy(student_ID,username);
    char fileName[] = "record.txt";
    

    
    if (strcmp(fileName + strlen(fileName) - 4, ".txt") != 0) {
        strcat(fileName, ".txt");
    }

    

    FILE *fp = fopen(fileName, "w");

    if (fp == NULL) {
        printf("Failed to create file.\n");
        return -1;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            
            if (rooms[i][j].currentReservation!=NULL)
            {
                fprintf(fp, "%s %d %d\n",username, (i), (j));
                
                free(rooms[i][j].currentReservation);
                rooms[i][j].currentReservation = NULL;
                printf("Room freed\n");
            } 
        }
    }

    fclose(fp);

    printf("Data stored to file.\n");
    return 0;

}




*/