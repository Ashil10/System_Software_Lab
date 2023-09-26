#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure for symbol table entries
struct SymbolTableEntry {
    char label[20];
    int address;
};

int main() {
    FILE *inputFile;
    char line[100];
    char label[20], opcode[20], operand[20];
    int locationCounter = 0;
    struct SymbolTableEntry symbolTable[100]; // Assuming a maximum of 100 symbols
    int symbolTableIndex = 0;

    // Open the input assembly file
    inputFile = fopen("input.asm", "r");
    if (inputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Process each line in the assembly code
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Tokenize the line
        sscanf(line, "%s %s %s", label, opcode, operand);

        // Check if there is a label
        if (strlen(label) > 0) {
            // Add the label and its address to the symbol table
            strcpy(symbolTable[symbolTableIndex].label, label);
            symbolTable[symbolTableIndex].address = locationCounter;
            symbolTableIndex++;
        }

        // Check the opcode and update the location counter
        if (strcmp(opcode, "START") == 0) {
            locationCounter = atoi(operand);
        } else if (strcmp(opcode, "LDA") == 0 || strcmp(opcode, "ADD") == 0) {
            locationCounter += 3;
        } else if (strcmp(opcode, "STA") == 0 || strcmp(opcode, "SUB") == 0) {
            locationCounter += 3;
        } else if (strcmp(opcode, "END") == 0) {
            // End of pass one
            break;
        }
    }

    // Close the input file
    fclose(inputFile);

    // Print the symbol table
    printf("Symbol Table:\n");
    for (int i = 0; i < symbolTableIndex; i++) {
        printf("%s %d\n", symbolTable[i].label, symbolTable[i].address);
    }


    Algorithm for Pass One of a Two-Pass Assembler:

1. Initialize necessary data structures and variables:
   - Open the input assembly file for reading.
   - Initialize the location counter (LC) to 0.
   - Initialize an empty symbol table.

2. Read each line from the input assembly file until the end of the file:
   a. Read a line from the input file.
   b. Tokenize the line into label, opcode, and operand.

3. Check if the opcode is "START":
   a. If yes, set the LC to the value specified in the operand (the starting address).

4. Check if there is a label:
   a. If yes, add the label and its address (LC) to the symbol table.

5. Check the opcode and update the LC accordingly:
   a. If the opcode is an instruction that consumes memory (e.g., LDA, STA, ADD, SUB, etc.), increment LC accordingly.

6. Check if the opcode is "END":
   a. If yes, stop the pass one phase.

7. Repeat steps 2-6 for each line in the input file.

8. Close the input file.

9. Print the symbol table, which now contains labels and their corresponding addresses.

10. End of Pass One.



    return 0;
}
