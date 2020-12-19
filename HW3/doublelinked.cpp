//**********************************************************
// This program is written by Emre Demirci, 26531
// Hybrid 2-D linkedlist class (linkedlist of linkedlist)
// Memory Leakage : possible but not expected
// Pre Scriptum: I used some functions(updated versions mostly) from the previous homework (homework 2)
//**********************************************************

#include <iostream>
#include "doublelinked.h"

using namespace std;


CardList::CardList()//default constructor that creates an empty list 
{
	head = NULL;
	tail = NULL;

}


void CardList:: swapper (expirationNodes *node_1, expirationNodes *node_2) // swaps the values of 2 nodes 
{
	int tempm = node_1->month;
	int tempy = node_1->year;
	creditCardexpirationNodes *tempc = node_1->cHead;
	node_1->month = node_2 -> month;
	node_1->year = node_2 ->year;
	node_1->cHead = node_2 ->cHead;
	node_2 -> month = tempm;
	node_2 -> year = tempy;
	node_2->cHead = tempc;
}

void CardList:: swapper_cardnums (creditCardexpirationNodes *node_1, creditCardexpirationNodes *node_2) // swaps the values of 2 nodes 
{
	string tempm = node_1->creditCardNo;
	node_1->creditCardNo = node_2 -> creditCardNo;
	node_2 -> creditCardNo = tempm;

}

