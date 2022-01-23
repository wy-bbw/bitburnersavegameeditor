#pragma once
#include <vector>
#include <memory>
#include <cstddef>
#include <core/json/Node.h>

namespace json {
	std::unique_ptr<Node> parseData(std::vector<std::byte> data);
}