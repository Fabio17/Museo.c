//librerie da includere nel programma
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct opera{	//definiamo la struttura chiamata opera in cui definiamo i campi di tipo char indicanti il titolo e l'autore e un campo di tipo int indicante l'anno di realizzazione
	char titolo[20];
	char autore[20];
	int anno;
	struct opera* succ;
};
typedef struct opera opera;


struct museo{	//definiamo una struttura chiamata museo
    char genere[20];
		opera* op;
		struct museo* next;
};
typedef struct museo museo;

struct prestito	//definiamo una struttura chiamata prestito in cui definiamo i campi di tipo char e int
{
	char titolo[20];
	char autore[20];
	int anno;
	int tempo;
	char gen[20];
	char destinatario[20];
	struct prestito* seguente;
};
typedef struct prestito prestito;

struct queue	//definiamo una struttura chiamata queue in cui abbiamo la struct restauro "testa" e "coda"
{
	struct restauro* h;
	struct restauro* t;
};
typedef struct queue queue;

struct restauro	//definiamo una struttura chiamata restauro in cui definiamo i campi di tipo char e int
{
	char titolo[20];
	char autore[20];
	int anno;
	int giorni;
	char genereopera[20];
	struct restauro* pross;
};
typedef struct restauro restauro;


//dichiaro le varie funzioni per consentire al programma di svolgere le varie operazioni assegnate
void inserimentogenere(struct museo** head);
void cancellagen(struct museo** head);
void inserimentoopera(struct museo** head);
void ricercagen(struct museo** head);
void modificaopera(struct museo** head);
void visgen(struct museo** head);
void cancellaopera(struct museo** head);
void ricercaopera(struct museo** head);
void inv_restauro(struct museo** head, struct queue** rest);
void inv_prestito(struct museo** head, struct prestito** prest);
void vis_res_pres(struct queue** rest,struct prestito** prest);
void avanzagiorno(struct museo** head, struct queue** rest,struct prestito** prest);
void salvamuseo(struct museo* head);
void salvarestauro(struct queue* rest);
void salvaprestito(struct prestito* prest);
void caricamuseo(struct museo** head);
void caricarestauro(struct queue** rest);
void caricaprestito(struct prestito ** prest);
struct museo* ricercabase(struct museo** head, char genere[]);
struct museo* inserimento1(struct museo** head, char genere[]);
void ricerca2(struct opera** r, struct opera** u, struct opera* nuovo);
void inserimento2(struct opera** r, struct opera** u, struct museo** q, struct opera** nuovo);
void inserimentocoda(struct restauro** nuovo, struct queue** rest);
void inserimentotesta(struct prestito ** prest, struct prestito** nuovo);


void main()
{
	struct museo* head=NULL;
  struct queue* rest=NULL;
  struct prestito* prest=NULL;
	caricamuseo(&head);
	caricarestauro(&rest);
	caricaprestito(&prest);
	int a;
    int x;
    int y=0;
    char ch;
  while(1)	//utilizzo questo while per far si che ad ogni esecuzione del programma e ogni operazioni che premiamo, si ripeta in modo da poter reinserire e svolgere una nuova funzione, fino a quando exit non è uguale a 0. In tal caso, digitando 0 usciamo dal programma
  {
    a=1;

    	printf("Menu': \n");	// da qui creo un menù a tendina per le varie operazioni che svolge il programma e per rendere più facile il suo utilizzo
    	printf("1- Inserimento di un genere di Opera\n");
    	printf("2- Cancellazione di un genere di Opera\n");
    	printf("3- Visualizzazione dei generi di opera presenti nel museo\n");
    	printf("4- Ricerca e visualizzazione di tutte le opere di un genere\n");
   		printf("5- Inserimento di un Opera\n");
    	printf("6- Cancellazione di un Opera\n");
    	printf("7- Modifica di un Opera\n");
    	printf("8- Ricerca di un Opera\n");
    	printf("9- Invio opera in restauro\n");
    	printf("10- Invio opera in prestito\n");
    	printf("11- Visualizzazione delle opere in prestito e in restauro\n");
    	printf("12- Giorno successivo\n");
    	printf("0- LOG OUT\n");
    	printf("Inserire il numero dell'operazione che si vuole svolgere : \n");
    	scanf("%d",&x);
        while((ch=getchar()) != '\n' && ch !=EOF);	// Pulitura buffer d'ingresso.
	while(a!=1)	
    {
      if(x>10 || x<0)
      {
        printf("Il numero inserito non corrisponde a nessuna operazione \n");
        printf("Inserisci un nuovo numero per effettuare un'operazione, altrimenti premi 0 per uscire \n");
        scanf("%d",&x);
      }
      else
        a=0;
    }
    switch(x)
    {
        	case 1:
                inserimentogenere(&head);
                break; //causa l'uscita immediata dallo switch

            case 2:
                cancellagen(&head);
                break;

			case 3:
				visgen(&head);
				break;

			case 4:
                ricercagen(&head);
                break;

            case 5:
                inserimentoopera(&head);
                break;

            case 6:
                cancellaopera(&head);
                break;

            case 7:
                modificaopera(&head);
                break;

            case 8:
                ricercaopera(&head);
                break;

            case 9:
                inv_restauro(&head, &rest);
                break;

           case 10:
                inv_prestito(&head, &prest);
                break;

           case 11:
                vis_res_pres(&rest,&prest);
                break;

            case 12:
                avanzagiorno(&head,&rest,&prest);
                break;

			  case 0:
					salvamuseo(head);
				 	salvaprestito(prest);
					salvarestauro(rest);
        		exit(0);
        		break;
    }
  }
}

