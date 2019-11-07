#ifndef SVG
#define SVG
#include <stdio.h>
#include "../figuras/figuras.h"

void iniciarSvg(char *fileName);
void finalizarSvg(char *fileName);

void desenharCirculo(char *fileName,Circulo recebeCirculo);
void desenharRetangulo(char *fileName,Retangulo recebeRetangulo);
void escreverTexto(char *fileName,Texto recebeTexto);
void desenharQuadra(char *fileName,Quadra recebeQuadra);
void desenharHidrante(char *fileName,Hidrante recebeHidrante);
void desenharSemaforo(char *fileName,Semaforo recebeSemaforo);
void desenharRadio(char *fileName,Radio recebeRadio);
void desenharPredio(FILE *saidaSvg);
void desenharMuro(char *fileName,Muro recebeMuro);

void escreverPontoInterno(double x,double y,char linhaArquivo[500],char *sTxt,char *sSvg);
void escreverPontoNaoInterno(double x,double y,char linhaArquivo[500],char *sTxt,char *sSvg);
void escreverRetaDistancia(double xInicio, double yInicio,double xFinal,double yFinal,char *cor,char *sSvg);
void escreverDistanciaSvg(double x,double y,double distancia,char *sSvg);
void escreverDistanciaTxt(char linhaArquivo[500],double distancia,char *sTxt);

#endif