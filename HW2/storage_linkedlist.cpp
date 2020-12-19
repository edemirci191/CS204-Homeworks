//***********************************************
// This code is written by Emre Demirci, 26531
// Start Date : 2/18/2020 11:25 PM
// End Date   : 2/25/2020
// Known Bugs : when user enters a file name with space in it, it recognizes input as two seperate inputs
//				like "aaaaa bbbbb" is the file name program reads as "aaaaa" "bbbbb" and gives proper warning twice or more depending on the space used while entering
// Pre Scriptum: Some functions from linkedList.cpp and from lecture slides is used( i wrote proper message to specify which functions)
// Pre Scriptum: BubbleSorting is used in this program i did not write the sorting all by myself(copy pasted from internet). I wrote the swapping function inside the bubbleSort though.
//***********************************************
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;



struct node // constructors might be innecessary and confusing did not use it in the program but did not want to delete it as well...
{
	int month,year;
	int time;
	vector<string> cards;
	node* next;
	// default constructor
	node::node ()
		:month(0), year(0), time(month*year), cards(NULL), next(NULL)
	{}
	//constructor
	node::node (int month,int year)
		:time(month*year)
	{}	
};
//************************************************ Start: Define PROTOTYPES*************
int  FindCursor(node *list, node *cursor);
int  is_valid_card(const string &str);
int  is_int(const string &str);
bool isEmpty(node *head);
bool SearchList(node *head, int mnum , int ynum);
void menu();
void DeleteOneNode (node * toBeDeleted, node * & head);
void insertFirstElement(node *&head, node *&last, string cardnumber, int mnum, int ynum);
void insert(node *&head, node *&last, string cardnumber,int mnum, int ynum);
void Delete(node *&head, node *&last);
void showList(node *current);
void my_swap (node *node_1, node *node_2);
void bubble_sort(node *&head);
node * GetNthNode(node *head, int n);
node* detailed_list_search(node* head_ptr, int mnum, int ynum);
node* detailed_list_search_string(node* head_ptr, string number_of_card);
//************************************************ End: Define PROTOTYPES*****************

//************************************************ Start: Define function bodies **************************************************************
bool isEmpty(node *head)
{
	if(head == NULL)
		return true;
	else
		return false;
}

void menu()
{
	cout << "1. Display List" << endl;
	cout << "2. Card search via credit number " << endl;
	cout << "3. Delete card with respect to expiration date" << endl;
	cout << "4. Exit" << endl;
}
void insertFirstElement(node *&head, node *&last, string cardnumber, int mnum, int ynum) // inserts the first node to a non existing linkedlist (creates the start of a linked list)
{
	node *temp = new node;
	temp -> cards.push_back(cardnumber);
	temp -> year = ynum;
	temp -> month = mnum;
	temp -> next = NULL;
	head = temp;
	last = temp;
}
void insert(node *&head, node *&last, string cardnumber, int mnum, int ynum) // inserts node to a linkedlist 
{
	if(isEmpty(head))
		insertFirstElement(head,last,cardnumber,mnum,ynum);
	else
	{
	node *temp = new node; // create

	temp -> cards.push_back(cardnumber);
	temp -> year = ynum; // fill
	temp -> month = mnum;

	temp -> next = NULL;

	last -> next = temp;
	last = temp;
	}

}


void swapper (node *node_1, node *node_2) // swaps the values of 2 nodes 
{
	int tempm = node_1->month;
	int tempy = node_1->year;
	vector<string> tempc = node_1->cards;
	int temptime = node_1->time;

	node_1->month = node_2 -> month;
	node_1->year = node_2 ->year;
	node_1->cards = node_2 ->cards;
	node_1->time = node_2->time;

	node_2 -> time = temptime;
	node_2 -> month = tempm;
	node_2 -> cards = tempc;
	node_2 -> year = tempy;
}