struct museo* ricercabase(struct museo** head, char genere[])
{	//gli passo il genere da cercare e la testa della lista
	struct museo *q=*head;
	while((q!=NULL) && (strcmp(q->genere,genere)!=0))	// qui si effettua la ricerca del genere da trovare
		q=q->next;
	return q;	//appena viene trovata la posizione o q=NULL viene ritornato q
}

struct museo* inserimento1(struct museo** head, char genere[])
{
	struct museo* q=*head;
	struct museo* r=*head;
	struct museo* nuovo=(struct museo*)malloc(sizeof(struct museo));
	strcpy(nuovo->genere,genere);
	nuovo->op=NULL;
	nuovo->next=NULL;
	while((q!=NULL) && (strcmp(q->genere,genere)<0))
	{
		r=q;
		q=q->next;
	}

	if(q==*head)
		*head=nuovo;
	else
		r->next=nuovo;	//l'elemento successivo di r è uguale all'elemento da inserire
	nuovo->next=q;		//inserisco tra r e q
	return nuovo;
}

void ricerca2(struct opera** r, struct opera** u, struct opera* nuovo)
{
	while((*r!=NULL) && (strcmp((*r)->titolo,nuovo->titolo)<0))
	{	//bisogna inserire tra u e r
		 *u=*r;
		 *r=(*r)->succ;
	}	//siccome ho passato il doppio puntatore non si ha un valore di ritorno perchè u e r vengono modificati
}

void inserimento2(struct opera** r, struct opera** u, struct museo** q, struct opera** nuovo)
{

	if((*u)==(*q)->op)
	 {
		 (*q)->op=*nuovo;
	 	}
 else
	 {
		 (*r)->succ=*nuovo;//l'elemento successivo di r è uguale all'elemento da inserire
	 }
 (*nuovo)->succ=(*u);	//inserisco tra u e r

}

void inserimentocoda(struct restauro** nuovo, struct queue** rest)	 //Si scorre tutta la lista fino a quando non si trova l’ultimo elemento e quindi si effettua l’inserimento del nuovo elemento.
{	// passo l'elemento da inserire nel restauro, e rest per la struct queue
	if((*rest)->h==NULL)	// se la testa della coda è null, metto la testa della coda che punta all'elemento da inseriere perchè signifca che quello è il primo e l'ultimo elemento
		{	
			(*rest)->h=(*nuovo);
			(*rest)->t=(*nuovo);
		}
		 else	//altrimenti faccio un normale inserimento in coda
		{
			(*rest)->t->pross=(*nuovo);	//aggiorno la tail della coda
			(*rest)->t=(*nuovo);
		}
}

void inserimentotesta(struct prestito ** prest, struct prestito** nuovo)
{
	if((*prest)!=NULL)
		(*nuovo)->seguente=(*prest);
	(*prest)=(*nuovo);
}

void inserimentogenere(struct museo** head)
{
  struct museo* nuovo=(struct museo*)malloc(sizeof(struct museo));	// ho creato lo "scatolino" per il nuovo genere da inserire
  printf("Inserisci il nuovo genere da inserire in lista: \n");
  gets(nuovo->genere);
	strcat(nuovo->genere,"\n");		//concateno "\n" alla stringa inserita per omologarla alla stringa letta da fgets(); che ha un "\n" prima del terminatore. il terminatore è /0
  nuovo->op=NULL;
  nuovo->next=NULL;
  struct museo* q=*head;	//successore
  struct museo* r=*head;	//predecessore
	while((q!=NULL) && (strcmp(q->genere,nuovo->genere)!=0))
    q=q->next;

  if(q!=NULL)
  {
  	printf("Genere gia' presente\n");
    return;
  }
  else
  {
    q=*head;
  	while((q!=NULL) && (strcmp(q->genere,nuovo->genere)<0))
  	{
    	r=q;
    	q=q->next;
 	 	}

    if(q==*head)
      *head=nuovo;
    else
      r->next=nuovo;
    nuovo->next=q;
  }
}

