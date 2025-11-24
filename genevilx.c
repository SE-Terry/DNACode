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
    if (command == NULL) {
        return INVALID;
    }

    while (*command == ' ' || *command == '\t') {
        command++;
    }

    if (*command == '\0') {
        return INVALID;
    }

    // Lay tu dau tien cua lenh, bo qua khoang trang va tab dau dong
    // Chuyen tu do thanh chu hoa, de so sanh khong phan biet chu hoa chu thuong
    // Cach nay giup nhan dien lenh duoc nhap bang bat ki chu hoa hoac thuong nao
    char firstWord[64];
    int i = 0;
    while (command[i] != '\0' && !isspace((unsigned char)command[i]) && i < 63) {
        firstWord[i] = (char)toupper((unsigned char)command[i]);
        i++;
    }
    firstWord[i] = '\0';

    if (strcmp(firstWord, "SANITIZE") == 0) {
        return SANITIZE;
    }
    if (strcmp(firstWord, "VALIDATION") == 0 || strcmp(firstWord, "CHECK") == 0) {
        return CHECK;
    }
    if (strcmp(firstWord, "ENCODE") == 0) {
        return ENCODE;
    }
    if (strcmp(firstWord, "DECODE") == 0) {
        return DECODE;
    }
    if (strcmp(firstWord, "CREATE") == 0) {
        return CREATE;
    }
    if (strcmp(firstWord, "PRINT") == 0) {
        return PRINT;
    }
    if (strcmp(firstWord, "DETECT") == 0 || strcmp(firstWord, "MUTATION") == 0) {
        return MUTATION;
    }
    if (strcmp(firstWord, "REPAIR") == 0) {
        return REPAIR;
    }
    if (strcmp(firstWord, "REVERSE") == 0) {
        return REVERSE;
    }
    if (strcmp(firstWord, "PIPELINE") == 0) {
        return PIPELINE;
    }
    if (strcmp(firstWord, "LONGEST") == 0) {
        return LONGEST;
    }
    if (strcmp(firstWord, "SHORTEST") == 0) {
        return SHORTEST;
    }
    // Kiem tra neu tu dau tien la "FIND"
    // Neu la FIND thi tim kiem cac tu khoa tiep theo trong lenh de quy dinh loai hanh dong
    // Chuyen toan bo chuoi command sang chu hoa de viec so sanh khong bi anh huong boi chu hoa chu thuong
    // Su dung strstr de kiem tra xem trong cau lenh co chua cac tu khoa "COMPLEMENT", "MRNA", "LONGEST", "SHORTEST", hoac "PIPELINE" hay khong
    // Neu co, tra ve gia tri tuong ung voi tu khoa do
    if (strcmp(firstWord, "FIND") == 0) {
        // Tao mot mang upperCommand de luu ban sao viet hoa cua command
        char upperCommand[256];
        int j = 0;
        // Duyet tung ky tu trong command, chuyen thanh chu hoa va luu vao upperCommand
        while (command[j] != '\0' && j < 255) {
            upperCommand[j] = (char)toupper((unsigned char)command[j]);
            j++;
        }
        upperCommand[j] = '\0'; // Ket thuc chuoi upperCommand

        if (strstr(upperCommand, "COMPLEMENT") != NULL) {
            return COMPLEMENT;
        }
        if (strstr(upperCommand, "MRNA") != NULL) {
            return MRNA;
        }
        if (strstr(upperCommand, "LONGEST") != NULL) {
            return LONGEST;
        }
        if (strstr(upperCommand, "SHORTEST") != NULL) {
            return SHORTEST;
        }
        if (strstr(upperCommand, "PIPELINE") != NULL) {
            return PIPELINE;
        }
    }

    return INVALID;
    // ----- End: Student Answer -----
}

char* sanitizeCode(char *codes) {
    // ----- Begin: Student Answer -----
    // Do dai chuoi duoc dam bao nam trong khoang [1, 300] ky tu
    static char cleaned[301];
    int i = 0;
    int j = 0;

    cleaned[0] = '\0';

    if (codes == NULL) {
        return cleaned;
    }

    while (codes[i] != '\0' && j < 300) {
        char ch = codes[i];

        if (ch == 'a') ch = 'A';
        else if (ch == 'c') ch = 'C';
        else if (ch == 'g') ch = 'G';
        else if (ch == 't') ch = 'T';

        if (ch == 'A' || ch == 'C' || ch == 'G' || ch == 'T') {
            cleaned[j] = ch;
            j++;
        }

        i++;
    }

    cleaned[j] = '\0';

    return cleaned;
    // ----- End: Student Answer -----
}

