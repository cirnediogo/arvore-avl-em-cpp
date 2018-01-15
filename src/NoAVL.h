/* 
 * File:   NoAVL.h
 * Author: ubuntu
 *
 * Created on 3 de Dezembro de 2009, 17:04
 */

#ifndef _NOAVL_H
#define	_NOAVL_H
#include "Chave.h"
#include "Informacao.h"

typedef struct NoAVL {
    Informacao info;
    Chave id;
    NoAVL* esq;
    NoAVL* dir;
};



#endif	/* _NOAVL_H */

