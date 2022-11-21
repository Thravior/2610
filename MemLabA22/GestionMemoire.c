#include "./libs/lib.h"
#include <limits.h>

unsigned int calculerNumeroDePage(unsigned long adresse) {
	// TODO
    return adresse / (1024);
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
	// TODO
     return adresse % (1024);
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
	// TODO
     return deplacementDansLaPage + (numeroDePage * 1024);
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	unsigned int numeroDePage = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned int deplacement = calculerDeplacementDansLaPage(req->adresseVirtuelle);
	req->adressePhysique = 0;
	req->estDansTLB = 0;
	
	for (int i = 0; i < TAILLE_TLB; ++i) {
		if (mem->tlb->numeroPage[i] == numeroDePage && mem->tlb->entreeValide[i]) {
			req->adressePhysique = calculerAdresseComplete(mem->tlb->numeroCadre[i], deplacement);
			req->estDansTLB = 1;
			mem->tlb->dernierAcces[i] = req->date;
			break;
		}
	}
}

void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	unsigned int numeroDePage = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned int deplacement = calculerDeplacementDansLaPage(req->adresseVirtuelle);
	req->adressePhysique = 0;
	req->estDansTablePages = 0;
	
	if (mem->tp->entreeValide[numeroDePage]) {
		req->adressePhysique = calculerAdresseComplete(mem->tp->numeroCadre[numeroDePage], deplacement);
		req->estDansTablePages = 1;
	}
}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	//TODO
	unsigned int numeroDePage = calculerNumeroDePage(req->adresseVirtuelle);
	unsigned int deplacement = calculerDeplacementDansLaPage(req->adresseVirtuelle);

	for (int i = 0; i < TAILLE_MEMOIRE; ++i){
		if(!(mem->memoire->utilisee[i])){
			mem->memoire->dateCreation[i] = req->date;
			mem->memoire->dernierAcces[i] = req->date;
			mem->memoire->utilisee[i] = 1;
			
			req->adressePhysique = calculerAdresseComplete(i, deplacement);			break;
		}
	}
}

void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	int indexOut = -1;
	unsigned long dateOut = ULONG_MAX;
	for (int i = 0; i<TAILLE_TLB; ++i){
		if (!mem->tlb->entreeValide[i]){
			mem->tlb->dateCreation[i] = req->date;
			mem->tlb->dernierAcces[i] = req->date;
			mem->tlb->entreeValide[i] = 1;
			mem->tlb->numeroCadre[i] = calculerNumeroDePage(req->adressePhysique);	
			mem->tlb->numeroPage[i]  = calculerNumeroDePage(req->adresseVirtuelle);
			indexOut = -1;
			break;
		}
		if (mem->tlb->dateCreation[i] < dateOut){
			dateOut = mem->tlb->dateCreation[i];
			indexOut = i;
		}
	}
	if (indexOut >= 0) {
		mem->tlb->dateCreation[indexOut] = req->date;
		mem->tlb->dernierAcces[indexOut] = req->date;
		mem->tlb->entreeValide[indexOut] = 1;
		mem->tlb->numeroCadre[indexOut] = calculerNumeroDePage(req->adressePhysique);	
		mem->tlb->numeroPage[indexOut]  = calculerNumeroDePage(req->adresseVirtuelle);
	}	
}

// NE PAS MODIFIER
int main() {
    evaluate(
		&calculerNumeroDePage, 
		&calculerDeplacementDansLaPage, 
		&calculerAdresseComplete, 
        &rechercherTLB, 
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire
    );
    return 0;
}
