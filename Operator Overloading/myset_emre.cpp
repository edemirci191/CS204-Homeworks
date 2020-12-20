#include <iostream>
#include "myset_emre.h"
#include <iomanip>

using namespace std;

void IntegerSet::setElement(int index, int element)
{
	set[index] = element;
}

void IntegerSet::setSize(int psize)// set size of the vector
{
	size = psize;
	set = new int[size];
}

int IntegerSet::getSize()const
{
	return size;
}

int IntegerSet::getElement(int index)const
{
	return set[index];
}

IntegerSet::IntegerSet()
{
	size = 0;
	set = NULL;
}

IntegerSet::IntegerSet(int psize)// constructor with vector size
{
	set = new int[psize];
	size = psize;
}

IntegerSet :: IntegerSet(const IntegerSet & copy)
{
	size = copy.getSize();
	set = new int[size]; // deep copy

	for(int i = 0; i < size; i++)
	{
		set[i] = copy.set[i];
	}
}

IntegerSet :: IntegerSet(const IntegerSet & copy,int size_new) // copy constructor + add extra space (memory allocate for extra space)
{
	size = copy.getSize();
	set = new int[size_new]; // deep copy

	for(int i = 0; i < size; i++)
	{
		set[i] = copy.set[i];
	}
}

IntegerSet::~IntegerSet()
{
	size = 0;
	delete[] set;
}

ostream & operator<<(ostream &output, IntegerSet intset)
{
	if(intset.getSize() == 0) cout << "{}";
	if(intset.getSize() != 0)
		{
		output << "{" ;
		for(int j = 0; j < intset.getSize() ; j++)
			{
				output << intset.getElement(j);
				if( j != intset.getSize())
				{
				output << ", ";
				}
			}
		output << "}";
		}
	return output;
}

IntegerSet operator + (const IntegerSet & lhs,const IntegerSet & rhs)
{
	int counter = 0;
	int alloc_counter = 0;
	//*********************************************** gives how much memory do i need to allocate
	for(int i= 0; i < rhs.getSize(); i++)
	{
		int checker = 0;
		for( int j = 0; j < lhs.getSize(); j++)
		{
			if( rhs.getElement(i) == lhs.getElement(j))
			{
				checker = 1;
				break;
			}
		}
		if(checker = 0)
		{
			alloc_counter++;
		}
	}
	//******************************************** tells me how much memory do i need to allocate
	//******************************************** do the same loop, put the variables in the array
	// assume lhs is 123 and alloc counter is 2 
	IntegerSet result(lhs,alloc_counter); // this line creates an array like this 123__ with 2 extra spaces
	int index_counter = lhs.getSize(); // starts adding from this index
	for(int i= 0; i < rhs.getSize(); i++)
	{
		int checker = 0;
		for( int j = 0; j < lhs.getSize(); j++)
		{
			if( lhs.getElement(j) == rhs.getElement(i))
			{
				checker = 1;
				break;
			}
		}
		if(checker != 1) // if character rhs(i) is not in lhs
		{
			result.setElement(index_counter,rhs.getElement(i));
			index_counter++;
		}
	}
	return result;
}

//********************** Start: taken from MathVector.cpp and updated accordingly
const IntegerSet & IntegerSet :: operator = (const IntegerSet & rhs)
{
	if(this != &rhs)// if they are not equal to each other
	{
	size = 0;
	delete[] set;
	set = new int[rhs.getSize()];
	for(int i = 0; i < rhs.getSize();i++)
		{
			set[i] = rhs.getElement(i);
			//this->setElement(i,rhs.getElement(i));
		}
	return *this;
	}
	else
	{
		return *this;
	}
}
//******************* End: taken from MathVector.cpp and updated accordingly

 IntegerSet & IntegerSet :: operator + (int & rhs)
{
	bool jump = true;
	for(int i = 0; i < this ->getSize() ; i++)
	{
		if(this->getElement(i) == rhs)
		{
			jump = false;
		}
	}
	if(jump == false)
	{
		return *this;
	}
	if(jump == true)
	{
		int old_size = this->getSize();
		int new_size = this->getSize() + 1;

		IntegerSet temp(*this,this->getSize() + 1);// copy this plus allocate +1 int memory
		temp.setElement(new_size - 1,rhs);

		size = 0;
		delete [] set;
		set = new int [new_size];
		for(int i= 0; i < new_size ;i++)
		{
			set[i] = temp.getElement(i);
		}
		temp.~IntegerSet();
		return *this;
	}
} 

