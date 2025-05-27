#pragma once
#include <string>
#include <array>
#include <vector>
#include <sodium.h>

bool firmarArchivo(
    const std::string& rutaArchivo,
    const std::array<unsigned char, crypto_sign_SECRETKEYBYTES>& clavePrivada,
    std::vector<unsigned char>& firma
);

bool verificarFirmaArchivo(
    const std::string& rutaArchivo,
    const std::vector<unsigned char>& firma,
    const std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>& clavePublica
);
