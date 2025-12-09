#include "include.h"

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

void sanitizeCode(char *codes, char *output) {
    // ----- Begin: Student Answer -----
    // Do dai chuoi duoc dam bao nam trong khoang [1, 300] ky tu
    if (output == NULL) {
        return;
    }

    output[0] = '\0';

    if (codes == NULL) {
        return;
    }

    int i = 0;
    int j = 0;

    while (codes[i] != '\0' && j < 300) {
        char ch = codes[i];

        if (ch == 'a') ch = 'A';
        else if (ch == 'c') ch = 'C';
        else if (ch == 'g') ch = 'G';
        else if (ch == 't') ch = 'T';

        if (ch == 'A' || ch == 'C' || ch == 'G' || ch == 'T') {
            output[j] = ch;
            j++;
        }

        i++;
    }

    output[j] = '\0';
    // ----- End: Student Answer -----
}

/* Global flag to optionally silence validCheck prints for nested calls */
static int silentValidation = 0;

bool validCheck(char *codes) {
    // ----- Begin: Student Answer -----
    char clean[301];
    sanitizeCode(codes, clean);
    int len = (int)strlen(clean);

    if (len <= 1) {
        if (!silentValidation) {
            printf("INVALID\nTYPE: BASE\n");
        }
        return false;
    }

    if (len == 3) {
        if (!silentValidation) {
            printf("INVALID\nTYPE: CODON\n");
        }
        return false;
    }

    if (len < 9 || (len % 3 != 0)) {
        if (!silentValidation) {
            printf("INVALID CODE\n");
        }
        return false;
    }

    if (strncmp(clean, "ATG", 3) != 0) {
        if (!silentValidation) {
            printf("INVALID CODE\n");
        }
        return false;
    }

    const char *end = clean + len - 3;
    if (strncmp(end, "TAA", 3) != 0
    && strncmp(end, "TAG", 3) != 0 
    && strncmp(end, "TGA", 3) != 0) {
        // Kiem tra xem chuoi co ket thuc bang "TAA", "TAG", hoac "TGA" khong
        if (!silentValidation) {
            printf("INVALID CODE\n");
        }
        return false;
    }

    if (!silentValidation) {
        printf("VALID GENE\n");
    }
    return true;
    // ----- End: Student Answer -----
}

void generateComplement(char *codes, char *output) {
    // ----- Begin: Student Answer -----
    if (output == NULL) {
        return;
    }

    char clean[301];
    sanitizeCode(codes, clean);

    if (!validCheck(codes)) {
        /* Return sanitized original on invalid */
        strncpy(output, clean, 300);
        output[300] = '\0';
        return;
    }

    int len = (int)strlen(clean);

    for (int i = 0; i < len && i < 300; i++) {
        char base = clean[i];
        if (base == 'A') {
            output[i] = 'T';
        } else if (base == 'T') {
            output[i] = 'A';
        } else if (base == 'C') {
            output[i] = 'G';
        } else if (base == 'G') {
            output[i] = 'C';
        } else {
            output[i] = base;
        }
    }

    if (len > 300) {
        len = 300;
    }
    output[len] = '\0';
    // ----- End: Student Answer -----
}

void generateMRNA(char *codes, char *output) {
    // ----- Begin: Student Answer -----
    if (output == NULL) {
        return;
    }

    /* Save current silentValidation state (used by callers like DNAPipeline) */
    int prevSilent = silentValidation;

    /* Validate once: prints "VALID GENE" only if not in silent mode */
    if (!validCheck(codes)) {
        char clean[301];
        sanitizeCode(codes, clean);
        strncpy(output, clean, 300);
        output[300] = '\0';
        silentValidation = prevSilent;
        return;
    }

    /* Build complement while silencing any internal validCheck calls */
    char complement[301];
    silentValidation = 1;
    generateComplement(codes, complement);
    silentValidation = prevSilent;

    int len = (int)strlen(complement);

    for (int i = 0; i < len && i < 300; i++) {
        char base = complement[i];
        if (base == 'A') {
            output[i] = 'U';
        } else if (base == 'T') {
            output[i] = 'A';
        } else if (base == 'C') {
            output[i] = 'G';
        } else if (base == 'G') {
            output[i] = 'C';
        } else {
            output[i] = base;
        }
    }

    if (len > 300) {
        len = 300;
    }
    output[len] = '\0';
    // ----- End: Student Answer -----
}

