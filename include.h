#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

enum commandType {
    SANITIZE, CHECK, COMPLEMENT, MRNA, ENCODE, DECODE,
    CREATE, PRINT, MUTATION, REPAIR, REVERSE, LONGEST,
    SHORTEST, PIPELINE, INVALID
};

#endif /* INCLUDE_H */