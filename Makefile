SOURCES=main.cpp tcpdumpparser.cpp dnsipprocessor.cpp dnspacketprocessor.cpp
GXX_FLAGS=-std=c++11 -O2 -pipe -MMD -MP
BUILD_DIR=obj/
OUTPUT_NAME=route_by_dns

all: $(OUTPUT_NAME)

$(OUTPUT_NAME): $(SOURCES:%.cpp=$(BUILD_DIR)%.o)
	g++ $(GXX_FLAGS) -o $@ $^

$(SOURCES:%.cpp=$(BUILD_DIR)%.o): $(BUILD_DIR)%.o : %.cpp $(BUILD_DIR)
	g++ $(GXX_FLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_NAME)

run: all
	sudo tcpdump -ttlni eth1.1415 port 53 and net 192.168.61.0/24 | sudo ./$(OUTPUT_NAME)

-include $(SOURCES:%.cpp=$(BUILD_DIR)%.d)
