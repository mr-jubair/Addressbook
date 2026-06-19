#include "addressbook.h"   // Header file for structure and function declarations
#include<string.h>         // For strlen()
#include<ctype.h>          // for isalpha()

int validate_name(char *name)
{
    if (name == NULL || strlen(name) == 0)      // check if name is NULL or empty
        return 0;
    for (int i = 0; name[i] != '\0'; i++)
    {                                           // check whether character is alphabet or space
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return 0;       // Invalid character found
        }
    }
    return 1;               // Name is valid
}

int validate_number(char *phone)
{
    int len = strlen(phone);      // to get length of phone number
    if(len != 10)                 // to check phone number contains exactly 10 digits
        return 0;
    int i;
    for(i = 0; i < 10; i++)
    {
        if(phone[i] < '0' || phone[i] > '9')    // check each character is digit
            return 0;
    }
    if(phone[0] < '6'|| phone[0] > '9')         // Indian mobile numbers start from 6-9
        return 0;
    
    return 1;       // valid number
}
    
int validate_email(char *email)
{
    if(email[0]=='@' || email[0] >= 'A' && email[0] <= 'Z')     // email cannot start with '@' or uppercase lette
        return 0;
    
    int i;
    for(i = 0; email[i] != '\0'; i++)
    {
        if(email[i] >= 'A' && email[i] <= 'Z')      // uppercase letters not allowed
            return 0;
    }
    int count = 0, at_pos = -1, dot_pos = -1;
    for(i = 0; email[i] != '\0'; i++)
    {
        if(email[i] == '@')     // count number of '@'
        {
            count++;
            at_pos = i;
        }
        else if(email[i] == '.'
            || (email[i] >= 'a' && email[i] <= 'z')
            || (email[i] >= '0' && email[i] <= '9'))
        {
            if(email[i] == '.')
            {
                dot_pos = i;    // store '.' position
            }
            continue;
        }
        else
        {
            return 0;           // invalid character  
        }
    }
    if(dot_pos < at_pos)        // '.' must appear after '@'
        return 0;
    if(dot_pos == at_pos + 1)   // no character between '@' and '.'
        return 0;
    if(count != 1)              // only one '@' allowed
        return 0;
    
    char *mail = strstr(email, ".com");     // check if ".com" exists
    if(mail == NULL || *(mail+4) != '\0')   // ensure email ends with ".com"
        return 0;
    
    return 1;       // valid email
}

void add_contact(struct AddressBook *addressBook)
{
    int index = addressBook->contactCount;
    int ret = 1,duplicate;                      
    do                              // Input and validate name
    {
        duplicate = 0;
        printf("Enter the name : ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);    // read full name including spaces until newline
        char *new_name = addressBook->contacts[addressBook->contactCount].name;
        ret = validate_name(new_name);
        if(ret == 0)
            printf("Invalid\n");
        for(int i = 0; i < addressBook->contactCount; i++)
        { 
            if(strcmp(new_name, addressBook->contacts[i].name) == 0)         // compare two strings to check duplicate names
            {
                duplicate = 1;
                printf(YELLOW"Duplicate value\n"RESET);
                break;
            }
        }
    }while(ret == 0 || duplicate == 1);
    printf(GREEN"Name added sucessfully\n"RESET);
    
    do                                  // Input and validate number
    {
        duplicate = 0;
        printf("Enter the number : ");
        scanf("%s", addressBook->contacts[addressBook->contactCount].phone);            // read phone number
        char *new_number = addressBook->contacts[addressBook->contactCount].phone;
        ret = validate_number(new_number);
        if(ret == 0)
            printf("Invalid\n");
        for(int i = 0; i < addressBook->contactCount; i++)
        { 
            if(strcmp(new_number, addressBook->contacts[i].phone) == 0)         // compare two strings to check duplicate phone numbers
            {
                duplicate = 1;
                printf(YELLOW"Duplicate value\n"RESET);
                break;
            }
        }
    }while(ret == 0 || duplicate == 1);
    printf(GREEN"Phone number added sucessfully\n"RESET);
    
    do                                     // Input and validate email
    {
        duplicate = 0;
        printf("Enter email id : ");
        scanf("%s", addressBook->contacts[addressBook->contactCount].email);            // read email id
        char *new_email = addressBook->contacts[addressBook->contactCount].email;
        ret = validate_email(new_email);
        if(ret == 0)
        {
            printf("Invalid\n");
        }
        for(int i = 0; i < addressBook->contactCount; i++)
        { 
            if(strcmp(new_email, addressBook->contacts[i].email) == 0)          // compare two strings to check duplicate email ids
            {
                duplicate = 1;
                printf(YELLOW"Duplicate email\n"RESET);
                break;
            }
        }
    }while(ret == 0 || duplicate == 1);
    printf(GREEN"Email added sucessfully\n"RESET);
    addressBook->contactCount++;                    // increase total number of stored contacts

}

void search_name(char *Name, struct AddressBook *addressBook)
{                                                       // searching for the contact by name
    int found=0;
    for(int i=0; i < addressBook->contactCount; i++)
    {
        if(strcmp(Name, addressBook->contacts[i].name)  ==  0)          
        {
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            found = 1;
        }
    }
    if(found == 0)
        printf(RED"Not found\n"RESET);
}
void search_phone(char *phone, struct AddressBook *addressBook)
{                                                       // searching for the contact by number
    int found=0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            found=1;
            break;
        }
    }
    if(found == 0)
        printf(RED"Not found\n"RESET);
}
void search_email(char *email, struct AddressBook *addressBook)
{                                                           // searching for the contact by email
    int found=0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            printf("Name  : %s \n", addressBook->contacts[i].name);
            printf("Phone : %s \n", addressBook->contacts[i].phone);
            printf("Email : %s \n", addressBook->contacts[i].email);
            found=1;
            break;
        }
    }
    if(found == 0)
        printf(RED"Not found\n"RESET);
}