bool validCheck(char *codes) {
    // ----- Begin: Student Answer -----
    char *clean = sanitizeCode(codes);
    int len = (int)strlen(clean);

    if (len <= 1) {
        printf("INVALID\nTYPE: BASE\n");
        return false;
    }

    if (len == 3) {
        printf("INVALID\nTYPE: CODON\n");
        return false;
    }

    if (len < 9 || (len % 3 != 0)) {
        printf("INVALID CODE\n");
        return false;
    }

    if (strncmp(clean, "ATG", 3) != 0) {
        printf("INVALID CODE\n");
        return false;
    }

    const char *end = clean + len - 3;
    if (strncmp(end, "TAA", 3) != 0
    && strncmp(end, "TAG", 3) != 0 
    && strncmp(end, "TGA", 3) != 0) {
    // Kiem tra xem chuoi co ket thuc bang "TAA", "TAG", hoac "TGA" khong
        printf("INVALID CODE\n");
        return false;
    }

    printf("VALID GENE\n");
    return true;
    // ----- End: Student Answer -----
}

char* generateComplement(char *codes) {
    // ----- Begin: Student Answer -----
    static char complement[301];

    if (!validCheck(codes)) {
        return codes;
    }

    char *clean = sanitizeCode(codes);
    int len = (int)strlen(clean);

    for (int i = 0; i < len && i < 300; i++) {
        char base = clean[i];
        if (base == 'A') {
            complement[i] = 'T';
        } else if (base == 'T') {
            complement[i] = 'A';
        } else if (base == 'C') {
            complement[i] = 'G';
        } else if (base == 'G') {
            complement[i] = 'C';
        } else {
            complement[i] = base;
        }
    }

    if (len > 300) {
        len = 300;
    }
    complement[len] = '\0';

    return complement;
    // ----- End: Student Answer -----
}

char* generateMRNA(char *codes) {
    // ----- Begin: Student Answer -----
    static char mrna[301];
    char *complement = generateComplement(codes);

    if (complement == codes) {
        return codes;
    }

    int len = (int)strlen(complement);

    for (int i = 0; i < len && i < 300; i++) {
        char base = complement[i];
        if (base == 'A') {
            mrna[i] = 'U';
        } else if (base == 'T') {
            mrna[i] = 'A';
        } else if (base == 'C') {
            mrna[i] = 'G';
        } else if (base == 'G') {
            mrna[i] = 'C';
        } else {
            mrna[i] = base;
        }
    }

    if (len > 300) {
        len = 300;
    }
    mrna[len] = '\0';

    return mrna;
    // ----- End: Student Answer -----
}

char* encode(char *codes) {
    // ----- Begin: Student Answer -----
    static char encoded[601]; // 100 codons max -> 600 chars + '\0'
    encoded[0] = '\0';

    if (!validCheck(codes)) {
        return codes;
    }

    char *clean = sanitizeCode(codes);
    int len = (int)strlen(clean);
    int pos = 0;

    for (int i = 0; i < len; i += 3) {
        char first = clean[i];
        char second = clean[i + 1];
        char third = clean[i + 2];

        int prefix = 0;
        if (first == 'A') prefix = 65;
        else if (first == 'C') prefix = 67;
        else if (first == 'G') prefix = 71;
        else if (first == 'T') prefix = 84;

        int suffix = ((second * 31) + (third * 37)) % 10000;

        pos += sprintf(encoded + pos, "%02d%04d", prefix, suffix);
    }

    encoded[pos] = '\0';
    return encoded;
    // ----- End: Student Answer -----
}

char* decode(char *codes) {
    // ----- Begin: Student Answer -----
    static char decoded[301];
    int len = (int)strlen(codes);
    int pos = 0;

    for (int i = 0; i + 6 <= len && pos < 300; i += 6) {
        char prefixStr[3];
        strncpy(prefixStr, codes + i, 2);
        prefixStr[2] = '\0';

        // atoi la ham chuyen chuoi ky tu so thanh so nguyen trong C
        // o day, prefixStr la xau co 2 ky tu so, vi du "65" thi atoi tra ve so nguyen 65
        int prefix = atoi(prefixStr); // doi chuoi so sang so nguyen
        char first = 'A';
        if (prefix == 65) first = 'A';
        else if (prefix == 67) first = 'C';
        else if (prefix == 71) first = 'G';
        else if (prefix == 84) first = 'T';

        char suffixStr[5];
        strncpy(suffixStr, codes + i + 2, 4);
        suffixStr[4] = '\0';
        int suffix = atoi(suffixStr);

        char bases[] = {'A', 'C', 'G', 'T'};
        int secondVal = 'A';
        int thirdVal = 'A';

        for (int si = 0; si < 4; si++) {
            for (int ti = 0; ti < 4; ti++) {
                int s = bases[si];
                int t = bases[ti];
                if (((s * 31) + (t * 37)) % 10000 == suffix) {
                    secondVal = s;
                    thirdVal = t;
                    si = 4;
                    break;
                }
            }
        }

        decoded[pos++] = first;
        if (pos < 300) decoded[pos++] = (char)secondVal;
        if (pos < 300) decoded[pos++] = (char)thirdVal;
    }

    decoded[pos] = '\0';
    return decoded;
    // ----- End: Student Answer -----
}

