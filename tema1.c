#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
typedef struct node //structura
{
struct node *prev;
struct node *next;
double timestamp;
double value;
}node, *DList; //ok
void listinsert(DList s,double x,double y)
{
    node *aux;
    aux=(node*)calloc(1,sizeof(node));
    aux->timestamp=x; //iau un nod auxiliar in care pun valorile date ca argument
    aux->value=y;
    aux->next=NULL; //il leg la null ca doar o sa fie ultimul nod in lista
    node *q; //iau un alt nod auxiliar cu care parcurg lista de la inceput la final
    q=s;
    if (s==NULL)
    {
    //dar mai intai verific daca lista e nula;
    //daca e, atunci nodul format anterior devine cap de lista
        aux->prev=NULL;
        s=aux;
        return;
    }
    while(q->next!=NULL)
    {
        q=q->next;
    }
    q->next=aux; //se adauga nodul la final
    aux->prev=q;
}

void listdel(DList s,double time)
{
    //aici este o functie care doreste sa elimine un nod din lista, cu o anumita valoare
    DList todel;
    while(s->next!=NULL)
    {
    //se parcurge lista pana la final
        if(s->next->timestamp==time)
        {
        //daca s-a gasit un nod cu valoarea cautata
            todel=s->next; //acesta se sterge cu ajutorul unei variabile ajutatoare
            s->next=todel->next;
            todel->next->prev=s;
            todel->next=NULL;
            todel->prev=NULL;
            free(todel);
        }
        s=s->next; //se trece mai departe in cautarea unui nod care ar putea avea valoarea cautata
    }
}//ok

void listfree(DList s) {
    node *q;
    //deci, creez un nod auxiliar q ca sa mai atenuez stergerea nodurilor pe rand din lista
    
   
  while(s!=NULL)
  {
      q=s->next; //sterg fiecare rand de la inceput, capul listei devenind urmatorul
      free(s); //eliberez memoria ocupata de nodul sters
      s=q;
  }
  free(s);  //cum la final se ajunge la un nod null, se sterge si acela
}
int nrnoduri(DList s)
{
    int nr;
    nr=0;
    while(s!=NULL) 
    {
    //de data aceasta parcurg lista fara nod auxiliar ca imi era sa nu alloc iar memorie ca sa nu mai eliberez iar
        s=s->next;
        nr++; //numar fiecare nod parcurs
    }
    nr--; //dar sterg unul pentru ca am numarat si capul de lista cu valoare random
    return nr;
}
void listprint(DList s)
{
 s=s->next; //afisez lista pe m,asura ce o parcurg
    while(s!=NULL)
    {
    printf("%.0lf",s->timestamp); //valorile se afiseaza pe ecran (stdout)
    printf(" %.2lf\n",s->value); 
        s=s->next; //se trece la nodul urmator
    }
}//ok
//deci, parcurg lista pana la final, apoi in timp  ce fac asta insemnez timestampul ca sa il elimin si elimin la final ce are timestamp-ul negativ (jos, la one)
void one(DList s)
{ //functia pentru rezolvarea primului task
node *q;
double xm;
double sigma;
q=s->next; //cu ajutorul acestui nod iau subliste de cate cinci elemente; asa  reusesc sa nu ma ating de primele si ultimele doua elemente
while (q->next->next->next->next!=NULL)
{
    xm=q->value+q->next->value+q->next->next->value+q->next->next->next->value+q->next->next->next->next->value; 
    xm=xm/5; //calculez xmediu conform formula 
    //xmediu ramane neschimbat indiferent de sublista de cinci elemente
    sigma=(q->value-xm)*(q->value-xm)+(q->next->value-xm)*(q->next->value-xm)
    +(q->next->next->value-xm)*(q->next->next->value-xm)+(q->next->next->next->value-xm)*(q->next->next->next->value-xm)
    +(q->next->next->next->next->value-xm)*(q->next->next->next->next->value-xm);
    sigma=sigma/5; //tot conform formulei calculez si sigma, scazand din fiecare element pe xmediu si apoi fac media si scot radicalul
    sigma=sqrt(sigma);
    if(q->next->next->value<xm-sigma||q->next->next->value>xm+sigma)
        q->next->next->timestamp=-1; //unde se intampla ca conditia din cerinta sa nu fie indeplinita, marchez cumva nodul de sters
        //cum timestampul e mereu pozitiv, m-am gandit sa-l fac -1 (ceva valoare negativa)
        q=q->next;
}
q=s->next;
while (q->next->next->next->next!=NULL)
{
        listdel(s,-1); //iau fiecare sublista si sterg nodurile insemnmate
        q=q->next;
}
}

