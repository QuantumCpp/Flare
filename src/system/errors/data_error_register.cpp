#include "data_error_register.h"
#include "../types/DataError.h"
#include "../types/ValidationError.h"
#include "../../system/registry/error/error_registry.h"
#include "../../system/errors/print_error.h"

void RegisterAllError() {

    // ================= Input / Syntax =================
    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::EmptyInput;
        err.NameError = "EmptyArguments";
        err.ShortDetail = "No se introdujo ningun elemento";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::InvalidSyntax;
        err.NameError = "InvalidSyntax";
        err.ShortDetail = "La sintaxis de entrada es invalida";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    // ================= Command =================
    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::NoCommand;
        err.NameError = "NoCommand";
        err.ShortDetail = "No se encontro ningun comando";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::MultipleCommands;
        err.NameError = "MultipleCommands";
        err.ShortDetail = "Se detectaron multiples comandos";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::CommandNotFound;
        err.NameError = "CommandNotFound";
        err.ShortDetail = "El comando no existe";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::CommandIncorrectPosition;
        err.NameError = "CommandIncorrectPosition";
        err.ShortDetail = "El comando no esta en la posicion correcta";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    // ================= Option =================
    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::OptionNotFound;
        err.NameError = "OptionNotFound";
        err.ShortDetail = "La opcion no existe";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::OptionForWrongCommand;
        err.NameError = "OptionForWrongCommand";
        err.ShortDetail = "La opcion no pertenece a este comando";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::DuplicateOption;
        err.NameError = "DuplicateOption";
        err.ShortDetail = "La opcion fue especificada multiples veces";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::OptionRequiresValue;
        err.NameError = "OptionRequiresValue";
        err.ShortDetail = "La opcion requiere un valor";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::OptionDoesNotAcceptValue;
        err.NameError = "OptionDoesNotAcceptValue";
        err.ShortDetail = "La opcion no acepta valores";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::ValueNotProvided;
        err.NameError = "ValueNotProvided";
        err.ShortDetail = "No se proporciono un valor valido";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    // ================= Type Validation =================
    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::InvalidValueType_Integer;
        err.NameError = "InvalidInteger";
        err.ShortDetail = "Se esperaba un entero valido";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::InvalidValueType_Float;
        err.NameError = "InvalidFloat";
        err.ShortDetail = "Se esperaba un flotante valido";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::InvalidValueType_Path;
        err.NameError = "InvalidPath";
        err.ShortDetail = "La ruta proporcionada es invalida";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::InvalidValueType_Date;
        err.NameError = "InvalidDate";
        err.ShortDetail = "El formato de fecha es invalido";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::ValueOutOfRange;
        err.NameError = "ValueOutOfRange";
        err.ShortDetail = "El valor esta fuera del rango permitido";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::InvalidChoice;
        err.NameError = "InvalidChoice";
        err.ShortDetail = "El valor no es una opcion valida";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    // ================= Conflict =================
    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::ConflictingOptions;
        err.NameError = "ConflictingOptions";
        err.ShortDetail = "Opciones mutuamente excluyentes";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::ConflictingValues;
        err.NameError = "ConflictingValues";
        err.ShortDetail = "Los valores entran en conflicto";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    // ================= Dependency =================
    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::MissingRequiredOption;
        err.NameError = "MissingRequiredOption";
        err.ShortDetail = "Falta una opcion requerida";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::MissingRequiredPositional;
        err.NameError = "MissingRequiredPositional";
        err.ShortDetail = "Falta un argumento posicional requerido";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::TooManyPositionals;
        err.NameError = "TooManyPositionals";
        err.ShortDetail = "Demasiados argumentos posicionales";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::TooFewPositionals;
        err.NameError = "TooFewPositionals";
        err.ShortDetail = "Faltan argumentos posicionales";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    // ================= Filesystem =================
    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::PathDoesNotExist;
        err.NameError = "PathDoesNotExist";
        err.ShortDetail = "La ruta no existe";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::PathNotDirectory;
        err.NameError = "PathNotDirectory";
        err.ShortDetail = "La ruta no es un directorio";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::PathNotFile;
        err.NameError = "PathNotFile";
        err.ShortDetail = "La ruta no es un archivo";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::PathNotReadable;
        err.NameError = "PathNotReadable";
        err.ShortDetail = "No hay permisos de lectura";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::PathNotWritable;
        err.NameError = "PathNotWritable";
        err.ShortDetail = "No hay permisos de escritura";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    // ================= Misc =================
    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::MultipleSeparators;
        err.NameError = "MultipleSeparators";
        err.ShortDetail = "Se detectaron multiples separadores '--'";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }

    {
        DataErrorDetail err;
        err.ErrorID = ValidationError::UnknownError;
        err.NameError = "UnknownError";
        err.ShortDetail = "Error desconocido";
        err.handler = PrintDetailGenericError;
        RegisterError(err);
    }
}

