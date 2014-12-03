#include "tcpdumpparser.h"

#include <sstream>

TcpDumpParser::TcpDumpParser(std::istream& input_stream): input(input_stream)
{

}

TcpDumpParser::packet TcpDumpParser::getNextPacket()
{
	std::string buffer;
	std::getline(input,buffer);
	return parce(buffer);
}

TcpDumpParser::packet TcpDumpParser::parce(const std::string& dump_str)
{
	packet result;
	std::string buffer;
	std::stringstream str(dump_str);

	str >> result.time;

	str >> buffer >> buffer; // trash;
}