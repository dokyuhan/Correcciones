#include "Bitacora.h"
#include <algorithm>
#include <numeric>
#include <unordered_map>

// Funcion para ordenar el archivo CSV respecto a su fecha
void Bitacora::ordenarCSV() {
    //Utiliza la clase Ordenaiento para ordenar el vector de conexiones
    conexiones = Ordenamiento<Conexion>::mergesort(conexiones, Ordenamiento<Conexion>::asc);
}

//Funcion que encuentra los registros totales del archivo CSV
void Bitacora::registrosTotal() {
    std::cout << "Total de registros: " << conexiones.size() << std::endl;
    std::cout << std::endl;
}

//Funcion que encuentra los registros por fecha, en este caso es para el segundo dia del archivo
void Bitacora::registrosPorFecha() {
    // Parametros iniciales para encontrar el segundo dia
    Date primerDia = conexiones[0].getFecha();
    Date segundoDia(0, 0, 0);
    int contador = 0;
    bool encontrado = false;

    // Funcion que recorre el vector en donde 
    for (const auto& conexion : conexiones) {
        // Condicion en donde si el record no es igual al primer dia, se asigna el segundo dia
        if (conexion.getFecha() != primerDia) {
            if (segundoDia.getYear() == 0) {
                segundoDia = conexion.getFecha();
                encontrado = true;
            }
            // Condiicon de contador por si encuentra registros del mismo dia
            if (conexion.getFecha() == segundoDia) {
                contador++;
            }
            else if (encontrado) {
                break;
            }
        }
    }

    std::cout << "El segundo día registrado es " << segundoDia << " y tiene " << contador << " registros." << std::endl;
    std::cout << std::endl;
}

//Funcion que busca por los nombres deseados

void Bitacora::buscarPorNombre() {
    // Vector con los nombres a buscar
    std::vector<std::string> nombresBuscados = {"jeffrey", "betty", "katherine", "scott", "benjamin", "samuel", "raymond"};
    std::unordered_map<std::string, bool> encontrados;

    // Inicializa el mapa con false para cada nombre buscado unico
    for (const auto& nombre : nombresBuscados) {
        encontrados[nombre] = false;
    }

    // Funcion para buscar si existe algun nombre buscado en el vector
    for (const auto& nombre : nombresBuscados) {
        for (const auto& conexion : conexiones) {
            // Se crea la variable a comparar
            Conexion conexionNombre;
            conexionNombre.setNomOrigen(nombre);

            // Utilizamos la búsqueda secuencial para buscar la conexión específica
            int indice = Busqueda<Conexion>::busquedaSecuencial(conexiones, conexionNombre);
            
            // Condicion que aplica el resultado de la busqueda, si lo enecuentra cambia el valor a true
            if (indice != -1) {
                encontrados[nombre] = true;
                break; 
            }
        }
    }

    for (const auto& nombre : nombresBuscados) {
        std::cout << "La computadora de " << nombre << (encontrados[nombre] ? " fue encontrada." : " no fue encontrada.") << std::endl;
        std::cout << std::endl;
    }
}


//Funcion que encuentra la direccion interna de la red de la compañia
std::string Bitacora::direccionInterna() {
    // Inicializa la IP origen extrayendo los primeros 3 secciones de numeros
    std::string redInterna = conexiones[0].getIpOrigen().substr(0, conexiones[0].getIpOrigen().find_last_of('.'));
    int contador = 1;

    // Funcion que compara las 2 IPs en base a la posiicion de i y la IP origen principal
    for (size_t i = 1; i < conexiones.size(); ++i) {
        std::string redActual = conexiones[i].getIpOrigen().substr(0, conexiones[i].getIpOrigen().find_last_of('.'));
        // Condiciones, s son iguales se incrementa un contador
        if (redActual == redInterna) {
            contador++;
        // Si no se encontro la misma IP se le asigna la nueva IP (solo cuando se encuentra mas veces una IP que la otra)
        } else if (contador == 1) {
            redInterna = redActual;
        } else {
            // Si no se encuentra la misma IP se resta el contador
            contador--;
        }
    }

    return redInterna;
}

