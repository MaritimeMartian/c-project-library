

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Book information structure
struct book {
    char bookName[50];
    char author[50];
    char libraryName[50];
    char publisher[50];
    double replacementCost;
    char subjectOfMaterial[25];
    int indexNumber;
    char currentlyOnLoanTo[50];
    char dueDate[25];
    struct book *next;
};

//Function acknowledgements
struct book *GenerateLinkedList();
void DisplayLinkedList(struct book*);
void BrowseLinkedList(struct book*);
void ModifyLinkedList(struct book*);
struct book *DeleteLinkedList(struct book *);
void SaveToFile(struct book *);
struct book *LoadFromFile();
struct book *MemoryCleanUp(struct book *);
void SortLinkedListByAuthor(struct book *);

//Begin program
int main() {

    //main variables
    int ch;
    int choice = 0;
    char keepGoing = 'y';
    
    //Initialize starting pointer
    struct book *start = NULL;

    //Ask user what to do
    puts("Welcome to the Library Database\n");
    while (keepGoing == 'y') {
        puts("Enter a choice:\n1. Add a database entry\n2. Browse database entries\n3. Edit database entry\n4. Delete database entry\n5. Save database to file\n6. Load database from file\n7. Sort database (by author's name)\n8. Exit\n");
        scanf("%d", &choice);
        while ((ch = getchar()) != '\n' && ch != EOF);
        switch (choice) {
        case 1:
            start = GenerateLinkedList();
            break;
        case 2:
            BrowseLinkedList(start);
            break;
        case 3:
            ModifyLinkedList(start);
            break;
        case 4:
            DeleteLinkedList(start);
            break;
        case 5:
            SaveToFile(start);
            break;
        case 6:
            start = LoadFromFile();
            break;
        case 7:
            SortLinkedListByAuthor(start);
            break;
        case 8:
            exit(0);
        }

        //Show user database status after each task
        puts("\nCurrent database status:\n");
        DisplayLinkedList(start);
        puts("Begin new task? (y/n):");
        scanf("%c", &keepGoing);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
    }
    //Clean up memory when finished
    start = MemoryCleanUp(start);
    puts("Program finished. Thanks for stopping by!");

    return 0;

}

//Add new entry
struct book *GenerateLinkedList() {
    struct book *start = NULL, *move = NULL, *new = NULL;
    char keepGoing = 'y';
    int ch;

    //allocate memory in case of first-time add
    while (keepGoing == 'y') {
        if (start == NULL) {

            new = (struct book*)malloc(sizeof(struct book));
            if (new == NULL) {
                puts("FATAL: Memory allocation error");
                exit(1);
            }

            //set starting pointer
            start = new;

            //First record already exists?
        } else {

            move = start;
            while (move->next != NULL) {
                move = move->next;
            }
            new = (struct book*)malloc(sizeof(struct book));
            if (new == NULL) {
                puts("memory error");
                exit(1);
            }
            
            //set move pointer to memory area after existing record
            move->next = new;
        }

        //Begin filling in data
        new->next = NULL;

        puts("Enter book name:");
        scanf("%s", new->bookName);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter book author:");
        scanf("%s", new->author);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter library name:");
        scanf("%s", new->libraryName);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
        
        puts("Enter book publisher:");
        scanf("%s", new->publisher);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
        
        puts("Enter book replacement cost:");
        scanf("%lf", &new->replacementCost);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
        
        puts("Enter subject of material:");
        scanf("%s", &new->subjectOfMaterial);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter index number:");
        scanf("%d", &new->indexNumber);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter the person the book is currently on loan to:"); scanf("%s", &new->currentlyOnLoanTo);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter book due date:");
        scanf("%s", &new->dueDate);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        //prompt to add another record
        puts("Create new entry? (y/n):"); scanf("%c", &keepGoing);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
    }
    return start;
}