void twoone(DList s)
{
node *q;
DList newnewlist;
int ok;
node *i;
double aux;
q=s->next;
s->next=NULL;
s->prev=NULL; //incerc sa sterg lista initiala, ca sa pun noile valori in ea, 
//noile valori fiind cele mediane, conform cerintei
//listfree(s->next);
s->next=(DList)calloc(1,sizeof(node));
while (q->next->next->next->next!=NULL) 
{  //tot asa iau subliste de cinci elemente, de data aceasta chiar creand o sublista
    newnewlist=(DList)calloc(1,sizeof(node));
    newnewlist->next=NULL;
    newnewlist->prev=NULL;
    listinsert(newnewlist,q->timestamp,q->value);
    listinsert(newnewlist,q->next->timestamp,q->next->value);
    listinsert(newnewlist,q->next->next->timestamp,q->next->next->value);
    listinsert(newnewlist,q->next->next->next->timestamp,q->next->next->next->value);
    listinsert(newnewlist,q->next->next->next->next->timestamp,q->next->next->next->next->value);
do //sublista nou creata o ordonez; am incercat mai multe optiuni de ordonare, dar cea care a functionat intr-un final a fost metoda bulelor
{
  ok = 1; //presupunem sublista ca fiind deja ordonata
  for(i = newnewlist->next ; i->next!=NULL ; i=i->next)
    if(i->value > i->next->value)
    {
      aux = i->value; //daca se gasesc elemente dupa valoare care nu sunt in ordine, se schimba intre ele si se marcheaza acest lucru
      i->value= i->next->value;
      i->next->value = aux;
      ok = 0;
    }
}
while(!ok); // se tot fac interschimbari de acest tip cat timp este marcat faptul ca lista este neordonata
listinsert(s,newnewlist->next->next->next->timestamp,newnewlist->next->next->next->value); 
//valoarea mediana rezultata in urma ordonarii se pune in lista mare
q=q->next;
i=newnewlist;
listfree(i);
}
while(q->prev->prev!=NULL)
{
    q=q->prev;
}
listfree(q);
listdel(s,s->timestamp); //aici dezaloc tot ce am alocat
}

void twotwo(DList s)
{
node *q;
//aceasta functie merge pe principiul lui twoone, 
//numai ca nu mai face ordonarea elementelor, cu face media lor aritmetica 
//si o introduce in lista mare
DList newnewlist;
double sum;
node *i;
double toadd1,toadd2;
q=s->next;
s->next=NULL;
s->prev=NULL;
//incerc sa sterg lista initiala, ca sa pun noile valori in ea, 
//noile valori fiind cele mediane, conform cerintei
//listfree(s->next);
s->next=(DList)calloc(1,sizeof(node));
while (q->next->next->next->next!=NULL)
{
//tot asa iau subliste de cinci elemente, de data aceasta chiar creand o sublista
    newnewlist=(DList)calloc(1,sizeof(node));
    newnewlist->next=NULL;
    newnewlist->prev=NULL;
    listinsert(newnewlist,q->timestamp,q->value);
    listinsert(newnewlist,q->next->timestamp,q->next->value);
    listinsert(newnewlist,q->next->next->timestamp,q->next->next->value);
    listinsert(newnewlist,q->next->next->next->timestamp,q->next->next->next->value);
    listinsert(newnewlist,q->next->next->next->next->timestamp,q->next->next->next->next->value);
    sum=0;
for (i=newnewlist->next;i!=NULL;i=i->next)
    sum=sum+i->value;
    sum=sum/5;
    toadd1=newnewlist->next->next->next->timestamp;
    toadd2=sum;
listinsert(s,toadd1,toadd2);
//valoarea rezultata in urma ordonarii se pune in lista mare
//timestampul ramane acelasi, dar l-am pus intr-o variabila toadd1 
//ca sa-mi fie oarecum mai usor la functia de adaugare in lista 
q=q->next;
i=newnewlist;
listfree(i);
}
while(q->prev->prev!=NULL)
{
    q=q->prev;
}
listfree(q);
listdel(s,s->timestamp); //eliberez tot ce am alocat; incercat cu valgrind si merge
}

void three(DList s)
{
//aici parcurg lista fara nod auxiliar si fac media intre valorile din nodurile vecine, asa cum cere cerinta, cand apare o diferenta la timestampuri de inre 100 si 1000
    s=s->next;
while (s->next!=NULL)
{
    s=s->next;
if((s->timestamp-s->prev->timestamp)>=100&&(s->timestamp-s->prev->timestamp)<=1000)
{
s->timestamp=(int)((s->timestamp+s->prev->timestamp)/2); //am facut cast la int ca cu double nu iesea cum era in checker
s->value=(double)((s->value+s->prev->value)/2);
}
}
} 

