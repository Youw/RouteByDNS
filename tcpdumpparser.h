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

	struct dns_packet
	{
		struct record
		{
			std::string type, value;
		};

		time_t time;
		unsigned id;
		std::string from, to, type;
		std::vector<record> records;
	};

	dns_packet getNextPacket();

private:
	static dns_packet parce(const std::string& dump_str);
};

#endif //TCPSUMPPARSER_H