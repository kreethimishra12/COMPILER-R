#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
int i=0,top=0;
char stack[2000][50],ip[20];
int nttop=0;

void push(char c[])
{
	if (top>=2000)
		printf("Stack Overflow");
	else
		strcpy(stack[top++],c);
	
}




void pop(void)
{
	if(top<0)
		printf("Stack underflow");
	else
		top--;
}

void error(void)
{
printf("\n\nSyntax Error!!!! String is invalid\n");
getch();
exit(0);
}

int main()
{
int n;
char filename[] = "y.txt";
FILE *file = fopen ( filename, "r" );
int m=0;
char line1[1000];
while(fgets(line1,sizeof line1,file)!= NULL){
   
    m++;
}

char line[m+1][50];
char line3[m+1][50];
strcpy(line3[m],"$");
strcpy(line3[m+1],"/0");
int l;

push("$");
push("S");
char filename1[] = "y.txt";
FILE *file1 = fopen ( filename1, "r" );
char line2[256];
int t=1;

while(m+1>= i)
 {fgets(line2,sizeof(line2),file1);
     
     l=0;
    l=strlen(line2);
    line2[l-1]='\0';
    strcpy(line[i],line2);
    if(i>=m && strcmp(stack[top-1],"$")==0 )
  { t=0;
	printf("\n\n Successful parsing of string \n");
	break;
  }
  else
    
	if(strcmp(line[i],stack[top-1])==0)
	{
	   printf("\n    match of %s \n", line[i]);
	  pop();
	}
	else
	{
		if(strcmp(stack[top-1],"S")==0)
		{ 
	    if(strcmp(line[i], "if")==0){
	        
	         printf(" \n S->if(condition){statement}S");
		      
		       pop();
		       push("S");
		       push("}");
 		       push("statement");
               push("{");
               push(")");
               push("condition");
               push("(");
               
          
        }else if(strcmp(line[i],"for")==0){
            printf("\n S->for ( identifier <- numeric){ statement }S");
            pop();
            push("S");
            push("}");
            push("statement");
            push("{");
            push(")");
            push("numeric");
            push("<-");  
            push("identifier");
            push("(");
           
        }else if(atoi(line[i])==50){
            printf("\n S->identifier <-identifier ops identifier ");
           pop();
           push("identifier");
           push("ops");
           push("identifier");
           push("<-");
           
            
        }
        else{
          printf("\n S-> $")  ;
          pop();
        }
		}
		
     	else if(strcmp(stack[top-1],"condition")==0){
	        if(atoi(line[i])){
	         printf("  condition->exp(numeric) op expr");
	         pop();
	         push("expr");
	         push("op");
	        
	         
	        
        }else{
            printf(" condition->exp(identifier) op expr");
            pop();
	         push("expr");
	         push("op");
	        
	         }
       }else if(strcmp(stack[top-1],"op")==0)
       {    
     
          if((strcmp(line[i],">")==0) || (strcmp(line[i],"<")==0)|| (strcmp(line[i],">=")==0) || (strcmp(line[i],"!=")==0)||(strcmp(line[i],"==")==0))
          {
               printf( " \n op->  %s",line[i]);
               pop();
          }
       }else if(strcmp(stack[top-1],"expr")==0){
           pop();
           if(atoi(line[i])==0){
               printf("\nexpr-> identifier %s", line[i]);
           }else {
               printf("\n %sexpr->numeric", line[i]);
           }
       }else if(strcmp(stack[top-1],"ops")==0){
           if((strcmp(line[i],"+")==0) || (strcmp(line[i],"-")==0)|| (strcmp(line[i],"*")==0) || (strcmp(line[i],"%")==0)||(strcmp(line[i],"/")==0))
          {
               printf( " \n op->  %s",line[i]);
               pop();
          }  else{
              pop();
              pop();
          }
           
       }
       
       else if(strcmp(stack[top-1],"statement")==0){
           printf("%s%s",line[i],stack[top-1]);
           if(atoi(line[i])==0 && strcmp(line[i],"print")!=0 && strcmp(line[i],"}")!=0 && strcmp(line[i],"<-")){
               printf("\nstatment-> identifier <- expr ops expr statement");
               pop();
               push("statement");
               push("expr");
               push("ops");
               push("expr");
               push("<-");
           }else if(strcmp(line[i],"print")==0){
               printf("\nstatement-> print( identifier ) statement");
               pop();
               push("statement");
               push(")");
               push("identifier");
               push("(");
               
           }else if(strcmp(line[i], "}")==0){
               printf("\n statement-> $");
               pop();
               pop();
           }
           
          }else if(strcmp(stack[top-1],"identifier")==0){
              if(atoi(line[i])==0){
                  printf("\n identifier found");
                  pop();
                  
              }
              
          }else if(strcmp(stack[top-1],"numeric")==0){
              if(atoi(line[i])!=0){
                  printf("\n numeric found");
                  pop();
                  
              }
              
          } else {
           printf("String invalid");
           break;
       }
	}
 
i++; }


}