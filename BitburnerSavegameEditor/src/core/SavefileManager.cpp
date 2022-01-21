
#include <core/SavefileManager.h>
#include <fstream>
#include <iterator>
#include <cstddef>

std::ostream& operator<<(std::ostream& os, std::byte b) {
	os << static_cast<int>(b);
	return os;
}

const std::vector<char>& SavefileManager::getData() const {
	return data;
}

bool SavefileManager::load(const std::string_view filename) {
	// TODO: string should always be null terminated, so this is fine.
	std::basic_ifstream<char> f(filename.data(), std::ios::binary);
	if (!f.good()) {
		return false;
	}
	data = { std::istreambuf_iterator<char>(f), {} };
	return true;
}

bool SavefileManager::store(const std::string_view filename) {
	std::cout << "storing file" << filename << std::endl;
	return true;
}