struct Gene {
    // ----- Begin: Student Answer -----
    char name[65]; // ten gen, max 64 ky tu
    char org_seq[301]; // chuoi DNA goc, max 300 ky tu
    int length; // do dai chuoi DNA
    char encoded_seq[601]; // chuoi DNA da duoc ma hoa, max 600 ky tu
    char complement_seq[301]; // chuoi DNA da duoc bao quan, max 300 ky tu
    char mrna_seq[301]; // chuoi mRNA da duoc tao ra, max 300 ky tu
    // ----- End: Student Answer -----
};

int createTable(struct Gene *emptyTable, char **geneInfo) {
    // ----- Begin: Student Answer -----
    int count = 0;

    if (emptyTable == NULL || geneInfo == NULL) {
        return 0;
    }

    for (int i = 0; geneInfo[i] != NULL; i++) {
        char *raw = geneInfo[i];
        int start = 0;
        int end = (int)strlen(raw) - 1;

        while (raw[start] == ' ' || raw[start] == '\t') {
            start++;
        }
        while (end >= start && (raw[end] == ' ' || raw[end] == '\t' || raw[end] == '\n')) {
            raw[end] = '\0';
            end--;
        }

        char cleanedInput[610];
        int idx = 0;
        for (int k = start; raw[k] != '\0' && idx < 609; k++) {
            cleanedInput[idx++] = raw[k];
        }
        cleanedInput[idx] = '\0';

        int isNumber = 1;
        for (int k = 0; cleanedInput[k] != '\0'; k++) {
            if (cleanedInput[k] < '0' || cleanedInput[k] > '9') {
                isNumber = 0;
                break;
            }
        }

        char realSeq[301];
        if (isNumber) {
            char *decoded = decode(cleanedInput);
            strncpy(realSeq, decoded, 300);
            realSeq[300] = '\0';
        } else {
            strncpy(realSeq, cleanedInput, 300);
            realSeq[300] = '\0';
        }

        struct Gene *gene = &emptyTable[count];
        snprintf(gene->name, sizeof(gene->name), "G%d", count + 1);

        strncpy(gene->org_seq, realSeq, 300);
        gene->org_seq[300] = '\0';
        gene->length = (int)strlen(gene->org_seq);

        char *encoded = encode(gene->org_seq);
        strncpy(gene->encoded_seq, encoded, 600);
        gene->encoded_seq[600] = '\0';

        char *complement = generateComplement(gene->org_seq);
        if (complement == gene->org_seq) {
            gene->complement_seq[0] = '\0';
        } else {
            strncpy(gene->complement_seq, complement, 300);
            gene->complement_seq[300] = '\0';
        }

        char *mrna = generateMRNA(gene->org_seq);
        if (mrna == gene->org_seq) {
            gene->mrna_seq[0] = '\0';
        } else {
            strncpy(gene->mrna_seq, mrna, 300);
            gene->mrna_seq[300] = '\0';
        }

        count++;
    }

    return count;
    // ----- End: Student Answer -----
}

void printTable(struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    if (geneTable == NULL || count <= 0) {
        return;
    }

    printf("| No. | Gene Name | DNA Sequence |\n");
    for (int i = 0; i < count; i++) {
        printf("| %-3d | %-9s | %-12s |\n",
               i + 1,
               geneTable[i].name,
               geneTable[i].org_seq);
    }
    // ----- End: Student Answer -----
}

int isMutated(struct Gene gene, struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    if (geneTable == NULL || count <= 0) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        if (strcmp(gene.org_seq, geneTable[i].org_seq) == 0) {
            return 0;
        }
    }

    return 1;
    // ----- End: Student Answer -----
}

int findMutatedCodons(struct Gene mutatedGene, char *originalGene) {
    // ----- Begin: Student Answer -----
    if (originalGene == NULL) {
        return 0;
    }

    char *mutSeq = mutatedGene.org_seq;
    int mutLen = (int)strlen(mutSeq);
    int origLen = (int)strlen(originalGene);

    int codonCount = mutLen / 3;
    if (origLen / 3 < codonCount) {
        codonCount = origLen / 3;
    }

    for (int i = 0; i < codonCount; i++) {
        int idx = i * 3;
        if (mutSeq[idx] != originalGene[idx] ||
            mutSeq[idx + 1] != originalGene[idx + 1] ||
            mutSeq[idx + 2] != originalGene[idx + 2]) {
            return i + 1;
        }
    }

    return codonCount;
    // ----- End: Student Answer -----
}

