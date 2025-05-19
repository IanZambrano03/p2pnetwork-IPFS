#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <sodium.h>
#include <fstream>
#include <iostream>
#include "identidad.hpp"

void generarCarpeta(){

   try {
    if (std::filesystem::create_directory("privateKey")) {
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

        std::ofstream filePriv("privateKey/private.key", std::ios::binary);

        if(filePriv.is_open()){
        
        filePriv.write(reinterpret_cast<const char*>(id.clavePrivada.data()), id.clavePrivada.size());
        filePriv.close();

        }else {
            std::cerr << "Error to create file: private.key \n";
        }

        std::ofstream filePub("privateKey/public.key", std::ios::binary);

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