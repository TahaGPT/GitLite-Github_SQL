#include <iostream>
#include <string>
#include "SHA256.h"

// Example usage
int main()
{
    std::string input = "Hello, World!";
    // cout << "Helo world ";
    // cout << "this is the biggest proghram n the wprd";
    std::string hash = computeSHA256(input);
    std::cout << "String: " << input << std::endl;
    std::cout << "SHA256: " << hash << std::endl;
    return 0;
}