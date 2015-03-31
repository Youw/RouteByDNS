#include "dnsipprocessor.h"

#include <algorithm>

DNSIPProcessor::DNSIPProcessor(const NameList& allowed_dns_names) :
	allowed_names(allowed_dns_names)
{
	int system_ret = system("/etc/route_by_dns/startup.sh");
	(void)system_ret;
}

DNSIPProcessor::~DNSIPProcessor()
{
        int system_ret = system("/etc/route_by_dns/shutdown.sh");
	(void)system_ret;
}


void DNSIPProcessor::process(const dns_ip& query)
{
	if (nameAllowed(query.name)) {
		for (auto& ip : query.addresses) {
			addToWhiteList(ip,query.name);
		}
	}
}

bool DNSIPProcessor::nameAllowed(const std::string& dns_name)
{
	return std::any_of(allowed_names.begin(), allowed_names.end(), [&](const std::string& name){
		return dns_name.find(name) != dns_name.npos;
	});
}

void DNSIPProcessor::addToWhiteList(const std::string& ip, const std::string& name)
{
	if (!ipInWhiteList(ip)) {
		allowed_ip.insert(ip);
		int system_ret = system(("/etc/route_by_dns/add_ip.sh \"" + ip + "\" \"" + name + "\"").c_str());
		(void)system_ret;
	}
}

bool DNSIPProcessor::ipInWhiteList(const std::string& ip)
{
	return allowed_ip.find(ip) != allowed_ip.end();
}
