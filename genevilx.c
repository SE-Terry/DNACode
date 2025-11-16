#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Enum
enum commandType {
    SANITIZE, CHECK, COMPLEMENT, MRNA, ENCODE, DECODE,
    CREATE, PRINT, MUTATION, REPAIR, REVERSE, LONGEST,
    SHORTEST, PIPELINE, INVALID
};

// ----- Begin: Student Answer -----

enum commandType getCommandType(char* command) {
    // ----- Begin: Student Answer -----
    
    return INVALID;
    // ----- End: Student Answer -----
}

char* sanitizeCode(char *codes) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

bool validCheck(char *codes) {
    // ----- Begin: Student Answer -----
    
    return false;
    // ----- End: Student Answer -----
}

char* generateComplement(char *codes) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

char* generateMRNA(char *codes) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

char* encode(char *codes) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

char* decode(char *codes) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

struct Gene {
    // ----- Begin: Student Answer -----
        
    // ----- End: Student Answer -----
};

int createTable(struct Gene *emptyTable, char **geneInfo) {
    // ----- Begin: Student Answer -----
    
    return 0;
    // ----- End: Student Answer -----
}

void printTable(struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----

    // Format reference
    // printf("| No. | Gene Name | DNA Sequence |\n");
    // printf("| %-3d | %-9s | %-12s |\n", 

    // ----- End: Student Answer -----
}

int isMutated(struct Gene gene, struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    
    return 0;
    // ----- End: Student Answer -----
}

int findMutatedCodons(struct Gene mutatedGene, char *originalGene) {
    // ----- Begin: Student Answer -----
    
    return 0;
    // ----- End: Student Answer -----
}

char* repairMutation(struct Gene gene, int pos) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

char* reverseGene(struct Gene gene) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

void longestGene(struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

void shortestGene(struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

void DNAPipeline(struct Gene gene) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

void getActionByCommand(enum commandType command, struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    
    // ----- End: Student Answer -----
}

// ----- End: Student Answer -----