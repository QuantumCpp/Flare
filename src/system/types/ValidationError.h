// ValidationError.h
#pragma once

enum class ValidationError {
    // Success
    AllCorrect = 0,
    
    // Input/Syntax Errors (1-10)
    EmptyInput = 1,                    // No arguments provided
    InvalidSyntax = 2,                 // Malformed input
    
    // Command Errors (11-20)
    NoCommand = 11,                    // No command found in tokens
    MultipleCommands = 12,             // More than one command specified
    CommandNotFound = 13,              // Command doesn't exist in registry
    CommandIncorrectPosition = 14,     // Command not in first position
    CommandNotImplemented = 100,  

    // Option Errors (21-40)
    OptionNotFound = 21,               // Option doesn't exist for this command
    OptionForWrongCommand = 22,        // Option exists but not for this command
    DuplicateOption = 23,              // Same option specified multiple times
    OptionRequiresValue = 24,          // Option needs value but missing
    OptionDoesNotAcceptValue = 25,     // Option doesn't accept values
    ValueNotProvided = 26,             // Value is empty or whitespace
    
    // Type Validation Errors (41-60)
    InvalidValueType_Integer = 41,     // Expected integer, got something else
    InvalidValueType_Float = 42,       // Expected float, got something else
    InvalidValueType_Path = 43,        // Invalid path format
    InvalidValueType_Date = 44,        // Invalid date format
    ValueOutOfRange = 46,              // Numeric value out of allowed range
    InvalidChoice = 47,                // Value not in allowed choices list
    
    // Conflict Errors (61-70)
    ConflictingOptions = 61,           // Mutually exclusive options present
    ConflictingValues = 62,            // Option values contradict each other
    
    // Dependency Errors (71-80)
    MissingRequiredOption = 71,        // Required option is missing
    MissingRequiredPositional = 72,    // Required positional argument missing
    TooManyPositionals = 73,           // More positional args than allowed
    TooFewPositionals = 74,            // Fewer positional args than required
    
    // Filesystem Validation (81-90)
    PathDoesNotExist = 81,             // Specified path doesn't exist
    PathNotDirectory = 82,             // Path exists but isn't a directory
    PathNotFile = 83,                  // Path exists but isn't a file
    PathNotReadable = 84,              // No read permissions
    PathNotWritable = 85,              // No write permissions
    
    // Miscellaneous (91-99)
    MultipleSeparators = 91,           // More than one '--' separator
    UnknownError = 99                  // Uncategorized error
};
