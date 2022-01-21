#pragma once
#include <vector>
#include <cstddef>
#include <core/base64.h>
#include <string>

class ContentRepository {
public:
	void addContent(const std::vector<char>& content);
private: 
	std::string repo;

};