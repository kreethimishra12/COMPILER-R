#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 20
void display();
struct DataItem {
   char data[20];   
   int key;
   char type[15];
};
struct DataItem* hashArray[SIZE]; 
struct DataItem* obj1;
struct DataItem* obj2;
int search(int);
int hashCode(int key) {
   return key % SIZE;
}

void insert(int key,char *data,char *type) {

   struct DataItem *obj2 = (struct DataItem*) malloc(sizeof(struct DataItem));
   strcpy(obj2->data,data);  
   obj2->key = key;
   strcpy(obj2->type,type);
   int hashIndex = hashCode(key);
    while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
     ++hashIndex;
	 hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = obj2;
}

char keyword[30][30]={"int","while","break","for","do","if","float","char","switch",
"double","short","long","unsigned","sizeof","else","register","extern","static","auto"
,"case","break","volatile","enum","typedef","strcmp","return"};
char id[20], num[10],rel[5];

int check_keyword(char s[])
{
int i;
for(i=0;i<26;i++)
if(strcmp(s,keyword[i])==0)
return 1;
return 0;
}
int convertkey(char *);
int main()
{int k=0;
obj1 = (struct DataItem*) malloc(sizeof(struct DataItem));
obj1->key = -1; 
FILE *fp1,*fp2;
char c;
int state=0;
int i=0,j=0,t=0;
fp1=fopen("x.txt","r");//input file containing src prog
fp2=fopen("y.txt","w");//output file name

while((c=fgetc(fp1))!=EOF)
{
switch(state)
{
case 0: if(isalpha(c)){
state=1; id[i++]=c;}
else if(isdigit(c)){
state=3; num[j++]=c;}
else if(c=='<' || c=='>'){
rel[t]=c;
state=5;
t++;
}
else if(c=='=' || c=='!')
{
rel[t]=c;
state=8;
t++;
}
else if(c=='/')
state=10;
else if(c==' ' || c=='\t' || c=='\n')
state=0;
else
fprintf(fp2,"\n%c",c);
break;
case 1:if(isalnum(c)){
state=1; id[i++]=c;
}
else{
id[i]='\0';
if(check_keyword(id)){
fprintf(fp2," \n %s : keyword ",id);

}
else{
fprintf(fp2,"\n %s : identifier",id);
// call a function which stores id in symbol table
k=convertkey(id);
if(k!=0){
    int found=search(k);
    if(found==0){
        insert(k,id,"identifier");
    }
}


}

state=0;
i=0;
ungetc(c,fp1);
}
break;
case 3:if(isdigit(c)){
num[j++]=c;
state=3;
}
else{
num[j]='\0';
fprintf(fp2," \n%s: number",num);
state=0;
j=0;
ungetc(c,fp1);

}
break;
case 5:if(c=='='){
  rel[t]=c;
  t++;
  rel[t]='\0';
fprintf(fp2,"\n%s relational operator ",rel);
t=0;

state=0;
}
else{
    rel[t]='\0';
fprintf(fp2,"\n%s relational operator ",rel);

state=0;
ungetc(c,fp1);
t=0;
}
break;
case 8:if(c=='='){
  rel[t]=c;
  t++;
  rel[t]='\0';
fprintf(fp2,"\n%s relational operator ",rel);
t=0;
state=0;
}
else{
ungetc(c,fp1);
state=0;
}
break;
case 10:if(c=='*')
state=11;
else
fprintf(fp2,"\n invalid lexeme");
break;
case 11: if(c=='*')
state=12;
else
state=11;
break;
case 12:if(c=='*')
state=12;
else if(c=='/')
state=0;
else
state=11;
break;

}//End of switch
}//end of while
if(state==11)
fprintf(fp2,"comment did not close");
fclose(fp1);
fclose(fp2);
display();
return 0;
}
void display() {
   int i = 0;
	printf("%s","SRNO\t\t\tID\t\t\ttype");
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i] != NULL){
         printf("\n");
         printf(" %d%s%s%s%s",hashArray[i]->key,"\t\t\t",hashArray[i]->data,"\t\t\t",hashArray[i]->type);
        
      }
     
   }
	
   printf("\n");
}
int convertkey(char *id){
    int sum =0;
    for(int i=0;i< strlen(id);i++){
       
       int num =(int)id[i]*(i+1);
       sum= sum+num;
    }
  
   return sum%2069;
}
int search(int key) {
   
   int hashIndex = hashCode(key);  
	while(hashArray[hashIndex] != NULL) {
	  if(hashArray[hashIndex]->key == key)
         return 1; 
	 ++hashIndex;
     hashIndex %= SIZE;
   }        
	
   return 0;        
}