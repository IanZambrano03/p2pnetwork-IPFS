#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sodium.h>
#include <array>

bool firmarArchivo(
    const std::string& rutaArchivo,
    const std::array<unsigned char, crypto_sign_SECRETKEYBYTES>& clavePrivada,
    std::vector<unsigned char>& firma)
{
    try {
        std::ifstream infile(rutaArchivo, std::ios::binary | std::ios::ate);
        if (!infile) {
            std::cerr << "Error abriendo el archivo para firmar.\n";
            return false;
        }

        std::streamsize size = infile.tellg();
        infile.seekg(0, std::ios::beg);

        std::vector<unsigned char> fileContent(size);
        if (!infile.read(reinterpret_cast<char*>(fileContent.data()), size)) {
            std::cerr << "Error leyendo el archivo.\n";
            return false;
        }

        
        firma.resize(crypto_sign_BYTES);

        unsigned long long firmaLen = 0;

        int result = crypto_sign_detached(
            firma.data(),          
            &firmaLen,             
            fileContent.data(),    
            fileContent.size(),    
            clavePrivada.data()    
        );

        if (result != 0) {
            std::cerr << "Error al generar la firma.\n";
            return false;
        }

        
        firma.resize(firmaLen);

        std::cout << "Firma generada con éxito. Tamaño: " << firma.size() << " bytes.\n";
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << "\n";
        return false;
    }
};
