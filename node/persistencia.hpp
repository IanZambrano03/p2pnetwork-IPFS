#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <sodium.h>
#include <fstream>
#include <iostream>
#include "identidad.hpp"

void generarCarpeta(){

   try {
    if (std::filesystem::create_directory("keys")) {
        std::cout << "A folder has been created with your private key\n";

    }else {
        std::cout << "Folder already exists, or could not be created\n";
    }
        } catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "You have a file error: " << e.what() << "\n";
        }

}

void guardarIdentidad(const identidad& id){

    try{

        std::ofstream filePriv("keys/private.key", std::ios::binary);

        if(filePriv.is_open()){
        
        filePriv.write(reinterpret_cast<const char*>(id.clavePrivada.data()), id.clavePrivada.size());
        filePriv.close();

        }else {
            std::cerr << "Error to create file: private.key \n";
        }

        std::ofstream filePub("keys/public.key", std::ios::binary);

        if(filePub.is_open()){
        
        filePub.write(reinterpret_cast<const char*>(id.clavePublica.data()), id.clavePublica.size());
        filePub.close();

        }else {
            std::cerr << "Error to create file: public.key \n";
        }
        

    }catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "You have a file error: " << e.what() << "\n";
        }
}

bool cargarIdentidad(identidad& id){
    
    try{

  if (!std::filesystem::exists("keys/private.key") || 
    !std::filesystem::exists("keys/public.key")) {
    std::cerr << "Missing key files.\n";
    return false;
}
    }catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "You have a file error: " << e.what() << "\n";
        }

        try{
    std::ifstream filePriv("keys/private.key", std::ios::binary); 
    std::ifstream filePub("keys/public.key", std::ios::binary);

    filePriv.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    filePub.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        
   if (filePriv.is_open() && filePub.is_open()) {
    filePriv.read(reinterpret_cast<char*>(id.clavePrivada.data()), id.clavePrivada.size());
    filePub.read(reinterpret_cast<char*>(id.clavePublica.data()), id.clavePublica.size());
    
    int privCount = filePriv.gcount();
    int pubCount = filePub.gcount();

    if (privCount == id.clavePrivada.size() && pubCount == id.clavePublica.size()) {
        std::cout << "Your identity has successfully been captured from local storage! \n";
        return true;
    } else {
        std::cerr << "Error: key file sizes mismatch.\n";
        std::cerr << "Private key bytes read: " << privCount
                  << " / Expected: " << id.clavePrivada.size() << "\n";
        std::cerr << "Public key bytes read: " << pubCount
                  << " / Expected: " << id.clavePublica.size() << "\n";
        return false;
    }
} else {
    std::cerr << "Error: Unable to open key files.\n";
    return false;
}        

    }catch (const std::ios_base::failure& e) {
    std::cerr << "Error while reading key files: " << e.what() << "\n";
    return false;
        }
}