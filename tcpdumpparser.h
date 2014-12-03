#ifndef TCPSUMPPARSER_H
#define TCPSUMPPARSER_H

#include <ctime>
#include <iostream>
#include <string>
#include <vector>


class TcpDumpParser 
{
	std::istream& input;
public:
	TcpDumpParser(std::istream& input_stream = std::cin);

	struct record
	{
		std::string type, value;
	};

	struct packet
	{
		time_t time;
		unsigned id;
		std::string from, to;
		std::vector<record> records;
	};

	packet getNextPacket();

private:
	static packet parce(const std::string& dump_str);
};

#endif //TCPSUMPPARSER_H