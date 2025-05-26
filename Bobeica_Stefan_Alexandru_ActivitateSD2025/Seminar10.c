#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* stg;
	struct Nod* dr;
	int gradEchilibru;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
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


void rotireStanga(Nod** arbore)
{
	Nod* aux = (*arbore)->dr;
	(*arbore)->dr = aux->stg;
	aux->stg = (*arbore);
	(*arbore) = aux;
	(*arbore)->gradEchilibru--;
}

void rotireDreapta(Nod** arbore)
{
	Nod* aux = (*arbore)->stg;
	(*arbore)->stg = aux->dr;
	aux->dr = (*arbore);
	(*arbore) = aux;
	(*arbore)->gradEchilibru++;
}

void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > masinaNoua.id) {
			adaugaMasinaInArboreEchilibrat(&((*radacina)->stg), masinaNoua);
			(*radacina)->gradEchilibru++;
		}
		else {
			adaugaMasinaInArboreEchilibrat(&((*radacina)->dr), masinaNoua);
			(*radacina)->gradEchilibru--;
		}
		if ((*radacina)->gradEchilibru == 2) {
			if ((*radacina)->stg->gradEchilibru == 1) {
				rotireDreapta(radacina);
			}
			else
			{
				rotireStanga(&((*radacina)->stg));
				rotireDreapta(radacina);
			}
		}
		if ((*radacina)->gradEchilibru == -2)
		{
			if ((*radacina)->dr->gradEchilibru == 1)
			{
				rotireDreapta(&((*radacina)->dr));
			}
			rotireStanga(radacina);
		}
	}

	else
	{
		Nod* radacinaNoua = malloc(sizeof(radacina));
		radacinaNoua->info = masinaNoua;
		radacinaNoua->dr = NULL;
		radacinaNoua->stg = NULL;
		radacinaNoua->gradEchilibru = 0;
		(*radacina) = radacinaNoua;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInArboreEchilibrat(&arbore, m);
	}
	fclose(f);
	return arbore;
}

void afisarePreOrdine(Nod* arbore)
{
	if (arbore)
	{

		afisareMasina(arbore->info);

		afisarePreOrdine(arbore->stg);
		afisarePreOrdine(arbore->dr);
	}
}

void afisareMasiniDinArbore() {
	
}

void dezalocareArboreDeMasini() {
	
}



Masina getMasinaByID(int id);

int determinaNumarNoduri();

float calculeazaPretTotal();

float calculeazaPretulMasinilorUnuiSofer(const char* numeSofer);

int main() {

	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
	afisarePreOrdine(arbore);
	return 0;
}