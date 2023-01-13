#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
// Paulo Lahude Salim e Bruno Elario Rheinheimer
int concat(int a, int b){
char str[3];
sprintf(str, "%d%d", a, b);
return atoi(str);
}
void campoBatalha(int mapa[20][20]){
int i, j;
for(i = 0; i < 20; i++){
for(j = 0; j < 20; j++){
mapa[i][j] = 0;
}
}
}
void renderizaCampoBatalha(int mapa[20][20], int tropasAlocadas){
int i, j;
char acerto, erro, agua, navio;
char linhas[] = "ABCDEFGHIJKLMNOPQRST";
if(tropasAlocadas){
printf("Posicione sua frota:\n\n");
printf(" ");
agua = '0';
navio = '1';
}else{
printf(" Dispare! \n");
printf(" ");
agua = '?';
acerto = '1';
erro = '0';
}
for(i = 0; i< 20; i++){
if(i >= 9){
printf(" %d ", i+1);
}else{
printf(" %d ", i+1);
}
}
printf("\n");
for(i = 0; i < 20; i++){
printf("%c ", linhas[i]);
for(j = 0; j < 20; j++){
int a = mapa[i][j];
switch(a){
case 0:
printf(" %c ", agua);
break;
case 1:

if(tropasAlocadas){
printf(" %c ", navio);
}else{
printf(" %c ", agua);
}
break;
case 2:
printf(" %c ", acerto);
break;
case 3:
printf(" %c ", erro);
break;
default:
break;
}
printf(" ");
}
printf("\n");
}
}
const int colunas[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
int * formataCoordenada(char *coord){
static int inteiroCoord[2];
for(int i = 0; i < 20; i++){
if(toupper(coord[0]) == "ABCDEFGHIJKLMNOPQRST"[i]){
inteiroCoord[0] = i;
}
}
if(isdigit(coord[2])){
int c = concat(coord[1] - '0', coord[2] - '0');
inteiroCoord[1] = c - 1;
}else{
inteiroCoord[1] = colunas[coord[1] - '0' - 1];
}
return inteiroCoord;
}
int coordenadaValida(char *coord){
char começoMapa = "ABCDEFGHIJKLMNOPQRST"[0];
char fimMapa = "ABCDEFGHIJKLMNOPQRST"[20 - 1];
if(!(toupper(coord[0]) >= começoMapa && toupper(coord[0]) <= fimMapa)){
return 0;
}
if(!isdigit(coord[1])){
return 0;
}
if(isdigit(coord[2])){
int c = concat(coord[1] - '0', coord[2] - '0');
if(c > 20){
return 0;
}
}
return 1;
}

int coordNavioValidas(int orientação, int coord[2], int mapa[20][20]){
int linha = coord[0], coluna = coord[1];
if(linha < 0 || linha >20){
return 0;
}
if(coluna < 0 || coluna > 20){
return 0;
}
if(orientação == 1){
if((coluna + 5) > 20){
return 0;
}
}
if(orientação == 2){
if((linha + 5) > 20){
return 0;
}
}
if(orientação == 1){
for(int j = coluna; j <= coluna + 4; j++){
if(mapa[linha][j] == 1){
return 0;
}
}
}
else if(orientação == 2){
for(int i = linha; i <= linha + 4; i++){
if(mapa[i][coluna] == 1){
return 0;
}
}
}
return 1;
}
void posicionaNavio(int mapa[20][20]){
int linha, coluna;
char coord[3];
int orientação;
int *inteiroCoord;
int faseAlocacao = 1;
while(faseAlocacao <3){
while(faseAlocacao == 1){
renderizaCampoBatalha(mapa, 1);
printf("\nDigite as coordenadas da proa do navio (coluna e linha): \n");
scanf("%s", coord);
if(!coordenadaValida(coord)){
printf("Posição inválida!\n");
} else{
inteiroCoord = formataCoordenada(coord);
linha = inteiroCoord[0];
coluna = inteiroCoord[1];
if(mapa[linha][coluna] != 1){
faseAlocacao = 2;
}else{

printf("Posição inválida!\n");
}
}
};
while(faseAlocacao== 2){
renderizaCampoBatalha(mapa, 1);
printf("\nDigite a posição da popa em relação à proa: \n");
printf("Leste(1)\n");
printf("Sul(2)\n");
scanf("%d", &orientação);
if(!coordNavioValidas(orientação, inteiroCoord, mapa)){
printf("Posição inválida!\n");
faseAlocacao=1;
continue;
}
if(orientação == 1){
for(int j = coluna; j < coluna + 5; j++){
mapa[linha][j] = 1;
}
faseAlocacao=3;
}else if(orientação == 2){
for(int i = linha; i < linha + 5; i++){
mapa[i][coluna] = 1;
}
faseAlocacao=3;
}
};
}
}
void ataque(int mapa[20][20], int disparos){
int linha, coluna;
char coord[3];
int *inteiroCoord;
int acertou = 0;
int fase = 1;
while(fase == 1){
renderizaCampoBatalha(mapa, 0);
printf("\n Número de tiros disparados: %d\n", disparos-1);
printf("\nCoordenadas do tiro, digite linha(alfabeto) e coluna(números) : \n");
scanf("%s", coord);
if(!coordenadaValida(coord)){
printf("\nTiro inválido \n");
} else{
inteiroCoord = formataCoordenada(coord);
linha = inteiroCoord[0];
coluna = inteiroCoord[1];
if(mapa[linha][coluna] == 1){
acertou = 1;
fase = 2;
}else if(mapa[linha][coluna] == 2 || mapa[linha][coluna] == 3){
printf("\nTiro inválido \n");
}else if(mapa[linha][coluna] == 0){
acertou = 0;
fase = 2;
}else{
printf("\nTiro inválido \n");

}
}
}
if(acertou){
mapa[linha][coluna] = 2;
renderizaCampoBatalha(mapa, 0);
printf("\nAcertou!\n");
}else{
mapa[linha][coluna] = 3;
renderizaCampoBatalha(mapa, 0);
printf("\nErrou!\n");
}
fase=3;
}
int sobreviventes(int mapa[20][20]){
int i, j;
for(i = 0; i < 20; i++){
for(j = 0; j < 20; j++){
if(mapa[i][j] == 1){
return 1;
}
}
}
return 0;
}
int main(void){
printf("Bem vindo à batalha naval em C!\n");
printf("Para indicar coordenadas, informe primeiro a coluna e depois a linha(ex:B7)\n");
printf("O Player 1 posiciona a frota, e o Player 2 realiza os ataques.\n");
printf("Vamos ao jogo!\n\n");
int querjogar = 1;
int mapa[20][20];
int tropasAlocadas = 1;
int qtdTropas;
char limpa;
while(querjogar == 1){
campoBatalha(mapa);
qtdTropas = 0;
while(qtdTropas < 3){
posicionaNavio(mapa);
qtdTropas++;
}
renderizaCampoBatalha(mapa, 1);
if (qtdTropas==3){
printf("Pressione 'v' para ocultar o mapa");
printf("\n");
scanf("%s", &limpa);
if(limpa=='v'){
system("clear");
printf("\n");
}
}
printf("\nFrota alocada! Prepare-se para o ataque: \n");
tropasAlocadas = 0;

for(int disparo = 1; disparo < 31; disparo++){
ataque(mapa, disparo);
if(!sobreviventes(mapa)){
printf("\nVitória!\n");
disparo=30;
printf("\nDeseja jogar novamente?\n");
printf("1 - Sim\n");
printf("2 - Nao\n");
scanf("%d", &querjogar);
}
}
if(sobreviventes(mapa)){
printf("\nDerrota\n");
printf("\nDeseja jogar novamente?\n");
printf("1 - Sim\n");
printf("2 - Nao\n");
scanf("%d", &querjogar);
}
}
return 0;
}
