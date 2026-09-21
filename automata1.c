#include <stdio.h>
#include <ctype.h>

int columna(int e, char c)
{
if (c == '@') return 8;

if (e == 0) {
if (c == '0') return 0;
if (c >= '1' && c <= '7') return 1;
if (c == '+' || c == '-') return 2;
if (c >= '8' && c <= '9') return 3;
}

if (e == 1) {
if (c == 'x' || c == 'X') return 6;
}

if (e == 2) {
if (c >= '0' && c <= '7') return 5;
if (c == '8' || c == '9') return 4;
}

if (e == 3) {
if (c == '0') return 0;
if (c >= '1' && c <= '7') return 1;
if (c >= '8' && c <= '9') return 3;
}

if (e == 4) {
if (c >= '0' && c <= '9') return 4;
}

if (e == 5 || e == 7) {
if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return 7;
}

return -1;
}

int esPalabraLeng(const char *cadena)
{
static int tt[8][9] = {
{ 1, 2, 3, 4, -1, -1, -1, -1, -1 },
{ -1, -1, -1, -1, -1, -1, 5, -1, 0 },
{ -1, -1, -1, -1, 4, 2, -1, -1, 0 },
{ 6, 2, -1, 4, -1, -1, -1, -1, -1 },
{ -1, -1, -1, -1, 4, -1, -1, -1, 0 },
{ -1, -1, -1, -1, -1, -1, -1, 7, -1 },
{ -1, -1, -1, -1, -1, -1, -1, -1, 0 },
{ -1, -1, -1, -1, -1, -1, -1, 7, 0 }
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

return e == 1 || e == 2 || e == 4 || e == 6 || e == 7;
}

int verifica(const char *s)
{
if (s == NULL || *s == '\0')
return 0;

for (unsigned i = 0; s[i] != '\0'; i++) {
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
char palabra[256];

printf("Introduce una cadena: ");
if (scanf("%255s", palabra) != 1)
return 1;

if (verifica(palabra) && esPalabraLeng(palabra))
printf("Cadena valida\n");
else
printf("Cadena invalida\n");

return 0;
}