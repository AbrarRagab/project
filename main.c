#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8;
typedef char Int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef enum
{
    false,
    true
} bool;

typedef struct SimpleDb
{
    uint32 Student_ID;
    uint32 Student_year;
    uint32 Course1_ID;
    uint32 Course1_grade;
    uint32 Course2_ID;
    uint32 Course2_grade;
    uint32 Course3_ID;
    uint32 Course3_grade;
    struct SimpleDb* link; //making the struct self referential by using pointer link to point to the struct of the same type to allow do Linked List.
} student;

student* AtleastThree();
bool SDB_IsFull(void);
uint8 SDB_GetUsedSize(void);
bool SDB_AddEntry();
void SDB_DeleteEntry(uint32 id);
bool SDB_ReadEntry(uint32 id);
void SDB_GetList(uint32 *list);
bool SDB_IsIdExist(uint32 id);

int count = 0;
student* start = NULL;
bool SDB_IsFull ()
{
    if(10 == count)
        return true;
    else
        return false;
}
uint8 SDB_GetUsedSize() // to return the number of students in the database
{
    student* current = start;

    while (current != NULL) // I'll be able to know the size used as long as the count is less than 10 and we didn't reach the end of the list
    {
        count++;
        current = current->link;
    }

    return count;
}

bool SDB_AddEntry()
{

    if (SDB_IsFull())
    {
        printf("Database is full. Cannot add more students.\n");
        return false;
    }

    student* NewStudent =(student*)malloc(sizeof(student));
    if (!NewStudent)
    {
        return false; // Allocation failed
    }

    printf("Enter the database for %d student : ",count+1);
    printf("Student ID: ");
    scanf("%d",&NewStudent->Student_ID);

    if (SDB_IsIdExist(NewStudent->Student_ID)) // To ask first whether the id existed before or not and if not then we will add it
    {
        if(start == NULL)
            return false;

        printf("Student ID already exists. Please enter a different ID.\n");
        free(NewStudent); // Free memory for the node
        // count--;
        return false;      // ID already exists, return false
    }

    printf("\nStudent year: ");
    scanf("%d",&NewStudent->Student_year);

    printf("\nCourse1 ID: ");
    scanf("%d",&NewStudent->Course1_ID);

    printf("\nCourse1 grade: ");
    scanf("%d",&NewStudent->Course1_grade);

    printf("\nCourse2 ID: ");
    scanf("%d",&NewStudent->Course2_ID);

    printf("\nCourse2 grade: ");
    scanf("%d",&NewStudent->Course2_grade);

    printf("\nCourse3_ID: ");
    scanf("%d",&NewStudent->Course3_ID);

    printf("\nCourse3 grade: ");
    scanf("%d",&NewStudent->Course3_grade);

    NewStudent->link = NULL;




    // Add the new node to the linked list
    if (start == NULL)
    {
        start = NewStudent;
    }
    else
    {
        student* current = start;
        while (current->link != NULL)
        {
            current = current->link;
        }
        current->link = NewStudent;
    }
    count++; //Increment the global count variable to keep updating



    return true ;

}
void SDB_DeleteEntry(uint32 id)
{
    student* temp=NULL;
    if(start == NULL) //list is empty, no nodes are created yet
    {
        printf("List is empty \n");
        return;
    }
    //Deleting if the id is found in the first node at the list
    if(start->Student_ID == id)
    {
        temp = start; //temporary pointer to have the address of the first node
        start = start->link;  // making the start or (the head) pointing to the address of the 2nd node
        free(temp);   //I can now free the temp, which means deleting that first node, since I cannot free the start
        count --; //decrementing the global count variable to keep updating
        return; //now the start or (the head) is pointing at the previous called 2nd node, which makes it now the first
    }

    //Deleting in betweens
    student* ptr = start;
    while(ptr->link != NULL)
    {
        if(ptr->link->Student_ID == id) //standing on the previous node and asking if the next is the  one to delete so i can manage to link again, as i am using only one pointer
        {
            temp=ptr->link;
            break;
        }
        ptr = ptr->link; //moving the pointer to the next one
    }
    if(ptr->link == NULL)
        printf("ID Not Found\n");
    else // if the break happens
    {
        ptr->link=temp->link;
        free(temp);
        count --; //decrementing the global count variable to keep updating
    }
    return;
}
bool SDB_ReadEntry(uint32 id) //function to display other data of student when his id is enterd
{
    student* current = start;
    while (current != NULL)
    {
        if (current->Student_ID == id)
        {
            printf("Student ID: %d\n", current->Student_ID);
            printf("Student Year: %d\n", current->Student_year);
            printf("Course1_ID: %d\n", current->Course1_ID);
            printf("Course1_grade: %d\n", current->Course1_grade);
            printf("Course2_ID: %d\n", current->Course2_ID);
            printf("Course2_grade: %d\n", current->Course2_grade);
            printf("Course3_ID: %d\n", current->Course3_ID);
            printf("Course3_grade: %d\n", current->Course3_grade);

            return true; // Data found
        }
        current = current->link;
    }

    return false; // Data not found
}
void SDB_GetList(uint32 *list) //creating a list (array) to have all the entered student IDs
{
    printf("Number of IDs : %d\n", count);
    student* current =start; //creating new pointer to struct student, have the adrdress of start
    uint8 index = 0; // Index to populate the list array
    while (current != NULL)
    {
        list[index]= current->Student_ID;  //assigning the current id of a student to the list array at the index position
        index++;
        current = current->link;
    }
    for(index = 0; index<10; index++)
    {
        printf("Student ID no.%d  : %d",count+1, list[index]);  // printing the student ID
    }
}