IntegerSet operator *  (const IntegerSet lhs,const IntegerSet & rhs)
{
	int alloc_counter = 0;
	for(int i = 0;i < lhs.getSize(); i++)
	{
		for(int j = 0; j < rhs.getSize(); j++)
		{
			if(lhs.getElement(i) == rhs.getElement(j))
			{
				alloc_counter++; // count how many spaces i need
			}
		}
	} 
	IntegerSet result(alloc_counter); // create object with that many spaces
	int index_chooser = 0;
	for(int i = 0;i < lhs.getSize(); i++)
	{
		for(int j = 0; j < rhs.getSize(); j++)
		{
			if(lhs.getElement(i) == rhs.getElement(j))
			{
				result.setElement(index_chooser,lhs.getElement(i)); // start putting from 0th index
				index_chooser++; // go to next index
			}
		}
	}
	return result;
} 

const IntegerSet & IntegerSet::operator+=(const IntegerSet & rhs)
{
int counter = 0;
	int alloc_counter = 0;
	//*********************************************** gives how much memory do i need to allocate
	for(int i= 0; i < rhs.getSize(); i++)
	{
		int checker = 0;
		for( int j = 0; j < this->getSize(); j++)
		{
			if( rhs.getElement(i) == this->getElement(j))
			{
				checker = 1;
				break;
			}
		}
		if(checker = 0)
		{
			alloc_counter++; // this is the number of elements that are different
		}
	}
	//******************************************** tells me how much memory do i need to allocate
	//******************************************** do the same loop, put the variables in the array
	// assume lhs is 123 and alloc counter is 2 
	IntegerSet result(*this,this->getSize() + alloc_counter); // this line creates an array like this 123__ with 2 extra spaces
	int index_counter = this->getSize(); // starts adding from this index
	for(int i= 0; i < rhs.getSize(); i++)
	{
		int checker = 0;
		for( int j = 0; j < this->getSize(); j++)
		{
			if( this->getElement(j) == rhs.getElement(i))
			{
				checker = 1;
				break;
			}
		}
		if(checker != 1) // if character rhs(i) is not in *this
		{
			result.setElement(index_counter,rhs.getElement(i));
			index_counter++;
		}
	}
	*this = result;
	return *this;
}

bool operator != (const IntegerSet & lhs,const IntegerSet&  rhs)
{
	long int checker = 0;
	if(lhs.getSize() != rhs.getSize())
	{
		return false;
	}
	else
	{
		for(int i= 0; i < lhs.getSize();i++)
		{
			for(int j = 0; j < rhs.getSize();j++)
			{
				if(lhs.getElement(i) == rhs.getElement(j))
				{
					checker++;
				}
			}
		}
		if(checker == lhs.getSize())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
}

bool operator <= (const IntegerSet & lhs,const IntegerSet & rhs)
{
	long int checker = 0;

	for(int i= 0; i < lhs.getSize();i++)
	{
		for(int j = 0; j < rhs.getSize();j++)
		{
			if(lhs.getElement(i) == rhs.getElement(j))
			{
				checker++;
			}
		}
	}
	if(checker == lhs.getSize())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator  <= (int & lhs , const IntegerSet set)
{
	for(int i = 0; i < set.getSize(); i++)
	{
		if(set.getElement(i) == lhs)
		{
			return true;
		}
	}
	return false;
}
