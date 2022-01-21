#include <core/ContentRepository.h>
#include <iostream>

void ContentRepository::addContent(const std::vector<char>& content) {
	std::cout << "i am here" << std::endl;
	std::vector<std::byte> decoded;
	decode(content.begin(), content.end(), std::back_inserter(decoded));
}