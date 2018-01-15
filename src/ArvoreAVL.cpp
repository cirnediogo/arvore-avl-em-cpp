/* 
 * File:   ArvoreAVL.cpp
 * Author: ubuntu
 * 
 * Created on 3 de Dezembro de 2009, 17:06
 */

#include "ArvoreAVL.h"

// Mesma função buscaABB da Arvore Binaria De Busca
int ArvoreAVL::buscaAVL(Chave idProcurado, NoAVL*& ptr) {
    NoAVL* ptNo = ptr;
    int f;
    if (ptNo == NULL) {
        f = 0;
    } else {
        if (idProcurado == ptNo->id) {
            f = 1;
        } else {
            if (idProcurado < ptNo->id) {
                f = 2;
                if (ptNo->esq != NULL) {
                    ptr = ptNo->esq;
                    f = buscaAVL(idProcurado, ptr);
                }
            } else {
                f = 3;
                if (ptNo->dir != NULL) {
                    ptr = ptNo->dir;
                    f = buscaAVL(idProcurado, ptr);
                }
            }
        }
    };
    return f;
}

// Mesma função find da Arvore Binaria De Busca
bool ArvoreAVL::find(Chave idProcurado, Informacao& valorRetorno) {
    NoAVL* ptr = Raiz;
    int f;
    f = buscaAVL(idProcurado, ptr);
    if (f == 1) {
        valorRetorno = ptr->info;
        return true;
    } else {
        return false;
    }
}

/*
 * buscaNoPai - Dada uma chave, e dois nós, o primeiro nó é atualizado para o
 * nó ao qual pertence a chave procurada, e o segundo nó e atualizado para o
 * pai do primeiro nó. Esta função é útil para ir balanceando a árvore de
 * baixo para cima.
 */
void ArvoreAVL::buscaNoPai(Chave idProcurado, NoAVL*& ptr, NoAVL*& noPai) {
    NoAVL* ptNo = ptr;
        if (idProcurado != ptNo->id) { //se igual, o nó já foi achado
            if (idProcurado < ptNo->id) { //menor - subárvore esquerda
                if (ptNo->esq != NULL) {
                    noPai = ptNo; //atualiza o pai
                    ptr = ptNo->esq; //atualiza o nó
                    buscaNoPai(idProcurado, ptr, noPai); //recursivamente continua a busca
                }
            } else { //maior - subárvore direita
                if (ptNo->dir != NULL) {
                    noPai = ptNo; //atualiza o pai
                    ptr = ptNo->dir; //atualiza o nó
                    buscaNoPai(idProcurado, ptr, noPai); //recursivamente continua a busca
                };
            }
        };
}

/*
 * balancear - Dado um nó, a função verifica seu fator de balanceamento e faz
 * as rotações necessárias levando em consideração o fator do seu filho. Em
 * seguida a função é aplicada ao pai do nó em questão, para balancear a
 * árvore de baixo para cima. Essa função é indispensável para a inserção e
 * remoção em uma Árvore AVL.
 */
void ArvoreAVL::balancear(NoAVL*& ptr) {
    NoAVL* ptNo = ptr;
    NoAVL* ptAux = Raiz; //apenas para realizar a busca do ptPai
    NoAVL* ptPai = Raiz; //apenas para indicar o pai do nó em questão
    int fator; //para armazenar o fator de balanceamento do nó em questão
    int fatorFilho; //o fator de balanceamento do filho, nescessário para saber se será feita uma rotação dupla
    Chave idAux;
    Chave idPai;
    buscaNoPai(ptNo->id, ptAux, ptPai); //armazena o pai para continuar a balancear o caminho até a raiz
    idAux = ptAux->id; //armazenar chave para comparação posterior
    idPai = ptPai->id; //armazenar chave para comparação posterior
    fator = fatorBalanceamentoAVL(ptAux); //calcula o fator de balanceamento
    if (fator > 1) { //necessária uma rotação à esquerda depois de analisar o filho direito
        fatorFilho = fatorBalanceamentoAVL(ptAux->dir); //calcula o fator de balanceamento do filho direito
        if (fatorFilho >= 0) { //nesse caso, basta uma rotação simples
            ptr = ptAux;
            rotacaoSimplesEsq(ptr, ptPai); //faz a rotacao à esquerda do nó
        } else { //nesse caso, é necessaria a rotacao dupla
            ptr = ptAux;
            rotacaoSimplesDir(ptr->dir, ptr); //rotação à direita do filho
            rotacaoSimplesEsq(ptr, ptPai); //rotação à esquerda do nó
        };
    } else {
        if (fator < -1) { //necessária uma rotação à direita depois de analisar o filho esquerdo
            fatorFilho = fatorBalanceamentoAVL(ptAux->esq); //calcula o fator de balanceamento do filho esquerdo
            if (fatorFilho <= 0) { //nesse caso, basta uma rotação simples
                ptr = ptAux;
                rotacaoSimplesDir(ptr, ptPai); //faz a rotacao à esquerda do nó
            } else { //nesse caso, é necessaria a rotacao dupla
                ptr = ptAux;
                rotacaoSimplesEsq(ptr->esq, ptr); //rotação à esquerda do filho
                rotacaoSimplesDir(ptr, ptPai); //rotação à direita do nó
            }
        }
    };
    if (idAux != idPai) { //se for igual, a buscaNoPai não atualizou os nós, então o nó em questão era a raiz e não será mas preciso balancear mais nós
        balancear(ptPai); //se diferente, continua a balancear o caminho até a raiz
    };
}

