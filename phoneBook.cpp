#include <iostream>
#include <fstream>
#include <sstream>
#include "BinarySearchTree.h"
#include "Contact.h"
#include <windows.h>
#include <conio.h>
using namespace std;

void loadTree();
string searchContact(string &fname, string &lname);
int nameValidity(string name);
int phoneValidity(string phone);
char operationPrompt();

// mentioning variables that are accessible to all members of the class

// USED LATER FOR OPENING A FILE HAVING CONTACT DETAILS
string fileName;
// POINTER TO BST HAVING CLASS CONTACT AS NODE
BinarySearchTree<Contact> *treePhoneBook;
int found = 0;
int main()
{
    // THIS FUNCTION IS USED FOR ADDING COLOUR TO THE TEXT(YELLOW)
    // USED WINDOWS.H library for this
    system("Color 0E");
    char role = '1', passChar;
    string pass = "mte-project";
    cout << "\n\n\n\t\t\t\t\t\t\t  --------------------My Phonebook Application------------------" << endl;
    cout << "\n\n\t\t\t\t\t\t\t|                                                                 |" << endl;
    cout << "\t\t\t\t\t\t\t|                                                                 |" << endl;
    cout << "\t\t\t\t\t\t\t|                            MADE BY                              |" << endl;
    cout << "\t\t\t\t\t\t\t|                                                                 |" << endl;
    cout << "\t\t\t\t\t\t\t|                	   LAKSHAY CHANDRA                 |" << endl;
    cout << "\t\t\t\t\t\t\t|                                                                 |" << endl;
    cout << "\t\t\t\t\t\t\t|                                                                 |" << endl;
    while (role == '1')
    {
        cout << "\t\t\t\t\t\t                    Please choose a role : 1. Admin  2. User " << endl;
        cin >> role;
        if (role == '1')
        {
            string passCheck;
            cout << "Enter password : ";
            passChar = _getch();
            while (passChar != 13)
            {
                passCheck.push_back(passChar);
                cout << "*";
                passChar = _getch();
            }
            if (passCheck == pass)
                break;
            else
                cout << "\nWrong password" << endl;
        }
    }
    string signIn = role == '1' ? "Admin" : "User";
    cout << "\nSigned in as " << signIn << endl;
    cout << "\t\t\t\t\t\t\t                     Please choose an operation: " << endl;

    // HERE WE CREATE A BINARY SEARCH TREE BASED DIRECTORY
    BinarySearchTree<Contact> directory;

    // DIRECTORY CREATED POINTS TO PHONEBOOK TREE
    treePhoneBook = &directory;

    // RUN VARIABLE MADE SO THAT PROGRAM DOES NOT END AFTER ANY ABSURD COMMAND
    bool run = true;

    // USED FOR OBTAINING CHAR FROM USER TO PERFORM A COMMAND
    char userRequest;

    // RUNS IN A LOOP UNTIL SOMEONE ENTERS Q/q/7
    while (run)
    {
        // USED FOR OBATAING CHAR FROM USER
        userRequest = operationPrompt();
        switch (userRequest)
        {
        case 'A':
        case 'a':
        case '1':
        {

            // get user input, name and phone#
            string contact_name, contact_phone;
            cout << "\nEnter name : ";
            getline(cin >> ws, contact_name);
            cout << "\nEnter phone : ";
            getline(cin >> ws, contact_phone);
            cout << endl;

            // break user name input into fname and lname
            string firstName, lastName;
            istringstream iss(contact_name);
            iss >> firstName;
            iss >> lastName;

            // check validity of user input
            while (!nameValidity(firstName) || !nameValidity(lastName) || !phoneValidity(contact_phone))
            {
                cout << "Please re-enter information" << endl;
                cout << "Enter name:";
                getline(cin >> ws, contact_name);
                cout << "Enter phone:";
                getline(cin >> ws, contact_phone);
                cout << endl;
                istringstream iss(contact_name);
                iss >> firstName;
                iss >> lastName;
            }

            // if user's input is valid, insert into tree
            Contact person_new(firstName, lastName, contact_phone);
            treePhoneBook->insert(person_new);
        }
        break;

        case 'L':
        case 'l':
        case '2':
        {
            // USED FOR LOADING INFORMATION FROM ANY FILE HAVING LIST OF DETAILS AND APPEND EVERY CONTACT TO THE BST IN LEXICOGRAPHICAL ORDER
            loadTree();
            cout << endl;
        }
        break;

        case 'S':
        case 's':
        case '3':
        {

            // GETTING USER INPUT FOR NAME TO SEARCH
            string contact_name, contact_phone;
            cout << "Enter name:";
            getline(cin, contact_name);

            string firstName, lastName;
            // ISTRINGSTREAM IS USED FOR BREAKING INTO FIRST NAME AND LAST NAME HAVING SPACE BETWEEN THEM
            istringstream iss(contact_name);
            iss >> firstName;
            iss >> lastName;

            // WE CHECK NAME VALIDITY FOR FIRST AND LAST NAME SUCH THAT NAME HAVE ALPHABTES ONLY
            while (!nameValidity(firstName) || !nameValidity(lastName))
            {
                cout << "Kindly re-enter information" << endl;
                cout << "Enter name:";
                getline(cin, contact_name);
                istringstream iss(contact_name);
                iss >> firstName;
                iss >> lastName;
            }
            // SEARCH CONTACT FUNCTION CALLED IF CONTACT EXIST IN BST THEN NAME AND CONATCT PRINTED ELSE SHOWS USER NOT PRESENT
            cout << searchContact(firstName, lastName) << endl;
            cout << endl;
        }
        break;

        case 'P':
        case 'p':
        case '4':
        {

            // USED FOR PRINTING ALL CONTACTS PRESEN IN BST IN LEXICOGRAPHICAL ORDER( ASCENDING ORDER) AS INORDER FOR BST IS ASCENDING ORDER
            treePhoneBook->inOrder();
            // USED FOR CALCULATING TOTAL NUMBER OF RECORDS PRESENT IN BST
            int contacts = treePhoneBook->nodeCount();
            cout << contacts;
            cout << " contacts present ...\n\n";
        }
        break;

        case 'F':
        case 'f':
        case '5':
        {

            string contact_name;
            cout << "Enter name to filter : ";
            getline(cin, contact_name);
            cout << endl;
            string firstName, lastName;
            // USED FOR BREAKING NAME
            istringstream iss(contact_name);
            iss >> firstName;
            iss >> lastName;

            // CHECK VALIDIITY
            while (!nameValidity(firstName) || !nameValidity(lastName))
            {
                cout << "Please re-enter information" << endl;
                cout << "Enter name: ";
                getline(cin, contact_name);
                istringstream iss(contact_name);
                iss >> firstName;
                iss >> lastName;
            }

            Contact person(firstName, lastName, "");

            // FIRST WE CHECK IF THE CONTACT ACTUALLY EXISTS
            person = treePhoneBook->search(person);
            if (person.getContactPhone() == "")
            {
                cout << "Contact doesn't exist in PhoneBook" << endl;
                cout << endl;
            }
            else
            {

                // IF CONTACT TO FILTER ARE LESS THAN TOTAL THEN PRINT FILTERED CONTACTS
                // IMPLEMENTED USING LINKED LIST
                LinkedList<Contact> *list = new LinkedList<Contact>();
                treePhoneBook->filter(person, list);
                cout << *list;
                // print number of contacts that appear before contact to filter by
                cout << list->length() << " Contacts present before " << firstName + " " + lastName << endl;
                cout << endl;
            }
        }
        break;

        case 'D':
        case 'd':
        case '6':
        {
            if (signIn == "Admin")
            {
                string contact_deleteName;
                cout << "\nEnter name of contact to delete : ";
                getline(cin >> ws, contact_deleteName);
                cout << endl;
                string fname, lname; // break user input into fname and lname
                istringstream iss(contact_deleteName);
                iss >> fname;
                iss >> lname;

                while (!nameValidity(fname) || !nameValidity(lname))
                {
                    cout << "\nPlease re-enter information" << endl;
                    cout << "Enter name: ";
                    getline(cin, contact_deleteName);
                    istringstream iss(contact_deleteName);
                    iss >> fname;
                    iss >> lname;
                }
                // FIRST CHECK IF EVEN THE CONTACT EXISTS OR NOT THEN DELETE
                // FOR DELETION WE CHOSSE THE INORDER SUCCESSOR OR PREDESSOR BASED ON HEIGHT OF THAT BRANCH OF TREE
                // WE TAKE LONGER BRANCH SO AS TO MAKE THE TREE MORE BALANCED
                cout << searchContact(fname, lname) << endl;
                cout << endl;
                if (found == 1)
                {
                    Contact person(fname, lname, "");
                    treePhoneBook->delete_node(person);
                    cout << "Contact deleted successfully\n";
                }
            }
            else
            {
                cout << "\nSorry sir! You are not authorised to delete contacts.\n"
                     << endl;
            }
        }
        break;

        case 'U':
        case 'u':
        case '7':
        {
            if (signIn == "User")
            {
                cout << "\nSorry sir! Only admins can update contacts.\n"
                     << endl;
                break;
            }
            string updateName, first_name, last_name, new_number;
            cout << "\nEnter name of contact to update : ";
            getline(cin >> ws, updateName);
            istringstream iss(updateName);
            iss >> first_name;
            iss >> last_name;
            searchContact(first_name, last_name);
            if (found == 0)
                cout << "\nContact not found " << endl
                     << endl;
            else
            {
                cout << "\nEnter new number : ";
                getline(cin >> ws, new_number);
                Contact person(first_name, last_name, new_number);
                treePhoneBook->update_number(person);
                cout << endl;
            }
        }
        break;

            break;
        case 'Q':
        case 'q':
        case '8':
        {
            // STOPS THE LOOP
            run = false;
            cout << "Good Bye!" << endl;
            cout << "Thankyou for being patient and using this program" << endl;
            return 0;
        }

        default:
            cout << "\nPlease, try again.\n";
        }
    }
}

