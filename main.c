/* 
   Name: N.S.Mahammed Jubair
   Date: 28/03/2026

   Project Description:
        The Address Book Project is a C-based console application designed to manage contact information 
        such as name, phone number, and email. It provides a user-friendly interface with proper validation 
        mechanisms for ensuring accurate and reliable data entry.

   This application supports the following key functionalities:

   1. Create Contact:
        - Allows users to add new contacts with name, phone number, and email.
        - Supports adding multiple contacts in a single session.
        - Validates user input to prevent invalid or duplicate entries.

   2. Search Contacts:
        - Enables searching for contacts using name, phone number, or email.
        - Displays all matching results, including cases where multiple matches are found.

   3. Edit Contact:
        - Allows modification of any field (name, phone number, email) or all fields of a contact.
        - Supports accurate selection of a contact when multiple matches exist during search.

   4. Delete Contact:
        - Removes a selected contact by name, phone number, or email.
        - Automatically shifts and updates the remaining contacts to maintain list consistency.

   5. Save Contacts:
        - Saves all contact records to an external file (database.csv) for persistent storage.
        - Stores the total contact count to ensure accurate loading in the next session.

   6. Load Contacts:
        - Loads previously saved contacts from the file when the program starts.
        - Restores the complete contact list for immediate use.

   7. List Contacts:
        - Displays all saved contacts in a clean, formatted table.
        - Automatically sorts contacts alphabetically by name for easy navigation.

   Overall, this project demonstrates then effective use of file handling, string manipulation, 
   structured data management and modular programming in C.
*/

#include<stdio.h>
#include "addressbook.h"

int main() 
{
    int choice;    						// Variable to store user's Choice

    struct AddressBook addressBook;     // Declaring AddressBook Structure
    addressBook.contactCount = 0;       // Initializing contact count to 0
    addressBook.ir_size = 0;			// Initializing index array size
	load_contacts(&addressBook);        // Function call to load contacts

    printf(MAGENTA"Size of AddressBook is %zu\n"RESET, sizeof(addressBook));  // To Print size of addressBook
    
    do 
    {
	printf(BOLD CYAN"\n***-------------------------------------------***\n");
    printf("                ADDRESS BOOK MENU                       \n");        // Displaying Addressbook menu
    printf("***-------------------------------------------***\n"RESET);
	printf("1. Add/Create contact\n");     // Add New contact
    printf("2. Search contact\n");         // Search contact by name/phone/email
    printf("3. Edit contact\n");           // Modify existing contact details
    printf("4. Delete contact\n");         // Remove contact from address book
    printf("5. List all contacts\n");      // Display all stored contacts
    printf("6. Save and Exit\n");          // Save contacts to file and exit program
    printf(BOLD CYAN"-------------------------------------------------\n"RESET);

	printf("\nEnter your choice: ");       

	scanf("%d", &choice);				   // Read user choice

	switch (choice) 
	{
	    case 1:
		add_contact(&addressBook);		   // Function call to add new contact
		break;
	    case 2:
		search_contact(&addressBook);	   // Function call to search contact
		break;
	    case 3:
		edit_contact(&addressBook);  	   // Function call to edit contact
		break;
	    case 4:
		delete_contact(&addressBook);	   // Function call to delete contact
		break;
	    case 5:
		list_contacts(&addressBook);	   // Function call to list the contacts
		break;
	    case 6:
		printf("Saving and Exiting...\n"); 
		save_contacts(&addressBook);       // Function call to save the contacts
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);				   // Repeat menu until user selects Exit option

    return 0;							   // End of the program
}
