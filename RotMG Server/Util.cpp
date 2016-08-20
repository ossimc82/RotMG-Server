#include "Util.h"
#include <string>
#include <sstream>
#include <zlib.h>
#include <random>

const std::string Util::base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

bool Util::is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Util::base64_decode(std::string const & encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

std::string Util::decompress_zlib(const unsigned char * str, size_t len) {
	z_stream zs;                        // z_stream is zlib's control structure
	memset(&zs, 0, sizeof(zs));

	/*
	MAX_WBITS = 15
	-8 to -15 for raw
	0_(inflateInit2 Only)_ or 8-15 for zlib
	> 15 :
	(8-15)+16 for gzip
	(8-15)+32 to automatically detect gzip/zlib header
	*/
	if (inflateInit2(&zs, MAX_WBITS) != Z_OK)
		throw(std::runtime_error("inflateInit failed while decompressing."));

	zs.next_in = (Bytef*)str;
	zs.avail_in = len;

	int ret;
	char outbuffer[32768];
	std::string outstring;

	// get the decompressed bytes blockwise using repeated calls to inflate
	do {
		zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
		zs.avail_out = sizeof(outbuffer);

		ret = inflate(&zs, Z_NO_FLUSH);

		if (outstring.size() < zs.total_out) {
			outstring.append(outbuffer,
				zs.total_out - outstring.size());
		}

	} while (ret == Z_OK);

	inflateEnd(&zs);

	if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
		std::ostringstream oss;
		oss << "Exception during zlib decompression: (" << ret << ") "
			<< zs.msg;
		throw(std::runtime_error(oss.str()));
	}
	return outstring;
}

int Util::randomRange(int min, int max) {
	return min == max ? min : (min + (rand() % (max - min)));
}
