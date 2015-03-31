#ifndef DNSIPPROCESSOR_H
#define DNSIPPROCESSOR_H

#include <unordered_set>
#include <string>
#include <vector>

class DNSIPProcessor
{
	using IpList = std::unordered_set<std::string>;
public:
	using NameList = std::vector<std::string>;

	DNSIPProcessor(const NameList& allowed_dns_names);
	DNSIPProcessor(const DNSIPProcessor&) = delete;
	DNSIPProcessor& operator=(const DNSIPProcessor&) = delete;
	DNSIPProcessor(DNSIPProcessor&&) = delete;
	DNSIPProcessor& operator=(DNSIPProcessor&&) = delete;
	~DNSIPProcessor();

	struct dns_ip
	{
		std::string name;
		std::vector<std::string> addresses;
	};

	void process(const dns_ip& query);

private:
	bool nameAllowed(const std::string& dns_name);
	void addToWhiteList(const std::string& ip, const std::string& name);
	bool ipInWhiteList(const std::string& ip);

	IpList allowed_ip;
	NameList allowed_names;
};

#endif //DNSIPPROCESSOR_H
