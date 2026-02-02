# c-files — CLI File Manager

> **Una herramienta de línea de comandos profesional en C++ para operaciones avanzadas sobre sistemas de archivos**

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C++-20-00599C.svg?logo=c%2B%2B)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

---

## 📖 Tabla de Contenidos

- [Visión General](#-visión-general)
- [Características](#-características)
- [Arquitectura](#-arquitectura)
- [Instalación](#-instalación)
- [Uso](#-uso)
- [Estado del Proyecto](#-estado-del-proyecto)
- [Contribuir](#-contribuir)
- [Licencia](#-licencia)

---

## 🎯 Visión General

**c-files** es una CLI (Command Line Interface) escrita en C++20 diseñada para gestionar archivos y directorios de manera eficiente, segura y escalable. El proyecto prioriza:

- **Arquitectura limpia**: Fases bien definidas (tokenización → clasificación → validación → ejecución)
- **Manejo robusto de errores**: Sistema de registro centralizado con mensajes descriptivos
- **Extensibilidad**: Diseño modular que permite agregar comandos y opciones sin refactorización
- **Rendimiento**: Uso de `std::filesystem` y algoritmos STL optimizados

Este proyecto es tanto una **herramienta útil** como un **caso de estudio** en diseño de software de calidad profesional en C++.

---

## ✨ Características

### Comandos Implementados

#### `list` - Listado Avanzado de Archivos
Lista archivos y directorios con filtrado y ordenamiento configurable.

**Opciones disponibles:**
- `--recursive` / `-r`: Recorrido recursivo de subdirectorios
- `--all` / `-a`: Mostrar archivos ocultos (conflictivo con `--extension`)
- `--extension=<ext>` / `-e=<ext>`: Filtrar por extensión (conflictivo con `--all`)
- `--min-size=<bytes>` / `-s=<bytes>`: Tamaño mínimo de archivo
- `--max-size=<bytes>`: Tamaño máximo de archivo
- `--after-date=<YYYY-MM-DD>` / `-d=<YYYY-MM-DD>`: Modificado después de fecha
- `--before-date=<YYYY-MM-DD>`: Modificado antes de fecha
- `--sort-by=<criteria>`: Ordenar por nombre, tamaño o fecha
- `--reverse`: Invertir orden (requiere `--sort-by`)
- `--long` / `-l`: Formato detallado con metadatos (conflictivo con `--simple`)
- `--simple`: Solo nombres de archivo (conflictivo con `--long`)

### Comandos Planificados

- **`find`**: Búsqueda por nombre/contenido con soporte de regex
- **`copy`/`move`**: Operaciones batch con dry-run y filtros
- **`duplicate`**: Detección de duplicados usando checksums (MD5/SHA-256)
- **`organize`**: Organización automática por tipo/fecha
- **`sync`**: Sincronización bidireccional de directorios
- **`stats`**: Reportes de uso de disco y archivos grandes

---

## 🏗️ Arquitectura

El diseño sigue un **pipeline de 4 fases** desacopladas:

```
Entrada del usuario
       ↓
┌──────────────────┐
│  1. TOKENIZATION │  → Análisis léxico (Command, Option, Positional, Separation)
└──────────────────┘
       ↓
┌──────────────────┐
│ 2. CLASSIFICATION│  → Agrupación + Normalización de alias (-r → --recursive)
└──────────────────┘  → Detección de duplicados
       ↓
┌──────────────────┐
│  3. VALIDATION   │  → Validación semántica (comandos válidos, opciones compatibles)
└──────────────────┘  → Verificación de políticas de valores
       ↓
┌──────────────────┐
│   4. EXECUTION   │  → Operaciones sobre filesystem
└──────────────────┘
       ↓
    Resultado
```

### Estructura del Proyecto

```
c-files/
├── src/
│   ├── main.cpp                    # Punto de entrada
│   ├── core/                       # Pipeline de procesamiento
│   │   ├── tokenization/           # Fase 1: Análisis léxico
│   │   ├── classification/         # Fase 2: Agrupación y normalización
│   │   ├── validation/             # Fase 3: Validación semántica
│   │   └── execution/              # Fase 4: Ejecución de comandos
│   ├── commands/                   # Implementación de comandos
│   │   └── list/                   # Comando list
│   ├── system/                     # Infraestructura del sistema
│   │   ├── registry/               # Registros centralizados
│   │   │   ├── command/            # Registro de comandos
│   │   │   ├── option/             # Registro de opciones
│   │   │   └── error/              # Registro de errores
│   │   ├── types/                  # Tipos y enums del sistema
│   │   └── errors/                 # Manejo de errores
│   └── utils/                      # Utilidades compartidas
├── tests/                          # Suite de pruebas
├── docs/                           # Documentación técnica
│   └── DESIGN.md                   # Especificación de diseño
├── build/                          # Artefactos de compilación
└── CMakeLists.txt                  # Configuración de CMake
```

### Componentes Clave

#### Sistema de Registro
Tres registros centralizados que desacoplan metadata de implementación:

1. **Command Registry** (`command_registry.cpp`)
   - Mapea nombres de comandos a `CommandMetaData`
   - Define opciones permitidas por comando
   - Almacena ejemplos de uso

2. **Option Registry** (`option_registry.cpp`)
   - Normaliza alias (`-r` → `--recursive`)
   - Define políticas de valores (`Required`, `Optional`, `None`)
   - Maneja conflictos entre opciones (`--all` vs `--extension`)

3. **Error Registry** (`error_registry.cpp`)
   - Centraliza mensajes de error
   - Asocia códigos de error con handlers de impresión

---

## 🚀 Instalación

### Requisitos

- **Compilador**: GCC 10+ / Clang 12+ / MSVC 19.28+ (soporte C++20)
- **CMake**: 3.20 o superior
- **Sistema Operativo**: Linux, macOS, Windows

### Compilación

```bash
# Clonar el repositorio
git clone https://github.com/tu-usuario/c-files.git
cd c-files

# Crear directorio de compilación
mkdir build && cd build

# Configurar con CMake
cmake ..

# Compilar
make

# El binario estará en build/c-files
./c-files --help
```

### Instalación Global (Opcional)

```bash
# Desde el directorio build/
sudo make install

# Ahora puedes usar c-files desde cualquier lugar
c-files list /home
```

---

## 📚 Uso

### Sintaxis General

```bash
c-files <comando> [opciones] [argumentos_posicionales]
```

### Ejemplos

```bash
# Listar archivos del directorio actual
c-files list

# Listar recursivamente todos los .cpp
c-files list --recursive --extension=.cpp /home/proyecto

# Formato detallado, ordenado por tamaño, invertido
c-files list --long --sort-by=size --reverse .

# Archivos modificados después del 2024-01-01, mayores a 1MB
c-files list --after-date=2024-01-01 --min-size=1048576

# Opciones cortas anidadas (-ral = -r -a -l)
c-files list -ral /etc

# Separador para argumentos posicionales con guiones
c-files list -- -nombre-con-guiones
```

### Convenciones de Opciones

- **Opciones largas con valor**: `--extension=.txt` (NO `--extension .txt`)
- **Opciones cortas**: `-e=.txt`  (NO `-e .txt`)
- **Flags sin valor**: `--recursive`, `-r`
- **Anidamiento de flags**: `-abc` equivale a `-a -b -c`
- **Separador `--`**: Todo después se trata como posicional

---

## 🛠️ Tecnologías Utilizadas

| Componente | Tecnología | Propósito |
|------------|-----------|-----------|
| **Core** | C++20 | Lenguaje base |
| **Filesystem** | `std::filesystem` | Operaciones de archivos |
| **Contenedores** | STL (`vector`, `unordered_map`, `set`) | Estructuras de datos |
| **Build System** | CMake 3.20+ | Compilación multiplataforma |
| **Testing** | Custom framework | Pruebas unitarias |

**Filosofía de dependencias**: Priorizar la biblioteca estándar sobre dependencias externas.

---

## 🤝 Contribuir

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama de feature (`git checkout -b feature/nueva-funcionalidad`)
3. Commit tus cambios siguiendo [Conventional Commits](https://www.conventionalcommits.org/)
4. Push a la rama (`git push origin feature/nueva-funcionalidad`)
5. Abre un Pull Request

### Estándares de Código

- **Formato**: ClangFormat con Google Style
- **Convenciones**: `PascalCase` para funciones/variables/clases
- **Comentarios**: Doxygen para documentación de API
- **Tests**: Cobertura mínima del 80%

---

## 📄 Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo [LICENSE](LICENSE) para más detalles.

---

<div align="center">
  <sub>Hecho con ❤️ y C++</sub>
</div>
