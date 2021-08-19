#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 25
struct symbtab
{
char *data;
int key;
};
struct symbtab* hash[SIZE];
struct symbtab* dummyItem;
struct symbtab* item;
int hashCode(int key) {
return key % SIZE;
}
struct symbtab *search(char* key) {
//get the hash
int index = 1;
//move in array until an empty
while(hash[index] != NULL) {
if(hash[index]->data == key)
return hash[index];
//go to next cell
++index;
//wrap around the table
index %= SIZE;
}
return 0;
}
void insert(int key,char* data) {
struct symbtab *item = (struct symbtab*) malloc(sizeof(struct symbtab));
item->data = data;
item->key = key;
struct symbtab *temp = (struct symbtab*) malloc(sizeof(struct symbtab));
temp = search(data);
if (temp == NULL){
//get the hash
int index = key;
//move in array until an empty or deleted cell
while(hash[index] != NULL && hash[index]->key != -1) {
//go to next cell
++index;
//wrap around the table
index %= SIZE;
}
hash[index] = item;
}
}
void display() {
int i = 0;
printf("\n\n");
printf("info\tid");
for(i = 0; i<SIZE; i++) {
if(hash[i] != NULL)
printf("\n %d\t%s",hash[i]->key,hash[i]->data);
}
printf("\n");
}
int main() {
char id[25][25];
int i = 0;
printf("Enter 'x' to stop giving input\n\nInput:\n");
while (i < 25){
scanf("%s",id[i]);
if (!strcmp(id[i],"x")){
break;
}
insert(i,id[i]);
i++;
}
display();
}

