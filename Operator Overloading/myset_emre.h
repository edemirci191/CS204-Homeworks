// Emre Demirci, 26531, cs204 - HW5,
// Date 12 April 2020

#ifndef MYSET_EMRE_H
#define MYSET_EMRE_H

using namespace std;

class IntegerSet
	{

	private:
		int * set;
		int size;

	public:
		IntegerSet(); 
		IntegerSet(int); 
		IntegerSet(const IntegerSet &);
		IntegerSet(const IntegerSet &,int); 
		~IntegerSet();

		IntegerSet & operator + (int &); 
		const IntegerSet & operator =  (const IntegerSet &);
		const IntegerSet & operator += (const IntegerSet &);
		int   IntegerSet :: getSize()const;
		int   IntegerSet :: getElement(int index)const;
		void  IntegerSet :: setSize(int psize);
		void  IntegerSet :: setElement(int index, int element);
	};
	IntegerSet  operator *  (const IntegerSet &,const IntegerSet &); 
	IntegerSet  operator + (const IntegerSet &,const IntegerSet &);
	ostream & operator << (ostream & output,IntegerSet set); 
	bool operator <= (const IntegerSet set,int &);
	bool operator <= (const IntegerSet & lhs, const IntegerSet & rhs);
	bool operator != (const IntegerSet & lhs, const IntegerSet & rhs);
#endif 
