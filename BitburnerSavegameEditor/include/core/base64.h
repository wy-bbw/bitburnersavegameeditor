#pragma once

#include <array>

std::array<char, 64> constexpr encode_table{ 'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '+', '/' };



template <typename T>
concept EncodingIterator = std::forward_iterator<T> && requires(T t) {
    {*t} -> std::convertible_to<char>;
};

std::array<std::byte, 3> decode_quad(std::array<char, 4> a);

template <EncodingIterator T, class Insert>
void decode(T begin, T end, Insert insert) {
	for (T t = begin; t != end; ) {
		std::array<char, 4> buf;
		for (int i = 0; i < 4; ++t, ++i) {
			buf[i] = *t;
		}
        std::array<std::byte, 3> decoded = decode_quad(buf);
		
		if (buf[3] == '=') {
            if (buf[2] == '=') {
                insert = decoded[0];
                // TODO: EOS, one byte decoding
                return;
            }
            insert = decoded[0];
            insert = decoded[1];
            return;
			// TODO: two byte decoding
		}
        std::copy(decoded.begin(), decoded.end(), insert);
	}
}