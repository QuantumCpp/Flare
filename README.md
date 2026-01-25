# File‑Manager — Gestor de Archivos Inteligente

> **Una CLI pragmática para dominar I/O de archivos, `std::filesystem` y operaciones batch robustas.**

---

## ✨ Visión general

File‑Manager es una herramienta de línea de comandos escrita en C++ cuyo objetivo es unir trabajo real con el sistema de archivos (recorrido de directorios, metadatos, I/O) y patrones de diseño propios de software de calidad profesional: fases bien definidas, comportamiento determinista y manejo defensivo de errores.

Este repositorio es **a la vez una herramienta utilizable y un proyecto de aprendizaje profundo**, enfocado en entender cómo se construye una CLI sólida desde cero.

## 🎯 Objetivos

* Dominar I/O de archivos (texto y binario).
* Comprender y usar correctamente `std::filesystem` para navegación y metadatos.
* Diseñar un pequeño ecosistema de comandos extensible.
* Priorizar corrección, reproducibilidad y rendimiento predecible.

## 🔧 Funcionalidades

Un conjunto compacto pero potente de operaciones:

* **Listado de archivos** con filtros por extensión, tamaño y fechas.
* **Búsqueda** por nombre o por contenido (escaneo de texto / patrones).
* **Operaciones batch**: copiar, mover y renombrar con filtros y modo *dry‑run*.
* **Detección de duplicados** usando checksums (MD5 / SHA‑256) y prefiltros (tamaño, hash parcial).
* **Organización automática** de archivos por tipo, fecha u otras reglas.
* **Comparación y sincronización de directorios** con planes de acción reproducibles.
* **Reportes**: archivos más grandes, más antiguos y estadísticas resumidas.

## 🧭 Conceptos clave que se practican

* I/O de archivos binarios y de texto
* Recursión de directorios con manejo robusto de errores
* Manejo multiplataforma de rutas (`std::filesystem::path`)
* Filtrado, ordenamiento y búsqueda eficiente sobre grandes conjuntos
* Hashing para comparación fiable de archivos

## 🧱 Arquitectura (alto nivel)

La CLI está organizada en fases explícitas y desacopladas:

1. **Tokenización**
   Clasificación léxica de la línea de comandos (Command, Option, Positional, Separation).

2. **Canonización** *(planificada)*
   Resolución de alias (`-e` ↔ `--extension`), normalización de nombres y forma canónica de opciones.

3. **Validación**
   Verificación semántica: comandos válidos, opciones permitidas por comando, políticas de valores, eliminación de duplicados.

4. **Ejecución**
   Operaciones reales sobre el sistema de archivos usando primitivas seguras y verificables.

Esta separación reduce acoplamiento y permite escalar el sistema sin reescrituras grandes.

## ⚙️ Tecnologías y librerías

Dependencias mínimas, mayormente estándar:

* `std::filesystem` — navegación, metadatos, paths
* `std::fstream` y I/O de bajo nivel — lectura y escritura de archivos
* STL — `vector`, `unordered_map`, algoritmos (`sort`, `find`, etc.)
* Hashing (MD5 / SHA‑256) — implementación interna ligera o headers auditados

El objetivo es **dominar los fundamentos**, no esconder complejidad tras frameworks.

## ✅ Criterios de éxito

* Procesar **10,000 archivos** dentro de un tiempo objetivo configurable.
* Detectar duplicados correctamente mediante checksums.
* Sincronización de directorios con detección precisa de diferencias.
* Robustez frente a archivos corruptos, errores de lectura y permisos denegados.

## 🔮 Roadmap y pendientes

Estas tareas están **deliberadamente postergadas** o planificadas para la siguiente fase de madurez del proyecto.

### CLI y Parsing

* [ ] Tabla de alias (canonización): `-e` ↔ `--extension` → nombre canónico único.
* [ ] Resolver duplicados de opciones prefiriendo la variante con valor asociado.
* [ ] Soporte completo para `ValuePolicy::Optional`.
* [ ] Separación clara entre errores léxicos y semánticos.

### Validación y UX

* [ ] Mensajes de error más expresivos (índice del token, texto original).
* [ ] Modo estricto vs modo permisivo de validación.
* [ ] Diagnósticos detallados en *dry‑run*.

### Ejecución y rendimiento

* [ ] Abstracción `FileWorker` para manejo centralizado de errores y reintentos.
* [ ] Hashing por etapas: tamaño → hash parcial → hash completo.
* [ ] Benchmarks automáticos y perfiles de rendimiento (CI).

### Escalado profesional

* [ ] Especificación formal de comandos y opciones (schema interno).
* [ ] Arquitectura orientada a *handlers* o *command objects*.
* [ ] Posible soporte para concurrencia controlada.
* [ ] Documentación técnica (`ARCHITECTURE.md`) con diagramas de flujo.

## 🧩 Principios de diseño

* **Explícito > implícito**: el comportamiento debe ser visible y razonable.
* **Fail‑safe**: por defecto no destructivo (dry‑run primero).
* **Composable**: fases pequeñas y bien definidas.
* **Dependencias mínimas**: estándar C++ siempre que sea posible.

## 📝 Uso (borrador)

```
# listar por extensión de forma recursiva
file-manager list --extension=jpg --recursive

# buscar duplicados y generar reporte
file-manager find-duplicates --hash=sha256 --output=dupes.csv

# organizar por año en modo dry-run
file-manager organize --by=year --dry-run
```

## 📜 Licencia

Consulta el archivo `LICENSE` en la raíz del repositorio.
