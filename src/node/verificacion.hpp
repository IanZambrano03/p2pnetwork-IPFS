#include <iostream>
#include <sodium.h>
#include <vector>
#include <array>
#include <fstream>
#include <filesystem>

bool verificarFirma(
    const std::string& rutaArchivo,
    const std::vector<unsigned char>& firma,
    const std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>& clavePublica
);