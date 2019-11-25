#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_TITLE_LENGHT = 255;

typedef struct Traccia {
	char *Traccia;
} traccia;

typedef struct Playlist { // Struttura dati rappresentante una playlist
	size_t NumeroTracce;  // Quantità di tracce
	traccia *Tracce;	  // Puntatore ad un array di tipo (traccia)
} playlist;

void parsePlaylist(FILE *stream, playlist *array, size_t numeroAmici) { // Funzione che salva le playlist nelle strutture dedicate
	for (size_t i = 0; i < numeroAmici; i++) {							// Per ogni amico
		size_t numeroTracce;
		fscanf(stream, "%zu", &numeroTracce);									   // Leggo il numero di tracce
		array[i].NumeroTracce = numeroTracce;									   // Scrivo il numero di tracce di questa singola playlist
		array[i].Tracce		  = (traccia *)malloc(numeroTracce * sizeof(traccia)); // Alloco memoria sull'array di tracce

		for (size_t j = 0; j < numeroTracce; j++) { // Per ogni traccia
			char temp[MAX_TITLE_LENGHT];
			fscanf(stream, "%s", temp);												  // Scrivo la traccia nella variabile temporanea
			array[i].Tracce[j].Traccia = (char *)malloc(sizeof(char) * strlen(temp)); // Alloco solo la memoria necessaria
			strcpy(array[i].Tracce[j].Traccia, temp);								  // Copio il nome della traccia
		}
	}
}

void stampaPlaylist(playlist *daStampare) { // Funzione che stampa una playlist a video
	puts("Contenuto della playlist:");
	for (size_t i = 0; i < daStampare->NumeroTracce; i++) { // Per ogni traccia
		printf("    %zu - ", i + 1);
		puts(daStampare->Tracce[i].Traccia); // Stampo il titolo della traccia
	}
	printf("\n");
}

size_t generaPlaylist(playlist *amici, size_t letturaAttuale, playlist *risultato) { // Genera le varie playlist seguendo il principio di moltiplicazione
	size_t conteggio = 0;

	if (letturaAttuale == risultato->NumeroTracce) { // Se sto leggendo l'ultimo elemento, stampo le combinazioni
		stampaPlaylist(risultato);
		return 1; // Interrompo la ricorsione
	}

	for (size_t i = 0; i < amici[letturaAttuale].NumeroTracce; i++) {								   // Per ogni traccia della corrente playlist
		memcpy(&risultato->Tracce[letturaAttuale], &amici[letturaAttuale].Tracce[i], sizeof(traccia)); // Copio la traccia nella playlist di risultato
		conteggio += generaPlaylist(amici, letturaAttuale + 1, risultato);							   // Lavoro ricorsivamente sul gruppo successivo
	}

	return conteggio;
}

int main() {
	FILE *stream = fopen("brani.txt", "r");
	size_t numeroAmici;
	fscanf(stream, "%zu", &numeroAmici); // Leggo il numero di amici nel file
	playlist amici[numeroAmici];		 // Array di playlist per ogni amico

	parsePlaylist(stream, amici, numeroAmici); // Leggo le playlist dal file

	playlist risultato;														   // Dichiaro una playlist d'appoggio per salvare i dati
	risultato.NumeroTracce = numeroAmici;									   // La playlist dovrà contenere sino a n brani dove n è il numero di amici
	risultato.Tracce	   = (traccia *)malloc(numeroAmici * sizeof(traccia)); // Alloco memoria sull'array di tracce

	size_t generazioni = generaPlaylist(amici, 0, &risultato); // Genero le playlist

	printf("Sono state generate %zu playlist\n", generazioni);
	fclose(stream);
	return 0;
}