// Funcion para saber si existen computadoras llamadas server.reto.com
void Bitacora::computadoraServer() {
    bool encontrado = false;

    for (const auto& conexion : conexiones) {
        if (conexion.getNomOrigen() == "server.reto.com" || conexion.getNomDestino() == "server.reto.com") {
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        std::cout << "Se encontró una computadora llamada server.reto.com." << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << "No se encontró ninguna computadora llamada server.reto.com." << std::endl;
        std::cout << std::endl;
    }
}

// Funcion para saber que servicios de correo utiliza
void Bitacora::servicioCorreo() {
    std::vector<std::string> puertosCorreo = {"25", "110", "143", "587", "465", "993", "995"};
    std::vector<std::pair<std::string, std::string>> correosEncontrados;

    for (const auto& puerto : puertosCorreo) {
        for (const auto& conexion : conexiones) {
            if (conexion.getPuertoDestino() == puerto) {
                correosEncontrados.push_back({puerto, conexion.getNomDestino()});
                break;
            }
        }
    }

    std::cout << "Servicios de correo electrónico utilizados:" << std::endl;
    for (const auto& par : correosEncontrados) {
        std::cout << "- Puerto " << par.first << ": " << par.second << std::endl;
    }
    std::cout << std::endl;
}

// Funcion para saber que puertos abajo de 1000 utiliza
void Bitacora::puertoMenor() {
    std::vector<std::pair<std::string, std::string>> puertosDestino;

    for (const auto& conexion : conexiones) {
        // Verificamos si puertoDestino contiene un carácter '-', si lo contiene lo guarda de esa manera
        if (conexion.getPuertoDestino().find('-') == std::string::npos) {
            std::string puertoStr = conexion.getPuertoDestino();
            // Convertimos a int para verificar si es menor a 1000
            int puerto = std::stoi(puertoStr);

            if (puerto < 1000) {
                auto it = std::find_if(puertosDestino.begin(), puertosDestino.end(),
                    [puertoStr](const std::pair<std::string, std::string>& elemento) {
                        return elemento.first == puertoStr;
                    });
                // Si el puerto no se encontró en la lista, añadirlo
                if (it == puertosDestino.end()) {
                    puertosDestino.push_back({puertoStr, conexion.getNomDestino()});
                }
            }
        }
    }

    // Ordenar los puertos destino numéricamente
    std::sort(puertosDestino.begin(), puertosDestino.end(), 
        [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
            return std::stoi(a.first) < std::stoi(b.first);
        });

    std::cout << "Puertos destino numéricos menores a 1000 y nombres destino correspondientes:" << std::endl;
    for (const auto& par : puertosDestino) {
        std::cout << "- Puerto " << par.first << ": " << par.second << std::endl;
    }
    std::cout << std::endl;
}

std::map<std::string, int> Bitacora::conexionesPorDia(const Date& fecha) {
    std::map<std::string, int> resultado;
    for (const auto& conexion : conexiones) {
        if (conexion.getFecha() == fecha && conexion.getNomDestino() != "-" && conexion.getNomDestino().find("reto.com") == std::string::npos) {
            resultado[conexion.getNomDestino()]++;
        }
    }
    return resultado;
}

// Función para imprimir los sitios top
void Bitacora::top(int n, const Date& fecha) {
    std::map<std::string, int> conexiones = conexionesPorDia(fecha);
    BST<std::pair<int, std::string>> bst;  // Cambia el orden del par para que el entero vaya primero

    // Inserta las conexiones en el BST con el número de conexiones como la clave
    for (const auto& conexion : conexiones) {
        bst.insert(std::make_pair(conexion.second, conexion.first));
    }

    // Recupera los top N sitios
    std::vector<std::pair<int, std::string>> topSitios = bst.getTopN(n);
    for (const auto& sitio : topSitios) {
        std::cout << "Sitio: " << sitio.second << " - Conexiones: " << sitio.first << std::endl;
    }
}

std::map<std::string, std::vector<std::string>> Bitacora::getTop5SitesPerDay() {
    std::map<std::string, std::vector<std::string>> top5PerDay;
    for (auto& [date, conns] : conexionesDia) {
        std::map<std::string, int> siteCount;
        for (Conexion& conn : conns) {
            if (conn.getNomDestino() != "-") {  // Ignorar conexiones con destino '-'
                siteCount[conn.getNomDestino()]++;
            }
        }

        std::vector<std::pair<std::string, int>> counts;
        for (auto& [site, count] : siteCount) {
            counts.push_back({site, count});
        }

        sort(counts.begin(), counts.end(), [](auto& a, auto& b) {
            return a.second > b.second; // Orden descendente por count
        });

        std::vector<std::string> topSites;
        for (int i = 0; i < std::min(5, (int)counts.size()); i++) {
            topSites.push_back(counts[i].first);
        }
        top5PerDay[date] = topSites;
    }
    return top5PerDay;
}


std::map<std::string, std::string> Bitacora::findPersistentTop5Sites() {
    auto top5PerDay = getTop5SitesPerDay();
    std::map<std::string, std::set<std::string>> siteAppearances;

    // Recopilar días en que cada sitio aparece en el top 5
    for (auto& [date, sites] : top5PerDay) {
        for (const auto& site : sites) {
            siteAppearances[site].insert(date);
        }
    }

    // Encontrar el primer día de aparición para cada sitio
    std::map<std::string, std::string> firstAppearance;
    for (const auto& [site, dates] : siteAppearances) {
        firstAppearance[site] = *dates.begin();
    }

    // Verificar que cada sitio aparece en todos los días desde su primer aparición
    std::map<std::string, std::string> persistentSites;
    for (const auto& [site, startDate] : firstAppearance) {
        bool isPersistent = true;
        auto it = top5PerDay.find(startDate);
        while (it != top5PerDay.end() && isPersistent) {
            if (std::find(it->second.begin(), it->second.end(), site) == it->second.end()) {
                isPersistent = false;
            }
            ++it;
        }
        if (isPersistent) {
            persistentSites[site] = startDate;
        }
    }

    return persistentSites;
}




std::vector<std::pair<std::string, std::string>> Bitacora::detectTrafficSpikes() {
    auto top5PerDay = getTop5SitesPerDay();
    std::map<std::string, std::vector<std::pair<int, std::string>>> siteTraffic;  // Cambiado para incluir fecha

    // Recolectar conteos de tráfico y las fechas asociadas
    for (auto& [date, sites] : top5PerDay) {
        for (auto& site : sites) {
            int count = std::count_if(conexionesDia[date].begin(), conexionesDia[date].end(),
                                      [&site](const Conexion& conn) { return conn.getNomDestino() == site; });
            siteTraffic[site].push_back(std::make_pair(count, date));  // Guardar también la fecha
        }
    }

    std::vector<std::pair<std::string, std::string>> sitesWithSpikes;
    for (auto& [site, traffics] : siteTraffic) {
        // Calcular la media de tráfico para el sitio
        int sum = std::accumulate(traffics.begin(), traffics.end(), 0, 
                                  [](int acc, const std::pair<int, std::string>& p) { return acc + p.first; });
        double mean = sum / (double)traffics.size();

        // Detectar picos significativos
        for (auto& [count, date] : traffics) {
            if (count > 2 * mean) {  // Si el tráfico es más del doble de la media
                sitesWithSpikes.push_back(std::make_pair(site, date));
            }
        }
    }

    return sitesWithSpikes;
}
