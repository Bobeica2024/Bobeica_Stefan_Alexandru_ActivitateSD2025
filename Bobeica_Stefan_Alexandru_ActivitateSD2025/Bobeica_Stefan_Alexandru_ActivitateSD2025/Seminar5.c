#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod {
	Masina* info;
	struct Nod* next;
	struct Nod* final;
};
typedef struct Nod Nod;
//creare structura pentru Lista Dubla 
struct ListaDubla {
	Nod* inceput;
	Nod* final;

};

typedef struct ListaDubla Lista;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = "\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniDeLaInceput(Lista list) {
	Nod* p = list.inceput;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void adaugaMasinaInLista(Lista* lis, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Lista* lis = malloc(sizeof(Lista));
	Nod* f = lis->final;
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->final = lis->final;
	if (lis->final != NULL) {
		lis->final->next = nou;
	}
	else {
		lis->inceput = nou;
	}
	lis->final = nou;
}

void adaugaLaInceputInLista(/*lista dubla de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
}

void* citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista* lis;
	lis->final = NULL;
	lis->inceput = NULL;
	while (!feof(f)) {
		Masina m;
		m = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&lis, m);
	}
	fclose(f);
	return lis;
}

void dezalocareLDMasini(Lista* lis) {
	
}

float calculeazaPretMediu(/*lista de masini*/) {
	float suma;
	int contor = 0;
	Nod* temp = lis.inceput;
	while (temp) {
		suma += temp->info->pret;
		contor++;
		temp = temp->next;
	}
	return 0;
}

void stergeMasinaDupaID(int id) {
	Nod* p = lis->inceput;
	while (p && p->info->id != id) {
		p = p->next;
	}
	if(p->next) {
		p->prev->next = 
	}
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {
	Lista lis;
	lis=citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(lis);
	printf("");
	return 0;
}