#ifndef IDENTIDAD_HPP
#define IDENTIDAD_HPP

#include <sodium.h>
#include <array>

struct identidad {
    std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> clavePublica;
    std::array<unsigned char, crypto_sign_SECRETKEYBYTES> clavePrivada;

    void generar();
};

#endif
