#pragma once
#include <iostream>
#include <vector>
#include <cstddef>
#include <iterator>

template <typename T>
concept DataInput = std::random_access_iterator<T>;

std::ostream& operator<<(std::ostream& os, std::byte b);

class SavefileManager {
public:
	bool load(const std::string_view filename);
	bool store(const std::string_view filename);
	const std::vector<char>& getData() const;
private:
	std::vector<char> data;
};