void cancellagen(struct museo** head)	//Si scorre tutta la lista fino a quando non si trova l'elemento da cancellare o non si arriva alla fine della lista. bisogna memorizzare un puntatore all'elemento corrente ed uno all'elemento precedente.
{
  char gen[20];
	printf("Quale genere va eliminato?\n");
	gets(gen);
	strcat(gen,"\n");	//concateno "\n" alla stringa inserita per omologarla alla stringa letta da fgets(); che ha un "\n" prima del terminatore
  struct museo* q=*head;
  struct museo* r=*head;
  while((q!=NULL) && (strcmp(q->genere,gen)!=0))
  {
    r=q;
    q=q->next;
  }
  if(q==NULL)
  {
    printf("Genere non trovato\n");
    return;
  }
  else
  {
    struct opera* ausiliario1=q->op;
    struct opera* ausiliario2=q->op;
    while(ausiliario1!=NULL)	//scorro tutta la lista di q finchè non libero tutta la lista
    {
      ausiliario1=ausiliario2;
      ausiliario2=ausiliario2->succ;
      free(ausiliario1);
      ausiliario1=ausiliario2;
    }
    if(q==*head)
			*head=q->next;
    else
  		r->next=q->next;
    free(q);
    //cosi' facendo ho liberato la lista e il genere
  }
}

void visgen(struct museo** head) //si mandano a video tutti i generi presenti nel museo
{
	if (*head==NULL)
        printf("Non c'e' nessun genere di opera nel museo'\n");

    else
    {
        struct museo* aux=*head;
        printf("I generi presenti nel museo sono: \n");

        while (aux!=NULL) // si scorre tutta la lista stampando tutti i generi presenti
        {
            printf("%s",aux->genere);
            aux=aux->next;
        }
    }
}

void inserimentoopera(struct museo** head)
{
 	struct museo* q=*head;
	char gen[20];
  printf("Inserisci il genere al quale appartiene l'opera \n");
  gets(gen);
	strcat(gen,"\n");
  while((q!=NULL) && (strcmp(q->genere,gen)!=0))
    q=q->next;
  if(q==NULL)
  {

   	printf("Genere non trovato\n");
		q=inserimento1(head,gen); //nel caso in cui il genere non venga trovato, viene inserito il genere nuovo
  }
    struct opera* nuovo=(struct opera*)malloc(sizeof(struct opera));	// ho creato lo "scatolino" per la nuova opera da inserire
    printf("Inserisci il titolo dell'opera \n");
    gets(nuovo->titolo);
		strcat(nuovo->titolo,"\n");
    printf("Inserisci il nome dell'autore dell'opera\n");
    gets(nuovo->autore);
		strcat(nuovo->autore,"\n");
    printf("Inserisci l'anno in cui e' stata realizzata l'opera\n");
    scanf("%d",&nuovo->anno);
    nuovo->succ=NULL;
    struct opera* s=q->op;
    struct opera* t=q->op;
    while((s!=NULL) && (strcmp(s->titolo,nuovo->titolo)<0))	//si cerca la posizione esatta dove inserire la nuova opera
  	{
       t=s;
       s=s->succ;
	  }
     if(s==q->op)
      q->op=nuovo;
    else
      t->succ=nuovo;
    nuovo->succ=s;
}

void ricercagen(struct museo** head)	//Si scorre tutta la lista fino a quando non si trova l’elemento oppure non si arriva alla fine della lista
{
	struct museo* v=*head;
	char gen[20];
	printf("Inserisci il genere delle opere da visualizzare: ");
	gets(gen);
	strcat(gen,"\n");	//concateno "\n" alla stringa inserita per omologarla alla stringa letta da fgets(); che ha un "\n" prima del terminatore

while((v!=NULL) && (strcmp(v->genere,gen)!=0))
  {
    v=v->next;
  }
  if(v==NULL)
  {
    printf("Genere non trovato\n");
    return;
  }
	else
	{
    struct opera* aus1=v->op;	// metto aus1 sul primo elemento della lista
        if (aus1==NULL)	
            printf("Il genere non ha opere al suo interno\n ");
		while(aus1!=NULL)	//scorro tutta la lista stampando le varie informazioni relative alle opere
		{
			printf("Titolo: %sAutore: %sAnno: %d\n", aus1->titolo, aus1->autore, aus1->anno);
  			aus1=aus1->succ;
		}
	}
}