char* repairMutation(struct Gene gene, int pos) {
    // ----- Begin: Student Answer -----
    static char repaired[301];
    strncpy(repaired, gene.org_seq, 300);
    repaired[300] = '\0';

    int len = (int)strlen(repaired);
    int codonCount = len / 3;
    if (pos < 1 || pos > codonCount) {
        return repaired;
    }

    int index = (pos - 1) * 3;

    if (pos == 1) {
        repaired[0] = 'A';
        repaired[1] = 'T';
        repaired[2] = 'G';
    } else if (pos == codonCount) {
        repaired[index] = 'T';
        repaired[index + 1] = 'A';
        repaired[index + 2] = 'G';
    } else {
        if (pos % 2 == 1) {
            int counts[4] = {0, 0, 0, 0}; // A, C, G, T
            for (int i = 0; i < len; i++) {
                if (repaired[i] == 'A') counts[0]++;
                else if (repaired[i] == 'C') counts[1]++;
                else if (repaired[i] == 'G') counts[2]++;
                else if (repaired[i] == 'T') counts[3]++;
            }

            int minIndex = 0;
            for (int i = 1; i < 4; i++) {
                if (counts[i] < counts[minIndex]) {
                    minIndex = i;
                }
            }

            char base = 'A';
            if (minIndex == 1) base = 'C';
            else if (minIndex == 2) base = 'G';
            else if (minIndex == 3) base = 'T';

            repaired[index] = base;
            repaired[index + 1] = base;
            repaired[index + 2] = base;
        } else {
            int newLen = len - 3;
            for (int i = index; i < newLen; i++) {
                repaired[i] = repaired[i + 3];
            }
            repaired[newLen] = '\0';
        }
    }

    return repaired;
    // ----- End: Student Answer -----
}

char* reverseGene(struct Gene gene) {
    // ----- Begin: Student Answer -----
    static char reversed[301];
    int len = (int)strlen(gene.org_seq);

    for (int i = 0; i < len && i < 300; i++) {
        reversed[i] = gene.org_seq[len - 1 - i];
    }

    if (len > 300) {
        len = 300;
    }
    reversed[len] = '\0';

    return reversed;
    // ----- End: Student Answer -----
}

void longestGene(struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    if (geneTable == NULL || count <= 0) {
        return;
    }

    int maxLen = geneTable[0].length;
    for (int i = 1; i < count; i++) {
        if (geneTable[i].length > maxLen) {
            maxLen = geneTable[i].length;
        }
    }

    for (int i = 0; i < count; i++) {
        if (geneTable[i].length == maxLen) {
            printf("NAME: %s\n", geneTable[i].name);
            printf("DNA: %s\n", geneTable[i].org_seq);
        }
    }
    // ----- End: Student Answer -----
}

void shortestGene(struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    if (geneTable == NULL || count <= 0) {
        return;
    }

    int minLen = geneTable[0].length;
    for (int i = 1; i < count; i++) {
        if (geneTable[i].length < minLen) {
            minLen = geneTable[i].length;
        }
    }

    for (int i = 0; i < count; i++) {
        if (geneTable[i].length == minLen) {
            printf("NAME: %s\n", geneTable[i].name);
            printf("DNA: %s\n", geneTable[i].org_seq);
        }
    }
    // ----- End: Student Answer -----
}

void DNAPipeline(struct Gene gene) {
    // ----- Begin: Student Answer -----
    char *complement = generateComplement(gene.org_seq);
    char *mrna = generateMRNA(gene.org_seq);

    printf("DNA: %s\n", gene.org_seq);
    if (complement == gene.org_seq) {
        printf("DNA-COM: \n");
    } else {
        printf("DNA-COM: %s\n", complement);
    }

    if (mrna == gene.org_seq) {
        printf("mRNA: \n");
    } else {
        printf("mRNA: %s\n", mrna);
    }
    // ----- End: Student Answer -----
}

