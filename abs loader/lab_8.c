#include <stdio.h>

#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *fp, *outp;
    int i, addr1, l, j, staddr1;
    char name[10], name2[10], len[10], line[1000], name1[10], addr[10], rec[10], ch, staddr[10];
    fp = fopen("input.txt", "r");
    outp = fopen("output.txt", "w");
    fscanf(fp, "%s", line);
    int count = 0, a = 0, b = 0, c = 0;
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '^')
        {
            count++;
            continue;
        }
        if (count == 1)
        {
            name1[a] = line[i];
            a++;
        }
        else if (count == 2)
        {
            name2[b] = line[i];
            b++;
        }
        else if (count == 3)
        {
            len[c] = line[i];
            c++;
        }
    }

    name1[a] = '\0';
    name2[b] = '\0';
    len[c] = '\0';
    printf("Program Name : %s\n\n", name1);
    fprintf(outp, "Program Name : %s\n\n", name1);
    printf("Starting Address : %s\n\n", name2);
    fprintf(outp, "Starting Address : %s\n\n", name2);
    do
    {
        fscanf(fp, "%s", line);
        if (line[0] == 'T')
        {
            count = 0;
            a = 0;
            for (i = 0; line[i] != '\0'; i++)
            {
                if (line[i] == '^')
                {
                    count++;
                    continue;
                }
                if (count == 1)
                {
                    staddr[a] = line[i];
                    a++;
                }
                else if (count == 3)
                {
                    break;
                }
            }
            staddr[a] = '\0';
            staddr1 = strtol(staddr, NULL, 16);
            i = 12;
            while (line[i] != '\0')
            {
                if (line[i] != '^')
                {
                    int objc1 = line[i];
                    int objc2 = line[i + 1];
                    objc1 -= 48;
                    if (objc1 > 10)
                        objc1 -= 7;
                    objc2 -= 48;
                    if (objc2 > 10)
                        objc2 -= 7;
                    int objc = objc1 * 16 + objc2;
                    printf("00%X \t %02X\n", staddr1, objc);
                    fprintf(outp, "00%X \t %02X\n", staddr1, objc);
                    staddr1++;
                    i = i + 2;
                }
                else
                    i++;
            }
        }
        else if (line[0] = 'E')
        {

            break;
        }
    } while (!feof(fp));
    fclose(fp);
    fclose(outp);
}

/*

INPUT
------
H^TEST^001000^00107A
T^001000^1E^141033^482039^001036^281030^301015^482061^3C1003^00102A^0C1039^00102D
T^00101E^15^0C1036^482061^081033^4C0000^454F46^000003^000000
E^001000

OUTPUT
--------
Program Name : TEST

Starting Address : 001000

001000 	 14
001001 	 10
001002 	 33
001003 	 48
001004 	 20
001005 	 39
001006 	 00
001007 	 10
001008 	 36
001009 	 28
00100A 	 10
00100B 	 30
00100C 	 30
00100D 	 10
00100E 	 15
00100F 	 48
001010 	 20
001011 	 61
001012 	 3C
001013 	 10
001014 	 03
001015 	 00
001016 	 10
001017 	 2A
001018 	 0C
001019 	 10
00101A 	 39
00101B 	 00
00101C 	 10
00101D 	 2D
00101E 	 0C
00101F 	 10
001020 	 36
001021 	 48
001022 	 20
001023 	 61
001024 	 08
001025 	 10
001026 	 33
001027 	 4C
001028 	 00
001029 	 00
00102A 	 45
00102B 	 4F
00102C 	 46
00102D 	 00
00102E 	 00
00102F 	 03
001030 	 00
001031 	 00
001032 	 00


*/
