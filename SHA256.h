#pragma once
#include <iostream>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <string>

std::string computeSHA256(const std::string input) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int length = 0;

    // Create a digest context
    EVP_MD_CTX *context = EVP_MD_CTX_new();
    if (!context) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }

    // Initialize, update, and finalize the hash computation
    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1 ||
        EVP_DigestUpdate(context, input.c_str(), input.size()) != 1 ||
        EVP_DigestFinal_ex(context, hash, &length) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Error computing SHA256");
    }

    EVP_MD_CTX_free(context);

    // Convert hash to a readable hexadecimal string
    std::stringstream ss;
    for (unsigned int i = 0; i < length; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}