void bubble_sort(node *&head) //This function is mostly based on a function i found on internet, i updated it (did not write it all myself),
{
	int swapped;

	node *lPtr; // left pointer will always point to the start of the list
	node *rPtr = NULL; // right pointer will always point to the end of the list
	do
	{	
		swapped = 0;
		lPtr = head;
		while(lPtr->next != rPtr)
		{
			if (((lPtr->year) > (lPtr->next->year)))
			{
				swapper(lPtr, lPtr->next);  //swapper function is written by me, found a example on internet and wrote it from the beginning for my code
                swapped = 1; 
			}
			if(((lPtr->year) == (lPtr->next->year)))
			{
				if(((lPtr ->month) > (lPtr->next->month)))
				{
					swapper(lPtr, lPtr ->next);
					swapped = 1;
				}
			}
			lPtr = lPtr->next;
		}
		//as the largest element is at the end of the list, assign that to rPtr as there is no need to
		//check a already sorted list
		rPtr = lPtr;

	}while(swapped);
}



void Delete(node *&head, node *&last) // deletes given node in linkedlist head being the firs node, last being the last node
{
	if(isEmpty(head))
		cout << "List is empty! " << endl;
	else if (head == last)
	{
		delete head;
		head = NULL;
		last = NULL;
	}
	else
	{
		node *temp = head;
		head = head -> next;
		delete temp;
	}
}
void showList(node *current) // prints the linkedlist as wanted
{
	
	if(isEmpty(current))
	{
		cout << "List is empty! \n";
	}
	else
	{
		cout << " The list contains: \n";
		while( current != NULL)
		{
			cout << "Expiration date " << current -> month <<" "<<  current -> year << endl;
			for(int i = 0; i < current -> cards.size() ; i++) 
			{
				cout << i + 1 << ")" <<" " << current -> cards[i] << endl;
			}
			current = current -> next; 
			cout <<"-------------------" << endl;
			cout << endl;
		}
	}
}

ifstream File_Check(string File_Name)
{
	ifstream txtfile;
	do{
	cout << "Please enter file name: ";
	cin >> File_Name;
	cout << endl;
	txtfile.open(File_Name.c_str());
	if(txtfile.is_open() != true)
		{
			cout << "Cannot find a file named " << File_Name << endl ;
		}
}while(txtfile.is_open() != true);

return txtfile;
}


int is_int(const string &str) // for checking invalid inputs
{
    return str.find_first_of("QWERTYIOPASDFGHJKLZXCVBNMqwertyuopasdfghjklizxcvbnm!'^+%&/()=?_");// assumed that user will only enter english chars even if it is invalid
}

bool  SearchList(node *head, int mnum , int ynum) //* Begin: code taken from linkedList.cpp
{
	int n = 0;
	while (head != NULL)
	{
		if(head->month == mnum && head -> year == ynum)//If the node is found
		{ 
			return true ;
		}

		head = head->next;
		n++;
	}
	return false;
	//If the code proceeds from here, it means that the whole list is traversed 
	//and a node with ID == searchValue could not be found. 
} //* End: code taken from linkedList.cpp


 node* detailed_list_search(node* head_ptr, int mnum, int ynum) // searches by month and date
 {
 node *cursor;
	for(cursor = head_ptr; cursor !=NULL; cursor = cursor->next)
		{
			if(mnum == cursor->month && ynum == cursor->year)
			{
				return cursor;
			}
		}
 return NULL;
 }

  node* detailed_list_search_string(node* head_ptr, string number_of_card) // searches by given string 
 {
 node *cursor;
	for(cursor = head_ptr; cursor !=NULL; cursor = cursor->next)
		{
			
			for(int i = 0; i <  cursor -> cards.size() ; i++)
			{
				if(number_of_card == cursor->cards[i])
				{
					return cursor;
				}

			}
		}
 return NULL;
 }