void search_contact(struct AddressBook *addressBook)
{
    if(addressBook->contactCount == 0)          // if contactCount is zero
    {
        printf(RED"There are no contacts to search\nAdd contacts first\n"RESET);
        return;
    }
    int choice;
    char name[30];
    char phone[20];
    char email[20]; 
    printf("Enter your choice for Searching :\n");
    do                                              // Menu list
    {
        printf("1.Search by Name \n");
        printf("2.Search by Phone \n");
        printf("3.Search by Email \n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            printf("\nEnter the name : ");
            scanf(" %[^\n]", name);
            search_name(name, addressBook);         // function call to search by name
            break;
            case 2:
            printf("\nEnter the phone number : ");
            scanf(" %s", phone);
            search_phone(phone, addressBook);       // function call to search by number
            break;
            case 3:
            printf("\nEnter the email : ");
            scanf(" %s", email);
            search_email(email, addressBook);       // function call to search by email
            break;
            default:
            printf(RED"Invalid choice, Please select from above\n"RESET);
        }
    }while(choice != 3);
}

int find_by_name(char *name, struct AddressBook *addressBook, int index[])
{
    int count = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(name, addressBook->contacts[i].name) == 0)
            index[count++] = i;     // store matching contact index in array and increment count
    }
    return count;
}
int find_by_phone(char *phone, struct AddressBook *addressBook, int index[])
{
    int count = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
            index[count++] = i;             // store matching contact index in array and increment count
    }
    return count;
}
int find_by_email(char *email, struct AddressBook *addressBook, int index[])
{
    int count = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
            index[count++] = i;         // store matching contact index in array and increment count
    }
    return count;
}
void display_matched(struct AddressBook *addressBook, int index[], int size)   // Display matched contacts using stored indices
{                                          
    for(int i = 0; i < size; i++)
    {
        int pos = index[i];
        printf("%d. %s  %s  %s\n", i+1,
        addressBook->contacts[pos].name,
        addressBook->contacts[pos].phone,
        addressBook->contacts[pos].email);
    }
}

void edit_field(struct AddressBook *addressBook, int pos)    // edit specific field of contacts
{
    int choice;
    printf("\nEdit Menu\n");
    printf("1.Name\n2.Mobile No\n3.Email\n");
    scanf("%d",&choice);

    if(choice == 1)
    {
        printf("Enter new name : ");
        scanf(" %[^\n]", addressBook->contacts[pos].name);      // direct overwrite
    }
    else if(choice == 2)            // validate before updating
    {
        char phone[20];
        int ret;
        do
        {
            printf("Enter new phone : ");
            scanf("%s", phone);
            ret = validate_number(phone);
            if(ret == 0)
                printf("Invalid number\n");
        }while(ret == 0);
        strcpy(addressBook->contacts[pos].phone, phone);
    }
    else if(choice == 3)
    {
        char email[50];
        int ret;
        do
        {
            printf("Enter new email : ");
            scanf("%s", email);
            ret = validate_email(email);
            if(ret == 0)
                printf("Invalid email\n");
        }while(ret == 0);
        strcpy(addressBook->contacts[pos].email, email);
    }
}