void CardList::bubble_sort(expirationNodes *&head)
{
int swapped;

	expirationNodes *lPtr; // left pointer will always point to the start of the list
	expirationNodes *rPtr = NULL; // right pointer will always point to the end of the list
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

void CardList::sort_card_nums(creditCardexpirationNodes *&head1)
{
int swapped;
	creditCardexpirationNodes *lPtr; // left pointer will always point to the start of the list
	creditCardexpirationNodes *rPtr = NULL; // right pointer will always point to the end of the list
	do
	{	
		swapped = 0;
		lPtr = head1;
		while(lPtr->next != rPtr)
		{
			long long int a = std::stoll(lPtr->creditCardNo); // for better memory management i choose "long long int " not " unsigned long long it"
			long long int b = std::stoll(lPtr->next->creditCardNo); 
			if (a > b)
			{
				swapper_cardnums(lPtr, lPtr->next); 
				swapped = 1; 
			}
			lPtr = lPtr->next;
		}
		rPtr = lPtr;
	}while(swapped);
}



 expirationNodes* CardList:: detailed_list_search(expirationNodes* head_ptr, int mnum, int ynum) // searches by month and date
 {
 expirationNodes *cursor;
	for(cursor = head_ptr; cursor !=NULL; cursor = cursor->next)
		{
			if(mnum == cursor->month && ynum == cursor->year)
			{
				return cursor;
			}
		}
 return NULL;
 }


 creditCardexpirationNodes* CardList:: detailed_list_search_inside(creditCardexpirationNodes* head_ptr, string cnum) 
 {
 creditCardexpirationNodes *cursor;
	for(cursor = head_ptr; cursor !=NULL; cursor = cursor->next)
		{

			if(cnum == cursor->creditCardNo )
			{
				return cursor;
			}
		}
 return NULL;
 }


void CardList::insertCardSorted (string creditCardNo, int month, int year) //inserts a new card to the structure in sorted fashion 
{
	creditCardexpirationNodes *head2 = NULL;
	if(head == NULL)
	{
		expirationNodes *temp1 = new expirationNodes;
		
		temp1->month = month;
		temp1->year = year;
		temp1-> next = NULL;
		temp1-> prev = NULL;
		head= temp1;
		tail = temp1;

		temp1->cHead =  new creditCardexpirationNodes;
		temp1->cHead->creditCardNo = creditCardNo;
		temp1 ->cHead->next = NULL;
		head2 = temp1->cHead;
		last = temp1->cHead;

	}
	else
	{
		if(detailed_list_search(head,month,year) == NULL)
		{
			expirationNodes *temp = new expirationNodes;

			temp->month = month;
			temp -> year = year;
			temp->next = NULL;
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			if(temp->cHead == NULL)
			{
				temp->cHead =  new creditCardexpirationNodes;
				temp->cHead->creditCardNo = creditCardNo;
				temp ->cHead->next = NULL;
				head2 = temp->cHead;
				last = temp->cHead;
		
			}
			else
			{
				temp -> cHead -> creditCardNo = creditCardNo;
				temp ->cHead ->next = NULL;
				last->next = temp->cHead;
				last = temp->cHead;
			}
			cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
			bubble_sort(head);// sort outer layer as new outer node added
		}
		else 
		{
			if(detailed_list_search_inside(detailed_list_search(head,month,year)->cHead,creditCardNo) == NULL)
			{
				creditCardexpirationNodes *tmp = new creditCardexpirationNodes;
				tmp->creditCardNo = creditCardNo;
				tmp->next = NULL;
				creditCardexpirationNodes * ptr = detailed_list_search(head,month,year)->cHead;
				while(ptr ->next != NULL)
				{
					ptr = ptr->next;
				}
				ptr->next = tmp; 
				cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
			}
			else
			{
				cout << creditCardNo << " " << month << " " << year << ": this card was already inserted" << endl;
			}
		}
		sort_card_nums(detailed_list_search(head,month,year)->cHead);
	}
}
 
void CardList::displayListChronological() //displays entire structure in chronological order 
{
	expirationNodes *right = head;
	creditCardexpirationNodes * down = NULL;
	if(right == NULL)
	{
		cout << "List is empty! \n";
	}
	else
	{
		while( right != NULL)
		{
			int i = 1 ;
			cout << "Expiration date " << right -> month <<" "<< right -> year << endl;
			down = right->cHead;
			while(down != NULL)
			{
				cout << i << ") " << down->creditCardNo << endl; 
				down = down->next;
				i++;
			}
			right = right -> next; 
			cout << "----------------" << endl;
		}
	}
}

void CardList::displayListReverseChronological () //displays entire structure in reverse chronological order 
{
	expirationNodes *right = tail;
	creditCardexpirationNodes * down = NULL;
	if(right == NULL || head == NULL)
	{
		cout << "List is empty! \n";
	}
	else
	{
		while( right != NULL)
		{
			int i = 1 ;
			cout << "Expiration date " << right -> month <<" "<<  right -> year << endl;
			down = right->cHead;
			while(down != NULL)
			{
				cout << i << ") " << down-> creditCardNo << endl;
				down = down->next;
				i++;
			}
			right = right -> prev; 
			cout << "----------------" << endl;
		}
	}

}

void CardList::cardSearch (string creditCardNo) //displays all of the occurrences of the given card number
{
	bool found = false;
	bool invalid = false;
	expirationNodes * current = head;
	creditCardexpirationNodes * current2 = NULL;
	if(creditCardNo.size() != 16)
	{
		invalid = true;
	}
	else if(creditCardNo.find_first_not_of("1234567890") != string::npos)
	{
		invalid = true;
	}
	if(invalid == false)
	{
		for( current; current != NULL; current = current->next)
		{
			for( current2 = current->cHead; current2 != NULL; current2 = current2->next)
			{
				if(creditCardNo == current2->creditCardNo)
				{
					cout << "There exists a credit card given number " << creditCardNo << " with expiration date: " << current->month << " " << current -> year << endl; 
					found = true;
				}
			}
		}}
		if(invalid)
		{
			cout << "Invalid format !" << endl;
		}
		if (found == false && !invalid)
		{
			cout << " There is no credit card with given credit card number: " << creditCardNo << endl;
		}

	
}
 
void CardList::bulkDelete (int month, int year) //deletes all expirationNodess up to and including given expiration date
{
		bool enter = true;
		expirationNodes * mr_muscle = NULL;
		creditCardexpirationNodes * eraser = NULL;
		if(head != NULL && tail != NULL)
		{
			if( (tail->year* 365 + tail->month *30) < (month*30 + year*365)) // if entered month and year is greater than the last elements month and year delete all ( it is sorted by date so bigger than every other node )
			{ 
				month = tail->month;
				year = tail->year;
			}
		}
		if(head == NULL) cout << "List is empty! " << endl; // if empty print and dont continue
		if(head != NULL) // if not empty (linkedlist)
		{
			while( ((head->year * 365) + (head->month *30)) < ((year*365)+(month*30)) && (head != detailed_list_search(head,month,year)) ) // move forward until you hit the end also check if current node dates are smaller than given value
			{
					if(head)
				{
				int i = 1;
				cout << "Node with expiration date " << head->month << " " << head->year << " and the following credit cards have been deleted ! " << endl;
				while(head->cHead)
				{
					eraser = head->cHead;
					head->cHead = head->cHead->next;
					cout << i << ") "<<  eraser->creditCardNo<< endl;
					delete eraser; // delete inside layers before deleting the outer layers ( mr_muscle)
					i++;
				}
				mr_muscle = head; 
				head = head -> next;
				head->prev = NULL;
				delete mr_muscle; // delete pointers in the outer layer after deleting inside layers
				}
			}

		// Below part is here for the last node i got error above so i decided to add this part, which takes care of it seperately
		int i2 = 1;
		if(detailed_list_search(head,month,year) != NULL)
		{
			cout << "Node with expiration date " <<head->month << " " << head->year << " and the following credit cards have been deleted ! " << endl;
		}
		if(detailed_list_search(head,month,year) == NULL) enter = false;
		if(enter)
		{
		while(detailed_list_search(head,month,year)->cHead)
			{
				eraser = head->cHead;
				head->cHead = head->cHead->next;
				cout << i2 << ") "<<  eraser->creditCardNo<< endl;
				delete eraser;
				i2++;
			}
			cout << endl;
			mr_muscle = head;
			head= head-> next;
			delete mr_muscle;
		}
		}
}


 
void CardList::deleteAll () //deletes the entire structure 
{
	expirationNodes * mr_muscle = NULL;
	creditCardexpirationNodes * eraser = NULL;
	while(head)
	{
		while(head->cHead)
		{
			eraser = head->cHead;
			head->cHead = head->cHead->next;
			delete eraser; // delete inner (singly) linkedlist first
		}
		mr_muscle = head;
		head = head -> next;
		delete mr_muscle; // and after deleting inners in the above while loop delete the outer (doubly) linkedlist
	}

}

