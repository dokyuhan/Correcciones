#include <stack>
#include <string>
#include "Bitacora.h"

class ConexionesComputadora {
private:
    std::string IP;
    std::string Nombre;
    std::stack<Conexion> ConexionesEntrantes;
    std::vector<Conexion> ConexionesSalientes;

    Bitacora& bitacora;

public:
    ConexionesComputadora(Bitacora& bitacoraRef) : bitacora(bitacoraRef) {}
    ConexionesComputadora(const std::string& ip, const std::string& nombre, Bitacora& bitacoraRef) : IP(ip), Nombre(nombre), bitacora(bitacoraRef) {}

    void setIP(const std::string& ip) {
        IP = ip;
    }

    void setNombre(const std::string& nombre) {
        Nombre = nombre;
    }

    size_t getNumConexionesEntrantes() const {
        return ConexionesEntrantes.size();
    }

    size_t getNumConexionesSalientes() const {
        return ConexionesSalientes.size();
    }

    void conexionComputadora();
    std::string direccionInterna() {
        return bitacora.direccionInterna();
    }
    std::string nombreComputadora(const std::string& ip);
    void getUltimaConexionIp() const;
    void conexionesSeguidas() const;
};
