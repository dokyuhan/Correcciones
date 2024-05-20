#include <iostream>
#include "date.h"
#include "time.h"

#pragma once
class Conexion
{
private:
    Date fecha;
    Time hora;
    std::string ipOrigen;
    std::string nomOrigen;
    std::string puertoOrigen;
    std::string ipDestino;
    std::string nomDestino;
    std::string puertoDestino;

public:
    Conexion() {};
    Conexion(const Date& fecha, const Time& hora, const std::string& ipOrigen, const std::string& puertoOrigen, const std::string& nomOrigen, const std::string& ipDestino, const std::string& puertoDestino, const std::string& nomDestino)
    : fecha(fecha), hora(hora), ipOrigen(ipOrigen), puertoOrigen(puertoOrigen), nomOrigen(nomOrigen), ipDestino(ipDestino), puertoDestino(puertoDestino), nomDestino(nomDestino) {}

    void setFecha(const Date& fecha) { this->fecha = fecha; }
    void setHora(const Time& hora) { this->hora = hora; }
    void setIpDestino(const std::string& ipDestino) { this->ipDestino = ipDestino; }
    void setIpOrigen(const std::string& ipOrigen) { this->ipOrigen = ipOrigen; }
    void setNomOrigen(const std::string& nomOrigen) { this->nomOrigen = nomOrigen; }
    void setNomDestino(const std::string& nomDestino) { this->nomDestino = nomDestino; }
    void setPuertoOrigen(const std::string& puertoOrigen) { this->puertoOrigen = puertoOrigen; }
    void setPuertoDestino(const std::string& puertoDestino) { this->puertoDestino = puertoDestino; }

    Date getFecha() const { return fecha; }
    Time getHora() const { return hora; }
    std::string getIpDestino() const { return ipDestino; }
    std::string getIpOrigen() const { return ipOrigen; }
    std::string getNomOrigen() const { return nomOrigen; }
    std::string getNomDestino() const { return nomDestino; }
    std::string getPuertoOrigen() const { return puertoOrigen; }
    std::string getPuertoDestino() const { return puertoDestino; }

    bool operator<(const Conexion& otra) const {
        // Compara primero por fecha
        if (this->getFecha() < otra.getFecha()) {
            return true;

        } else if (this->getFecha() == otra.getFecha()) {
            // Si las fechas son iguales, compara por hora
            return this->getHora() < otra.getHora();
        }
        return false;
    }

    bool operator == (const Conexion& otra) const {
        std::string nombreConex = this->nomOrigen.substr(0, this->nomOrigen.find('.'));
        std::string otroNombreConex = otra.nomOrigen.substr(0, otra.nomOrigen.find('.'));
        
        return nombreConex == otroNombreConex;
    }

    friend std::ostream& operator << (std::ostream& os, const Conexion& c) {
        os << "Fecha: " << c.fecha << ", Hora: " << c.hora << ", IP Origen: " << c.ipOrigen << ", Puerto Origen: " << c.puertoOrigen
           << ", Nombre Origen: " << c.nomOrigen << ", IP Destino: " << c.ipDestino
           << ", Puerto Destino: " << c.puertoDestino << ", Nombre Destino: " << c.nomDestino;
        return os;
    }
};