void edit_contact(struct AddressBook *addressBook)   // editing the existing contact
{
    if(addressBook->contactCount == 0)          // check if addressBook is empty
    {
        printf(RED"No contacts available\n"RESET);
        return;                                 // exit early if no data present
    }
    int choice, index[100], size = 0;
    char key[50];
    printf("Search contact by\n");
    printf("1.Name\n2.Phone\n3.Email\n");       // user choice
    scanf("%d",&choice);

    if(choice == 1)
    {
        printf("Enter name : ");
        scanf(" %[^\n]", key);      // read full name including spaces
        size = find_by_name(key, addressBook, index);   // function call
    }
    else if(choice == 2)
    {
        printf("Enter phone number : ");
        scanf("%s", key);
        size = find_by_phone(key, addressBook, index);
    }
    else if(choice == 3)
    {
        printf("Enter email : ");
        scanf("%s", key);
        size = find_by_email(key, addressBook, index);
    }

    if(size == 0)
    {
        printf(RED"No matching contact\n"RESET);
        return;
    }
    printf(CYAN"\nMatched Contacts\n"RESET);                 // display all matched contacts with numbering
    display_matched(addressBook, index, size);      // function call to display matched contacts
    
    int select;
    printf("Select contact : ");
    scanf("%d",&select);
    if(select < 1 || select > size)         // validate selection range
    {
        printf("Invalid selection\n");
        return;
    }
    int pos = index[select-1];
    edit_field(addressBook, pos);           // edit selected contacts
    printf(GREEN"Contact updated successfully\n"RESET); 
}

void remove_contact(struct AddressBook *addressBook, int pos)
{
    for(int i = pos; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];  // Left shift
    }
    addressBook->contactCount--;        // Count decrement
    printf(GREEN"Contact deleted successfully\n"RESET);
}
void delete_contact(struct AddressBook *addressBook)    // deleting the existing contact
{
    if(addressBook->contactCount == 0)          // check if addressBook is empty
    {
        printf(RED"No contacts available\n"RESET);
        return;
    }
    int choice, index[100], size = 0;
    char key[50];
    printf("Search contact to delete by\n");
    printf("1.Name\n2.Phone\n3.Email\n");
    scanf("%d",&choice);
                // Validating based on user choice
    if(choice == 1)             
    {
        printf("Enter name : ");
        scanf(" %[^\n]", key);
        size = find_by_name(key, addressBook, index);
    }
    else if(choice == 2)
    {
        printf("Enter phone : ");
        scanf("%s", key);
        size = find_by_phone(key, addressBook, index);
    }
    else if(choice == 3)
    {
        printf("Enter email : ");
        scanf("%s", key);
        size = find_by_email(key, addressBook, index);
    }
    else
    {
        printf("Invalid choice\n");
        return;
    }

    if(size == 0)
    {
        printf(RED"No matching contact found\n"RESET);
        return;
    }
    printf(CYAN"\nMatched Contacts\n"RESET);
    display_matched(addressBook, index, size);

    int select;
    printf("Select contact to delete : ");
    scanf("%d",&select);
    if(select < 1 || select > size)         // validate selection range
    {
        printf("Invalid selection\n");
        return;
    }

    int pos = index[select - 1];
    remove_contact(addressBook, pos);
}

void save_contacts(struct AddressBook *addressBook)     // save contacts to csv file
{
    FILE *fp = fopen("database.csv", "w");          // opening the file and copying the data
    if(fp == NULL)
    {
        printf(RED"File open error\n"RESET);
        return;
    }
    sort_contacts(addressBook);         // function call to sort contacts

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
    }
    fclose(fp);                         // closing the file
    printf(GREEN"Contacts saved successfully\n"RESET);
}

void load_contacts(struct AddressBook *addressBook)     // load contacts from file
{
    FILE *fp = fopen("database.csv","r");               // opening and reading the data from the file
    if(fp == NULL)
    {
        printf(RED"No saved contacts found\n"RESET);
        return;
    }

    addressBook->contactCount = 0;
    while(fscanf(fp, "%[^,],%[^,],%[^\n]\n",
          addressBook->contacts[addressBook->contactCount].name,
          addressBook->contacts[addressBook->contactCount].phone,
          addressBook->contacts[addressBook->contactCount].email) != EOF)
    {
        addressBook->contactCount++;
    }
    fclose(fp);                 // closing the file
    printf(GREEN"Contacts loaded successfully\n"RESET);
}

void sort_contacts(struct AddressBook *addressBook)     // sort contact in alphabetical order
{
    struct Contact temp;

    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = i + 1; j < addressBook->contactCount; j++)
        {
            if(strcmp(addressBook->contacts[i].name,
                      addressBook->contacts[j].name) > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}
void list_contacts(struct AddressBook *addressBook)     // display all contacts
{
    if(addressBook->contactCount == 0)
    {
        printf(RED"No contacts available to display\n"RESET);
        return;
    }

    sort_contacts(addressBook);   // sort before displaying

    printf(YELLOW"\n---->   List of the Contacts    <----\n"RESET);
    printf(BOLD CYAN"\n--------------------------------------------------------------------------------\n");
    printf("|%-5s  | %-25s |%-15s  | %-30s\n","S.NO ", "NAMES","PHONE NUMBERS","EMAIL ID'S");
    printf("--------------------------------------------------------------------------------\n"RESET);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-5d | %-25s | %-15s | %-30s\n",i+1,addressBook->contacts[i].name,                    // formatted table output for displaying contacts
                    addressBook->contacts[i].phone,addressBook->contacts[i].email);

        printf(BOLD CYAN"--------------------------------------------------------------------------------\n"RESET);
    }
}



