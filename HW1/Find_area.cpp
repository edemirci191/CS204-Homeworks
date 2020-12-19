//**********************************************************************************
//	This program finds the closed area in a matrix if there is any and displays it coordinates
//	CS204 Homework_1 2019-2020 Spring
//	Known bugs : Not known
//	Made by : Emre Demirci, su_id = 26531, edemirci@sabanciuniv.edu
//	Start Date : 2/5/2020 1:11 AM
//  Last Modified at : 2/12/2020 9:11 PM
//  Some functions and codes from recitation are used in this cpp file there is appropiate comment in those lines
//  Even though there could be more functions for better understanding and modification i tried to write most parts seperatly and independently in cpp file
//**********************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

//****************************************** This part is based on the print function from MatrixDemo2.cpp
void Print(const vector<vector<char>> & mat)
{
    for (int j=0; j < mat.size(); j++)
    {   
		for (int k=0; k < mat[0].size(); k++)
        {   
			cout << setw(4) << mat[j][k];
        }
        cout << endl;
    }
}
//****************************************** 


void Amount_Error(string name)
{
cout << name << " is invalid matrix does not contain same amount of char each row! " << endl;
}

void Char_Error(string name)
{
cout << name << " includes invalid char(s)" << endl;
}

void Coordinate_Error()
{
cout << "Terminating... " << endl;
}

void Empty_Cell()
{
cout << "This cell is not occupied! " << endl;
}

void Invalid_Coordinates()
{
cout << "Invalid Coordinates" << endl;
}

int is_int(const string &str) // for checking invalid inputs
{
    return str.find_first_of("QWERTYIOPASDFGHJKLZXCVBNMqwertyuopasdfghjklizxcvbnm!'^+%&/()=?_");// assumed that user will only enter english chars even if it is invalid
}

