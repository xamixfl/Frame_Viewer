#include "math_utils.h"
#include <cmath>
#include <stdexcept>


SquareMatrix<double> createIdentityMatrix(int size)
{
	SquareMatrix<double> identity(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			identity[i][j] = 0.0;

	for (int i = 0; i < size; i++)
		identity[i][i] = 1.0;
	return identity;
}

static double dot(const std::vector<double> &v1, const std::vector<double> &v2)
{
	if (v1.size() != 3 || v2.size() != 3)
	{
		throw std::invalid_argument("Vectors must have 3 components dot");
	}
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

static double determinant(const SquareMatrix<double> &mat)
{
	if (mat.getSize() != 4)
	{
		throw std::invalid_argument("Matrix must be 4x4");
	}
	double a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3];
	double e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3];
	double i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3];
	double m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3];
	return a * (f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n))
		- b * (e * (k * p - l * o) - g * (i * p - l * m) + h * (i * o - k * m))
		+ c * (e * (j * p - l * n) - f * (i * p - l * m) + h * (i * n - j * m))
		- d * (e * (j * o - k * n) - f * (i * o - k * m) + g * (i * n - j * m));
}

double radians(double degrees)
{
	return degrees * M_PI / 180.0;
}

SquareMatrix<double> translate(const SquareMatrix<double> &mat, const std::vector<double> &offset)
{
	if (offset.size() != 3)
	{
		throw std::invalid_argument("Offset must have 3 components");
	}
	SquareMatrix<double> result(mat);
	SquareMatrix<double> translation = createIdentityMatrix(4);

	translation[0][0] = 1;
	translation[1][1] = 1;
	translation[2][2] = 1;
	translation[3][3] = 1;
	translation[0][3] = offset[0];
	translation[1][3] = offset[1];
	translation[2][3] = offset[2];
	return result * translation;
}

SquareMatrix<double> rotate(const SquareMatrix<double> &mat, double rad, const std::vector<double> &offset)
{
	if (offset.size() != 3)
		throw std::invalid_argument("Axis must have 3 components");

	double x = offset[0], y = offset[1], z = offset[2];
	double length = std::sqrt(x * x + y * y + z * z);
	if (length > 1e-10)
	{
		x /= length;
		y /= length;
		z /= length;
	}

	SquareMatrix<double> rotation = createIdentityMatrix(4);
	double c = std::cos(rad);
	double s = std::sin(rad);
	double t = 1.0 - c;

	rotation[0][0] = t * x * x + c;
	rotation[0][1] = t * x * y - s * z;
	rotation[0][2] = t * x * z + s * y;
	rotation[0][3] = 0;

	rotation[1][0] = t * x * y + s * z;
	rotation[1][1] = t * y * y + c;
	rotation[1][2] = t * y * z - s * x;
	rotation[1][3] = 0;

	rotation[2][0] = t * x * z - s * y;
	rotation[2][1] = t * y * z + s * x;
	rotation[2][2] = t * z * z + c;
	rotation[2][3] = 0;

	rotation[3][0] = 0;
	rotation[3][1] = 0;
	rotation[3][2] = 0;
	rotation[3][3] = 1;

	return rotation * mat;
}

SquareMatrix<double> scale(const SquareMatrix<double> &mat, const std::vector<double> &scale)
{
	if (scale.size() != 3)
	{
		throw std::invalid_argument("Scale must have 3 components");
	}
	SquareMatrix<double> result(mat);
	SquareMatrix<double> scaling = createIdentityMatrix(4);
	scaling[0][0] = scale[0];
	scaling[1][1] = scale[1];
	scaling[2][2] = scale[2];
	scaling[3][3] = 1;
	return result * scaling;
}

SquareMatrix<double>
lookAt(const std::vector<double> &pos, const std::vector<double> &eye, const std::vector<double> &dir)
{
	if (pos.size() != 3 || eye.size() != 3 || dir.size() != 3)
	{
		throw std::invalid_argument("Vectors must have 3 components");
	}
	std::vector<double> forward = {eye[0] - pos[0], eye[1] - pos[1], eye[2] - pos[2]};
	forward = normalize(forward);
	std::vector<double> right = cross(forward, dir);
	right = normalize(right);
	std::vector<double> up = cross(right, forward);
	SquareMatrix<double> result(4);
	result[0][0] = right[0];
	result[0][1] = right[1];
	result[0][2] = right[2];
	result[0][3] = -dot(right, pos);
	result[1][0] = up[0];
	result[1][1] = up[1];
	result[1][2] = up[2];
	result[1][3] = -dot(up, pos);
	result[2][0] = -forward[0];
	result[2][1] = -forward[1];
	result[2][2] = -forward[2];
	result[2][3] = dot(forward, pos);
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
	return result;
}

SquareMatrix<double> perspective(double rad, double aspect, double zNear, double zFar)
{
	if (zNear <= 0 || zFar <= zNear)
	{
		throw std::invalid_argument("Invalid zNear or zFar");
	}
	SquareMatrix<double> result(4);
	double f = 1.0 / std::tan(rad / 2.0);
	result[0][0] = f / aspect;
	result[1][1] = f;
	result[2][2] = (zNear + zFar) / (zNear - zFar);
	result[2][3] = (2 * zNear * zFar) / (zNear - zFar);
	result[3][2] = -1;
	result[3][3] = 0;
	return result;
}

SquareMatrix<double> inverse(SquareMatrix<double> mat)
{
	if (mat.getSize() != 4)
	{
		throw std::invalid_argument("Matrix must be 4x4");
	}
	SquareMatrix<double> result(4);
	double det = determinant(mat);
	if (std::abs(det) < 1e-10)
	{
		throw std::runtime_error("Matrix is not invertible");
	}
	SquareMatrix<double> augmented(4);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			augmented[i][j] = mat[i][j];
			augmented[i][j + 4] = (i == j) ? 1.0 : 0.0;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		double pivot = augmented[i][i];
		if (std::abs(pivot) < 1e-10)
		{
			throw std::runtime_error("Matrix is singular");
		}
		for (int j = 0; j < 8; ++j)
		{
			augmented[i][j] /= pivot;
		}
		for (int k = 0; k < 4; ++k)
		{
			if (k != i)
			{
				double factor = augmented[k][i];
				for (int j = 0; j < 8; ++j)
				{
					augmented[k][j] -= factor * augmented[i][j];
				}
			}
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result[i][j] = augmented[i][j + 4];
		}
	}
	return result;
}

std::vector<double> normalize(const std::vector<double> &vec)
{
	if (vec.size() != 3)
	{
		throw std::invalid_argument("Vector must have 3 components");
	}
	double length = std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	if (length < 1e-10)
	{
		return vec;
	}
	return {vec[0] / length, vec[1] / length, vec[2] / length};
}

std::vector<double> cross(const std::vector<double> &v1, const std::vector<double> &v2)
{
	return {
		v1[1] * v2[2] - v1[2] * v2[1],
		v1[2] * v2[0] - v1[0] * v2[2],
		v1[0] * v2[1] - v1[1] * v2[0]
	};
}