/*Begin code taken from linkedList.cpp
Returns the nth node in the list. If the total number of nodes 
in the list is smaller than n, it returns null */
node * GetNthNode(node *head, int n)
{
	int counter=0;
	node *ptr = head;
	while (ptr != NULL && counter<n-1)
	{ 
		ptr = ptr->next;
		counter++;
	}
	return ptr;
} // end code taken from linkedList.cpp */

int  FindCursor(node *list, node *cursor) // given the start of  my linkedlist(list) "head" in my program is the start cursor is the node we are looking for  
{
	int counter=0;
	node *ptr = list;
	while (ptr != cursor)
	{ 
		ptr = ptr->next;
		counter++;
	} // so everytime ptr becomes next counter is incremented by one so if what i am looking is the 4th node from the beginning then counter becomes 4 
	return counter; // tells you the location of cursor (node) from the beginning of the linkedlist
}



void DeleteOneNode (node * toBeDeleted, node * & head) //*************** taken from lecture slayts(2.2 pointers linkedlists) start here 
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node * ptr;
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{     head = head->next;
		delete toBeDeleted;
	}
	else  //if the node to be deleted is in the middle or at the end
	{     ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		//after while, ptr points to the node just before toBeDeleted

		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
} //************************************************************************ taken from lecture slayts(2.2 pointers linkedlists ends here