void getActionByCommand(enum commandType command, struct Gene *geneTable, int count) {
    // ----- Begin: Student Answer -----
    struct Gene com_mutation_geneTable[10] = {
        {"G_1", "ATGCGTTAA", 9, "", "", ""},
        {"G_2", "ATGAAACTAGTTTGA", 15, "", "", ""},
        {"G_3", "ATGAAACTATTTGGGTGA", 18, "", "", ""},
        {"G_4", "ATGCGTGGCTAATAG", 15, "", "", ""},
        {"G_5", "ATGCGCTGA", 9, "", "", ""},
        {"G_6", "ATGCCGTAATAG", 12, "", "", ""},
        {"G_7", "ATGTTTAAACCCGGGTAA", 18, "", "", ""},
        {"G_8", "ATGCGATCGCTAG", 13, "", "", ""},
        {"G_9", "ATGAAATTTCCCGGGTGA", 18, "", "", ""},
        {"G_10", "ATGACTGACTAA", 12, "", "", ""}
    };

    if (geneTable == NULL || count <= 0) {
        if (command == INVALID) {
            printf("INVALID COMMAND\n");
        }
        return;
    }

    switch (command) {
        case SANITIZE:
            for (int i = 0; i < count; i++) {
                char *clean = sanitizeCode(geneTable[i].org_seq);
                printf("%s\n", clean);
            }
            break;
        case CHECK:
            for (int i = 0; i < count; i++) {
                validCheck(geneTable[i].org_seq);
            }
            break;
        case COMPLEMENT:
            for (int i = 0; i < count; i++) {
                char *comp = generateComplement(geneTable[i].org_seq);
                if (comp != geneTable[i].org_seq) {
                    printf("%s\n", comp);
                }
            }
            break;
        case MRNA:
            for (int i = 0; i < count; i++) {
                char *mrna = generateMRNA(geneTable[i].org_seq);
                if (mrna != geneTable[i].org_seq) {
                    printf("%s\n", mrna);
                }
            }
            break;
        case ENCODE:
            for (int i = 0; i < count; i++) {
                char *enc = encode(geneTable[i].org_seq);
                if (enc != geneTable[i].org_seq) {
                    printf("%s\n", enc);
                }
            }
            break;
        case DECODE:
            for (int i = 0; i < count; i++) {
                char *dec = decode(geneTable[i].encoded_seq);
                printf("%s\n", dec);
            }
            break;
        case CREATE:
            createTable(geneTable, NULL);
            break;
        case PRINT:
            printTable(geneTable, count);
            break;
        case MUTATION:
            for (int i = 0; i < count; i++) {
                int mutated = isMutated(geneTable[i], com_mutation_geneTable, 10);
                if (mutated) {
                    printf("Gene %s: MUTATED\n", geneTable[i].name);
                } else {
                    printf("Gene %s: NORMAL\n", geneTable[i].name);
                }
            }
            break;
        case REPAIR:
            for (int i = 0; i < count; i++) {
                int mutated = isMutated(geneTable[i], com_mutation_geneTable, 10);
                if (mutated) {
                    char *fixed = repairMutation(geneTable[i], 1);
                    printf("Gene %s: %s\n", geneTable[i].name, fixed);
                } else {
                    printf("Gene %s: NORMAL\n", geneTable[i].name);
                }
            }
            break;
        case REVERSE:
            for (int i = 0; i < count; i++) {
                char *rev = reverseGene(geneTable[i]);
                printf("%s\n", rev);
            }
            break;
        case LONGEST:
            longestGene(geneTable, count);
            break;
        case SHORTEST:
            shortestGene(geneTable, count);
            break;
        case PIPELINE:
            for (int i = 0; i < count; i++) {
                DNAPipeline(geneTable[i]);
            }
            break;
        case INVALID:
        default:
            printf("INVALID COMMAND\n");
            break;
    }
    // ----- End: Student Answer -----
}

// ----- End: Student Answer -----

// Test Functions
void testSanitizeCode() {
    printf("=== TEST: sanitizeCode (3 test cases) ===\n");
    
    // Test case 1: String with special characters
    char test1[] = "A-TG@@ata–TAG??!!";
    char *result1 = sanitizeCode(test1);
    printf("Test 1 - Input: '%s'\n", test1);
    printf("Test 1 - Output: '%s'\n", result1);
    printf("\n");
    
    // Test case 2: Lowercase DNA sequence
    char test2[] = "atgcgtTAA";
    char *result2 = sanitizeCode(test2);
    printf("Test 2 - Input: '%s'\n", test2);
    printf("Test 2 - Output: '%s'\n", result2);
    printf("\n");
    
    // Test case 3: Mixed case with invalid characters
    char test3[] = "ATGcgT123XYZtAA";
    char *result3 = sanitizeCode(test3);
    printf("Test 3 - Input: '%s'\n", test3);
    printf("Test 3 - Output: '%s'\n", result3);
    printf("\n");
}

void testValidCheck() {
    printf("=== TEST: validCheck (3 test cases) ===\n");
    
    // Test case 1: Valid gene
    printf("Test 1 - Valid gene (ATGCGTTAA):\n");
    validCheck("ATGCGTTAA");
    printf("\n");
    
    // Test case 2: Invalid - too short
    printf("Test 2 - Invalid gene (too short - ATG):\n");
    validCheck("ATG");
    printf("\n");
    
    // Test case 3: Invalid - no start codon
    printf("Test 3 - Invalid gene (no ATG start - CGTTAA):\n");
    validCheck("CGTTAA");
    printf("\n");
}

