#include <stdio.h>
#include <ctype.h>

int columna(int e, char c)
{
    if (c == '@') return 8;

    if (e == 0 || e == 3) {
        if (c == '0') return 0;
        if (c >= '1' && c <= '7') return 1;
        if (c == '+' || c == '-') return 2;
        if (c >= '8' && c <= '9') return 3;
    }

    if (e == 1 || e == 2) {
        if (c >= '0' && c <= '7') return 5;
        if (e == 1 && (c == 'x' || c == 'X')) return 6;
    }

    if (e == 4 || e == 5) {
        if (c >= '0' && c <= '9') return 4;
    }

    if (e == 5 || e == 7) {
        if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return 7;
        if (e == 7 && c >= '0' && c <= '9') return 7;
    }

    return -1;
}

int esPalabraLeng(const char *cadena)
{
    /* 0: inicio, 1: despues de 0, 2: octal, 3: signo,
       4: decimal, 5: despues de 0x, 6: estado no usado, 7: hexadecimal */
    static int tt[8][9] = {
        /*  0  1-7  +,-  1-9  0-9  0-7  X,x  hex  @ */
        /* 0 */ { 1,   2,   3,   4,  -1,  -1,  -1, -1, -1 },
        /* 1 */ { -1, -1,  -1, -1,  -1,   2,   5, -1,  0 },
        /* 2 */ { -1, -1,  -1, -1,  -1,   2,  -1, -1,  0 },
        /* 3 */ { 1,   2,  -1,   4,  -1,  -1,  -1, -1, -1 },
        /* 4 */ { -1, -1,  -1, -1,   4,  -1,  -1, -1,  0 },
        /* 5 */ { -1, -1,  -1, -1,   7,  -1,  -1,  7, -1 },
        /* 6 */ { -1, -1,  -1, -1,  -1,  -1,  -1, -1, -1 },
        /* 7 */ { -1, -1,  -1, -1,  -1,  -1,  -1,  7,  0 }
    };
    int e = 0;
    int i = 0;
    int c = cadena[0];

    while (c != '\0' && e != -1) {
        int col = columna(e, c);

        if (col == -1)
            return 0;

        e = tt[e][col];
        i++;
        c = cadena[i];
    }

    return e == 1 || e == 2 || e == 4 || e == 7;
}

int verifica(const char *s)
{
    unsigned i;

    for (i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];

        if (!(isdigit(c) || c == '+' || c == '-' || c == '@' ||
              c == 'x' || c == 'X' ||
              (c >= 'a' && c <= 'f') ||
              (c >= 'A' && c <= 'F')))
            return 0;
    }

    return 1;
}

int main(void)
{
    struct {
        char *palabra;
        int esperado;
    } pruebas[] = {


        { "0", 1 },
        { "1", 1 },
        { "7", 1 },
        { "8", 1 },
        { "9", 1 },
        { "10", 1 },
        { "12345", 1 },
        { "99999", 1 },

        /* Decimales con signo */
        { "+1", 1 },
        { "-1", 1 },
        { "+17", 1 },
        { "-34", 1 },
        { "+12345", 1 },
        { "-98765", 1 },



        { "0", 1 },
        { "01", 1 },
        { "02", 1 },
        { "07", 1 },
        { "10", 1 },
        { "17", 1 },
        { "20", 1 },
        { "75", 1 },
        { "123", 1 },
        { "777", 1 },
        { "12345670", 1 },


        { "0x1", 1 },
        { "0x0", 1 },
        { "0x9", 1 },
        { "0x12", 1 },
        { "0x123456", 1 },

        /* Letras minúsculas */
        { "0xa", 1 },
        { "0xf", 1 },
        { "0xab", 1 },
        { "0xabcdef", 1 },

        /* Letras mayúsculas */
        { "0xA", 1 },
        { "0xF", 1 },
        { "0xAB", 1 },
        { "0xABCDEF", 1 },

        /* Mezcla de mayúsculas y minúsculas */
        { "0xAa", 1 },
        { "0xAbCd", 1 },
        { "0XaBcD", 1 },
        { "0XABCdef", 1 },


        { "0@1", 1 },
        { "1@2", 1 },
        { "123@456", 1 },
        { "-34@56", 1 },
        { "+17@-25", 1 },

        { "0x12@075", 1 },
        { "0x12@075@-34@0XAF", 1 },

        { "1@075@0xAF", 1 },
        { "-123@+456@0xABC", 1 },
        { "0@07@0x1@999", 1 },
        { "12345@777@0xABCDEF@-89", 1 },

        /* Muchos elementos */
        { "0@1@07@123@0x1@0XFF@-34@+56", 1 },



        /* 8 y 9 no pueden aparecer después de comenzar
           una constante que se esté interpretando como octal */
        { "08", 0 },
        { "09", 0 },
        { "078", 0 },
        { "089", 0 },
        { "1789", 0 },



        /* Prefijo sin dígitos */
        { "0x", 0 },
        { "0X", 0 },

        /* Caracteres fuera del rango hexadecimal */
        { "0xG", 0 },
        { "0xg", 0 },
        { "0x1G", 0 },
        { "0x12G", 0 },
        { "0x123Z", 0 },


        { "+", 0 },
        { "-", 0 },
        { "++1", 0 },
        { "--1", 0 },
        { "+-1", 0 },
        { "-+1", 0 },
        { "1+", 0 },
        { "1-", 0 },
        { "12+34", 0 },



        { "@12", 0 },
        { "12@", 0 },
        { "1@@2", 0 },
        { "@", 0 },
        { "@@", 0 },
        { "1@@", 0 },
        { "@@1", 0 },

        /* @ entre números */
        { "1@2@3", 1 },
        { "1@07@0xFF", 1 },



        { "12G", 0 },
        { "ABC", 0 },
        { "xyz", 0 },
        { "12#", 0 },
        { "12.5", 0 },
        { "12,5", 0 },
        { "1 2", 0 },
        { "0x12@", 0 },
        { "12@G", 0 },


        { "0x12@", 0 },
        { "@0x12", 0 },
        { "0x@12", 0 },
        { "1@08", 0 },
        { "0x12@@075", 0 },
        { "+@12", 0 },
        { "12@-", 0 },
        { "12@+", 0 },
        { "12@0x", 0 },
        { "12@0xG", 0 }
    };

    unsigned i;

    for (i = 0; i < sizeof(pruebas) / sizeof(pruebas[0]); i++) {

        int resultado = verifica(pruebas[i].palabra) &&
                         esPalabraLeng(pruebas[i].palabra);

        printf("%-30s -> %s\n",
               pruebas[i].palabra,
               resultado == pruebas[i].esperado ? "OK" : "FALLO");
    }

    return 0;
}
