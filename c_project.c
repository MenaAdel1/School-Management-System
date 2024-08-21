/*********************************************************************************************************************
Name                : main.c
Author              : MINA ADEL KADESS
Data                : 6-8-2024
Description         : School Management System Project Using C
********************************************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for student information
struct student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Define the structure for a linked list node
struct node {
    struct student data;
    struct node *next;
};

// Global pointers for managing the linked list
struct node* Head = NULL;
struct node* current = NULL;

// Function prototypes
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    int choice;
    struct student tempStudent;
    int id;

    while (1) {  // Infinite loop
        // Display menu
        printf("-------------------------------------------------------------------------------------------------------------------------\n");
        printf("1. Add a Student\n");
        printf("2. Display All Students\n");
        printf("3. Search for a Student by ID\n");
        printf("4. Update Student Information\n");
        printf("5. Delete a Student\n");
        printf("6. Calculate Average GPA\n");
        printf("7. Find Student with Highest GPA\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("-------------------------------------------------------------------------------------------------------------------------\n");

        // Handle user choice
        switch (choice) {
            case 1:
                printf("Enter the ID: ");
                scanf("%d", &tempStudent.id);
                printf("Enter the name: ");
                fflush(stdin);
                gets(tempStudent.name);
                printf("Enter the age: ");
                scanf("%d", &tempStudent.age);
                printf("Enter the GPA: ");
                scanf("%f", &tempStudent.gpa);
                addStudent(&tempStudent);
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                printf("Enter the ID to search: ");
                scanf("%d", &id);
                searchStudentByID(id);
                break;

            case 4:
                printf("Enter the ID to update: ");
                scanf("%d", &id);
                updateStudent(id);
                break;

            case 5:
                printf("Enter the ID to delete: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;

            case 6:
                printf("Average GPA: %.2f\n", calculateAverageGPA());
                break;

            case 7:
                searchHighestGPA();
                break;

            case 8:
                printf("Exiting...\n");
                exit(0);  // Exit the program

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}

//==============================================================================================================================================
// Function to add a new student to the linked list
void addStudent(const struct student *const ptr)
{
	// Allocate memory for a new node
	struct node *link = (struct node*) malloc(sizeof(struct node));

	if (link == NULL) {
		printf("Memory allocation failed\n");
		return;
	}
	// Initialize the next pointer of the new node to NULL
	link->next = NULL;
	// Copy the student data into the new node
	link->data=*ptr  ;

	// If the list is empty, make the new node the head
	if (Head == NULL) {
		Head = link;
		return;
	}

	// Start from the head of the list
	current = Head;

	// loop until reach the last node in the old list
	while (current != NULL)
	{
		//check for duplicate IDs If a node with the same ID is found
		if (current->data.id == link->data.id)
		{   printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("This ID is already reserved\n");
			// Free the memory allocated for the new node
			free(link );
			return;
		}
		// Move to the next node in the list
		current = current->next;
	}
	// Start from the head of the list again
	current = Head;
	// loop until reach the last node in the old list
	while (current->next != NULL)
	{
		current = current->next;
	}
	// Add the new node at the end of the list
	current->next = link;
}
//=========================================================================================================================================
// Function to display all students in the linked list
void displayStudents(void)
{
	// Initialize a pointer to start traversing the list from the head
	struct node *ptr = Head;

	// Check if the linked list is empty
	if (ptr == NULL) {
		printf("No students to display.\n");
		return;
	}
	//start looping from the head until the last node
	while (ptr != NULL)
	{
		// Print the current student's ID, Name, Age, and GPA
		printf("[ID: %d, Name: %s, Age: %d, GPA: %.2f]\n", ptr->data.id, ptr->data.name, ptr->data.age, ptr->data.gpa);
		// Move the pointer to the next node in the linked list
		ptr = ptr->next;
	}
}

//============================================================================================================================================
// Function to search for a student by their ID
void searchStudentByID(int id) {
	if (Head == NULL) {
		printf("The linked list is empty.\n");
		return;
	}

	current = Head;
	while (current != NULL) {
		if (current->data.id == id) {
			printf("Student found\n");
			printf("[ID: %d, Name: %s, Age: %d, GPA: %.2f]\n", current->data.id, current->data.name, current->data.age, current->data.gpa);
			return;
		}
		current = current->next;
	}

	printf("Student ID %d does not exist.\n", id);
}

//==============================================================================================================================================
// Function to update the details of a student by their ID
void updateStudent(int id)
{
	// Check if the linked list is empty
	if (Head == NULL) {
		printf("The linked list is empty.\n");
		return;
	}

	// Start from the head of the list
	current = Head;

	//start looping from the head until the last node
	while (current != NULL)
	{
		// Check if the current node's ID matches the given ID
		if (current->data.id == id)
		{
			// If a match is found, print a message indicating the student was found
			printf("Enter new details for student with ID = %d\n", id);

			// Print the student's ID, Name, Age, and GPA
			printf("Enter the new name: \n");
			fflush(stdin);
			fflush(stdout);
			gets(current->data.name);
			printf("Enter the new age: \n");
			scanf("%d", &current->data.age);
			printf("Enter the new GPA: \n");
			scanf("%f", &current->data.gpa);
			printf("Student details updated successfully.\n");
			return;
		}
		// Move the pointer to the next node in the linked list
		current = current->next;
	}
	// Move the pointer to the next node in the linked list
	printf("Student ID %d does not exist.\n", id);
}

//==============================================================================================================================================
// Function to calculate and return the average GPA of all students
float calculateAverageGPA(void)
{
	 // Check if the linked list is empty
    if (Head == NULL) {
    	// Print a message indicating the list is empty
        printf("The linked list is empty.\n");
        return 0;
    }

    // Start from the head of the list
    current = Head;

    // Initialize variables to hold the sum of GPAs and the count of students
    float sum = 0;
    int count = 0;

    //start looping from the head until the last node
    while (current != NULL)
    {
    	// Add the current student's GPA to the sum
        sum += current->data.gpa;
        // Move to the next node in the linked list
        current = current->next;
        // Increment the student count
        count++;
    }
    // Calculate and return the average GPA
    return (sum / count);
}

//==============================================================================================================================================
// Function to find and display the student with the highest GPA
void searchHighestGPA(void) {
    if (Head == NULL) {
        printf("The linked list is empty.\n");
        return;
    }
    // Start from the head of the list
    current = Head;
    struct student *highest = &current->data;

    //start looping from the head until the last node
    while (current != NULL) {
        if (current->data.gpa > highest->gpa) {
            highest = &current->data;
        }
        current = current->next;
    }

    printf("Student with the highest GPA:\n");
    printf("[ID: %d, Name: %s, Age: %d, GPA: %.2f]\n", highest->id, highest->name, highest->age, highest->gpa);
}

//==============================================================================================================================================
// Function to delete a student by their ID
void deleteStudent(int id)
{

	// Initialize a pointer and initially NULL
	struct node*previous=NULL;
	if(Head==NULL)
	{
		printf("the linked list is empty:");
		return;
	}
	  // Start from the head of the list
	current=Head;
	  // Start from the head of the list
	previous=Head;
	// Check if the first node's ID matches the given ID
	if(current->data.id==id)
	{
		 // Move to the next node in the linked list
		Head=current->next;
		// Free the first  memory allocated
		free(current);
		return;
	}
	 // Move to the next node in the linked list
	current=Head->next;
	while(current!=NULL)
	{
		// Check if the current node's ID matches the given ID
		if(current->data.id==id)
		{

			previous->next = current->next;
			free(current);
			printf("Student with ID %d deleted Successfully . \n",id);

			return;

		}


		current=current->next;
		previous=previous->next;
	}

	printf("Student ID %d does not exist.\n", id);

}