int main(){


ifstream txtfile;

string inside_file, inside_file_copy, inside_file2, File_Name;

vector<vector<char>> matrix;

//while file with file name can not found ask for another file name 
cout << "Please enter file name: "; // initial asking part
cin >> File_Name;
cout << endl;
txtfile.open(File_Name.c_str());

while(txtfile.is_open() != true)  //if file with file name is found it skips while part
	{
		cout << "Cannot find a file named " << File_Name << endl ;
		cout << endl;
		cout << "Please enter file name ";
		cin >> File_Name;
		cout << endl;
		txtfile.open(File_Name.c_str());
	}



txtfile.clear();// otherwise gives error
txtfile.seekg(0);// otherwise gives error
inside_file.clear(); // works without this one as well just doing it 

//while loop below is taken from "MatrixDemo2.cpp" also shown in recitation
// only difference here is type<int> is changed to type<char> and some of the variable names are adjusted appropiately
while(!txtfile.eof())
	{
		getline(txtfile, inside_file);
		stringstream ss(inside_file);

		char ch;
		vector<char> temp;

		while( ss >> ch )
			{
				temp.push_back(ch);
			}

		matrix.push_back(temp);
	}

//************************************** CHECKING FILE VALIDITY BELOW**************************
// For loop below checks for non-valid characters in the matrix(txt file) 
int Column_Size = matrix[0].size();
int Row_Size = matrix.size();
bool char_validity = true;

bool size_validity = true;
for(int i = 0; i < matrix.size() -1 ; i++)
{
	int temp = matrix[i].size();
	int temp2 = matrix[i+1].size();
	if(temp != temp2)
		{
			size_validity = false;
			Amount_Error(File_Name);
			while(1){}
		}	
}


for( int row = 0; row < Row_Size ; row++)
	{
	for( int column = 0; column < Column_Size; column ++)
		{
			if((matrix[row][column] != 'x' ) && (matrix[row][column] != 'o'))///////**********
			{
				char_validity = false;
				Char_Error(File_Name);
				break;
			}
		}

	}



// As Homeworks says it gives error when characters in matrix is not valid


//printing the file as it is if matrix(file) is valid
if((size_validity == true) && (char_validity == true))
	{
		cout << " Input Matrix :" << endl;
		cout << endl;
		Print(matrix);
	}

//**************************************INPUT CHECKS FOR  txt FILE ARE DONE *********************

//**************************************CHECKING INPUTS FOR COORDINATES**************************
bool coordinate_check = true;
bool terminated=false;
bool invalid_coordinates = false;
int str_check;
int coordinate_x = 0, coordinate_y = 0;
string raw_coordinate_x, raw_coordinate_y;
while(coordinate_x != -1 && coordinate_y != -1)
{
	invalid_coordinates = false;
	if(char_validity == true && size_validity == true)
	{
		cout << endl;
		cout << "Please enter the starting coordinates, first row X then column Y: ";
		//***************************************************************************************************************************************************
		// i know this part is a bit complicated sorry modifying this part after writing the whole program but it is just about string input checks nothing more
		cin >> raw_coordinate_x >> raw_coordinate_y; // taking as a string cause i am gonna check if there is any string in given coordinates

		if(is_int(raw_coordinate_x)  == string::npos && is_int(raw_coordinate_y) == string::npos) // characters are valid so im converting raw(string) coordinates to int coordinates
		{
			coordinate_x = stoi(raw_coordinate_x);
			coordinate_y = stoi(raw_coordinate_y);
		}

		else// if inputs are invalid then basically choose invalid coordinates assign them to coordinates 
		{
			coordinate_x = matrix.size(); // coordinates are bigger so invalid
			coordinate_y = matrix[0].size(); // this and above line makes sure it enters the second if loop below here and it prints invalid message
		}
		//***************************************************************************************************************************************************************

		if( (coordinate_x == -1) && (coordinate_y == -1)) // if coordinates are negative give error
			{
				Coordinate_Error();
				coordinate_check = false;
				terminated = true;
			}

		if(coordinate_check = true && terminated == false )
		{
			if ( (coordinate_x >= matrix.size()|| coordinate_y >= matrix[0].size()) ) // if coordinates are bigger than matrix coordinates give error again
				{
					Invalid_Coordinates();
					coordinate_check =false;
					invalid_coordinates = true;
				}
		}
		if(coordinate_check == true && terminated == false && invalid_coordinates ==false)
		{
			if( matrix[coordinate_x][coordinate_y] == 'o') // if given coordinate is 'o' give another message
				{
					Empty_Cell();
					coordinate_check = false;
				}
		}

	}
//*************************************** INPUT CHECKS FOR COORDINATES ARE DONE ABOVE *******

//*************************************** CALCULATING AREA BELOW ***********************
// Notes about this part
// 1) any character except( 'x' and 'o' ) can be used instead of char 'Y'
// 2)  Overall flow of while loops below : it follows x and then changes x to y in order to follow its location... more explanation is given below
// 3) Assumption is in order to find a closed area all corner_check's must be true
//
	if(coordinate_check ==true  && char_validity ==true)
	{
	
		int pivot_x = coordinate_x;
		int pivot_y = coordinate_y;

		bool ex1 =false; // used the check if it entered the nested while loop at the end of the outer while loop (making sure its not iterating to infinity)
		bool ex2=false; 
		bool ex3=false;
		bool ex4=false;
		bool corner_check1 = false; // used to check if it entered the nested while loop at least once
		bool corner_check2 = false;
		bool corner_check3 = false;
		bool corner_check4 = false;

		int found_closed_area = 2; // looking for closed area this works with anything (int) but 0 or 1... not necessarily 2
		vector<int> coordinate_storage; // stores the coordinates of followed path in one dimension
		// reason some x changed to y is to prevent it from stucking into to the same location ( bir ileri bir geri gitmesin diye )

		while(matrix[pivot_x][pivot_y] != 'o')
		{
			ex1 =false;
			ex2=false;
			ex3=false;
			ex4=false;

			while(pivot_x != matrix.size() -1)
			{ 
				while(matrix[pivot_x+1][pivot_y] =='x')
				{
					matrix[pivot_x][pivot_y] = 'Y';
					pivot_x = pivot_x + 1;
					pivot_y = pivot_y;
					coordinate_storage.push_back(pivot_x);
					coordinate_storage.push_back(pivot_y);
					ex1 =true;
					corner_check1 = true;
					break;
				}
				break;
			}
	
			while(pivot_y != matrix[0].size()-1)
			{
				while(matrix[pivot_x][pivot_y+1] =='x')
				{
					matrix[pivot_x][pivot_y] = 'Y';
					pivot_x = pivot_x ;
					pivot_y = pivot_y+1;
					coordinate_storage.push_back(pivot_x);
					coordinate_storage.push_back(pivot_y);
					ex2=true;
					corner_check2 = true;
					break;
				}
				break;
			}

			while(pivot_y != 0)
			{
				while(matrix[pivot_x][pivot_y-1] =='x')
				{
					matrix[pivot_x][pivot_y] = 'Y';
					pivot_x = pivot_x;
					pivot_y = pivot_y - 1;
					coordinate_storage.push_back(pivot_x);
					coordinate_storage.push_back(pivot_y);
					ex3 = true;
					corner_check3 = true;
					break;
				}
				break;
			}

			while(pivot_y != matrix[0].size() && pivot_x != 0)
			{
				while (matrix[pivot_x-1][pivot_y] =='x')
				{
					matrix[pivot_x][pivot_y] = 'Y';
					pivot_x = pivot_x - 1;
					pivot_y = pivot_y;
					coordinate_storage.push_back(pivot_x);
					coordinate_storage.push_back(pivot_y);
					ex4 = true;
					corner_check4 = true;
					break;
				}
				break;
			}

			if(pivot_x == coordinate_x && pivot_y == coordinate_y)
			{
				// just by following x arrived the same location so found a closed area
				found_closed_area = 1; // found closed area 
				break;
			} 

			// if it is iterating inside the outer while loop without entering the inner while loops and 
			// if program didnt enter all nested while loops at least once then there can not be any closed area (triangles does not cound since we are not checking diagonal)
			if((ex1 == false && ex2==false && ex3== false && ex4 == false) && (corner_check1 == false || corner_check2 == false || corner_check3 == false || corner_check4 == false)) 
			{ 
				found_closed_area = 0;
				break;
			}
			// if statement below basically checks: if there is at least 4 corner and you are iterating the while loop for no reason without entering nested while loops that means there is a closed area
			if(ex1 == false && ex2==false && ex3== false && ex4 == false && corner_check1 == true && corner_check2 == true && corner_check3 == true && corner_check4 == true) // if all corner checks == true that means there is a closed area
			{
				found_closed_area = 1;
				break;
			}
		}
//**********************************************************SEARCHING FOR CLOSED AREA IS DONE****************

//*********************************************************IF CLOSED AREA IS FOUND PRINT COORDINATES
// example for better understanding of below while loops:
// assume coordinates are (1 2) and (3 4)
// in vector it is "1234"
// it prints (1 2) and (3 4) seperatly not (1 2) (2 3) (4)...

		if(found_closed_area == 1 && invalid_coordinates == false && char_validity== true && terminated == false) // this line also probably works with only found_closed_area == 1 but just incase i wrote others
		{
			cout << "Found an enclosed area. The coordinates of the followed path: " << endl;
			cout << coordinate_x << " " << coordinate_y << endl;
			for(int i = 0; i < coordinate_storage.size();i++) 
			{
				cout << coordinate_storage[i] << " ";
				i++;
				cout << coordinate_storage[i] << endl;
			}

		}

		else if(found_closed_area == 0)
		{
			cout << "Cannot found an enclosed area starting with given coordinates. The coordinates of the followed path: " << endl;
			cout << coordinate_x << " " << coordinate_y << endl;
			for(int i = 0; i < coordinate_storage.size();i++) 
			{
				cout << coordinate_storage[i] << " ";
				i++;
				cout << coordinate_storage[i] << endl;
			}
	
		}
	// because we are iterating in a while loop until coordinates are -1 -1 i make sure to change old Y to x and clean the vector for old storage
		coordinate_storage.clear();
		for( int row = 0; row < Row_Size ; row++)
		{
		for( int column = 0; column < Column_Size; column ++)
			{
				if(matrix[row][column] == 'Y' )///////**********
				{
					matrix[row][column] = 'x';
				}
			}

		}
	}
}

return 0;
}