/*
 * Prints operation prompt
 */
char operationPrompt()
{
    char userWants;
    cout << "1. A (Add) \n2. L (Load) \n3. S (Search) \n4. P (Print) \n5. F (Filter)\n6. D (Delete contact)\n7. U (Update Contact)\n8. Q (Quit): \n";
    cin >> userWants;
    cin.ignore();
    return userWants;
}

/*
 * This method load's the BST via the text file
 */
void loadTree()
{

    //    string fileName;
    cout << "Enter file name: ";
    cin >> fileName; // get the file name

    ifstream myFile("C:/Users/Lakshay/Myfiles/Phonebook Final/" + fileName);
    if (myFile.is_open())
    {

        while (!myFile.eof())
        { //

            string Fname = "";
            string Lname = "";
            string phone = "";

            myFile >> Fname; // get first name
            myFile >> Lname; // get last name
            myFile >> phone; // get phone

            // if file has no empty lines, add them to tree, if empty line, go to next line
            if (Fname != "" && Lname != "" && phone != "")
            {
                Contact person = Contact(Fname, Lname, phone);
                if (nameValidity(Fname) && nameValidity(Lname) && phoneValidity(phone))
                    treePhoneBook->insert(person); // add the person to the tree
            }
        }
        myFile.close();
    }
    else
        cout << "Unable to open file" << endl;
}