void cancellaopera(struct museo** head)	 //si scorre tutta la lista per cercare il genere al quale appartiene l'opera successivamente si cerca l'opera all'interno della lista del genere
{
  char gen[20];
	printf("L'opera che va eliminata a quale genere appartiene?\n");
	gets(gen);
	strcat(gen,"\n");
  char canc[20];
  struct museo* q=*head;
  while((q!=NULL) && (strcmp(q->genere,gen)!=0))	//scorro tutta la lista principale
  {
    q=q->next;
  }
  if(q==NULL)
  {
    printf("Genere non trovato\n");
    return;
  }
  else
  {
    printf("Inserisci il titolo dell'opera che va eliminata\n");
		gets(canc);
		strcat(canc,"\n");
    struct opera* ausiliario1=q->op;	
  	struct opera* ausiliario2=q->op;
    while((ausiliario2!=NULL) && (strcmp(ausiliario2->titolo,canc)!=0))	//scorro tutta la lista delle opere presenti del genere al quale appartiene l'opera da cancellare
      {
        ausiliario1=ausiliario2;
        ausiliario2=ausiliario2->succ;
      }
    	if(ausiliario2==NULL)
        printf("L'opera non e' presente nella lista\n");
      else
  		{
				if(ausiliario2==q->op)	//nel caso in cui l'opera sia la prima in lista
					q->op=ausiliario2->succ;
				else
        	ausiliario1->succ=ausiliario2->succ; 
    	 	free(ausiliario2);	//libero ausiliario2
		}
  }
}

void modificaopera(struct museo** head)
{
  char gen[20];
	printf("L'opera che va modificata a quale genere appartiene?\n");
	gets(gen);
	strcat(gen,"\n");
  char mod[20];
  struct museo* q=*head;
  while((q!=NULL) && (strcmp(q->genere,gen)!=0))
    q=q->next;
  if(q==NULL)
  {
    printf("Genere non trovato\n");
    return;
  }
  else
  {
    printf("Inserisci il titolo dell'opera che va modificata \n");
		gets(mod);
		strcat(mod,"\n");
    struct opera* aus=q->op;	//metto aus sul primo elemento della lista
    while((aus!=NULL) && (strcmp(aus->titolo,mod)!=0))
    {
      aus=aus->succ;	//cosi portiamo avanti la lista delle opere di un genere
    }
    if(aus==NULL)
			printf("L'opera non e' presente nella lista\n");
    else
  	{	//inseriamo i nuovi dati relativi all'opera
  		printf("Inserisci l'artista dell'opera: ");
  		gets(aus->autore);
			strcat(aus->autore,"\n");
  		printf("Inserisci l'anno di realizzazione dell'opera: ");
  		scanf("%d", &(aus->anno));
		}
  }
}

void ricercaopera(struct museo** head)	//viene effettuato uno switch per scegliere secondo quale criterio deve essere effettutata la ricerca, poi si scorre tutta la lista fino a quando non si trova l’elemento oppure non si arriva alla fine della lista
{
  int c;
  int x;
  int a=1;
  c=1;
  printf("Secondo quale parametro va effettuata la ricerca? \n");
  printf("1 - Ricerca secondo il nome dell'opera \n");
  printf("2 - Ricerca delle opere di un artista \n");
  printf("Inserisci il numero corrispondente all'operazione da effettuare: ");
	scanf("%d",&x);
  while(a!=1)
  {
    if(x>2 || x<1)
    {
    printf("Numero non corrispondente a nessuna operazione. \n Inserisci un nuovo numero: ");
    scanf("%d",&x);
    }
    else
    	a=0;
  }
  struct museo* q=*head;
  char ric[20];
  int w=0;
  char ch;
 while((ch=getchar()) != '\n' && ch !=EOF);
   switch(x)
	{
    case 1:
    {
      printf("Inserisci il titolo dell'opera da cercare: ");
      gets(ric);
			strcat(ric,"\n");
      struct opera* aus=q->op;	// metto aus sul primo elemento della lista
			while(q!=NULL && w==0)
      {
				aus=q->op;
				while(aus!=NULL)
        {
        	if(strcmp(aus->titolo,ric)==0)
					{
  					printf("L'artista dell'opera e' %s", aus->autore);
  					printf("L'anno di realizzazione dell'opera e' %d\n", aus->anno);
                    printf("Il genere a cui appartiene l'opera e': %s", q->genere);
  					w=1;
					}
          aus=aus->succ;
        }
        q=q->next;
      }
      if (w==0)
      	printf("L'opera non e' presente nel museo\n");
		}
    break;

		case 2:
		{
      printf("Inserisci l'artista di cui cercare le opere: \n");
      gets(ric);
			strcat(ric,"\n");
      struct opera* aus=q->op;
			while(q!=NULL)
        {
				aus=q->op;
				while(aus!=NULL)
				{
        	if(strcmp(aus->autore,ric)==0)
					{
  					printf("Un'opera di quest'artista e' %s", aus->titolo);
  					printf("L'anno di realizzazione dell'opera e' %d\n", aus->anno);
                    printf("Il genere dell'opera e': %s", q->genere);
  					w=1;
					}
					aus=aus->succ;
				}
      	q=q->next;
        }
      if (w==0)
      	printf("Non e' presente nessun'opera di quest'artista nel museo\n");
    }
    break;
	}
}

