//***********************************************
// This program stores credit card information( number, month , year) in a given txt file using linkedlists
// This code is written by Emre Demirci, 26531
// Start Date : Unknown
// End Date   : 3/11/2020
// Known Bugs : None, however if user enters a number like 1830912809129381012 (above int capacity) than it gives debug error, can be handled by using long long int
//				did not fix it because i found it unnecessary and it uses more memory.
// Pre Scriptum: Some functions from linkedList.cpp and from lecture slides is used( i wrote proper message to specify which functions)
// Pre Scriptum: Some functions from my previous homework (edemirci_Demirci_Emre_Hw2.cpp) are also used and updated
//***********************************************

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>
#include "doublelinked.h"
using namespace std;

//********************** Start: function prototypes ************************
void menu();
void error();
//********************** End:   function prototypes ************************

//********************** Start: Define function bodies *********************
void menu()
{
	cout << "1) Upload Card(s)" << endl;
	cout << "2) Display List Chronological " << endl;
	cout << "3) Display List Reverse Chronological" << endl;
	cout << "4) Card Search " << endl;
	cout << "5) Bulk Delete " << endl;
	cout << "6) Exit" << endl;
} 

void error()
{
	cout << "Invalid operation" << endl;
}
//************************* End: Define function bodies***********************

//************************* Start: Main **************************************
int main(){

	bool dontenter = false;
	bool not_empty = true;
	string File_Name, inside_of_file,card_number,month,year_in_file;
	CardList object; // creating out main "structure(list)"
	int int_user_input = 8; // this value can be any integer but 6



	do{ // while input is not 6 ( user decides not the exit enter this loop
//***************************************** Start: Asking user for operation number *********************
		// check if given number is correct if not then ask again
		bool valid_input = false;
		string user_input;
		do{
			menu();
			cin >> user_input;
			if(user_input.find_first_not_of("123456") == string::npos) // if user enters anything rather than 1,2,3,4,5,6 then it is invalid
			{
				if(stoi(user_input) > 6) // user can enter valid too but what if enter something like 12, this part checks that also
				{ 
					valid_input = false;
					error();
					cout << endl;
				}
				else
				{
					valid_input = true;
				}
			}
			else
			{
				cout << "Invalid format! ";
				cout << endl;
			}
		}while(valid_input != true);
		int_user_input = stoi(user_input);

//********************************** End: Asking user for operation number *************************************************

//********************************** Start: Asking for file name, if int_user_input is 1************************************
		if(int_user_input != 6)
		{
			if(int_user_input == 1)
			{
				ifstream txtfile2; // to read file 
				bool opening= true;
				cout << "Please enter file name: ";
				cin >> File_Name;
				cout << endl;
				txtfile2.open(File_Name);
				if(!(txtfile2.is_open()))
				{ 
					opening = false;
					cout << "Could not find a file named " << File_Name << endl ;
				}
				if(opening){
					if(txtfile2.peek() == std::ifstream::traits_type::eof()) not_empty = false; // checks if file is empty basically peeks* 
					while( not_empty == true && !txtfile2.eof() ) 
					{

//******End: asking for file name, if int_user_input is 1 *******************

//****** Start: file reading into sstream ***************
						dontenter = false;
						int month_int;
						int year_int;
						getline(txtfile2, inside_of_file);
						istringstream inside_of_file_line(inside_of_file);
						inside_of_file_line >> card_number >> month >> year_in_file; // seperated
//******* End: file reading into ssteam ******************

						month_int = stoi(month);
						year_int = stoi(year_in_file); // converting
						object.insertCardSorted(card_number,month_int,year_int); // start adding nodes
					}
				}
			}
//*************************************** End: Asking for file name, if int_user_input is 1**************************************
			if(int_user_input == 2) // if input is 2 display list
			{
				object.displayListChronological();
			}
			if(int_user_input == 3) // if input is 3 display list in a reverse order
			{
				object.displayListReverseChronological();
			}
			if(int_user_input == 4) // if input is 4 search for card and print occurences
			{
				cout << "Please enter the credit card number: ";
				string creditcardnumber;
				cin >> creditcardnumber;
				cout << endl;
				object.cardSearch(creditcardnumber);
			}
			if(int_user_input == 5) // if input is 5 delete all the nodes until given month and year (included)
			{
				bool valid = true;
				cout << "Please enter month and year: ";
				string del_month, del_year;
				cin >> del_month >> del_year;
				if(del_month.find_first_not_of("1234567890") != string::npos || del_year.find_first_not_of("1234567890") != string::npos)
				{ 
					valid = false;
				}
				if(valid)
				{
					if(stoi(del_month) > 12 || stoi(del_month) < 0 )  valid = false;
				}
				if(valid)
				{
					object.bulkDelete(stoi(del_month),stoi(del_year));
				}
				else
				{
					cout << "Invalid format!" << endl;
				}

			}
			not_empty = true; // so if user first enters creditCards3.txt as file name it keeps accepting other file names 
		}
	}while(int_user_input != 6); // if input is 6 exit the loop

	object.deleteAll(); // Delete all pointers and return memory back to heap
	cout << "All the nodes have been deleted !" << endl;
	cout << "Terminating!!!" << endl;
	return 0;
}