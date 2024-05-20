#include <fstream>
#include <sstream>
#include <stdexcept>
#include "csv_reader.h"

std::vector<Conexion> read_csv_conexion(std::string filename) {
    std::vector<Conexion> conexiones;
    std::ifstream file(filename);

    if (!file.is_open()) throw std::runtime_error("No se puede abrir el archivo");

    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);

        std::string fechaStr, horaStr, ipOrigen, puertoOrigen, nomOrigen, ipDestino, puertoDestino, nomDestino;

        getline(ss, fechaStr, ',');
        getline(ss, horaStr, ',');
        getline(ss, ipOrigen, ',');
        getline(ss, puertoOrigen, ',');
        getline(ss, nomOrigen, ',');
        getline(ss, ipDestino, ',');
        getline(ss, puertoDestino, ',');
        getline(ss, nomDestino, ',');

        int dia, mes, anio, hora, minuto, segundo;
        char delim;
        std::stringstream fechaSS(fechaStr);
        fechaSS >> dia >> delim >> mes >> delim >> anio;
        Date fecha(dia, mes, anio);

        std::stringstream horaSS(horaStr);
        horaSS >> hora >> delim >> minuto >> delim >> segundo;
        Time horaObj(hora, minuto, segundo);

        Conexion conexion(fecha, horaObj, ipOrigen, puertoOrigen, nomOrigen, ipDestino, puertoDestino, nomDestino);
        conexiones.push_back(conexion);
    }

    file.close();
    return conexiones;
}