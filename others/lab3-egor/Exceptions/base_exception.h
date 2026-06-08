#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <cstdio>

class BaseException: public std::exception
{
protected:
	static const size_t sizebuff = 256;
	char error_message[sizebuff]{};
public:
	BaseException() noexcept = default;
	explicit BaseException(const char *file_name,
							const int line,
							const char *function_name,
							const char *msg = "Undefined error") noexcept
	{
		snprintf(error_message,
				 sizebuff,
				 "File: %s, line: %d, function: %s, error: %s",
				 file_name,
				 line,
				 function_name,
				 msg);
	};

	~BaseException() override = default;

	[[nodiscard]] const char *what() const noexcept override
	{
		return error_message;
	}
};

#endif //BASE_EXCEPTION_H
