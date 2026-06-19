#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"

struct Contact{                  // Structure to store one contact details 
    char name[50];               // Store contact name
    char phone[15];              // Store phone number
    char email[50];              // Store email id
    char location[20];           // Store location address
};

struct AddressBook {                   // Main Address Book structure
    struct Contact contacts[100];      // Array to store maximum of 100 contacts
    int contactCount;                  // Number of contacts saved
    int index_record[100];             // Used for search indexing
    int ir_size;                       // Size of index record array
};

void add_contact(struct AddressBook *addressBook);      // Function to add new contact
void search_contact(struct AddressBook *addressBook);   // Function to search a contact
void edit_contact(struct AddressBook *addressBook);     // Function to edit a contact
void delete_contact(struct AddressBook *addressBook);   // Function to delete a contact
void list_contacts(struct AddressBook *addressBook);    // Function to display the contacts
void save_contacts(struct AddressBook *addressBook);    // Function to save contacts into file
void load_contacts(struct AddressBook *addressBook);    // Function to load contacts from file
void sort_contacts(struct AddressBook *addressBook);    // Function to sort contacts alphabetically

#endif