void inv_restauro(struct museo** head, struct queue** rest)	//cerco l'opera da mandare in restauro la inserisco nella coda del restauro e successivamente la elimino dalla lista principale
{
  char gen[20];
  printf("L'opera che va mandata in restauro a quale genere appartiene?\n");
	gets(gen);
	strcat(gen,"\n");
  char mod[20];
  struct museo* q=*head;
  struct museo* r=*head;
  while((q!=NULL) && (strcmp(q->genere,gen)!=0))
  {
    q=q->next;
  }
  if(q==NULL)
  {
    printf("Genere non trovato\n");
    return;
  }
  else
  {
    printf("Inserisci il titolo dell'opera che va restaurata\n");
		gets(mod);
		strcat(mod,"\n");
    struct opera* aus=q->op;
    struct opera* aus2=q->op;
    while((aus!=NULL) && (strcmp(aus->titolo,mod)!=0))
    {
      aus2=aus;
      aus=aus->succ;
    }
    if(aus==NULL)
      return;
    else
    {
      if(*rest==NULL)
      {
        (*rest)=(struct queue*)malloc(sizeof(struct queue));
        (*rest)->h=NULL;
        (*rest)->t=NULL;
      }
      struct restauro* aux=(struct restauro*)malloc(sizeof(struct restauro));
      strcpy(aux->titolo,aus->titolo);
      strcpy(aux->autore,aus->autore);
      aux->anno=aus->anno;
      strcpy(aux->genereopera,q->genere);	//mi salvo il genere dell'opera per poterla poi reinserire al posto corretto
      printf("Quanti giorni deve rimanere in restauro l'opera?\n");
      scanf("%d",&(aux->giorni));
      aux->pross=NULL;
			inserimentocoda(&aux,rest);
      if (q->op==aus2)
        	q->op=aus2->succ;
      else
      	aus2->succ=aus->succ;
      free(aus);
    }
  }
}

void inv_prestito(struct museo** head, struct prestito** prest)	//cerco l'opera da mandare in prestito la inserisco nella lista del prestito e successivamente la elimino dalla lista principale
{

  char gen[20];
	printf("L'opera che deve essere mandata in prestito a quale genere appartiene?\n");
	gets(gen);
	strcat(gen,"\n");
  char mod[20];
  struct museo* q=*head;
  while((q!=NULL) && (strcmp(q->genere,gen)!=0))
    q=q->next;
  if(q==NULL)
  {
    printf("Genere non trovato\n");
    return;
  }
  else
  {
    struct prestito* ausiliario=(struct prestito*)malloc(sizeof(struct prestito));
    printf("Inserisci il titolo dell'opera che deve essere mandata in prestito \n");
		gets(mod);
		strcat(mod,"\n");
    struct opera* aus1=q->op;
    struct opera* aus2=q->op;
    while((aus1!=NULL) && (strcmp(aus1->titolo,mod)!=0))
    {
      aus2=aus1;
      aus1=aus1->succ;
    }
    if(aus1==NULL)
			printf("L'opera non e' presente nel museo\n");
    else
  	{

      strcpy(ausiliario->titolo,aus1->titolo);
      strcpy(ausiliario->autore,aus1->autore);
      ausiliario->anno=aus1->anno;
      strcpy(ausiliario->gen,q->genere);	//mi salvo il genere dell'opera per poterla poi reinserire al posto corretto
      printf("In quale museo viene mandata in prestito l'opera?\n");
      gets(ausiliario->destinatario);
			strcat(ausiliario->destinatario,"\n");
      printf("Quanti giorni restera' in prestito l'opera?\n");
      scanf("%d",&(ausiliario->tempo));
      ausiliario->seguente=NULL;
      if(*prest!=NULL)
				ausiliario->seguente=*prest;
			*prest=ausiliario;


		if(aus1==q->op)
			q->op=aus1->succ;
		else
			aus2->succ=aus1->succ;
    free(aus1);
    }
  }
}

