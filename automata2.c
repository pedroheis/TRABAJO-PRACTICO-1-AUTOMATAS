#include <stdio.h>


int caracterAEntero(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';     }
   
    return -1; }


int main(void)
{
    char pruebas[] = {'0', '5', '9', 'a', '+'};
    int totalPruebas = sizeof(pruebas) / sizeof(pruebas[0]);


    printf("PRUEBAS EJERCICIO 2\n");
    for (int i = 0; i < totalPruebas; i++)
    {
        char c = pruebas[i];
        int res = caracterAEntero(c);


        if (res != -1)
        {
            printf("Caracter: '%c' -> Entero retornado: %d (Exito)\n", c, res);
        }
        else
        {
            printf("Caracter: '%c' -> Error Lexico (No es digito)\n", c);
        }
    }


    return 0;
}