void testEncodeDecode() {
    printf("=== TEST: encode/decode (3 test cases) ===\n");
    
    // Test case 1: Simple gene
    char *gene1 = "ATGCGTTAA";
    char *encoded1 = encode(gene1);
    char *decoded1 = decode(encoded1);
    printf("Test 1 - Original: %s\n", gene1);
    printf("Test 1 - Encoded: %s\n", encoded1);
    printf("Test 1 - Decoded: %s\n", decoded1);
    printf("\n");
    
    // Test case 2: Longer gene
    char *gene2 = "ATGAAACTAG";
    char *encoded2 = encode(gene2);
    char *decoded2 = decode(encoded2);
    printf("Test 2 - Original: %s\n", gene2);
    printf("Test 2 - Encoded: %s\n", encoded2);
    printf("Test 2 - Decoded: %s\n", decoded2);
    printf("\n");
    
    // Test case 3: Another gene
    char *gene3 = "ATGCGTGGCTAATAG";
    char *encoded3 = encode(gene3);
    char *decoded3 = decode(encoded3);
    printf("Test 3 - Original: %s\n", gene3);
    printf("Test 3 - Encoded: %s\n", encoded3);
    printf("Test 3 - Decoded: %s\n", decoded3);
    printf("\n");
}

void testComplementMRNA() {
    printf("=== TEST: generateComplement & generateMRNA (3 test cases) ===\n");
    
    // Test case 1
    char *gene1 = "ATGCGTTAA";
    char *comp1 = generateComplement(gene1);
    char *mrna1 = generateMRNA(gene1);
    printf("Test 1 - Original: %s\n", gene1);
    printf("Test 1 - Complement: %s\n", comp1);
    printf("Test 1 - mRNA: %s\n", mrna1);
    printf("\n");
    
    // Test case 2
    char *gene2 = "ATGAAACTAG";
    char *comp2 = generateComplement(gene2);
    char *mrna2 = generateMRNA(gene2);
    printf("Test 2 - Original: %s\n", gene2);
    printf("Test 2 - Complement: %s\n", comp2);
    printf("Test 2 - mRNA: %s\n", mrna2);
    printf("\n");
    
    // Test case 3
    char *gene3 = "ATGCGTGGCTAATAG";
    char *comp3 = generateComplement(gene3);
    char *mrna3 = generateMRNA(gene3);
    printf("Test 3 - Original: %s\n", gene3);
    printf("Test 3 - Complement: %s\n", comp3);
    printf("Test 3 - mRNA: %s\n", mrna3);
    printf("\n");
}

void testMutation() {
    printf("=== TEST: Mutation functions (3 test cases) ===\n");
    
    struct Gene com_mutation_geneTable[10] = {
        {"G_1", "ATGCGTTAA", 9, "", "", ""},
        {"G_2", "ATGAAACTAGTTTGA", 15, "", "", ""},
        {"G_3", "ATGAAACTATTTGGGTGA", 18, "", "", ""},
        {"G_4", "ATGCGTGGCTAATAG", 15, "", "", ""},
        {"G_5", "ATGCGCTGA", 9, "", "", ""},
        {"G_6", "ATGCCGTAATAG", 12, "", "", ""},
        {"G_7", "ATGTTTAAACCCGGGTAA", 18, "", "", ""},
        {"G_8", "ATGCGATCGCTAG", 13, "", "", ""},
        {"G_9", "ATGAAATTTCCCGGGTGA", 18, "", "", ""},
        {"G_10", "ATGACTGACTAA", 12, "", "", ""}
    };
    
    // Test case 1: Normal gene (not mutated)
    struct Gene testGene1 = {"G1", "ATGCGTTAA", 9, "", "", ""};
    int mut1 = isMutated(testGene1, com_mutation_geneTable, 10);
    printf("Test 1 - Gene: %s\n", testGene1.org_seq);
    printf("Test 1 - isMutated: %d (0=normal, 1=mutated)\n", mut1);
    printf("\n");
    
    // Test case 2: Mutated gene
    struct Gene testGene2 = {"G2", "ATGCGTTAC", 9, "", "", ""};
    int mut2 = isMutated(testGene2, com_mutation_geneTable, 10);
    int codonPos = findMutatedCodons(testGene2, "ATGCGTTAA");
    printf("Test 2 - Gene: %s\n", testGene2.org_seq);
    printf("Test 2 - isMutated: %d (0=normal, 1=mutated)\n", mut2);
    printf("Test 2 - First mutated codon position: %d\n", codonPos);
    printf("\n");
    
    // Test case 3: Repair mutation
    struct Gene testGene3 = {"G3", "ATGCGTTAC", 9, "", "", ""};
    char *repaired = repairMutation(testGene3, 1);
    printf("Test 3 - Original: %s\n", testGene3.org_seq);
    printf("Test 3 - Repaired (pos 1): %s\n", repaired);
    printf("\n");
}

