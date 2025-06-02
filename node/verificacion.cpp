#include "verificacion.hpp"

bool verificarFirma(
    const std::string& rutaArchivo,
    const std::vector<unsigned char>& firma,
    const std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>& clavePublica
){


    try{
          std::ifstream infile(rutaArchivo, std::ios::binary | std::ios::ate);
        if (!infile) {
            std::cerr << "Error abriendo el archivo para firmar.\n";
            return false;
        }

        std::streamsize size = infile.tellg();
        infile.seekg(0, std::ios::beg);

        std::vector<unsigned char> fileContent(size);

        fileContent.resize(size);
        infile.read(reinterpret_cast<char*>(fileCOntent.data()), size);
        if (!infile.read(reinterpret_cast<char*>(fileContent.data()), size)) {
            std::cerr << "Error leyendo el archivo.\n";
            return false;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "You have a file error: " << e.what() << "\n";
        return false;
  
    }
     
    if (firma.size() != crypto_sign_BYTES){
            std::cerr << "The size of your signature is invalid: It has been resized: \n";
            return false; 
        }
     
        int result4Detached  = crypto_sign_verify_detached(
            firma.data(),
            fileContent.data(),
            fileContent.size(),
            clavePublica.data()
        );

    if (result4Detached != 0){
        std::cerr << "La funcion para verificar ha fallado: \n";
        return false; 
    }

    std::cout << "Your signature verification was successfull \n";
    return true;
}