bool SDB_IsIdExist(uint32 id)
{
    student* current = start;
    while (current != NULL)
    {
        if (current->Student_ID == id)
        {
            return true; // ID exists in the database
        }
        current = current->link;
    }
    return false; // ID not found in the database
}

void SDB_action(uint8 choice) //function contains a super loop to preform a certain operation(case), depending on the choice of the user
{
    switch (choice)
    {
    case 1: //will be performed if pressed 1
        if (SDB_AddEntry()) //calling for the function to allow the user to add one more student to the database
        {
            printf("Student data added successfully.\n"); //one student added
        }
        else
        {
            printf("Failed to add student data.\n"); //couldn't add a student
        }
        break;

    case 2: //will be performed if pressed 2
        printf("Used size in database: %d\n", SDB_GetUsedSize()); //will print the size (number of students) currently in the database
        break;

    case 3: //will be performed if pressed 3
    {
        uint32 idToSearch; //creating new variable represents existing id, to read the student information
        printf("Enter student ID to read: ");
        scanf("%d", &idToSearch);
        if (SDB_ReadEntry(idToSearch)) //we will do the searching by calling the function ReadEntry
        {
            printf("Data found for student with ID %d.\n", idToSearch);
        }
        else
        {
            SDB_IsIdExist(idToSearch); //in case the user didn't enter an existing id
            printf("Data not found for student with ID %d.\n", idToSearch);
        }
        break;
    }

    case 4:  //will be performed if pressed 4
    {
        uint32 idList[10]; // Assuming you have a maximum of 10 students
        SDB_GetList(idList); //allowing the list of students' IDs to be created when the user wants to
        break;
    }

    case 5:  //will be performed if pressed 5
    {
        uint32 idToCheck;  //creating new variable represents id, to compare it with the existing IDs in the database to know whether it exists or not
        printf("Enter student ID to check: ");
        scanf("%d", &idToCheck);
        if (SDB_IsIdExist(idToCheck)) //the comparing will be preformed when IsExist function is called, giving it the new id (idToCheck)
        {
            printf("Student with ID %d exists.\n", idToCheck); //id already exits
        }
        else
        {
            printf("Student with ID %d does not exist.\n", idToCheck); //id doesn't exixt
        }
        break;
    }

    case 6: //will be performed if pressed 6
    {
        uint32 idToDelete;
        printf("Enter student ID to delete: ");
        scanf("%d", &idToDelete);
        if (SDB_IsIdExist(idToDelete) == 0) // in case the user entered an Id that doesn't exist to be deleted
            printf("Sorry! you entered an invalid ID, please make sure you enter an existing ID");
        SDB_DeleteEntry(idToDelete);
        break;
    }

    case 7: //will be performed if pressed 7
        if (SDB_IsFull())
        {
            printf("Database is full.\n");
        }
        else
        {
            printf("Database is not full.\n");
        }
        break;

    case 0: //will be performed if pressed 0
        printf("Exiting the program.\n");
        exit(0);  //if the user wants no further operation to be done

    default:
        printf("Invalid choice. Please choose a valid option.\n"); //if the user entered an invalid case
    }
}

void SDB_APP()  // This function concludes the whole app
{
    while (1)  // to ensure the program always working
    {
        uint8 choice;   //to allow the user to choose the operation he wants to be done

        printf("Choose an option:\n");
        printf("1. Add entry\n");
        printf("2. Get used size in database\n");
        printf("3. Read student data\n");
        printf("4. Get the list of all student IDs\n");
        printf("5. Check if ID exists\n");
        printf("6. Delete student data\n");
        printf("7. Check if database is full\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        SDB_action(choice); //calling for the function that will enable the operation selected to be preformed
    }
}


int main()
{
    SDB_AddEntry();
   // SDB_AddEntry();
   // SDB_AddEntry();
    void SDB_APP();




    return 0;
}


