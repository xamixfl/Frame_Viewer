#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include <vector>

template<typename T>
class SquareMatrix
{
private:
	std::vector<std::vector<T>> matrix;
	size_t size;

public:
	SquareMatrix();
	explicit SquareMatrix(size_t n, T initial_value = T());

	[[nodiscard]] size_t getSize() const;
	void resize(size_t new_size, const T &initial_value = T());
	T &at(size_t row, size_t col);
	[[nodiscard]] const T &at(size_t row, size_t col) const;
	std::vector<T> &operator[](size_t row);
	const std::vector<T> &operator[](size_t row) const;
	SquareMatrix<T> operator+(const SquareMatrix<T> &other) const;
	SquareMatrix<T> &operator+=(const SquareMatrix<T> &other);
	SquareMatrix<T> operator*(const SquareMatrix<T> &other) const;
	std::vector<T> operator*(const std::vector<T> &other) const;
	SquareMatrix<T> &operator*=(const SquareMatrix<T> &other);
	[[nodiscard]] std::vector<T> multiplyLeft(const std::vector<T> &vec) const;
	[[nodiscard]] std::vector<T> multiplyRight(const std::vector<T> &vec) const;
};

template<>
inline std::vector<double> SquareMatrix<double>::multiplyLeft(const std::vector<double> &vec) const
{
	if (size == 4 && vec.size() == 4)
	{
		std::vector<double> result(4, 0.0);
		for (size_t i = 0; i < 4; ++i)
			for (size_t j = 0; j < 4; ++j)
				result[i] += matrix[i][j] * vec[j];
		return result;
	}

	std::vector<double> result(size, 0.0);
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			result[i] += matrix[i][j] * vec[j];
	return result;
}

#include "square_matrix.hpp"

#endif //SQUARE_MATRIX_H
