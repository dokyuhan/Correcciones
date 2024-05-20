#ifndef csv_reader_h
#define csv_reader_h

#include <vector>
#include "conexion.h"

std::vector<Conexion> read_csv_conexion(std::string filename);

#endif /* csv_reader_h */