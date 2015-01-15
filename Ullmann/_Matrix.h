#pragma once

#include <vector>

template<typename T>
class _Matrix
{
public:
		_Matrix(int rows, int cols, const T& value);
		~_Matrix(void);
		std::vector<T>& operator [](const int n);
		inline int getRows();
		inline int getCols();
		int getRows() const{ return rows;}
		int getCols() const{ return cols; }

		// operator 
		_Matrix<T> operator *(_Matrix<T> &rhs);
private:
		std::vector< std::vector<T> > elems;
		int rows;
		int cols;
};

