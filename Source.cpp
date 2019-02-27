//============================================================================
// Name			: Source.cpp
// Author		: Quinn Brum
// Version		: February 25, 2019
// Descpription	: Project 2 in C++
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

template <class DT>
class ExceptionAdd {};

template <class DT>
class ExceptionMultiply {};

template <class DT>
class ExceptionCV {};

template<class DT>
class SparseRow {
protected:
	int row; //Row#
	int col; //Column#
	DT value; //We will assume that all our values will be integers
public:
	SparseRow(); //default constructor; row=-1; col=-1; value=0
	SparseRow(int r, int c, DT& v);
	virtual ~SparseRow(); //destructor
	void displaySparse(); //print Row#, Column#, value

	int getRow(); //gets the row# for a given value
	void setRow(int r); //sets the row# for a given value
	int getCol(); // gets the col# for a given value
	void setCol(int c); //sets the col# for a given value
	int getValue(); //gets the value
	void setValue(int v); //sets the value
};

//returns the int value of the Row of the sparseRow
template <class DT>
int SparseRow<DT>::getRow()
{
	return row;
}

//sets the value of a given row
template <class DT>
void SparseRow<DT>::setRow(int r)
{
	row = r;
}

//returns the int value of the column of the sparseRow
template <class DT>
int SparseRow<DT>::getCol()
{
	return col;
}

//sets the value of a given column
template <class DT>
void SparseRow<DT>::setCol(int c)
{
	col = c;
}

//returns the int value of the value assigned in the sparseRow
template <class DT>
int SparseRow<DT>::getValue()
{
	return value;
}


//sets the value of the given SparseRow value
template <class DT>
void SparseRow<DT>::setValue(int v)
{
	value = v;
}

//default constructor for SparseRow
template <class DT>
SparseRow<DT>::SparseRow()
{
	row = -1;
	col = -1;
	value = 0;
}

//parameterized constructor for SparseRow
template <class DT>
SparseRow<DT>::SparseRow(int r, int c, DT& v)
{
	row = r;
	col = c;
	value = v;
}

//destructor
template <class DT>
SparseRow<DT>::~SparseRow()
{
}

//display method for SparseRow
template <class DT>
void SparseRow<DT>::displaySparse()
{
	cout << row << ", " << col << ", " << value << endl;
}

template <class DT>
class SparseMatrix {
protected:
	int noRows; //Number of rows of the original matrix
	int noCols; //Number of columns of the original matrix
	int commonValue; //Read from input
	int noNonSparseValues; //number of values that are not the common value
	vector<SparseRow<DT> >* myMatrix = new vector<SparseRow<DT> >(); //Array - should be dynamic
public:
	SparseMatrix(); //Default constructor
	SparseMatrix(int n, int m, int cv); //constructor
	virtual ~SparseMatrix(); //destructor
	void setSparseRow(int pos, int r, int c, DT& v); //sets the values of the SpareRow object

	friend SparseMatrix<DT> operator* (const SparseMatrix<DT>& S, const SparseMatrix<DT>& F); //for mulitplication and similar for addition and transpose
	friend SparseMatrix<DT> operator+ (const SparseMatrix<DT>& S, const SparseMatrix<DT>& F); //for addition
	friend SparseMatrix<DT> operator~ (SparseMatrix<DT>& M); //for transposition
	friend ostream& operator<< (ostream& os, SparseMatrix<DT>& M);

	void display(); //Display the sparse matrix in sparse row form
	void displayMatrix(); //Display the matrix in its original form
	int valFromRowCol(int r, int c); //returns the value at a specific row and column
};

//passes parameters to the SparseRow object myMatrix to create a sparseRow
template <class DT>
void SparseMatrix<DT>::setSparseRow(int pos, int r, int c, DT& v)
{
	myMatrix->push_back(SparseRow<DT>(r,c,v));
}

//default constructor for SparseMatrix
template <class DT>
SparseMatrix<DT>::SparseMatrix()
{

}

/*paraterize constructor for SparseMatrix
	n - number of rows
	m - number of columns
	cv - common value from the matrix
*/
template <class DT>
SparseMatrix<DT>::SparseMatrix(int n, int m, int cv)
{
	noRows = n;
	noCols = m;
	commonValue = cv;
	//noNonSparseValues = noNSV;
	//myMatrix = new SparseRow[noNSV];
}

//returns the value at a specific row and column
template <class DT>
int SparseMatrix<DT>::valFromRowCol(int r, int c)
{
	//iterating loop through the array
	for (int i = 0; i < noRows; ++i)
	{
		//returns the value if the row and column passed in are the same as the row and column in the matrix
		if ((r == myMatrix->at(i).getRow()) && (c == myMatrix->at(i).getCol()))
		{
			return myMatrix->at(i).getValue();
		}
		//returns 0 if not
		else
		{
			return 0;
		}
	}
	//returns zero regardless (breaks code if not here so I'm rolling with it)
	return 0;

}