//Browse linked list
void BrowseLinkedList(struct book* start){
    struct book *move = start;
    char keepGoing = 'y';
    int choice;
    char bookSearch[50];
    int resultsFound = 0;
    int ch;

    //Ask user for search choice
    puts("Do you want to:\n1. Search by book name\n2. Search by author\n");
    scanf("%d", &choice);
    while ( ( ch = getchar() ) != '\n' && ch != EOF );
    switch(choice) {
        //Selected book name search?
		case 1:
        puts("Please enter the name of the book you would like to search for:\n");
        scanf("%s", bookSearch);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
        while (move != NULL) {
            if (strcmp(move->bookName, bookSearch) == 0) {
                puts("\nFound result:\n");
                printf("%s, %s, %s, %s, %f, %s, %d, %s, %s\n",move->bookName, move->author, move->libraryName, move->publisher, move->replacementCost, move->subjectOfMaterial, move->indexNumber, move->currentlyOnLoanTo, move->dueDate);
                resultsFound++;
            }
            move = move->next; 
        }
        printf("\nDone. Found %d results.\n", resultsFound);
		break;

        //Selected author search?
		case 2:
        puts("Please enter the name of the author you would like to search for:\n");
        scanf("%s", bookSearch);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        //Search results
        while (move != NULL) {
            if (strcmp(move->author, bookSearch) == 0) {
                puts("\nFound result:\n");
                printf("%s, %s, %s, %s, %f, %s, %d, %s, %s\n",move->bookName, move->author, move->libraryName, move->publisher, move->replacementCost, move->subjectOfMaterial, move->indexNumber, move->currentlyOnLoanTo, move->dueDate);
                resultsFound++;
            }
            move = move->next; 
        }
        printf("\nDone. Found %d results.", resultsFound);

		break;
	}
}
//Modify entry dunction
void ModifyLinkedList(struct book* start) {
    struct book *move = start;
    int indexNumber;
    int ch;

    //Ask user for entry to modify (starting at #1)
    puts("Type the index number of the entry you want to modify:\n");
    scanf("%d", &indexNumber);
    while ( ( ch = getchar() ) != '\n' && ch != EOF );
    if (indexNumber != 0) {
        for (int counter = 0; counter < indexNumber; counter++) {
            move = move->next;
        }
    }
    //Show user what's at the index
    puts("Here is what's currently located at the index:\n");
    printf("%s, %s, %s, %s, %f, %s, %d, %s, %s\n",move->bookName, move->author, move->libraryName, move->publisher, move->replacementCost, move->subjectOfMaterial, move->indexNumber, move->currentlyOnLoanTo, move->dueDate);

    //Allow user to replace the data
    puts("You can fill this index in with new data.\n");
    puts("Enter book name:");
        scanf("%s", move->bookName);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter book author:");
        scanf("%s", move->author);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter library name:");
        scanf("%s", move->libraryName);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
        
        puts("Enter book publisher:");
        scanf("%s", move->publisher);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
        
        puts("Enter book replacement cost:");
        scanf("%lf", &move->replacementCost);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );
        
        puts("Enter subject of material:");
        scanf("%s", &move->subjectOfMaterial);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter index number:");
        scanf("%d", &move->indexNumber);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter the person the book is currently on loan to:"); scanf("%s", &move->currentlyOnLoanTo);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("Enter book due date:");
        scanf("%s", &move->dueDate);
        while ( ( ch = getchar() ) != '\n' && ch != EOF );

        puts("\nChanges applied.\n");

}

//Display list of entries
void DisplayLinkedList(struct book* start){
    struct book *move = start;
    while (move->next != NULL) {
        printf("%s, %s, %s, %s, %f, %s, %d, %s, %s\n",move->bookName, move->author, move->libraryName, move->publisher, move->replacementCost, move->subjectOfMaterial, move->indexNumber, move->currentlyOnLoanTo, move->dueDate);
        move = move->next;
    }

    printf("%s, %s, %s, %s, %f, %s, %d, %s, %s\n",move->bookName, move->author, move->libraryName, move->publisher, move->replacementCost, move->subjectOfMaterial, move->indexNumber, move->currentlyOnLoanTo, move->dueDate);
}

//Delete entries from linked list
struct book *DeleteLinkedList(struct book *start) {
    struct book *move = start, *prev = NULL;
    int indexNumber;
    int ch;

    puts("Type the index number of the entry you want to delete:\n");
    scanf("%d", &indexNumber);
    while ((ch = getchar()) != '\n' && ch != EOF);

    // Look for entry the user specified
    if (move != NULL && move->indexNumber == indexNumber) {
        start = move->next;
        free(move);
        puts("\nEntry deleted.\n");
        return start;
    }

    for (int counter = 0; counter < indexNumber; counter++) {
        prev = move;
        move = move->next;
    }