void vis_res_pres(struct queue** rest,struct prestito** prest)	//visualizzo tutte le opere presenti in prestito e in restauro scorrendo e mandando a video le opere presenti nella reispettiva lista o coda 
{

    if ((*rest==NULL)||((*rest)->h==NULL))
        printf("Non ci sono opere in restauro\n");
		else
    {
        struct restauro* aus1=(*rest)->h;
        printf("Le opere in restauro sono: \n");

        while (aus1!=NULL)	//scorro tutta la coda e mando a video tutte le opere in restauro
        {
            printf("Titolo: %sL'autore e': %sL'opera e' stata realizzata nel %d\n",aus1->titolo, aus1->autore,aus1->anno);
            printf("L'opera restera' in restauro per %d giorni \n\n", aus1->giorni);
						aus1=aus1->pross;
        }
    }

    if (*prest==NULL)
        printf("Non ci sono opere in prestito\n");

    else
    {
        struct prestito* aux=*prest;
        printf("Le opere in prestito sono: \n");

        while (aux!=NULL)	//scorro tutta la lista e mando a video tutte le opere in prestito con i relativi musei di destinazione
        {
            printf("Titolo: %sL'autore e': %sL'opera e' stata realizzata nel %d\n",aux->titolo, aux->autore,aux->anno);
            printf("L'opera e' stata mandata nel museo di %s", aux->destinatario);
            printf("L'opera restera' in prestito per %d giorni \n\n", aux->tempo);
            aux=aux->seguente;
        }
    }
}

void avanzagiorno(struct museo** head, struct queue** rest,struct prestito** prest)	//quando sono presenti opere in prestito o in restauro con questa funzione viene diminuito di uno il numero di giorni di rimanenza di tutte leopere in prestito, e viene diminuito di uno il giorno di rimanenza della sola opera nella testa della coda
{
	struct restauro* t;
	struct prestito* s;
	struct prestito* s1;
	struct prestito *aux;
	struct prestito *aux1;
	struct opera* r;
	struct opera* u;
	struct museo* q;
	//Restauro
	if ((*rest==NULL)||((*rest)->h==NULL))
		printf("Non ci sono opere in restauro\n");
	else	//viene diminuito il numero di giorni rimanenti in restauro solo al primo elemento della coda
	{
		t=(*rest)->h;
		t->giorni=(t->giorni)-1;
		if((t->giorni)==0)	//quando l'opera deve tornare dal restauro attraverso il genere presalvato precedentemente essa viene rimessa al posto giusto
		{
			struct opera* nuovo=(struct opera*)malloc(sizeof(struct opera));
			strcpy(nuovo->titolo,t->titolo);
			strcpy(nuovo->autore,t->autore);
			nuovo->anno=t->anno;
			nuovo->succ=NULL;
			q=ricercabase(head,t->genereopera);
			if(q==NULL)
				q=inserimento1(head,t->genereopera);
			r=q->op;
			u=q->op;
			ricerca2(&r,&u,nuovo);
			inserimento2(&r,&u,&q,&nuovo);
			(*rest)->h=t->pross;
			if((*rest)->h==NULL)
				(*rest)->t=NULL;
		}
	}

//Prestito
	if(*prest==NULL)
		printf("Non ci sono opere in prestito\n");
	else
	{
		s=*prest;
		while(s!=NULL)	//viene scorsa tutta la lista e diminuito di uno il numero di giorni di rimanenza in prestito
		{
			s->tempo=(s->tempo)-1;
			s=s->seguente;
		}
		s=*prest;
		s1=*prest;
		while(s!=NULL)
		{
			aux=s;
			aux1=s1;
			s1=s;
			s=s->seguente;
		if((aux->tempo)==0)		//quando l'opera deve tornare dal prestito attraverso il genere presalvato precedentemente essa viene rimessa al posto giusto
		{

			struct opera* new=(struct opera*)malloc(sizeof(struct opera));
			strcpy(new->titolo,aux->titolo);
			strcpy(new->autore,aux->autore);
			new->anno=aux->anno;
			new->succ=NULL;

			q=ricercabase(head,aux->gen);
			if(q==NULL)
			q=inserimento1(head,aux->gen);
			r=q->op;
			u=q->op;
			ricerca2(&r,&u,new);
			inserimento2(&r,&u,&q,&new);
			if(aux==*prest)
				{
				*prest=aux->seguente;
				}
	   		else
			{
	  			aux1->seguente=aux->seguente;
			}
		   	free(aux);
		}
	}
    }
}

