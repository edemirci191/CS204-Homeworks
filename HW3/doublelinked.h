//***********************************************
// This code is written by Emre Demirci, 26531
// Start Date : Unknown
// End Date   : 3/11/2020 8:14PM
// Pre Scriptum: I used some functions(updated versions mostly) from the previous homework (homework 2)
// main structure of header file was given in the homework document
//***********************************************
#ifndef _DOUBLELINKED_H
#define _DOUBLYLINKED_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>



using namespace std;

struct creditCardexpirationNodes  
{ 
 string creditCardNo; 
 creditCardexpirationNodes * next; 
	//*********** Start: added by me *************
	creditCardexpirationNodes :: creditCardexpirationNodes()
	{}
	creditCardexpirationNodes::creditCardexpirationNodes(string creditCardno, creditCardexpirationNodes * nxt)
		:creditCardNo(creditCardno), next(nxt)
	{}
	//*********** End: added by me *****************
};

struct expirationNodes 
{ 
 int month, year,data; // data is added by me
 creditCardexpirationNodes * cHead; 
 expirationNodes * next; 
 expirationNodes * prev; 
	// ************* Start: added by me **************
	expirationNodes::expirationNodes()
		:month(0),year(0),next(NULL),prev(NULL),cHead(NULL), data()
	{}
	expirationNodes::expirationNodes(int month,int year,expirationNodes * nxt,expirationNodes * prv, creditCardexpirationNodes * head)
		 :month(month),year(year), next(nxt), prev(prv), cHead(head), data((year*365)+(month*30))
	{}
	// ************* End: added by me ****************
}; 

class CardList  
{ 
public: 
	CardList(); 
	void insertCardSorted (string creditCardNo, int month, int year); 
	void displayListChronological (); 
	void displayListReverseChronological (); 
	void cardSearch (string creditCardNo); 
	void bulkDelete (int month, int year); 
	void deleteAll ();
	//**********Start: added by me *****************
	void CardList::bubble_sort(expirationNodes *&headf);
	void CardList:: swapper (expirationNodes *node_1, expirationNodes *node_2);
	void CardList::sort_card_nums(creditCardexpirationNodes *&head);
	void CardList:: swapper_cardnums (creditCardexpirationNodes *node_1, creditCardexpirationNodes *node_2);
	expirationNodes* CardList:: detailed_list_search(expirationNodes* head_ptr, int mnum, int ynum);
	creditCardexpirationNodes* CardList:: detailed_list_search_inside(creditCardexpirationNodes* head_ptr, string cnum);
	//*********** End: added by me *******************

private: 
	expirationNodes * head; 
	expirationNodes * tail; 
	creditCardexpirationNodes *last; // to keep track of singly linked list, added by me
 
};
#endif