#include "node/verificacion.hpp"


bool verificarFirma(
    const std::string& rutaArchivo,
    const std::vector<unsigned char>& firma,
    const std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>& clavePublica
) {
    
    std::vector<unsigned char> fileContent;

    
    try {
        std::ifstream infile(rutaArchivo, std::ios::binary | std::ios::ate);
        if (!infile) {
            std::cerr << "Error abriendo el archivo para verificación.\n";
            return false;
        }

        std::streamsize size = infile.tellg();
        infile.seekg(0, std::ios::beg);

        fileContent.resize(size);
        if (!infile.read(reinterpret_cast<char*>(fileContent.data()), size)) {
            std::cerr << "Error leyendo el archivo.\n";
            return false;
        }

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error de sistema de archivos: " << e.what() << "\n";
        return false;
    }

    if (firma.size() != crypto_sign_BYTES) {
        std::cerr << "Tamaño de firma inválido.\n";
        return false;
    }

    int resultado = crypto_sign_verify_detached(
        firma.data(),
        fileContent.data(),
        fileContent.size(),
        clavePublica.data()
    );

    if (resultado != 0) {
        std::cerr << "La verificación de la firma ha fallado.\n";
        return false;
    }

    std::cout << "Verificación de firma exitosa.\n";
    return true;
}