void salvamuseo(struct museo*head)	// con questa funzione si effettua l'operazione di salvataggio relativa alla struct museo
{
		int i=0;
    FILE* fp=fopen("museo.txt","w");	// creo il file tramite il puntatore "fp" e apro il file	"museo.txt" in modalita scrittura 
    struct museo* v=head;

    while(v!=NULL)
    {
			if(i!=0)
				fprintf(fp,"\n");
      fprintf(fp,"%s",v->genere);
      struct opera* aus1=v->op;
			i++;
			while(aus1!=NULL)
		{
			fprintf(fp,"%s%s%d\n", aus1->titolo, aus1->autore, aus1->anno);
  		aus1=aus1->succ;
		}
    fprintf(fp,"-"); //separatore tra generi diversi
    v=v->next;
    }
}


void salvarestauro(struct queue* rest)	// con questa funzione si effettua l'operazione di salvataggio relativa alle opere in restauro
{
    FILE* fp=fopen("restauro.txt","w");	// creo il file chiamandolo "fp" e apro il file	"restauro.txt" in modalita scrittura 
    if (rest==NULL|| rest->h==NULL)
        printf("Non ci sono opere in restauro\n");
    else
    {
        struct restauro* aus1=rest->h;

        while (aus1!=NULL)
        {
            fprintf(fp,"%s%s%d\n",aus1->titolo, aus1->autore,aus1->anno);
            fprintf(fp,"%d\n", aus1->giorni);
            fprintf(fp,"%s",aus1->genereopera);
            aus1=aus1->pross;
        }
    }
}


void salvaprestito(struct prestito* prest)	// con questa funzione si effettua l'operazione di salvataggio relativa alle opere in prestito
{
	struct prestito* aux;
   FILE* fp=fopen("prestito.txt","w");	// creo il file chiamandolo "fp" e apro il file	"prestito.txt" in modalita scrittura 
    if (prest==NULL)
        printf("Non ci sono opere in prestito\n");
    else
    {
        while (prest!=NULL)
        {
            fprintf(fp,"%s%s%d\n",prest->titolo, prest->autore,prest->anno);
            fprintf(fp,"%d\n", prest->tempo);
            fprintf(fp,"%s", prest->gen);
            fprintf(fp,"%s", prest->destinatario);
            prest=prest->seguente;
        }
    }
}

void caricamuseo(struct museo** head)	//creo la funzione carica per caricare al momento dell'avvio del programma tutti gli elementi della lista "struct museo"
{
	struct opera* aux=NULL;
	struct opera* aux2=NULL;
	struct museo* q=NULL;
	char prova[20];
	int key=0;
	int cont=0;
	char ch[20];
	FILE* fp=fopen("museo.txt","r");	// creo il file chiamandolo "fp" e apro il file	"museo.txt" in modalita lettura 
	if(fp==NULL)	// faccio un if in cui se il file "fp" risulterà uguale a NULL significherà che non è stato trovato e apparirà a video il messaggio che il file è inesistente
	{
		printf("File inesistente\n");
		return;
	}
	fgets(prova,20,fp);//con fgets leggo il primo carattere perchè se non lo avessimo, il file non viene riconosciuto come file vuoto. quindi faccio fgets per vedere se il file esiste o meno
	while(!feof(fp))	// se invece il file risulta esserci, allora si entra nel while
	{
		if(cont!=0)	// se non è la prima iterazione, faccio di nuovo fgets e verifico che il file sia vuoto. questo perchè c'è il /n nella fscanf quindi leggere l'invio e successivamente termina e per vedere se dopo l'invio c'è qualcosa o meno.
			fgets(prova,20,fp);
		if(feof(fp))
			break;
		struct museo* nuovo=(struct museo*)malloc(sizeof(struct museo));	//si crea uno "scatolino" denominato "nuovo" in cui si alloca memoria
		strcpy(nuovo->genere,prova);
	  nuovo->op=NULL;

		nuovo->next=NULL;
		key=0;
		cont++;
		q=inserimento1(head,nuovo->genere);

		while(key!=1)
    {
			fgets(ch,20,fp);

      if(strncmp(ch,"-",1)==0)
       key=1;
      else
      {

				struct opera* new=(struct opera*)malloc(sizeof(struct opera));
        strcpy(new->titolo,ch);

        fgets(new->autore,20,fp);	//si utilizza la funzione fgets per leggere le stringhe in un file

        fscanf(fp,"%d\n",&(new->anno));

        new->succ=NULL;
        aux=q->op;
				aux2=aux;


        while((aux!=NULL) && (strcmp(aux->titolo,new->titolo)<0))
        {
					aux2=aux;
          aux=aux->succ;
        }
				inserimento2(&aux2,&aux,&q,&new);

			}
		}
	}
	fclose(fp);//chiusura del file
}


