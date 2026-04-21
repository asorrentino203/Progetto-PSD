typedef struct st* studente;
studente creaStudente(char mat[],char*name,char course[]);
char*getMatricola(studente nuovoStudente);
char*getNome(studente nuovoStudente);
char*getCorsoDiLaurea(studente nuovoStudente);
int StudenteUguale(studente s1,studente s2);
int Distruttore(studente nuovoStudente);
int input_studente_da_file(FILE*nome_file, /*puntatore alla struttura*/);
studente input_studente_da_tastiera();