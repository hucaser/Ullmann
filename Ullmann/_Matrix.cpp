#include "StdAfx.h"
#include "_Matrix.h"

template<typename T>
_Matrix<T>::_Matrix(int rows, int cols, const T& value)
{
		elems.resize(rows);
		for(int i = 0; i < elems.size(); i++){
				elems[i].resize(cols, value);
		}
		this->rows = rows;
		this->cols = cols;
}

template<typename T>
_Matrix<T>::~_Matrix(void)
{
}

template<typename T>
std::vector<T>& _Matrix<T>::operator[](const int n)
{
		return elems[n];
}

template<typename T>
int _Matrix<T>::getRows()
{
		return this->rows;
}

template<typename T>
int _Matrix<T>::getCols()
{
		return cols;
}


template<typename T>
_Matrix<T> _Matrix<T>::operator*(_Matrix<T>& rhs) {
		int row1 = this->rows;
		int column1 = this->cols;
		int row2 = rhs.getRows();
		int column2 = rhs.getCols();

		if(column1 != row2) {
				printf("matrix cannot multiple\n");
				exit(0);
				//return NULL;
		}
		_Matrix<T> result(row1, column2, 0);
		for (int i = 0; i < row1; i++){
				for (int j = 0; j < column2; j++){
						// rowi * columnj
						float value = 0;
						for(int k = 0; k < this->cols; ++k){
								value += (elems[i][k]) * (rhs[k][j]);
						}
						result[i][j] = value;
				}
		}
		return result;
}