/*
 * insereAVL - Mesma função insereABB da Árvore Binária de Busca
 * com um adicional: sempre que um nó é inserido, a função balancear é
 * chamada para iniciar o balanceamento de todo o caminho do nó inserido
 * até a raiz.
 */
bool ArvoreAVL::insereAVL(Chave idPosicao, Informacao valorNovo, NoAVL*& ptr) {
    NoAVL* ptNo = ptr;
    NoAVL* ptNovo;
    int f;
    f = buscaAVL(idPosicao, ptNo);
    if (f == 1) {
        return false;
    } else {
        ptNovo = new NoAVL;
        ptNovo->id = idPosicao;
        ptNovo->info = valorNovo;
        ptNovo->esq = NULL;
        ptNovo->dir = NULL;
        if (f == 0) {
            Raiz = ptNovo; //se inserido foi a raiz, não é necessário balancear
        } else {
            if (f == 2) {
                ptNo->esq = ptNovo;
                balancear(ptNo); //elemento inserido, é preciso balancear a partir de seu pai
            } else {
                ptNo->dir = ptNovo;
                balancear(ptNo); //elemento inserido, é preciso balancear a partir de seu pai
            }
        };
        return true;
    }
}

// Mesma função insert da Arvore Binaria De Busca
bool ArvoreAVL::insert(Chave idPosicao, Informacao valorNovo) {
    bool r;
    r = insereAVL(idPosicao, valorNovo, Raiz);
    return r;
}

// Mesma função localizaMin da Arvore Binaria De Busca
void ArvoreAVL::localizaMin(NoAVL*& ptr) {
    NoAVL* esq = ptr->esq;
    if (esq != NULL) {
        ptr = esq;
        localizaMin(ptr);
    };
}

/*
 * removeAVL - Mesma função removeABB da Árvore Binária de Busca
 * com um adicional: sempre que um nó é removido, a função balancear é
 * chamada para iniciar o balanceamento de todo o caminho do nó removido
 * até a raiz.
 */
bool ArvoreAVL::removeAVL(Chave idPosicao, NoAVL*& ptr) {
    NoAVL* ptNo = ptr;
    NoAVL* ptAux = Raiz;
    NoAVL* ptPai = Raiz;
    bool r = true;
    if (ptr == NULL) {
        r = false;
    } else {
        if (idPosicao < ptr->id) {
            removeAVL(idPosicao, ptr->esq);
        } else {
            if (idPosicao > ptr->id) {
                removeAVL(idPosicao, ptr->dir);
            } else {
                if ((ptr->esq != NULL) && (ptr->dir != NULL)) {
                    ptNo = ptr->dir;
                    localizaMin(ptNo);
                    ptr->id = ptNo->id;
                    ptr->info = ptNo->info;
                    removeAVL(ptNo->id, ptr->dir);
                    balancear(ptNo); //ponteiros foram alterados, a árvore foi modificada, logo, é preciso balancear
                } else {
                    ptNo = ptr;
                    buscaNoPai(ptNo->id, ptAux, ptPai); //busca o pai do nó removido para o caso de ser necessário iniciar o balanceamento por ele
                    if (ptNo->esq != NULL) {
                        ptr = ptr->esq;
                    } else {
                        ptr = ptr->dir;
                    };
                    delete [] ptNo; //elemento foi removido
                    if (ptr == NULL) { //se for nulo não tinha filhos, então balanceamento inicia pelo pai
                        if (ptAux->id != ptPai->id) { //se for igual, removido foi a raiz, então não precisa balancear
                        balancear(ptPai); //inicia o balanceamento pelo pai
                        };
                    } else { //nesse caso, o nó tinha filhos, entao o balanceamento inicia pelo filho que tomou seu lugar
                        balancear(ptr);
                    }
                }
            }
        }
    };
    return r;
}

