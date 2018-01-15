/* 
 * File:   ArvoreAVL.h
 * Author: ubuntu
 *
 * Created on 3 de Dezembro de 2009, 17:06
 */

#ifndef _ARVOREAVL_H
#define	_ARVOREAVL_H
#include "NoAVL.h"
#include <iostream>
using namespace std;

class ArvoreAVL {
public:
    ArvoreAVL();
    ArvoreAVL(Chave idRaiz, Informacao infoRaiz, NoAVL* subArvEsq, NoAVL* subArvDir);
    virtual ~ArvoreAVL();
    bool find(Chave idProcurado, Informacao& valorRetorno);
    bool insert(Chave idPosicao, Informacao valorNovo);
    bool remove(Chave idPosicao);
    void imprime();
private:
    NoAVL* Raiz;
    bool insereAVL(Chave idPosicao, Informacao valorNovo, NoAVL*& ptr);
    int buscaAVL(Chave idProcurado, NoAVL*& ptr);
    bool removeAVL(Chave idPosicao, NoAVL*& ptr);
    void localizaMin(NoAVL*& ptr);
    void imprimeArv(int nivel, NoAVL*& ptr);
    int fatorBalanceamentoAVL(NoAVL*& ptr);
    int alturaNoAVL(NoAVL*& ptr);
    void rotacaoSimplesDir(NoAVL*& ptr, NoAVL*& noPai);
    void rotacaoSimplesEsq(NoAVL*& ptr, NoAVL*& noPai);
    void buscaNoPai(Chave idProcurado, NoAVL*& ptr, NoAVL*& noPai);
    void balancear(NoAVL*& ptr);
};

#endif	/* _ARVOREAVL_H */