void encode(char *codes, char *output) {
    // ----- Begin: Student Answer -----
    if (output == NULL) {
        return;
    }

    output[0] = '\0';

    if (!validCheck(codes)) {
        char clean[301];
        sanitizeCode(codes, clean);
        strncpy(output, clean, 600);
        output[600] = '\0';
        return;
    }

    char clean[301];
    sanitizeCode(codes, clean);
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

        pos += sprintf(output + pos, "%02d%04d", prefix, suffix);
    }

    output[pos] = '\0';
    // ----- End: Student Answer -----
}

void decode(char *codes, char *output) {
    // ----- Begin: Student Answer -----
    if (output == NULL) {
        return;
    }

    /* Keep only digit characters; ignore others to avoid invalid chunks */
    char digitsOnly[601];
    int dlen = 0;
    for (int i = 0; codes[i] != '\0' && dlen < 600; i++) {
        if (codes[i] >= '0' && codes[i] <= '9') {
            digitsOnly[dlen++] = codes[i];
        }
    }
    digitsOnly[dlen] = '\0';

    int len = dlen;
    int pos = 0;

    for (int i = 0; i + 6 <= len && pos < 300; i += 6) {
        char prefixStr[3];
        strncpy(prefixStr, digitsOnly + i, 2);
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
        strncpy(suffixStr, digitsOnly + i + 2, 4);
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

        output[pos++] = first;
        if (pos < 300) output[pos++] = (char)secondVal;
        if (pos < 300) output[pos++] = (char)thirdVal;
    }

    output[pos] = '\0';
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
        const char *raw = geneInfo[i];
        int start = 0;
        int end = (int)strlen(raw) - 1;

        /* Skip leading spaces/tabs */
        while (raw[start] == ' ' || raw[start] == '\t') {
            start++;
        }
        /* Move end backward over spaces/tabs/newlines, but DO NOT modify raw (it may be a string literal) */
        while (end >= start &&
               (raw[end] == ' ' || raw[end] == '\t' || raw[end] == '\n' || raw[end] == '\r')) {
            end--;
        }

        char cleanedInput[610];
        int idx = 0;
        /* Copy trimmed substring [start, end] into cleanedInput */
        for (int k = start; k <= end && raw[k] != '\0' && idx < 609; k++) {
            cleanedInput[idx++] = raw[k];
        }
        cleanedInput[idx] = '\0';

        /* Skip empty entries after trimming */
        if (cleanedInput[0] == '\0') {
            continue;
        }

        int isNumber = 1;
        for (int k = 0; cleanedInput[k] != '\0'; k++) {
            if (cleanedInput[k] < '0' || cleanedInput[k] > '9') {
                isNumber = 0;
                break;
            }
        }

        char realSeq[301];
        if (isNumber) {
            char decoded[301];
            decode(cleanedInput, decoded);
            sanitizeCode(decoded, realSeq);
        } else {
            sanitizeCode(cleanedInput, realSeq);
        }

        /* Skip if sanitization removed all valid bases */
        if (realSeq[0] == '\0') {
            continue;
        }

        struct Gene *gene = &emptyTable[count];
        snprintf(gene->name, sizeof(gene->name), "G%d", count + 1);

        strncpy(gene->org_seq, realSeq, 300);
        gene->org_seq[300] = '\0';
        gene->length = (int)strlen(gene->org_seq);
        
        encode(gene->org_seq, gene->encoded_seq);
        gene->encoded_seq[600] = '\0';

        char complement[301];
        generateComplement(gene->org_seq, complement);
        if (strcmp(complement, gene->org_seq) == 0) {
            gene->complement_seq[0] = '\0';
        } else {
            strncpy(gene->complement_seq, complement, 300);
            gene->complement_seq[300] = '\0';
        }

        char mrna[301];
        generateMRNA(gene->org_seq, mrna);
        if (strcmp(mrna, gene->org_seq) == 0) {
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

    /* Sanitize and validate lengths are multiples of 3; otherwise no valid codon to compare */
    char mutSeqClean[301];
    char origSeqClean[301];
    sanitizeCode(mutatedGene.org_seq, mutSeqClean);
    sanitizeCode(originalGene, origSeqClean);

    int mutLen = (int)strlen(mutSeqClean);
    int origLen = (int)strlen(origSeqClean);

    if (mutLen < 3 || origLen < 3 || (mutLen % 3 != 0) || (origLen % 3 != 0)) {
        return 0;
    }

    int codonCount = mutLen / 3;
    if (origLen / 3 < codonCount) {
        codonCount = origLen / 3;
    }

    for (int i = 0; i < codonCount; i++) {
        int idx = i * 3;
        if (mutSeqClean[idx] != origSeqClean[idx] ||
            mutSeqClean[idx + 1] != origSeqClean[idx + 1] ||
            mutSeqClean[idx + 2] != origSeqClean[idx + 2]) {
            return i + 1;
        }
    }

    return codonCount;
    // ----- End: Student Answer -----
}

void repairMutation(struct Gene gene, int pos, char *output) {
    // ----- Begin: Student Answer -----
    if (output == NULL) {
        return;
    }

    strncpy(output, gene.org_seq, 300);
    output[300] = '\0';

    int len = (int)strlen(output);
    int codonCount = len / 3;
    if (pos < 1 || pos > codonCount) {
        return;
    }

    int index = (pos - 1) * 3;

    if (pos == 1) {
        output[0] = 'A';
        output[1] = 'T';
        output[2] = 'G';
    } else if (pos == codonCount) {
        output[index] = 'T';
        output[index + 1] = 'A';
        output[index + 2] = 'G';
    } else {
        if (pos % 2 == 1) {
            int counts[4] = {0, 0, 0, 0}; // A, C, G, T
            for (int i = 0; i < len; i++) {
                if (output[i] == 'A') counts[0]++;
                else if (output[i] == 'C') counts[1]++;
                else if (output[i] == 'G') counts[2]++;
                else if (output[i] == 'T') counts[3]++;
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

            output[index] = base;
            output[index + 1] = base;
            output[index + 2] = base;
        } else {
            int newLen = len - 3;
            for (int i = index; i < newLen; i++) {
                output[i] = output[i + 3];
            }
            output[newLen] = '\0';
        }
    }
    // ----- End: Student Answer -----
}

void reverseGene(struct Gene gene, char *output) {
    // ----- Begin: Student Answer -----
    if (output == NULL) {
        return;
    }

    int len = (int)strlen(gene.org_seq);

    for (int i = 0; i < len && i < 300; i++) {
        output[i] = gene.org_seq[len - 1 - i];
    }

    if (len > 300) {
        len = 300;
    }
    output[len] = '\0';
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
    char complement[301];
    char mrna[301];

    /* Suppress any "VALID GENE" prints inside the pipeline */
    int prevSilent = silentValidation;
    silentValidation = 1;
    generateComplement(gene.org_seq, complement);
    generateMRNA(gene.org_seq, mrna);
    silentValidation = prevSilent;

    printf("DNA: %s\n", gene.org_seq);
    if (strcmp(complement, gene.org_seq) == 0) {
        printf("DNA-COM: \n");
    } else {
        printf("DNA-COM: %s\n", complement);
    }

    if (strcmp(mrna, gene.org_seq) == 0) {
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
                char clean[301];
                sanitizeCode(geneTable[i].org_seq, clean);
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
                char comp[301];
                generateComplement(geneTable[i].org_seq, comp);
                if (strcmp(comp, geneTable[i].org_seq) != 0) {
                    printf("%s\n", comp);
                }
            }
            break;
        case MRNA:
            for (int i = 0; i < count; i++) {
                char mrna[301];
                generateMRNA(geneTable[i].org_seq, mrna);
                if (strcmp(mrna, geneTable[i].org_seq) != 0) {
                    printf("%s\n", mrna);
                }
            }
            break;
        case ENCODE:
            for (int i = 0; i < count; i++) {
                char enc[601];
                encode(geneTable[i].org_seq, enc);
                if (strcmp(enc, geneTable[i].org_seq) != 0) {
                    printf("\"%s\"\n", enc);
                }
            }
            break;
        case DECODE:
            for (int i = 0; i < count; i++) {
                char dec[301];
                decode(geneTable[i].encoded_seq, dec);
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
                    char fixed[301];
                    /* Find the first mutated codon position compared to the corresponding original gene */
                    int pos = findMutatedCodons(geneTable[i], com_mutation_geneTable[i].org_seq);
                    repairMutation(geneTable[i], pos, fixed);
                    printf("Gene %s: %s\n", geneTable[i].name, fixed);
                } else {
                    printf("Gene %s: NORMAL\n", geneTable[i].name);
                }
            }
            break;
        case REVERSE:
            for (int i = 0; i < count; i++) {
                char rev[301];
                reverseGene(geneTable[i], rev);
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
                if (i < count - 1) {
                    printf("\n");
                }
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
