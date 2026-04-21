#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studente.h"

//definizione della struttura studente
struct st{
  char  matricola[11];
  char *nome;
  char corso_di_laurea[6];
};

//funzione che alloca spazio per la creazione di uno studente
studente creaStudente(char mat[], char *name, char course[]){
    studente nuovoStudente =malloc(sizeof(struct st)); 
    if(nuovoStudente == NULL){
        return NULL;
    }
    strncpy(nuovoStudente->matricola,mat,10);
    nuovoStudente->matricola[10]='\0';
    nuovoStudente->nome=malloc(strlen(name)+1);
    if(nuovoStudente->nome != NULL){
        strcpy(nuovoStudente->nome,name);
    }
    else{
        free(nuovoStudente);
        nuovoStudente=NULL;
        return NULL;
    }
    strncpy(nuovoStudente->corso_di_laurea,course,5);
    nuovoStudente->corso_di_laurea[5]='\0';
    return nuovoStudente;
}

//funzione "getter" che restituisce la matricola dello studente
char *getMatricola(studente nuovoStudente){
    if(nuovoStudente != NULL){
    return nuovoStudente->matricola;
    }
    else{
        return NULL;
    }
}

//funzione "getter" che restituisce il nome dello studente
char* getNome(studente nuovoStudente){
    if(nuovoStudente != NULL){
        return nuovoStudente->nome;
    }
    else{
        return NULL;
    }
}
//funzione "getter" che restituisce il corso di laurea dello studente
char* getCorsoDiLaurea(studente nuovoStudente){
    if(nuovoStudente != NULL){
        return nuovoStudente->corso_di_laurea;
    }
    else{
        return NULL;
    }
}

//funzione che verifica se 2 studenti soono uguali tramite la matricola (leggere lezione 5 per capire il motivo di questa implementazione)
int studenteUguale(studente s1, studente s2){
    if(strcmp(getMatricola(s1),getMatricola(s2))==0){
        return 1; //gli studenti sono uguali
    }
    else{
        return -1;//gli studenti sono diversi
    }
}

//funzione per leggere gli input da tastiera (come farebbe un operatore di banco)
studente input_studente_da_tastiera(){
    //creazione di buffer temporanei per memorizzare gli input
    char temp_mat[11];
    char temp_corsoDiLaurea[50];
    char temp_nome[50];

    puts("inserisci la matricola dello studente IN MAIUSCOLO");
    fgets(temp_mat, 11, stdin); //funzione per leggere stringhe in modo sicuro da tastiera,fgets aggiuge il carattere di terminazione in automatico
    while (getchar() != '\n'); //puliamo il buffer in modo da non avere caratteri non letti in sospeso, compreso '\n'
    puts("inserisci il nome");
    fgets(temp_nome,50,stdin);//se c'è spazio nel buffer, la funzione fgets copia anche '\n'
    temp_nome[strcspn(temp_nome, "\n")] = '\0'; //la funzione strcspn sostituisce '\n' con il carattere di terminazione '\0'
    puts("inserisci corso di laurea");
    fgets(temp_corsoDiLaurea,6,stdin);
    temp_corsoDiLaurea[strcspn(temp_corsoDiLaurea, "\n")] = '\0';
    return creaStudente(temp_mat,temp_nome,temp_corsoDiLaurea);
}


//funzione per leggere gli input da file (per eseguire test)
//CASO ECCEZIONALE: dopo la lettura facciamo anche l'inserimento (perché stiamo gestendo grandi quantità di dati)
int input_studente_da_file(FILE* nome_file, /*parametro della struttura*/){
    //creazione di buffer temporanei per memorizzare gli input
    char temp_mat[11];
    char temp_corsoDiLaurea[100];
    char temp_nome[50];
    //dichiarazione di un puntatore a file per leggere nel file
    FILE* fp;
    //apriamo il file in modalità lettura
    fp=fopen(nome_file,"r");
    //controllo che l'apertura del file sia andata a buon fine
    if(fp == NULL){
        return 1;
    }
        //finché ci sono dati nel file, li leggo
        while(fgets(temp_mat,11,fp)!=NULL){
            temp_mat[strcspn(temp_mat,"\n")=='\0'];
            if(fgest(temp_nome,50,fp)!=NULL){
                temp_nome[strcspn(temp_nome, "\n")=='\0'];
            }
            else{return 1;}
            if(fgets(temp_corsoDiLaurea,6,fp)!=NULL){
                temp_corsoDiLaurea[strcspn(temp_corsoDiLaurea,"\n")=='\0'];
            }
            else{return 1;}
        }
        //chiudiamo il file
        fclose(fp);
        // Se l'operazione di lettura è andata a buon fine, restituisco 1
        return 0;

}

//funzione "distruttore" per deallocare la memoria ed evitare problemi di overflow
//deallochiamo solo nuovoStudente->nome perché matricola e corso di laurea sono array di dim fissa
//quindi il loro spazio è già stato calcolato nella definizione della struttura
int Distruttore(studente nuovoStudente){
    if(nuovoStudente != NULL){
        if(nuovoStudente->nome != NULL){
            free(nuovoStudente->nome);
        }
        free(nuovoStudente);
    }
    return 0;
}