#ifndef MODEL_EXCEPTION_H
#define MODEL_EXCEPTION_H

#include "base_exception.h"

class OutOfRangeException: public BaseException
{
public:
	explicit OutOfRangeException(const char *file_name,
								 const int line,
								 const char *function_name,
								 const char *msg = "Index out of range") noexcept
		: BaseException(file_name, line, function_name, msg)
	{};
};

class FileOpenException: public BaseException
{
public:
	explicit FileOpenException(const char *file_name,
							   const int line,
							   const char *function_name,
							   const char *msg = "File open error") noexcept
		: BaseException(file_name, line, function_name, msg)
	{}
};

class FileBadFormatException: public BaseException
{
public:
	explicit FileBadFormatException(const char *file_name,
									const int line,
									const char *function_name,
									const char *msg = "File bad format") noexcept
		: BaseException(file_name, line, function_name, msg)
	{}
};

class SolutionAlreadyExistException: public BaseException
{
public:
	explicit SolutionAlreadyExistException(const char *file_name,
										   const int line,
										   const char *function_name,
										   const char *msg = "Solution already exist") noexcept
		: BaseException(file_name, line, function_name, msg)
	{}
};

class SolutionNotFoundException: public BaseException
{
public:
	explicit SolutionNotFoundException(const char *file_name,
									   const int line,
									   const char *function_name,
									   const char *msg = "Solution not found") noexcept
		: BaseException(file_name, line, function_name, msg)
	{}
};

class IndexException: public BaseException
{
public:
	explicit IndexException(const char *file_name,
									   const int line,
									   const char *function_name,
									   const char *msg = "Index error") noexcept
		: BaseException(file_name, line, function_name, msg)
	{}
};

class WrongTypeException: public BaseException
{
public:
	explicit WrongTypeException(const char *file_name,
							const int line,
							const char *function_name,
							const char *msg = "Wrong type") noexcept
		: BaseException(file_name, line, function_name, msg)
	{}
};

#endif //MODEL_EXCEPTION_H
