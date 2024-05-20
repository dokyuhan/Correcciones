#include <iostream> 
#include <vector>
#include <map>
#include <set>
#include <string>
#include "conexion.h"
#include "Ordenamiento.hpp"
#include "Busqueda.hpp"
#include "csv_reader.h"
#include "BST.hpp"


#pragma once
class Bitacora 
{
private:
    std::vector<Conexion> conexiones;
    std::map<std::string, std::vector<Conexion>> conexionesDia;

public:
    Bitacora() {};
    
    void loadConexiones(const std::string& filename) {
        conexiones = read_csv_conexion(filename);
        for (const Conexion& conn : conexiones) {
            std::string fecha_str = std::to_string(conn.getFecha().getDay()) + "-" + 
                                    std::to_string(conn.getFecha().getMonth()) + "-" + 
                                    std::to_string(conn.getFecha().getYear());
            conexionesDia[fecha_str].push_back(conn);
        }
    }

    const std::vector<Conexion>& getConexiones() const {
        return conexiones;
    }

    std::map<std::string, int> conexionesPorDia(const Date& fecha);
    void top(int n, const Date& fecha);

    void ordenarCSV();
    void registrosTotal();
    void registrosPorFecha();
    void buscarPorNombre();
    std::string direccionInterna();
    void computadoraServer();
    void servicioCorreo();
    void puertoMenor();

    std::map<std::string, std::vector<std::string>> getTop5SitesPerDay();
    std::map<std::string, std::string> findPersistentTop5Sites();
    std::vector<std::pair<std::string, std::string>> detectTrafficSpikes();

};
