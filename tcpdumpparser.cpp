#include "tcpdumpparser.h"

#include <algorithm>
#include <cctype>
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
	if (is_nxdomain(buffer)) {
		result.records.push_back({ "nxdomain", "" });
		return result;
	}
	if (!is_last_trash(buffer)) {
		for (size_t i = 0; i < buffer.size(); i++) {
			str.unget();
		}
	}
	while (std::getline(str, buffer, ',')) {
		dns_packet::record record;
		std::stringstream tmp(buffer);
		tmp >> record.type >> record.value;
		if (record.type != "") {
			result.records.push_back(record);
		}
	}
	return result;
}

bool TcpDumpParser::is_nxdomain(const std::string& str)
{
	std::string buffer(str);
	std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
	return buffer.find("nxdomain") != buffer.npos;
}

bool TcpDumpParser::is_last_trash(const std::string& str)
{
	int slash_count = 0;
	bool ok = std::all_of(str.begin(), str.end(), [&](char c)->bool {
		if (c == '/') {
			slash_count++;
			return true;
		}
		return std::isdigit(c);
	});
	if (ok && slash_count==2) return true;
	if (str == "[1au]") return true;
}