int is_valid_card(const string &str) // for checking invalid inputs for card number
{
    return str.find_first_not_of("0123456789"); // if finds return the index, if nothing is found except 0123456789 it returns string::npos
}
//************************************************ End: Define function bodies **************************************************************
int main()
{

node *head = NULL; // to avoid memory leakage
node *tail = NULL;
node *current = NULL;

int counter = 0;
string choice = "5"; // could be anything except 1,2,3,4,
string File_Name, inside_of_file,card_number,month,year_in_file;

ifstream txtfile2; // to read file 
ifstream (*p)(string); // from the pointer function

p = File_Check;
txtfile2 = p(File_Name);

bool first_element_inserted= false;
bool dontenter = false;
bool not_empty = true;
//**************************************** File processing
if(txtfile2.peek() == std::ifstream::traits_type::eof()) not_empty = false; // checks if file is empty basically peeks* 
while( not_empty == true && !txtfile2.eof() ) // while not_empty == true because otherwise it gives error
{
	dontenter = false;
	int month_int;
	int year_int;
	getline(txtfile2, inside_of_file);
	istringstream inside_of_file_line(inside_of_file);
	inside_of_file_line >> card_number >> month >> year_in_file;
	month_int = stoi(month);
	year_int = stoi(year_in_file);
	
	if(first_element_inserted == false) // first goes in this one and then never goes in this one again its a special case for the first node
	{
		insert(head,tail,card_number,month_int,year_int);// insert first element
		cout <<"New node with expiration date " << month_int << " " << year_int << endl;
		cout <<"Credit card " <<  card_number << " is added to node " << month_int <<" "<< year_int << endl;
		cout <<"***************" << endl;
		cout << endl;

		dontenter = true;
		first_element_inserted = true;

		current = head;
	}
	if(dontenter == false) // getting in in the second while loop second line of txt file now 
	{
		current = head;
		if(SearchList(head,month_int,year_int))// number in the while looop(text) already existed in the previously added elements
		{
			cout <<"Node with expiration date " << month_int << " " << year_int << " already exists"  << endl;
			cout <<"Credit card " << card_number << " is added to node " << month_int << " " << year_int <<  endl;
			cout <<"***************" << endl;
			cout << endl;
			int pos = FindCursor(head,detailed_list_search(head,month_int,year_int)); // tells me where i want to add gives me index in other words
			for(int i = 0 ; i < pos ; i++) // starts from the beginning goes until the right node and then exits the loop
			{
				if(current->next != NULL) // just to make sure not get "access violation" error
				{
					current = current ->next; // and point to the next one 
				}
			}
			current->cards.push_back(card_number);	// now current is the node we are looking for
		}
		else // a node could not be found in the list with given month and year so we are adding one to the end
		{
		
		insert(head,tail,card_number,month_int,year_int); 
		cout <<"New node with expiration date " << month_int << " " << year_int << endl;
		cout <<"Credit card " <<  card_number << " is added to node " << month_int <<" "<< year_int << endl;
		cout <<"***************" << endl;
		cout << endl;
		}

	
	}
	counter++;
}
if( not_empty == true)
{
	bubble_sort(head); // sorting linkedlist by date after everything is set 
}

while(choice != "4")
{
cout << endl;
menu(); // showing options to choose for user 
cin >> choice; 

while(choice.find_first_not_of("1234") != string::npos)
{
	cout << " Invalid input, you must enter 1 or 2 or 3 or 4 " << endl;
	menu();
	cin >> choice;
}

if(choice == "1")
{
	if(isEmpty(head))
	{
		cout << " List is empty" << endl;
	}
	else
	{
		showList(head);
		cout << endl;
	}
}

if(choice == "2") 
{
	bool valid_user_card = true;
	string user_input_card;
	do{
		cout << "Please enter the credit card number: ";
		cin >> user_input_card;
		if((is_valid_card(user_input_card) != string::npos) && (user_input_card.length() != 16)) // if it is not size of 16 and if it does not only contains numbers enter this if statement
			{
				cout << "Invalid format! " << endl;
				valid_user_card = false;

			}
		else
			{
				valid_user_card = true;
			}
	}while(valid_user_card == false);
	if(detailed_list_search_string(head,user_input_card) != NULL) // if this card number exists
	{
		cout << "There exist a credit card given number " << user_input_card << " with expiration date : " << endl; // print that cards number
		cout << detailed_list_search_string(head,user_input_card)->month << " " << detailed_list_search_string(head,user_input_card)->year << endl; // and print the month and year of that node that matches the card number that user entered
	}
	else
	{
	cout << "There is no credit card with given credit number: " << endl;
	cout << user_input_card << endl;
	}

}

if(choice == "3")
{
string input_month;
string input_year;
int int_input_month;
int int_input_year;
bool month_valid = true;
bool year_valid = true;
do{
month_valid = true;
year_valid = true;
cout << "Please enter month and year: ";
cin >> input_month >> input_year; // taking input as strings so i can check later 

if(is_int(input_month) == string::npos)
{ 
	int_input_month = stoi(input_month);
}
else
{
	month_valid = false;
}
if(is_int(input_year) == string::npos)
{ 
	int_input_year = stoi(input_year);
}
else
{
	year_valid = false;
}
if( (int_input_month > 12) || (int_input_month < 0)) // month cant be bigger than 12 or smaller than 0
{
	month_valid = false;
}

if((year_valid == true) && (month_valid == true) && (detailed_list_search(head,int_input_month,int_input_year) != NULL)) // if there exists a card with given month and year
{
	cout << "Node with expiration date " << int_input_month << " " <<  int_input_year << " and the following credit cards have been deleted!" << endl;
	for(int i = 0; i <  detailed_list_search(head,int_input_month,int_input_year) -> cards.size() ; i++) // for loop because our storage is in vectors that is why i am checking every element in that vector
			{
				cout << i + 1 << ")" <<  detailed_list_search(head,int_input_month,int_input_year)-> cards[i] << endl; // finds the node with given month and year and then accesses to card number in that node ( -> cards[i])
			}
	DeleteOneNode(detailed_list_search(head,int_input_month,int_input_year),head);// equivalent of: DeleteOneNode( node you are looking for , and start of the node )
	showList(head); // and then show the new linkedlist
}
else if((year_valid == true) && (month_valid == true))
{
	cout << "There is no node with expiration date " << int_input_month << " " << int_input_year << ", nothing deleted! " << endl;
}
else
{
cout << "Invalid Date!" << endl;

}
	
}while(year_valid == false || month_valid == false);
}
}

cout << "Terminating!!!" << endl;

delete head; // deleting to avoid memory leakage after the execution is over
delete tail;
delete current;

return 0;
}