void testGeneOperations() {
    printf("=== TEST: Gene operations (3 test cases) ===\n");
    
    // Test case 1: Reverse gene
    struct Gene testGene1 = {"G1", "ATGCGTTAA", 9, "", "", ""};
    char *reversed = reverseGene(testGene1);
    printf("Test 1 - Original: %s\n", testGene1.org_seq);
    printf("Test 1 - Reversed: %s\n", reversed);
    printf("\n");
    
    // Test case 2: Longest/Shortest genes
    struct Gene testTable[3] = {
        {"G1", "ATGCGTTAA", 9, "", "", ""},
        {"G2", "ATGAAACTAGTTTGA", 15, "", "", ""},
        {"G3", "ATGCGTGGCTAATAG", 15, "", "", ""}
    };
    printf("Test 2 - Longest genes:\n");
    longestGene(testTable, 3);
    printf("\nTest 2 - Shortest genes:\n");
    shortestGene(testTable, 3);
    printf("\n");
    
    // Test case 3: DNA Pipeline
    struct Gene testGene3 = {"G1", "ATGCGTTAA", 9, "", "", ""};
    printf("Test 3 - DNA Pipeline:\n");
    DNAPipeline(testGene3);
    printf("\n");
}

void testCommandType() {
    printf("=== TEST: getCommandType (3 test cases) ===\n");
    
    // Test case 1: ENCODE command
    enum commandType cmd1 = getCommandType("Encode the first GENE");
    printf("Test 1 - Command: 'Encode the first GENE'\n");
    printf("Test 1 - Result: %d (ENCODE=%d)\n", cmd1, ENCODE);
    printf("\n");
    
    // Test case 2: FIND COMPLEMENT command
    enum commandType cmd2 = getCommandType("Find the complement sequence");
    printf("Test 2 - Command: 'Find the complement sequence'\n");
    printf("Test 2 - Result: %d (COMPLEMENT=%d)\n", cmd2, COMPLEMENT);
    printf("\n");
    
    // Test case 3: Invalid command
    enum commandType cmd3 = getCommandType("Invalid command test");
    printf("Test 3 - Command: 'Invalid command test'\n");
    printf("Test 3 - Result: %d (INVALID=%d)\n", cmd3, INVALID);
    printf("\n");
}

