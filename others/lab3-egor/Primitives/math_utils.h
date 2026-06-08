#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "square_matrix.h"
#include <cmath>

SquareMatrix<double> createIdentityMatrix(int size);

double radians(double degrees);

SquareMatrix<double> translate(const SquareMatrix<double>&mat, const std::vector<double>& offset);
SquareMatrix<double> rotate(const SquareMatrix<double>&mat, double rad, const std::vector<double>& offset);
SquareMatrix<double> scale(const SquareMatrix<double>&mat, const std::vector<double>& scale);


SquareMatrix<double> lookAt(const std::vector<double>& pos, const std::vector<double>& eye, const std::vector<double>& dir);
SquareMatrix<double> perspective(double rad, double aspect, double zNear, double zFar);

SquareMatrix<double> inverse(SquareMatrix<double> mat);

std::vector<double> normalize(const std::vector<double>& vec);
std::vector<double> cross(const std::vector<double> &v1, const std::vector<double> &v2);



#endif //MATH_UTILS_H