    // Delete entry
    if (move != NULL) {
        prev->next = move->next;
        free(move);
        puts("\nEntry deleted.\n");
    } else {
        puts("\nEntry not found.\n");
    }

    return start;
}

// Function to save data to a file
void SaveToFile(struct book *start) {
    FILE *file = fopen("library_database.txt", "w");
    if (file == NULL) {
        puts("Error opening file for writing. Make sure the directory is accessible.");
        return;
    }
    struct book *move = start;
    while (move != NULL) {
        fprintf(file, "%s,%s,%s,%s,%.2f,%s,%d,%s,%s\n",
                move->bookName, move->author, move->libraryName, move->publisher, move->replacementCost, move->subjectOfMaterial, move->indexNumber,move->currentlyOnLoanTo, move->dueDate);

        // Debugging output
        printf("Writing to file: %s by %s\n", move->bookName, move->author);
        
        move = move->next;
    }
    fclose(file);
    puts("Data saved successfully. Check the directory for 'library_database.txt'.");
}

// Function to load data from a file
struct book *LoadFromFile() {
    FILE *file = fopen("library_database.txt", "r");
    if (file == NULL) {
        puts("Error opening file for reading.");
        return NULL;
    }
    struct book *start = NULL, *move = NULL, *new = NULL;
    while (!feof(file)) {
        new = (struct book *)malloc(sizeof(struct book));
        if (new == NULL) {
            puts("Memory allocation error.");
            exit(1);
        }
        if (fscanf(file, "%49[^,],%49[^,],%49[^,],%49[^,],%lf,%24[^,],%d,%49[^,],%24[^\n]\n",
                   new->bookName, new->author, new->libraryName, new->publisher,
                   &new->replacementCost, new->subjectOfMaterial, &new->indexNumber,
                   new->currentlyOnLoanTo, new->dueDate) == 9) {
            new->next = NULL;
            if (start == NULL) {
                start = new;
            } else {
                move->next = new;
            }
            move = new;
        } else {
            free(new);
        }
    }
    fclose(file);
    puts("Data loaded successfully!");
    return start;
}

//Sort linked list alphabetically (by author's name)
void SortLinkedListByAuthor(struct book *start) {
    if (start == NULL) {
        puts("The list is empty; nothing to sort.");
        return;
    }

    struct book *current, *next;
    char dataToMove[50];
    double movingCost;
    int movingIndex;

    int swapped;

    do {
        swapped = 0;
        current = start;

        while (current->next != NULL) {
            next = current->next;

            // Compare author's names and move data if out of order
            if (strcmp(current->author, next->author) > 0) {
                strcpy(dataToMove, current->bookName);
                strcpy(current->bookName, next->bookName);
                strcpy(next->bookName, dataToMove);

                strcpy(dataToMove, current->author);
                strcpy(current->author, next->author);
                strcpy(next->author, dataToMove);

                strcpy(dataToMove, current->libraryName);
                strcpy(current->libraryName, next->libraryName);
                strcpy(next->libraryName, dataToMove);

                strcpy(dataToMove, current->publisher);
                strcpy(current->publisher, next->publisher);
                strcpy(next->publisher, dataToMove);

                movingCost = current->replacementCost;
                current->replacementCost = next->replacementCost;
                next->replacementCost = movingCost;

                strcpy(dataToMove, current->subjectOfMaterial);
                strcpy(current->subjectOfMaterial, next->subjectOfMaterial);
                strcpy(next->subjectOfMaterial, dataToMove);

                movingIndex = current->indexNumber;
                current->indexNumber = next->indexNumber;
                next->indexNumber = movingIndex;

                strcpy(dataToMove, current->currentlyOnLoanTo);
                strcpy(current->currentlyOnLoanTo, next->currentlyOnLoanTo);
                strcpy(next->currentlyOnLoanTo, dataToMove);

                strcpy(dataToMove, current->dueDate);
                strcpy(current->dueDate, next->dueDate);
                strcpy(next->dueDate, dataToMove);

                swapped = 1;
            }

            current = current->next;
        }
    } while (swapped);

    puts("List sorted successfully by author's name.");
}

//Clean memory
struct book *MemoryCleanUp(struct book *start) {
    //Loop through entries until all are freed
    struct book* move = start;

    while (move->next != NULL) {
        struct book* last = move;
        move = move->next;
        free(last);
    }

    //free last entry
    free(move);

    return NULL;
}