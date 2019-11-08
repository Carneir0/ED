#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionsQry.h"
#include "../util/util.h"
#include "../svg/svg.h"
#include "../figuras/figuras.h"
#include "../figuras/estrutura/rbtree.h"
#include "../figuras/estrutura/hash.h"
#include <math.h>


// Função para exemplo de consulta nas trees e hash
void comandoDq (char* comandos, char* temp2, char* temp3, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad) {
    char metrica[3], id[50];
    double dist1, dist2, x1, y1, x2, y2, w1, h1;
    int tam;
    sscanf(comandos, "dq %s %s %lf", metrica, id, &dist1);

    // Declaração variaveis para cada figura
    Hidrante h;
    Semaforo s;
    Radio r;
    Quadra q;

    // Verifica a qual figura pertence o id dado
    if ((h = getObjetoHash(*hashHid, id)) != NULL) {
        x2 = getHidranteX(h);
        y2 = getHidranteY(h);
    } else if ((s = getObjetoHash(*hashSem, id)) != NULL) {
        x2 = getSemaforoX(s);
        y2 = getSemaforoY(s);
    } else if ((r = getObjetoHash(*hashRad, id)) != NULL) {
        x2 = getRadioX(r);
        y2 = getRadioY(r);
    }

    tam = getTamHash(*hashQuad);

    if (strcmp(metrica, "L1") == 0) {
        // Percorrer a hash de quadra para encontrar qual satisfaz a condicao dada. isso aqui é reutilizavel
        for (int i = 0; i < tam; i++) {
    		listaHash n = getIndiceHash(*hashQuad, i);
    		if (n != NULL) {
    			listaHash aux = n;
    			while (aux != NULL) {
    				n = getProxHash(n);
                    // Daqui pra baixo pode mudar dependendo do que o comando pede
                    q = getObjetoHash2(aux); // Para poder dar os get precisa desse comando antes
                    x1 = getQuadraX(q);
                    y1 = getQuadraY(q);
                    h1 = getQuadraAltura(q);
                    w1 = getQuadraLargura(q);
                    if ((fabs(x2 - x1) + fabs(y2 - y1)) <= dist1 && (fabs(x2 - (x1+w1)) + fabs(y2 - y1)) <= dist1 && (fabs(x2 - x1) + fabs(y2 - (y1+h1))) <= dist1 && (fabs(x2 - (x1+w1)) + fabs(y2 - (y1+h1))) <= dist1) {
                        // Se satisfazer condicao remover primeiro da hash depois da tree (sempre nessa ordem)
                        removerObjetoHash(*hashQuad, getQuadraId(q));
                        // Para excluir da tree precisa antes dar o findtree e salvar na variavel da figura
                        q = findTree(*quadra, q);
                        deleteNodeTree(*quadra, q);
                    }
                    // Isso n muda
    				aux = n;
    			}
    		}
    	}
    } else if (strcmp(metrica, "L2") == 0) {
        for (int i = 0; i < tam; i++) {
    		listaHash n = getIndiceHash(*hashQuad, i);
    		if (n != NULL) {
    			listaHash aux = n;
    			while (aux != NULL) {
    				n = getProxHash(n);
                    // Daqui pra baixo pode mudar dependendo do que o comando pede
                    q = getObjetoHash2(aux); // Para poder dar os get precisa desse comando antes
                    x1 = getQuadraX(q);
                    y1 = getQuadraY(q);
                    h1 = getQuadraAltura(q);
                    w1 = getQuadraLargura(q);
                    if ((sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2))) <= dist1 && (sqrt(pow((x2 - (x1+w1)), 2) + pow((y2 - y1), 2))) <= dist1 && (sqrt(pow((x2 - x1), 2) + pow((y2 - (y1+h1)), 2))) <= dist1 && (sqrt(pow((x2 - (x1+w1)), 2) + pow((y2 - (y1+h1)), 2))) <= dist1) {
                        // Se satisfazer condicao remover primeiro da hash depois da tree (sempre nessa ordem)
                        removerObjetoHash(*hashQuad, getQuadraId(q));
                        // Para excluir da tree precisa antes dar o findtree e salvar na variavel da figura
                        q = findTree(*quadra, q);
                        deleteNodeTree(*quadra, q);
                    }
                    // Isso n muda
    				aux = n;
    			}
    		}
        }
    }
}

void comandoDmprbt(char* comandos, char* localSaida, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, struct tree**predio, struct tree**muro) {
    char nomeArq[50], t, *temp1 = NULL;
    Quadra q;
    Hidrante h;
    Semaforo s;
    Radio r;
    Predio p;
    Muro m;
    sscanf(comandos, "dmprbt %c %s", &t, nomeArq);
    strcat(nomeArq, ".svg");
    temp1 = getArquivo(localSaida, nomeArq);

    iniciarSvg(temp1);

    if (t == 'q') {
        printTree(*quadra, temp1, printValorQuadra);
    } else if (t == 'h') {
        printTree(*hidrante, temp1, printValorHidrante);
    } else if (t == 's') {
        printTree(*semaforo, temp1, printValorSemaforo);
    } else if (t == 't') {
        printTree(*radio, temp1, printValorRadio);
    } else if (t == 'p') {
        printTree(*predio, temp1, printValorPredio);
    } else if (t == 'm') {
        printTree(*muro, temp1, printValorMuro);
    }
    finalizarSvg(temp1);

    free(temp1);
}

void comandoMoradores(char* comandos, char* nomeTxt, tabelaHash **hashQuad, tabelaHash **hashMor) {
    char id[50], result[500];
    int verifica = 0, tamQuadra = getTamHash(*hashQuad), tamMorador = getTamHash(*hashMor);
    Morador m;
    Quadra q;
    sscanf(comandos, "m? %s", id);
    escreverTextoTxt(nomeTxt, comandos);

    for (int i = 0; i < tamQuadra; i++) {
        listaHash n = getIndiceHash(*hashQuad, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                q = getObjetoHash2(aux);
                if (!strcmp(getQuadraId(q), id)) {
                    verifica = 1;
                }
                aux = n;
            }
        }
    }

    if (verifica == 1) {
        for (int i = 0; i < tamMorador; i++) {
            listaHash n = getIndiceHash(*hashMor, i);
            if (n != NULL) {
                listaHash aux = n;
                while (aux != NULL) {
                    n = getProxHash(n);
                    m = getObjetoHash2(aux);
                    if (!strcmp(getMoradorCep(m),id)) {
                        printf("teste\n");
                        sprintf(result, "CPF: %s | Nome Completo: %s %s | Sexo: %s | Nascimento: %s | CEP: %s | Face: %c | Num: %d | Complemento: %s", getMoradorCpf(m), getMoradorNome(m), getMoradorSobrenome(m), getMoradorSexo(m) == 'M' ? "Masculino" : "Feminino", getMoradorNascimento(m), getMoradorCep(m), getMoradorFace(m), getMoradorNum(m), getMoradorCompl(m));
                        escreverTextoTxt(nomeTxt, result);
                        escreverTextoTxt(nomeTxt, "\n");
                    }
                    aux = n;
                }
            }
        }
    } else {
        escreverTextoTxt(nomeTxt, "Quadra não existente!");
    }
    escreverTextoTxt(nomeTxt, "\n");
}