void caricarestauro(struct queue** rest)		//creo la funzione carica per caricare al momento dell'avvio del programma tutti gli elementi della lista "struct restauro"
{
	char ch[20];
	int cont=0;
	char prova[20];
	//struct restauro;
	FILE* fp=fopen("restauro.txt","r");		// creo il file chiamandolo "fp" e apro il file	"restauro.txt" in modalita lettura 
	if (fp==NULL)	// faccio un if in cui se il file "fp" risulterà uguale a NULL significherà che non è stato trovato e apparirà a video il messaggio che il file è inesistente
	{
		printf("File Inesistente\n");
		return;
	}
	*rest=(struct queue*)malloc(sizeof(struct queue));
	(*rest)->h=(*rest)->t=NULL;
	fgets(prova,20,fp);	//con fgets leggo il primo carattere perchè se non lo avessimo, il file non viene riconosciuto come file vuoto. quindi faccio fgets per vedere se il file esiste o meno
	while(!feof(fp))	// se invece il file risulta esserci, allora si entra nel while
	{
		if(cont!=0)		// se non è la prima iterazione, faccio di nuovo fgets e verifico che il file sia vuoto. questo perchè c'è il /n nella fscanf quindi leggere l'invio e successivamente termina e per vedere se dopo l'invio c'è qualcosa o meno.

		{
			fgets(prova,20,fp);//si utilizza la funzione fgets per leggere le stringhe in un file
			if(feof(fp))
				return;
		}
			struct restauro* nuovo=(struct restauro*)malloc(sizeof(struct restauro));
			strcpy(nuovo->titolo,prova);
			fgets(nuovo->autore,20,fp);
			fscanf(fp,"%d\n",&nuovo->anno);
			fscanf(fp,"%d\n",&nuovo->giorni);
			fgets(nuovo->genereopera,20,fp);	//si utilizza la funzione fgets per leggere le stringhe in un file
			nuovo->pross=NULL;
			inserimentocoda(&nuovo,rest);
			cont++;


	}
  fclose(fp);//chiusura del file
}

void caricaprestito(struct prestito ** prest)		//creo la funzione carica per caricare al momento dell'avvio del programma tutti gli elementi della lista "struct prestito"
{
	int cont=0;
	char prova[20];
	FILE* fp=fopen("prestito.txt","r");		// creo il file chiamandolo "fp" e apro il file	"prestito.txt" in modalita lettura 
	if (fp==NULL)	// faccio un if in cui se il file "fp" risulterà uguale a NULL significherà che non è stato trovato e apparirà a video il messaggio che il file è inesistente
	{
		printf("File Inesistente\n");
		return;
	}
	fgets(prova,20,fp);	//con fgets leggo il primo carattere perchè se non lo avessimo, il file non viene riconosciuto come file vuoto. quindi faccio fgets per vedere se il file esiste o meno
	while(!feof(fp))	// se invece il file risulta esserci, allora si entra nel while
	{
		if(cont!=0)		// se non è la prima iterazione, faccio di nuovo fgets e verifico che il file sia vuoto. questo perchè c'è il /n nella fscanf quindi leggere l'invio e successivamente termina e per vedere se dopo l'invio c'è qualcosa o meno.

		{
			fgets(prova,20,fp);	//si utilizza la funzione fgets per leggere le stringhe in un file
			if(feof(fp))
				return;
		}
		struct prestito* nuovo=(struct prestito*)malloc(sizeof(struct prestito));
		strcpy(nuovo->titolo,prova);
		fgets(nuovo->autore,20,fp);
		fscanf(fp,"%d\n",&(nuovo->anno));
		fscanf(fp,"%d\n", &(nuovo->tempo));
		fgets(nuovo->gen,20,fp);	//si utilizza la funzione fgets per leggere le stringhe in un file
		fgets(nuovo->destinatario,20,fp);	
	 	nuovo->seguente=NULL;
		inserimentotesta(prest,&nuovo);
		cont++;
	}
	fclose(fp);	//chiusura del file
}