// Mesma função remove da Arvore Binaria De Busca
bool ArvoreAVL::remove(Chave idPosicao) {
    bool r;
    r = removeAVL (idPosicao, Raiz);
    return r;
}

/*
 * alturaNoAVL - Calcula a altura do nó dado. Essa função é essencial para
 * calcular o fator de balanceamento de um nó.
 */
int ArvoreAVL::alturaNoAVL(NoAVL*& ptr) {
    NoAVL* ptNo = ptr;
    int altEsq;
    int altDir;
    if (ptNo->esq == NULL){
        if (ptNo->dir == NULL) {
            return 1; //nesse caso o nó não tem filhos, então sua altura é 1
        } else {
            return (1 + alturaNoAVL(ptNo->dir)); // nesse caso só tem filho direito, então sua altura é 1 a mais que a subárvore direita
        };
    } else {
        if (ptNo->dir == NULL){
            return (1 + alturaNoAVL(ptNo->esq)); // nesse caso só tem filho esquerdo, então sua altura é 1 a mais que a subárvore esquerda
        } else {
            altEsq = alturaNoAVL(ptNo->esq); //armazena a altura da subárvore esquerda
            altDir = alturaNoAVL(ptNo->dir); //armazena a altura da subárvore direita
            if (altEsq >= altDir) { //verifica qual a maior subárvore e retorna 1 a mais que a maior
                return (1 + altEsq);
            } else {
                return (1 + altDir);
            }
        }
    }
}

/*
 * fatorBalanceamentoAVL - Calcula o fator de balanceamento do nó dado.
 * Essa função é essencial para a árvore AVL uma vez que é o fator de
 * balanceamento que indica se um nó está ou não balanceado.
 */
int ArvoreAVL::fatorBalanceamentoAVL(NoAVL*& ptr) {
    NoAVL* ptNo = ptr;
    int altEsq;
    int altDir;
    if (ptNo->esq == NULL) {
        altEsq = 0; //não possui subárvore esquerda
    } else {
        altEsq = alturaNoAVL(ptNo->esq); //calcula a altura da subárvore esquerda
    };
    if (ptNo->dir == NULL) {
        altDir = 0; //não possui subárvore direita
    } else {
        altDir = alturaNoAVL(ptNo->dir); //calcula a altura da subárvore direita
    };
    return altDir-altEsq; //fator de balanceamento é igual à diferença entra as subárvores direita e esquerda, respectivamente
}

/*
 * rotacaoSimplesDir - faz a rotação de uma subárvore para a direita.
 * Importante para balancear a árvore.
 */
void ArvoreAVL::rotacaoSimplesDir(NoAVL*& ptr, NoAVL*& NoPai) {
    NoAVL* ptNo = ptr;
    NoAVL* ptEsq = ptr->esq;
    Chave idNo = ptNo->id;
    Chave idPai = NoPai->id;
    int t; //apenas para em qual subárvore(esquerda ou direita) do pai será a rotação
    if (idNo != idPai) { //se for igual, o nó que será rotacionado é a raiz
        if ((NoPai->esq != NULL) && ((NoPai->esq)->id == idNo)) { //o nó que será rotacionado é o filho esquerdo do NoPai
            t = 1; //1 indica que o ponteiro esq do NoPai deverá ser atualizado
        };
        if ((NoPai->dir != NULL) && ((NoPai->dir)->id == idNo)) { //o nó que será rotacionado é o filho direito do NoPai
            t = 2; //2 indica que o ponteiro dir do NoPai deverá ser atualizado
        };
    }
    ptNo->esq = ptEsq->dir; //atualização dos ponteiros
    ptEsq->dir = ptNo; //atualização dos ponteiros
    ptr = ptEsq; //atualização do nó em questão
    if (idNo != idPai) { //se for igual, o nó é a raiz, e não terá pai para ser atualizado
        if (t == 1) { //ponteiro esq do NoPai deve ser atualizado para o novo nó
            NoPai->esq = ptr;
        } else { //ponteiro dir do NoPai deve ser atualizado para o novo nó
            NoPai->dir = ptr;
        }
    }
    if (ptNo->id == Raiz->id) { //nó rotacionado foi a raiz e ele mudou de lugar, logo, a raiz precisa se atualizada
        Raiz = ptr; //o ponteiro raiz é atualizado para o nó que tomou o lugar da antiga raiz
    };
}

