#ifndef UTIL_H_
#define UTIL_H_

#include <string>

static class Util {
public:
	static bool is_base64(unsigned char c);
	static std::string base64_decode(std::string const& encoded_string);
	static std::string decompress_zlib(const unsigned char* str, size_t len);
	static int randomRange(int min, int max);
private:
	static const std::string base64_chars;
};

#endif // !UTIL_H_
