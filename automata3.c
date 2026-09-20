#include <stdio.h>
#include <ctype.h>


int caracterAEntero(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }

    return -1;
}


int columna(char c)
{
    if (c == '0')
        return 0;

    if (c >= '1' && c <= '9')
        return 1;

    if (c == '+' || c == '-' || c == '*')
        return 2;

    return -1;
}


int verifica(const char *s)
{
    for (unsigned i = 0; s[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)s[i];

        if (!(isdigit(c) || c == '+' || c == '-' || c == '*'))
            return 0;
    }

    return 1;
}

int esPalabraLeng(const char *cadena)
{

    static int tt[4][3] = {
        { 1,  2, -1 },
        {-1, -1,  3 },
        { 2,  2,  3 },
        { 1,  2, -1 }
    };

    int e = 0;
    int i = 0;

    while (cadena[i] != '\0' && e != -1)
    {
        int col = columna(cadena[i]);

        if (col == -1)
            return 0;

        e = tt[e][col];
        i++;
    }

    return e == 1 || e == 2;
}


int evaluarExpresion(const char *cadena)
{
    int resultado = 0;
    int numero = 0;
    int ultimoNumero = 0;
    char operador = '+';

    int i = 0;

    while (cadena[i] != '\0')
    {
        numero = 0;

        while (cadena[i] != '\0' &&
               isdigit((unsigned char)cadena[i]))
        {
            numero = numero * 10 + caracterAEntero(cadena[i]);
            i++;
        }

        
        if (operador == '+')
        {
            resultado += numero;
            ultimoNumero = numero;
        }
        else if (operador == '-')
        {
            resultado -= numero;
            ultimoNumero = -numero;
        }
        else if (operador == '*')
        {
            resultado -= ultimoNumero;
            ultimoNumero *= numero;
            resultado += ultimoNumero;
        }

       
        if (cadena[i] != '\0')
        {
            operador = cadena[i];
            i++;
        }
    }

    return resultado;
}

int main(void)
{
    char palabra[256];

    printf("Introduce una operacion simple: ");

    if (scanf("%255s", palabra) != 1)
        return 1;

    if (verifica(palabra) && esPalabraLeng(palabra))
    {
        printf("Cadena valida\n");

        int resultado = evaluarExpresion(palabra);

        printf("Resultado = %d\n", resultado);
    }
    else
    {
        printf("Cadena invalida\n");
    }

    return 0;
}

