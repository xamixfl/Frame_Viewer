#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H


class DataSource
{
public:
	virtual ~DataSource() = default;

	virtual void open() = 0;
	virtual void close() = 0;
	[[nodiscard]] virtual bool isOpen() const = 0;
};


#endif //DATA_SOURCE_H
