#include "node/firma.hpp"
#include "node/generar.hpp"
#include "node/identidad.hpp"
#include "node/persistencia.hpp"
#include "node/verificacion.hpp"
#include <iostream>

int main() {
    if (sodium_init() < 0) {
        std::cerr << "Failed to initialize libsodium\n";
        return 1;
    }

    initialize();
    int opcion = 0;
    identidad laIdentidad;

    std::cout << "You have four options\n";
    std::cout << "1: Generate your keys (Very first step);\n";
    std::cout << "2: Add a signature to a file;\n";
    std::cout << "3: Verify a signature;\n";
    std::cout << "4: Exit\n";
    std::cout << "Enter option: ";
    std::cin >> opcion;

    if (opcion == 1) {
        std::cout << "You have selected to generate your keys\n";

        laIdentidad.generar();  

        generarCarpeta();         

        guardarIdentidad(laIdentidad); 

        std::cout << "Keys generated and saved successfully.\n";
        return 0;
    }
}