double findmax(DList s)
{
double maxi; //functia aceasta cauta valoarea maxima intr-o lista, asemanator cum se facea la vectori
//presupun ca primul nod are valoarea value maxima
maxi=s->next->value;
node *q;
q=s->next->next;
while(q!=NULL) //parcurg lista cu un nod ajutator; de la inceput pana cand nu s-a ajuns la finalul listei
{
    if (q->value>maxi) //daca s-a intamplat ca maximul sa fie mai mic decat o valoare
    maxi=q->value; //acea valoare devine maxim
    q=q->next; //se trece mai departe
}
return maxi; //se returneaza valoarea maxima din lista
}

double findmin(DList s)
{
//asemanator ca functia de mai sus de aflare maxim, doar ca e cu minim
//functia aceasta cauta valoarea minima intr-o lista, asemanator cum se facea la vectori
double mini;
mini=s->next->value; //presupun ca primul nod are valoarea value minima
node *q;
q=s->next->next;
while(q!=NULL) //parcurg lista cu un nod ajutator; de la inceput pana cand nu s-a ajuns la finalul listei
{
    if (q->value<mini) //daca s-a intamplat ca minimul presupus sa fie mai mare decat o valoare
    mini=q->value;  //acea valoare devine minimul
    q=q->next; //trec mai departe in lista, indiferent ce se intampla cu minimul acela
}
return mini;
}

int numara(DList s,double start, double stop)
{
    int nr;
    nr=0;
    s=s->next; //parcurg lista de la primul nod efectiv si pana la final
    while(s!=NULL)
    {
        if (s->value>=start&&s->value<=stop) //daca am gasit o valore in lista intre cele doua valori date ca parametru (in cazul de fata vor fi maxim si minim)
        {
            nr++; //numara aparitia
        }
        s=s->next; //trece mai departe in lista
    }
    return nr; 
}

void cinci(DList s,double delta,double start,double stop)
{
    double delta1,delta2;
    int nr;
    if (start<0&&(int)start%(int)delta)
    start=floor(start);
    int strt;
    strt=(int)start;
    start=(double)strt;
    delta1=start; 
    delta2=start+delta;
    stop=floor(stop);
    //delta1 si delta2 au la inceput valorile de valoarea minima si delta
    //cele doua delta1 si delta2 cresc pe parcurs cu delta, pana se ajunge la valoarea maxima
    while(delta1<=stop)
    {
        nr=numara(s,delta1,delta2); //de fiecare data se numara cate valori din lista sunt intre delta1 si delta2
        if (nr!=0) //si daca e macar unul, se afiseaza intervalul si numarul de elemente
        printf("[%.0lf, %.0lf] %d\n", delta1, delta2, nr);
        delta1=delta1+delta;
        delta2=delta2+delta;
    }
}

void five(DList s,double delta){
    double stop,start;
stop=findmax(s);
start=findmin(s);
cinci(s,delta,start,stop);
//toate functiile in legatura cu delta,numarare valori din lista, max,min puse laolalta
}

int main(int argc,char **argv)
{
    int j,k;
    DList s;
    char num[4];
    double delta;
    char *p;
    k=0; 
    delta=0;
    int n;
int i;
int nr;
double x,y;
int ok;
ok=0;
s=(DList)calloc(1,sizeof(node)); //aloc lista, mai bine zis capul de lista
    s->next=NULL;
    s->prev=NULL; //si il leg la null
    scanf("%d",&n); //citesc numarul de noduri si elementele de la tastatura
    for (i=0;i<n;i++){
        scanf("%lf",&x);
        scanf("%lf",&y); 
        listinsert(s,x,y); //si inserez
    }

    for(i=1;i<argc;i++)
    {
    if(strcmp(argv[i],"--e1")==0)
    {
        one(s); //ficare functie one, twoone,twotwo,three,five (de four nu am reusit) corespund unui argument
        ok=1; //ok=1 nu e statistica, deci se afiseaza lista mare
    }
    if(strcmp(argv[i],"--e2")==0)
    {
        twoone(s);
        ok=1;
    }
    if(strcmp(argv[i],"--e3")==0)
    {
        twotwo(s);
        ok=1;
    }
    if(strcmp(argv[i],"--u")==0)
    {
        three(s);
        ok=1;
    }
    if(strchr(argv[i],'s')!=0)
    {
    ok=2;
    for (j=4;j<strlen(argv[i]);j++)
    num[k++]=argv[i][j];
    num[k]='\0';
    delta=strtod(num,&p);
    five(s,delta);
    }
    //nu e ok=1, deci nu se afiseza lista, ci doar statistica
    }
    if(ok==1)
    {
        nr=nrnoduri(s);
        printf("%d\n",nr);
        listprint(s);
    }
    listfree(s); //se elibereaza lista
    return 0;
}
