#include <sodium.h>
#include <array>
#include <iostream>

struct identidad{

        std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> clavePublica;
        std::array<unsigned char, crypto_sign_SECRETKEYBYTES> clavePrivada;
    
    void generar(){

        try{

        int claves = crypto_sign_keypair(clavePublica.data(), clavePrivada.data());
        
        if(claves == 0 ){

            std::cout << "Your keys have been succesfully generated:  \n";

        } else {

            std::cout << "An error has ocurred !\n";
        }

        } catch(std::exception& e){
            
            std::cerr << "There is an error: " << e.what() << "\n";

        }


    }
};