//operation multiply class
template<class DT>
SparseMatrix<DT> operator*(const SparseMatrix<DT>& S, const SparseMatrix<DT>& F)
{
	SparseMatrix<DT>* multTemp = new SparseMatrix<DT>();

	/*try
	{

	}
	catch (const std::exception&)
	{

	}*/

	return multTemp;
}

//operation add class
template <class DT>
SparseMatrix<DT> operator+(const SparseMatrix<DT>& S, const SparseMatrix<DT>& F)
{
	SparseMatrix<DT>* addTemp = new SparseMatrix<DT>();

	/*try
	{

	}
	catch (const std::exception&)
	{

	}*/

	return addTemp;
}

//operation transpose class
template <class DT>
SparseMatrix <DT> operator~(SparseMatrix<DT>& M)
{
	SparseMatrix<DT>* transposed = new SparseMatrix<DT>();

	/*try
	{

	}
	catch (const std::exception&)
	{

	}*/

	for (int i = 0; i < M->size(); i++)
	{
		((*transposed).M.at(i)).setRow(M->at(i).getCol());
		((*transposed).M->at(i)).setCol(M->at(i).getRow());
		((*transposed).M->at(i)).setValue(M->at(i).getValue());
	}

	return transposed;
}

template <class DT>
ostream& operator<<(ostream& os, SparseMatrix<DT>& M)
{
	os << (*M).display();

	return os;
}

//destructor class
template<class DT>
SparseMatrix<DT>::~SparseMatrix()
{
}

//displays the SparseMatrix object in sparse matrix format
template <class DT>
void SparseMatrix<DT>::display()
{
	//iterating through the matrix and making sure all values are covered if the matrix is not square
	for (int i = 0; i < noRows && i < noCols; i++)
	{
		//displays the matrix after getting the repsective (row, column, or value) value
		myMatrix->at(i).displaySparse();
	}
}

//displays the sparseMatrix in the normal matrix format
template <class DT>
void SparseMatrix<DT>::displayMatrix()
{
	//iterates through the number of rows and columns
	for (int i = 0; i < noRows; ++i)
	{
		for (int j = 0; j < noCols; ++j)
		{
			//checks to make sure the row number is equal for the respective index
			//and makes sure the column value at the row index is equal to the row value is equal to the column index
			if (myMatrix->at(i).getRow() == myMatrix->at(j).getRow() && myMatrix->at(i).getCol() == myMatrix->at(j).getRow())
			{
				//prints the value
				cout << myMatrix->at(i).getValue();
			}
			//the exact opposite of the previous if statements, makes sure the column values are equal for the respective index
			//and makes sure the row value at the column index is the same as the column value at the row index
			else if (myMatrix->at(j).getCol() == myMatrix->at(i).getCol() && myMatrix->at(j).getRow() == myMatrix->at(i).getCol())
			{
				//prints the value
				cout << myMatrix->at(i).getValue();
			}
			//returns the common value if none of the above conditions are met
			else
			{
				cout << commonValue;
			}			

		}
		//makes sure the line breaks at the appropriate place in the matrix
		cout << endl;
	}

}


int main() {

	int n, m, cv;
	SparseMatrix<int>* temp = new SparseMatrix<int>();
	int v;
	//k value for firstOne
	int kf = 0;
	//k value for secondOne
	int ks = 0;

	cin >> n >> m >> cv;
	SparseMatrix<int>* firstOne = new SparseMatrix<int>(n, m, cv);

	//Statements to read in the first matrix
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> v;
			if (v != cv)
			{
				(*firstOne).setSparseRow(kf, i, j, v);
				kf++;
			}
		}
	}

	cout << "First one in sparse matrix format" << endl;
	//cout << firstOne;
	(*firstOne).display();

	cout << "First one in normal matrix format" << endl;
	(*firstOne).displayMatrix();

	cin >> n >> m >> cv;
	SparseMatrix<int>* secondOne = new SparseMatrix<int>(n, m, cv);

	//statment to read in the first matrix
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> v;
			if (v != cv)
			{
				(*secondOne).setSparseRow(ks, i, j, v);
				ks++;
			}
		}
	}

	cout << "Second one in sparse matrix format" << endl;
	//cout << secondOne;
	(*secondOne).display();

	cout << "Second one in normal matrix format" << endl;
	(*secondOne).displayMatrix();

	//temp = ~(firstOne); //swear this thing hates me
	//cout << "After Transpose first one in normal format" << endl;
	//(*temp).displayMatrix();

	//temp = ~secondOne;
	//cout << "After Transpose second one in normal format" << endl;
	//(*temp).displayMatrix();

	//cout << "Multiplication of matrices in sparse matrix form:" << endl;
	//temp = secondOne*firstOne;
	//cout << temp;

	//cout << "Addition of matrices in sparse matrix form:" << endl;
	//temp = secondOne+firstOne;
	//cout << temp;

	return 1;
};