void testOverallProgram() {
    printf("========================================\n");
    printf("OVERALL PROGRAM INTEGRATION TEST\n");
    printf("========================================\n\n");
    
    // Scenario 1: Create a gene table from raw DNA sequences
    printf("=== SCENARIO 1: Creating Gene Table ===\n");
    struct Gene geneTable[5];
    char *geneInfo[] = {
        "ATGCGTTAA",           // Valid gene
        "ATGAAACTAG",          // Valid gene
        "ATGCGTGGCTAATAG",     // Valid gene
        NULL
    };
    
    int count = createTable(geneTable, geneInfo);
    printf("Created %d genes in the table\n", count);
    printf("\n");
    
    // Scenario 2: Print the gene table
    printf("=== SCENARIO 2: Printing Gene Table ===\n");
    printTable(geneTable, count);
    printf("\n");
    
    // Scenario 3: Sanitize all genes
    printf("=== SCENARIO 3: Sanitizing All Genes ===\n");
    getActionByCommand(SANITIZE, geneTable, count);
    printf("\n");
    
    // Scenario 4: Validate all genes
    printf("=== SCENARIO 4: Validating All Genes ===\n");
    getActionByCommand(CHECK, geneTable, count);
    printf("\n");
    
    // Scenario 5: Generate complements
    printf("=== SCENARIO 5: Generating Complements ===\n");
    getActionByCommand(COMPLEMENT, geneTable, count);
    printf("\n");
    
    // Scenario 6: Generate mRNA sequences
    printf("=== SCENARIO 6: Generating mRNA Sequences ===\n");
    getActionByCommand(MRNA, geneTable, count);
    printf("\n");
    
    // Scenario 7: Encode all genes
    printf("=== SCENARIO 7: Encoding All Genes ===\n");
    getActionByCommand(ENCODE, geneTable, count);
    printf("\n");
    
    // Scenario 8: Decode encoded sequences
    printf("=== SCENARIO 8: Decoding Encoded Sequences ===\n");
    getActionByCommand(DECODE, geneTable, count);
    printf("\n");
    
    // Scenario 9: Reverse all genes
    printf("=== SCENARIO 9: Reversing All Genes ===\n");
    getActionByCommand(REVERSE, geneTable, count);
    printf("\n");
    
    // Scenario 10: Find longest and shortest genes
    printf("=== SCENARIO 10: Finding Longest Genes ===\n");
    getActionByCommand(LONGEST, geneTable, count);
    printf("\n");
    
    printf("=== SCENARIO 11: Finding Shortest Genes ===\n");
    getActionByCommand(SHORTEST, geneTable, count);
    printf("\n");
    
    // Scenario 11: DNA Pipeline for all genes
    printf("=== SCENARIO 12: DNA Pipeline for All Genes ===\n");
    getActionByCommand(PIPELINE, geneTable, count);
    printf("\n");
    
    // Scenario 12: Mutation detection
    printf("=== SCENARIO 13: Detecting Mutations ===\n");
    getActionByCommand(MUTATION, geneTable, count);
    printf("\n");
    
    // Scenario 13: Repair mutations
    printf("=== SCENARIO 14: Repairing Mutations ===\n");
    getActionByCommand(REPAIR, geneTable, count);
    printf("\n");
    
    // Scenario 14: Test command parsing with various inputs
    printf("=== SCENARIO 15: Testing Command Parsing ===\n");
    char *commands[] = {
        "Sanitize the code",
        "Validation check",
        "Find the complement sequence",
        "Find the mRNA sequence",
        "Encode",
        "Decode",
        "Create the table",
        "Print the gene table",
        "Detect a mutation",
        "Repair the mutated gene",
        "Reverse",
        "Find the longest gene",
        "Find the shortest gene",
        "Print the DNA pipeline",
        "Invalid command here"
    };
    
    for (int i = 0; i < 15; i++) {
        enum commandType cmd = getCommandType(commands[i]);
        printf("Command: '%s' -> Type: %d\n", commands[i], cmd);
    }
    printf("\n");
    
    // Scenario 15: Complete workflow test - Encode/Decode round trip
    printf("=== SCENARIO 16: Encode/Decode Round Trip Test ===\n");
    char *testGenes[] = {"ATGCGTTAA", "ATGAAACTAG", "ATGCGTGGCTAATAG"};
    for (int i = 0; i < 3; i++) {
        char *original = testGenes[i];
        char *encoded = encode(original);
        char *decoded = decode(encoded);
        printf("Original: %s\n", original);
        printf("Encoded:  %s\n", encoded);
        printf("Decoded:  %s\n", decoded);
        printf("Match: %s\n\n", (strcmp(original, decoded) == 0) ? "YES" : "NO");
    }
    
    // Scenario 16: Complete DNA processing pipeline for a single gene
    printf("=== SCENARIO 17: Complete DNA Processing Pipeline ===\n");
    char *testGene = "ATGCGTTAA";
    printf("Original DNA: %s\n", testGene);
    
    char *sanitized = sanitizeCode(testGene);
    printf("Sanitized: %s\n", sanitized);
    
    bool isValid = validCheck(testGene);
    printf("Valid: %s\n", isValid ? "YES" : "NO");
    
    if (isValid) {
        char *complement = generateComplement(testGene);
        printf("Complement: %s\n", complement);
        
        char *mrna = generateMRNA(testGene);
        printf("mRNA: %s\n", mrna);
        
        char *encoded = encode(testGene);
        printf("Encoded: %s\n", encoded);
        
        struct Gene testGeneStruct;
        strcpy(testGeneStruct.name, "TestGene");
        strcpy(testGeneStruct.org_seq, testGene);
        testGeneStruct.length = (int)strlen(testGene);
        testGeneStruct.encoded_seq[0] = '\0';
        testGeneStruct.complement_seq[0] = '\0';
        testGeneStruct.mrna_seq[0] = '\0';
        char *reversed = reverseGene(testGeneStruct);
        printf("Reversed: %s\n", reversed);
    }
    printf("\n");
    
    // Scenario 17: Test with encoded input (numbers)
    printf("=== SCENARIO 18: Creating Table from Encoded Input ===\n");
    char *encodedGene = encode("ATGCGTTAA");
    struct Gene encodedTable[2];
    char *encodedGeneInfo[] = {
        encodedGene,  // Encoded sequence (numbers)
        "ATGAAACTAG", // Regular sequence
        NULL
    };
    int encodedCount = createTable(encodedTable, encodedGeneInfo);
    printf("Created %d genes (one from encoded input)\n", encodedCount);
    printTable(encodedTable, encodedCount);
    printf("\n");
    
    printf("========================================\n");
    printf("INTEGRATION TEST COMPLETED\n");
    printf("========================================\n\n");
}

int main() {
    printf("========================================\n");
    printf("DNA CODE TEST SUITE\n");
    printf("========================================\n\n");

    // Unit tests (individual function tests)
    // Uncomment the ones you want to test:
    
    // testSanitizeCode();
    // testValidCheck();
    // testEncodeDecode();
    // testComplementMRNA();
    // testMutation();
    // testGeneOperations();
    // testCommandType();

    // Overall program integration test
    testOverallProgram();

    printf("========================================\n");
    printf("ALL TESTS COMPLETED\n");
    printf("========================================\n");

    return 0;
}