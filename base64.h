#ifndef BASE64_H
#define BASE64_H

#include <string>

namespace Base64 {
    std::string encode(const char *bytes_to_encode, unsigned int in_len);
    std::string encode(const std::string& source_string);
    std::string encode(const int& source_integer);
    std::string encode(const double& source_double);
    std::string decode(const std::string& encoded_string);
    inline bool isBase64(unsigned char c);

    // there are 64 characters
    static const std::string base64_chars =
        std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz"
                    "0123456789+/");
};

#endif
