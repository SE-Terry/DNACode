#include "include.h"
#include "genevilx.c"

void tc1(){
    char output[301];
    generateComplement("ATGAAATAA", output);
    printf("\"%s\"\n", output);
    generateMRNA("ATGAAATAA", output);
    printf("\"%s\"\n", output);
}
void tc2(){
    char *geneInfo[] = {
        "ATGCGTTAA",
        "ATGACGCTAGTTTGA",
        "ATGAAACTATTTGGGTGA",
        NULL
    };

    struct Gene geneTable[3];
    int count = createTable(geneTable, geneInfo);

    printf("=== TEST ALL COMMANDS ===\n\n");

    // 1. SANITIZE
    printf("1. SANITIZE COMMAND:\n");
    getActionByCommand(SANITIZE, geneTable, count);
    printf("\n");

    // 2. CHECK
    printf("2. CHECK COMMAND:\n");
    getActionByCommand(CHECK, geneTable, count);
    printf("\n");

    // 3. COMPLEMENT
    printf("3. COMPLEMENT COMMAND:\n");
    getActionByCommand(COMPLEMENT, geneTable, count);
    printf("\n");

    // 4. MRNA
    printf("4. MRNA COMMAND:\n");
    getActionByCommand(MRNA, geneTable, count);
    printf("\n");

    // 5. ENCODE
    printf("5. ENCODE COMMAND:\n");
    getActionByCommand(ENCODE, geneTable, count);
    printf("\n");

    // 6. DECODE
    printf("6. DECODE COMMAND:\n");
    getActionByCommand(DECODE, geneTable, count);
    printf("\n");

    // 7. PRINT
    printf("7. PRINT COMMAND:\n");
    getActionByCommand(PRINT, geneTable, count);
    printf("\n");

    // 8. MUTATION
    printf("8. MUTATION COMMAND:\n");
    getActionByCommand(MUTATION, geneTable, count);
    printf("\n");

    // 9. REPAIR
    printf("9. REPAIR COMMAND:\n");
    getActionByCommand(REPAIR, geneTable, count);
    printf("\n");

    // 10. REVERSE
    printf("10. REVERSE COMMAND:\n");
    getActionByCommand(REVERSE, geneTable, count);
    printf("\n");

    // 11. LONGEST
    printf("11. LONGEST COMMAND:\n");
    getActionByCommand(LONGEST, geneTable, count);
    printf("\n");

    // 12. SHORTEST
    printf("12. SHORTEST COMMAND:\n");
    getActionByCommand(SHORTEST, geneTable, count);
    printf("\n");

    // 13. PIPELINE
    printf("13. PIPELINE COMMAND:\n");
    getActionByCommand(PIPELINE, geneTable, count);
    printf("\n");

    // 14. INVALID
    printf("14. INVALID COMMAND:\n");
    getActionByCommand(INVALID, geneTable, count);
    printf("\n");
}
void tc3(){
    struct Gene mutated ={"G4", "ATGCGTTA", 9, "", "", ""};;
    char original[] = "ATGCGTTAA";

    printf("%d\n", findMutatedCodons(mutated, original));
}

void tc4(){ 
    struct Gene g = {"G1_mut", "TTGAAATAA", 9, "", "", ""};
    char repaired[301];

    repairMutation(g, 1, repaired);
    printf("%s\n", repaired);
}

/* Harder edge cases */
void tc5_invalid_inputs() {
    char out[601];
    /* encode with invalid length -> should print INVALID and return sanitized original */
    encode("AT", out);
    printf("encode short -> %s\n", out);

    /* complement with mixed/dirty input */
    generateComplement("  a-tg@atatag!!**  ", out);
    printf("complement dirty -> %s\n", out);

    /* mrna with lowercase + junk */
    generateMRNA("xxttgatagTAA", out);
    printf("mrna dirty -> %s\n", out);

    /* decode then sanitize */
    decode("655231675309844420", out);
    printf("decode mixed -> %s\n", out);
}

void tc6_createTable_mixed() {
    char *geneInfo[] = {
        "  ATGCGTTAA   ",
        "  a-tg@atatag!!**  ",
        "123456", /* numeric -> decode -> sanitize */
        "xx",      /* too short -> sanitized empty -> skipped */
        NULL
    };

    struct Gene table[5];
    int count = createTable(table, geneInfo);
    printf("created: %d\n", count);
    printTable(table, count);
}

int main () {
    tc1();
    tc2();
    tc3();
    tc4();
    tc5_invalid_inputs();
    tc6_createTable_mixed();
    return 0;
}

// gcc test_case.c -o test_case.exe
// .\test_case.exe