/*
 * rotacaoSimplesEsq - faz a rotação de uma subárvore para a esquerda.
 * Importante para balancear a árvore.
 */
void ArvoreAVL::rotacaoSimplesEsq(NoAVL*& ptr, NoAVL*& NoPai) {
    NoAVL* ptNo = ptr;
    NoAVL* ptDir = ptr->dir;
    Chave idNo = ptNo->id;
    Chave idPai = NoPai->id;
    int t; //apenas para em qual subárvore(esquerda ou direita) do pai será a rotação
    if (idNo != idPai) { //se for igual, o nó que será rotacionado é a raiz
        if ((NoPai->esq != NULL) && ((NoPai->esq)->id == idNo)) { //o nó que será rotacionado é o filho esquerdo do NoPai
            t = 1; //1 indica que o ponteiro esq do NoPai deverá ser atualizado
        };
        if ((NoPai->dir != NULL) && ((NoPai->dir)->id == idNo)) { //o nó que será rotacionado é o filho direito do NoPai
            t = 2; //2 indica que o ponteiro dir do NoPai deverá ser atualizado
        };
    }
    ptNo->dir = ptDir->esq; //atualização dos ponteiros
    ptDir->esq = ptNo; //atualização dos ponteiros
    ptr = ptDir; //atualização do nó em questão
    if (idNo != idPai) { //se for igual, o nó é a raiz, e não terá pai para ser atualizado
        if (t == 1) { //ponteiro esq do NoPai deve ser atualizado para o novo nó
            NoPai->esq = ptr;
        } else { //ponteiro dir do NoPai deve ser atualizado para o novo nó
            NoPai->dir = ptr;
        }
    }
    if (ptNo->id == Raiz->id) { //nó rotacionado foi a raiz e ele mudou de lugar, logo, a raiz precisa se atualizada
        Raiz = ptr; //o ponteiro raiz é atualizado para o nó que tomou o lugar da antiga raiz
    };
}

// Mesma função imprimeArv da Arvore Binaria De Busca.
void ArvoreAVL::imprimeArv(int nivel, NoAVL*& ptr) {
    for (int i = 0; i < (nivel-1)*5; i++) {
        cout << "-";
    };
    cout << ptr->id << endl;
    if (ptr->esq != NULL) {
        imprimeArv((nivel+1), ptr->esq);
    };
    if (ptr->dir != NULL) {
        imprimeArv((nivel+1), ptr->dir);
    };
}

// Mesma função imprime da Arvore Binaria De Busca.
void ArvoreAVL::imprime() {
    imprimeArv(1,Raiz);
}

// Mesmo construtor da Arvore Binaria De Busca.
ArvoreAVL::ArvoreAVL() {
    Raiz = new NoAVL;
    Raiz->id = 0;
    Raiz->info = 0;
    Raiz->dir = NULL;
    Raiz->esq = NULL;
}

// Mesmo construtor da Arvore Binaria De Busca.
ArvoreAVL::ArvoreAVL(Chave idRaiz, Informacao infoRaiz, NoAVL* subArvEsq, NoAVL* subArvDir) {
    Raiz = new NoAVL;
    Raiz->id = idRaiz;
    Raiz->info = infoRaiz;
    Raiz->dir = subArvDir;
    Raiz->esq = subArvEsq;
}

// Mesmo destrutor da Arvore Binaria De Busca.
ArvoreAVL::~ArvoreAVL() {
    delete [] Raiz;
}

