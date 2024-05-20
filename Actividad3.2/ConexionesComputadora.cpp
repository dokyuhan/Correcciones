#include "ConexionesComputadora.h"


void ConexionesComputadora::conexionComputadora() {
    for (const auto& conexion : bitacora.getConexiones()) {
        if (conexion.getIpDestino() == IP) {
            ConexionesEntrantes.push(conexion);
        }

        if (conexion.getIpOrigen() == IP) {
            ConexionesSalientes.push_back(conexion);
        }
    }
}

std::string ConexionesComputadora::nombreComputadora(const std::string& ip) {
    for (const auto& conexion : bitacora.getConexiones()) {
        if (conexion.getIpOrigen() == ip) {
            std::string nombre = conexion.getNomOrigen();
            return nombre.substr(0, nombre.find('.'));
        }
    }
    return "Nombre no encontrado";  // Retorna esto si no encuentra la IP.
}

void ConexionesComputadora::getUltimaConexionIp() const {
    if (!ConexionesEntrantes.empty()) {
        Conexion ultima = ConexionesEntrantes.top();
        
        // Obtiene los primeros tres nodos de la IP destino de la última conexión
        std::string ultimaIp = ultima.getIpDestino().substr(0, ultima.getIpDestino().find_last_of('.'));
        std::string ipBase = IP.substr(0, IP.find_last_of('.'));  // Obtiene los primeros tres nodos de la IP de la computadora

        if (ultimaIp == ipBase) {
            std::cout << "La última conexión recibida fue interna:" << std::endl;
        } 
        else {
            std::cout << "La última conexión recibida fue externa:" << std::endl;
        }
        std::cout << ultima << std::endl;
    }
}


void ConexionesComputadora::conexionesSeguidas() const {
    std::vector<std::string> puertosInteres = {"80", "443"};
    std::string last_site = "";
    int last_count = 0;

    for (const auto& conexion : bitacora.getConexiones()) {
        std::string site = conexion.getNomDestino();
        std::string puerto = conexion.getPuertoDestino();

        // Comprobar si el puerto de la conexión actual está en la lista de puertos de interés
        if (std::find(puertosInteres.begin(), puertosInteres.end(), puerto) != puertosInteres.end()) {
            std::string site_key = site + ":" + puerto;

            if (site_key == last_site) {
                last_count++;
                if (last_count == 3) { // Verifica si hay 3 conexiones seguidas al mismo sitio
                    std::cout << "La computadora ha hecho 3 conexiones seguidas al mismo sitio web: " << site << " en el puerto " << puerto << std::endl;
                    std::cout << std::endl;
                    return;
                }
            } else {
                last_site = site_key;
                last_count = 1;
            }
        }
    }

    std::cout << "No se encontraron 3 conexiones seguidas al mismo sitio web." << std::endl;
}