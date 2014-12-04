#include "tcpdumpparser.h"

#include <algorithm>
#include <sstream>

TcpDumpParser::TcpDumpParser(std::istream& input_stream): input(input_stream)
{

}

TcpDumpParser::dns_packet TcpDumpParser::getNextPacket()
{
	std::string buffer;
	std::getline(input,buffer);
	return parce(buffer);
}

TcpDumpParser::dns_packet TcpDumpParser::parce(const std::string& dump_str)
{
	dns_packet result;
	std::string buffer;
	std::stringstream str(dump_str.substr(0, dump_str.find_last_of('(')));

	str >> result.time;

	str >> buffer >> buffer; // trash;

	str >> buffer;
	result.from = buffer.substr(0, buffer.find_last_of('.'));

	str >> buffer;// trash;

	str >> buffer;
	result.to = buffer.substr(0, buffer.find_last_of('.'));

	str >> buffer;
	{
		std::stringstream tmp(buffer);
		tmp >> result.id >> result.type;
	}

	str >> buffer;
	std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
	if (buffer.find("nxdomain")==buffer.npos) {
		while (std::getline(str, buffer, ',')) {
			dns_packet::record record;
			std::stringstream tmp(buffer);
			tmp >> record.type >> record.value;
			if (record.type != "") {
				result.records.push_back(record);
			}
		}
	}
	else {
		result.records.push_back({"nxdomain",""});
	}

	return result;
}