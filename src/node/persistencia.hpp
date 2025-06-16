#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP

#include "identidad.hpp"

void generarCarpeta();
void guardarIdentidad(const identidad& id);
bool cargarIdentidad(identidad& id);

#endif // PERSISTENCIA_HPP