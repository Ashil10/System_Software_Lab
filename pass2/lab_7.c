#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct qwe
{
    char a[100];
} arr[100];

struct poi
{
    int ind;
    int len;
} leng[100];

void main()
{
    FILE *fin, *fout, *fsym, *fopt, *flen;
    fin = fopen("input.txt", "r");
    fopt = fopen("optab.txt", "r");
    fout = fopen("output.txt", "w");
    fsym = fopen("symtab.txt", "r");
    flen = fopen("length.txt", "r");
    leng[0].len = 0;
    leng[0].ind = 0;
    char label[100], opcode[100], operand[100], mnemonic[100], value[100], locctr[100], symadd[100], symbol[100], l[100];
    int start, len, c = 0, co = 0, co_len = 1, i = 0, j;
    fscanf(fin, "%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        start = strtol(operand, NULL, 16);
        fscanf(flen, "%s", l);
    }
    len = strtol(l, NULL, 10);
    fprintf(fout, "H^%s^%06X^%02d\n", label, start, len);
    fscanf(fin, "%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    while (strcmp(opcode, "END") != 0)
    {
        while (!(feof(fopt)))
        {
            fscanf(fopt, "%s\t%s", mnemonic, value);
            if (strcmp(mnemonic, opcode) == 0)
            {
                while (!(feof(fsym)))
                {
                    fscanf(fsym, "%s\t%s", symbol, symadd);
                    if (strcmp(symbol, operand) == 0)
                    {
                        strcpy(arr[c].a, value);
                        strcat(arr[c++].a, symadd);
                        co += strlen(value);
                        co += strlen(symadd);
                        if (co >= 60)
                        {
                            leng[co_len].ind = c - 1;
                            leng[co_len++].len = co - strlen(value) - strlen(symadd);
                            co = strlen(value) + strlen(symadd);
                        }
                        break;
                    }
                }
                fseek(fsym, SEEK_SET, 0);
                break;
            }
        }
        fseek(fopt, SEEK_SET, 0);
        if (strcmp(opcode, "WORD") == 0 || strcmp(opcode, "BYTE") == 0)
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                char zero[6 - strlen(operand)];
                for (i = 0; i < (6 - strlen(operand)); i++)
                {
                    zero[i] = '0';
                }
                strcpy(arr[c].a, zero);
                strcat(arr[c++].a, operand);
                co += 6;
                if (co >= 60)
                {
                    leng[co_len].ind = c - 1;
                    leng[co_len++].len = co - 6;
                    co = 6;
                }
            }
            if (strcmp(opcode, "BYTE") == 0)
            {
                int byte[100], as = 0, index = 0;
                char str[100];
                for (i = 2; i < strlen(operand) - 1; i++)
                {
                    byte[as++] = (int)operand[i];
                }
                for (i = 0; i < as; i++)
                {
                    index += sprintf(&str[index], "%x", byte[i]);
                }
                strcpy(arr[c++].a, str);
                co += strlen(str);
                if (co >= 60)
                {
                    leng[co_len].ind = c - 1;
                    leng[co_len++].len = co - strlen(str);
                    co = strlen(str);
                }
            }
        }
        fscanf(fin, "%s\t%s\t%s\t%s", locctr, label, opcode, operand);
    }
    if (co < 60)
    {
        leng[co_len].ind = c;
        leng[co_len++].len = co;
    }
    for (i = 0; i < co_len - 1; i++)
    {
        start = start + leng[i].len / 2;
        fprintf(fout, "T^%06X^%02X^", start, leng[i + 1].len / 2);
        for (j = leng[i].ind; j < leng[i + 1].ind; j++)
        {
            fprintf(fout, "%s^", arr[j].a);
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "E^%06X", start);
}

/*

input.txt
-	    CODE	START	1000
1000	-	    LDA	    ALPHA
1003	-	    ADD	    INCR
1006	-	    SUB	    ONE
1009	-	    STA	    BETA
100C	ALPHA	WORD    1
100F	INCR	RESW    1
1012	ONE	    WORD    1
1015	BETA	RESW    1
-	    -	    END	    -

optab.txt
START	-
LDA	    00
ADD	    18
SUB	    1C
STA	    0C
END	    -

symtab.txt
ALPHA   100C
INCR    100F
ONE     1012
BETA    1015

length.txt
18

output.txt
H^CODE^001000^000018
T^001000^12^00100C^18100F^1C1012^0C1015^000001^000001^
E^001000

*/
