#pragma once
#include <array>
#include <string>
#include <filesystem>
#include <vector>
#include <sodium.h>

// libsodium types
using SignPublicKey = std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>;
using SignPrivateKey = std::array<unsigned char, crypto_sign_SECRETKEYBYTES>;
using EncryptPublicKey = std::array<unsigned char, crypto_kx_PUBLICKEYBYTES>;
using EncryptPrivateKey = std::array<unsigned char, crypto_kx_SECRETKEYBYTES>;

// Init libsodium
bool initialize();

// Key generation
bool generate_signing_keypair(SignPublicKey& publicKey, SignPrivateKey& privateKey) noexcept;
bool generate_encryption_keypair(EncryptPublicKey& publicKey, EncryptPrivateKey& privateKey);

// Derive AES key
std::array<unsigned char, 32> derive_aes_key(const EncryptPrivateKey& priv);

// Encrypt
bool encrypt_file(
    const std::filesystem::path& input_path,
    const std::filesystem::path& output_path,
    const std::array<unsigned char, 32>& key
);

// Read binary file
std::vector<unsigned char> read_file(const std::filesystem::path& path);
