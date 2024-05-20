#include <iostream>
#include "Bitacora.h"
#include "ConexionesComputadora.h"

int main() {
    std::string archivoConexiones = "/Users/dokyuhan/Documents/Programacion de estructura de datos y algoritmos fundamentales/Reto/Actividad3.2/equipo8.csv";

    // Carga y preparación de datos en Bitacoras
    Bitacora bitacora;
    bitacora.loadConexiones(archivoConexiones);
    //bitacora.ordenarCSV();  // Asumimos que quieres los datos ordenados
    // Creación de una instancia de ConexionesComputadora usando la referencia de Bitacora
    ConexionesComputadora computadora(bitacora);

    Date fecha;

    int opcion, direccion, n, dia, mes, anio;
    std::string sitio;
    do {
        std::cout << "---------- Menu ----------" << std::endl;
        std::cout << "1. Registros totales del archivo" << std::endl;
        std::cout << "2. Registros del segundo día" << std::endl;
        std::cout << "3. Verificar computadoras por nombre" << std::endl;
        std::cout << "4. Direccion interna de la red de la compañía" << std::endl;
        std::cout << "5. Verificar existencia de server.reto.com" << std::endl;
        std::cout << "6. Servicios de correo utilizados" << std::endl;
        std::cout << "7. Puertos usados por debajo de 1000" << std::endl;
        std::cout << "8. Configurar IP y Nombre de una Computadora, Datos sobre esa computadora" << std::endl;
        std::cout << "9. Ver top N sitios para una fecha específica" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cout << std::endl;

        switch (opcion) {
            case 1:
                bitacora.registrosTotal();
                break;
            case 2:
                bitacora.registrosPorFecha();
                break;
            case 3:
                bitacora.buscarPorNombre();
                break;
            case 4:
                std::cout << "Direccion interna de la red: " << bitacora.direccionInterna() << std::endl;
                break;
            case 5:
                bitacora.computadoraServer();
                break;
            case 6:
                bitacora.servicioCorreo();
                break;
            case 7:
                bitacora.puertoMenor();
                break;
            case 8:
                std::cout << "Introduzca un número entre 1 y 150: ";
                std::cin >> direccion;
                if (direccion < 1 || direccion > 150) {
                    std::cerr << "Número fuera de rango. Debe ser entre 1 y 150." << std::endl;
                } else {
                    std::string ip = computadora.direccionInterna() + "." + std::to_string(direccion);
                    computadora.setIP(ip);
                    std::string nombre = computadora.nombreComputadora(ip);
                    computadora.setNombre(nombre);

                    computadora.conexionComputadora();
                    std::cout << "IP de la computadora: " << ip << std::endl;
                    std::cout << "Nombre de la computadora: " << nombre << std::endl;

                    computadora.getUltimaConexionIp();
                    std::cout << "Conexiones entrantes: " << computadora.getNumConexionesEntrantes() << std::endl;
                    std::cout << "Conexiones salientes: " << computadora.getNumConexionesSalientes() << std::endl;

                    computadora.conexionesSeguidas();

                }
                break;
            case 9: {
                auto topSites = bitacora.getTop5SitesPerDay();
                auto persistentSites = bitacora.findPersistentTop5Sites();
                auto spikes = bitacora.detectTrafficSpikes();

                std::cout << "Top 5 sites per day:" << std::endl;
                for (const auto& [date, sites] : topSites) {
                    std::cout << "Date: " << date << std::endl;
                    std::cout << "Top Sites: ";
                    for (const std::string& site : sites) {
                        std::cout << site << ", ";
                    }
                    std::cout << std::endl << std::endl;
                }

                std::cout << "Ingrese la fecha: " << std::endl;
                std::cout << "Día: ";
                std::cin >> dia;
                if (dia < 1 || dia > 31) {
                    std::cerr << "Día fuera de rango. Debe ser entre 1 y 31." << std::endl;
                    break;
                }
                std::cout << "Mes: ";
                std::cin >> mes;
                if (mes < 1 || mes > 12) {
                    std::cerr << "Mes fuera de rango. Debe ser entre 1 y 12." << std::endl;
                    break;
                }
                std::cout << "Año: ";
                std::cin >> anio;
                fecha = Date(dia, mes, anio);
                std::cout << "Conexiones en el día: " << fecha.getDay() << "/" << fecha.getMonth() << "/" << fecha.getYear() << std::endl;
                std::cout << std::endl;

                std::cout << "Ingrese el número N de top sitios que desea ver: ";
                std::cin >> n;
                std::cout << std::endl;
                bitacora.top(n, fecha);

                std::cout << std::endl;

                std::cout << "Sitios persistentes en el Top 5 desde su primera aparición:" << std::endl;
                for (const auto& [site, startDate] : persistentSites) {
                    std::cout << "Sitio: " << site << " - Desde: " << startDate << std::endl;
                }
                std::cout << std::endl;

                std::cout << "Sitios con mayor trafico en su fecha: " << std::endl;
                for (const auto& [site, date] : spikes) {
                    std::cout << "Site: " << site << " - Date: " << date << std::endl;
                }
                
                break;
            }
            case 0:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida." << std::endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}
