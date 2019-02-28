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
	SparseRow(int r, int c, DT& v); //constructor
	SparseRow(const SparseRow &copy);
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

//Copy constructor for the sparseRow class
template <class DT>
SparseRow<DT>::SparseRow(const SparseRow &copy)
{
	row = copy.row;
	col = copy.col;
	value = copy.value;
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
class SparseMatrix;

template <class DT>
ostream& operator<< <>(ostream& os, const SparseMatrix<DT>& M);

template <class DT>
SparseMatrix<DT> operator* (const SparseMatrix<DT>& M);

template <class DT>
SparseMatrix<DT> operator+(const SparseMatrix<DT>& M);

template<class DT>
SparseMatrix<DT> operator!(const SparseMatrix<DT>& M);

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
	SparseMatrix(const SparseMatrix &copy); //copy constructor
	virtual ~SparseMatrix(); //destructor
	void setSparseRow(int pos, int r, int c, DT& v); //sets the values of the SpareRow object

	friend SparseMatrix<DT> operator* <>(const SparseMatrix<DT>& M); //for mulitplication and similar for addition and transpose
	friend SparseMatrix<DT> operator+ <>(const SparseMatrix<DT>& M); //for addition
	friend SparseMatrix<DT> operator! <>(const SparseMatrix<DT>& M); //for transposition
	friend ostream& operator<< <>(ostream& os, const SparseMatrix<DT>& M);//overloaded Ostream operator

	void display(); //Display the sparse matrix in sparse row form
	void displayMatrix(); //Display the matrix in its original form
	int valFromRowCol(int r, int c); //returns the value at a specific row and column
	int getNoRows();
	int getNoCols();
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
}

//copy constructor
template <class DT>
SparseMatrix<DT>::SparseMatrix(const SparseMatrix &copy)
{
	noRows = copy.noRows;
	noCols = copy.noCols;
	commonValue = copy.commonValue;
}

//destructor class
template <class DT>
SparseMatrix<DT>::~SparseMatrix()
{
}

template <class DT>
int SparseMatrix<DT>::getNoRows()
{
	return noRows;
}

template <class DT>
int SparseMatrix<DT>::getNoCols()
{
	return noCols;
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
	}
	//returns the commonValue
	return commonValue;

}

//operation multiply class
template<class DT>
SparseMatrix<DT> operator*(const SparseMatrix<DT>& M)
{
	SparseMatrix<int>* multTemp = new SparseMatrix<int>(M.noRows, M.noCols, M.commonValue);

	/*try
	{

	}
	catch (const std::exception&)
	{

	}*/

	int pos = 0;
	
	for (int i = 0; i < multTemp->getNoRows(); ++i)
	{
		for (int j = 0; j < multTemp->getNoCols(); ++j)
		{
			int finVal = 0;
			for (int k = 0; k < M.noRows; ++k)
			{
				if (M.myMatrix->at(k).getRow() == i)
				{
					for (int b = 0; b < M.noCols; ++b)
					{
						if (M.myMatrix->at(b).getCol() == j)
						{
							if (M.myMatrix->at(k).getCol() == M.myMatrix->at(b).getRow())
							{
								finVal += M.myMatrix->at(k).getValue() * M.myMatrix->at(b).getValue();
							}
						}
					}
				}
			}

			if (finVal != multTemp->commonValue)
			{
				multTemp->setSparseRow(pos, i, j, finVal);
				pos++;
			}
		}		
	}
	return (*multTemp);
}

//operation add class
template <class DT>
SparseMatrix<DT> operator+(const SparseMatrix<DT>& M)
{
	SparseMatrix<int>* addTemp = new SparseMatrix<int>(this->getNoRows(), this->getNoCols(), this->commonValue+M.commonValue);

	/*try
	{

	}
	catch (const std::exception&)
	{

	}*/

	int pos = 0;

	for (int i = 0; i < addTemp->getNoRows(); ++i)
	{
		for (int j = 0; j < addTemp->getNoCols(); ++j)
		{
			int sum = 0;
			for (int k = 0; k < M.noRows; ++k)
			{
				if (M.myMatrix->at(k).getRow() == i)
				{
					for (int b = 0; b < M.noCols; ++b)
					{
						if (M.myMatrix->at(b).getCol() == j)
						{
							if (M.myMatrix->at(k).getCol() == M.myMatrix->at(b).getRow())
							{
								sum += M.myMatrix->at(k).getValue() + M.myMatrix->at(b).getValue();
							}
						}
					}
				}
			}

			if (sum != addTemp->commonValue)
			{
				addTemp->setSparseRow(pos, i, j, sum);
				pos++;
			}
		}
	}

	return addTemp;
}

//operation transpose class
template <class DT>
SparseMatrix <DT> operator! (const SparseMatrix<DT>& M)
{
	SparseMatrix<int>* transposed = new SparseMatrix<int>(M.noRows, M.noCols, M.commonValue);

	/*try
	{

	}
	catch (const std::exception&)
	{

	}*/

	for (int i = 0; i < M.noRows; i++)
	{
		((*transposed).myMatrix->at(i)).setRow(M.myMatrix->at(i).getCol());
		((*transposed).myMatrix->at(i)).setCol(M.myMatrix->at(i).getRow());
		((*transposed).myMatrix->at(i)).setValue(M.myMatrix->at(i).getValue());
	}

	return (*transposed);
}

template <class DT>
ostream& operator<< <>(ostream& os, const SparseMatrix<DT>& M)
{
	(*M).display();
	return os;
}

//displays the SparseMatrix object in sparse matrix format
template <class DT>
void SparseMatrix<DT>::display()
{
	//iterating through the matrix and making sure all values are covered if the matrix is not square
	for (int i = 0; i < noRows; i++)
	{
		//displays the matrix after getting the repsective (row, column, or value) value
		(*myMatrix).at(i).displaySparse();
	}
}

//displays the sparseMatrix in the normal matrix format
template <class DT>
void SparseMatrix<DT>::displayMatrix()
{
	//iterates through the rows
	for (int i = 0; i < noRows; i++)
	{
		//interates through the columns
		for (int j = 0; j < noCols; j++)
		{
			//calls the method to return the value from a given row and column value in the matrix
			cout << valFromRowCol(i, j) << " ";
		}

		//printing a new line after each row to keep the proper format
		cout << endl;
	}

}


int main() 
{

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
	//cout << (*firstOne);
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
	//cout << (*secondOne);
	(*secondOne).display();

	cout << "Second one in normal matrix format" << endl;
	(*secondOne).displayMatrix();

	(*temp) = !(*firstOne); //swear this thing hates me
	cout << "After Transpose first one in normal format" << endl;
	(*temp).displayMatrix();

	(*temp) = !(*secondOne);
	cout << "After Transpose second one in normal format" << endl;
	(*temp).displayMatrix();

	/*cout << "Multiplication of matrices in sparse matrix form:" << endl;
	temp = (*secondOne)*(*firstOne);
	cout << (*temp);

	cout << "Addition of matrices in sparse matrix form:" << endl;
	temp = (*secondOne)+(*firstOne);
	cout << (*temp);*/

	return 1;
};