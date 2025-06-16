#include "node/identidad.hpp"
#include <iostream>
#include <exception>

void identidad::generar() {
    try {
        int claves = crypto_sign_keypair(clavePublica.data(), clavePrivada.data());

        if (claves == 0) {
            std::cout << "Your keys have been successfully generated.\n";
        } else {
            std::cerr << "An error has occurred during key generation.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "There is an error: " << e.what() << "\n";
    }
}
