#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>
#define null 0

int size = 0;
void insert ();
void display ();
int search(char lab[]);
struct symbtab 
{
char label[15];
char info[15];
struct symbtab *next;
};
struct symbtab *first, *last;
void main () 
{
int op;
int y;
char la[15];
do
{
printf ("\n0 Input a value\n");
printf ("1 Display table\n");
printf ("\nEnter option: ");
scanf ("%d", &op);
switch (op){
case 0:
insert ();
break;
case 1:
display ();
break;
}
}
while (op < 2);
getch ();
}

void insert () {
int n;
char l[15];
printf ("Enter the Identifier: \n");
scanf ("%s", l);
n = search (l);
if (n == 1)
printf("Given label already exists\n");
else{
struct symbtab *p;
p = malloc (sizeof (struct symbtab));
strcpy (p->label, l);
printf ("Enter the info:\n ");
scanf ("%s", p->info);
p->next = null;
if (size == 0){
first = p;
last = p;
}
else{
last->next = p;
last = p;
}
size++;
}
}
void display (){
int i;
struct symbtab *p;
p = first;
printf ("\nId\t\t\tInfo\n");
for (i = 0; i < size; i++){
printf ("%s\t\t\t%s\n", p->label, p->info);
p = p->next;
}
}
int search (char lab[]){
int i, flag = 0;
struct symbtab *p;
p = first;
for (i = 0; i < size; i++){
if (strcmp (p->label, lab) == 0)
flag = 1;
p = p->next;
}
return flag;
}