/*
 * This method searches for a specific contact within the BST
 */
string searchContact(string &fname, string &lname)
{

    Contact person = Contact(fname, lname, "");
    person = treePhoneBook->search(person);
    found = 0;
    if (person.getContactPhone() == "")
    { // phone field wasn't updated
        found = 0;
        return "Sorry! Unable to find any contact with name " + person.getContactPhone();
    }
    else
    {
        found = 1;
        return "Phone: " + person.getContactPhone(); // return's person's phone number
    }
}

/*
 * Checks validity of user's input for names, input contains letters only
 * returns 1 if name contains letters only
 * returns 0 if name contains characters other than letters
 */
int nameValidity(string name)
{

    // Iterate through the string one letter at a time.
    for (int i = 0; i < name.length(); i++)
    {
        // Get a char from string
        // if it's NOT within these bounds, then it's not a character
        if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z')))
        {
            return 0; // number used instead of alphabet
        }
    }

    return 1; // all ok!
}

/*
 * This method checks if the phone number entered by the user is valid, input doesn't include letters
 *  returns 1 if phone contains numbers only
 * returns 0 if name contains characters other than numbers
 */
int phoneValidity(string phoneNumber)
{
    char c;
    if (phoneNumber.length() != 10)
        return 0;
    // Iterate through the string one number at a time.
    for (int i = 0; i < phoneNumber.length(); i++)
    {
        c = phoneNumber.at(i); // Get a char from string
        // if it's NOT within these bounds, then it's not a character
        if (!(c >= '0' && c <= '9'))
        {
            return 0; // number used instead of alphabet
        }
    }
    return 1; // all ok!
}