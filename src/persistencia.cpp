#include "node/persistencia.hpp"    // Tu archivo de cabecera con las declaraciones
#include <filesystem>
#include <fstream>
#include <iostream>

// Crea la carpeta "keys" para almacenar las claves, si no existe
void generarCarpeta() {
    try {
        if (std::filesystem::create_directory("keys")) {
            std::cout << "Se ha creado la carpeta 'keys' para guardar las claves.\n";
        } else {
            std::cout << "La carpeta 'keys' ya existe o no pudo ser creada.\n";
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error de sistema de archivos: " << e.what() << "\n";
    }
}

// Guarda la clave privada y pública en archivos binarios dentro de "keys/"
void guardarIdentidad(const identidad& id) {
    try {
        // Guardar clave privada
        std::ofstream filePriv("keys/private.key", std::ios::binary);
        if (!filePriv.is_open()) {
            std::cerr << "No se pudo crear el archivo private.key\n";
            return;
        }
        filePriv.write(reinterpret_cast<const char*>(id.clavePrivada.data()), id.clavePrivada.size());
        filePriv.close();

        // Guardar clave pública
        std::ofstream filePub("keys/public.key", std::ios::binary);
        if (!filePub.is_open()) {
            std::cerr << "No se pudo crear el archivo public.key\n";
            return;
        }
        filePub.write(reinterpret_cast<const char*>(id.clavePublica.data()), id.clavePublica.size());
        filePub.close();

        std::cout << "Claves guardadas exitosamente.\n";

    } catch (const std::ios_base::failure& e) {
        std::cerr << "Error de E/S al guardar las claves: " << e.what() << "\n";
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error de sistema de archivos al guardar las claves: " << e.what() << "\n";
    }
}

// Carga la clave privada y pública desde archivos binarios, devuelve true si tuvo éxito
bool cargarIdentidad(identidad& id) {
    try {
        if (!std::filesystem::exists("keys/private.key") || !std::filesystem::exists("keys/public.key")) {
            std::cerr << "Faltan archivos de claves.\n";
            return false;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error de sistema de archivos: " << e.what() << "\n";
        return false;
    }

    try {
        std::ifstream filePriv("keys/private.key", std::ios::binary);
        std::ifstream filePub("keys/public.key", std::ios::binary);

        filePriv.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        filePub.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        if (filePriv.is_open() && filePub.is_open()) {
            filePriv.read(reinterpret_cast<char*>(id.clavePrivada.data()), id.clavePrivada.size());
            filePub.read(reinterpret_cast<char*>(id.clavePublica.data()), id.clavePublica.size());

            int privCount = filePriv.gcount();
            int pubCount = filePub.gcount();

            if (privCount == static_cast<int>(id.clavePrivada.size()) &&
                pubCount == static_cast<int>(id.clavePublica.size())) {
                std::cout << "Identidad cargada exitosamente desde almacenamiento local.\n";
                return true;
            } else {
                std::cerr << "Error: tamaño de claves leído no coincide.\n";
                std::cerr << "Bytes leídos clave privada: " << privCount << " / Esperados: " << id.clavePrivada.size() << "\n";
                std::cerr << "Bytes leídos clave pública: " << pubCount << " / Esperados: " << id.clavePublica.size() << "\n";
                return false;
            }
        } else {
            std::cerr << "Error: no se pudieron abrir los archivos de claves.\n";
            return false;
        }

    } catch (const std::ios_base::failure& e) {
        std::cerr << "Error al leer los archivos de claves: " << e.what() << "\n";
        return false;
    }
}
