#include <core/base64.h>

namespace base64 {
    // TODO: big thank you goes to Matheuses Gomes for instructions and code for base64 (de|en)coding https://github.com/matheusgomes28/base64pp/blob/main/base64pp/base64pp.cpp
    std::array<std::uint8_t, 128> constexpr decode_table{ 0x64, 0x64, 0x64, 0x64,
        0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
        0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
        0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
        0x64, 0x64, 0x64, 0x3E, 0x64, 0x64, 0x64, 0x3F, 0x34, 0x35, 0x36, 0x37,
        0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64,
        0x64, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
        0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
        0x17, 0x18, 0x19, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x1A, 0x1B, 0x1C,
        0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x64,
        0x64, 0x64, 0x64, 0x64 };

    std::array<std::byte, 3> decode_quad(std::array<char, 4> a) {
        std::uint32_t const concat_bytes =
            (decode_table[a[0]] << 18) | (decode_table[a[1]] << 12)
            | (decode_table[a[2]] << 6) | decode_table[a[3]];

        std::byte const byte1 = static_cast<std::byte>((concat_bytes >> 16) & 0b1111'1111);
        std::byte const byte2 = static_cast<std::byte>((concat_bytes >> 8) & 0b1111'1111);
        std::byte const byte3 = static_cast<std::byte>(concat_bytes & 0b1111'1111);
        return { byte1, byte2, byte3 };
    }
}