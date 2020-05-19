#include<stdio.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define FILENAME "PHONEBOOK.PHN"

struct PhoneBook{
char name[100];
char address[200];
int phoneNo;
char email[100];
};
void mainMenu();
void addContact(FILE *fp);
void readContacts(FILE *);
void deleteContact(FILE *);
void modifyContact(FILE *);
struct PhoneBook basicDetails(char[]);
void searchContact(FILE *);
int checkForMatch(char[],char[]);
void menuDesign(char[]);
void showMessage(char[]);
void pressForMainMenu();
void fileOpen(FILE *);
void fileClose(FILE *);
main(){
system("cls");
mainMenu();
}
void mainMenu(){
printf("\n\n\n\t\tLOADING . PLEASE WAIT....");
FILE *fp;
fp=fopen(FILENAME,"rb+");
if(fp==NULL){
fp=fopen(FILENAME,"wb+");
if(fp==NULL){
printf("CANNOT OPEN THE FILE");
}
}
system("cls");
int choice;
char ch;
int result;
printf("\n");
menuDesign("|PHONEBOOK MANAGEMENT SYSTEM|");
printf("\n1. ADD NEW ");
printf("\n2. VIEW ALL ");
printf("\n3. SEARCH ");
printf("\n4. MODIFY");
printf("\n5. DELETE ");
printf("\n6. EXIT");
printf("\n\n\t ENTER YOUR CHOICE : ");
fflush(stdin);
ch=getche();
system("cls");
switch(ch){
case '1' :
addContact(fp);
break;
case '2':
readContacts(fp);
break;
case '3':
searchContact(fp);
break;
case '4':
modifyContact(fp);
break;
case '5':
deleteContact(fp);
break;
case '6':
exit(0);
break;
default:
 system("cls");
 showMessage("ERROR !! PLEASE ENTER 1-6 ONLY");
 pressForMainMenu();
 getch();
}
}
void searchContact(FILE *fp){
menuDesign("SEARCH CONTACT");
struct PhoneBook ph;
int result;
int count=0;
char item[50];
printf("\n\t\tEnter Some text to be Search : ");
scanf("%s",&item);
while(fread(&ph,sizeof(ph),1,fp)==1){
result=checkForMatch(ph.name,item);
if(result==1){
count++;
printf("\n \t\t Name : %s \n\t\t Address : %s \n\t\t E-Mail:%s\n\t\t Phone No %d \n\n",ph.name,ph.address,ph.email,ph.phoneNo);
}
}
fclose(fp);
if(count==0)
printf("\n\t\tNothing found for Name : %s",item);
else
printf("\n\t\tTotal %d no of Contact(s) found for : %s",count,item);
pressForMainMenu();
}
 int checkForMatch(char a[],char b[])
 {
int i,k;
char *p,temp[strlen(b)];
if(strlen(a)>=strlen(b)){
for(i=0;i<=(strlen(a)-strlen(b));i++)
 {
p=&a[i];
k=0;
while(k!=strlen(b))
{
 temp[k]=*(p+k);
 k++;
}
temp[k]='\0';

if(strcmp(strupr(temp),strupr(b))==0)
{
return 1;
}
}
}
return 0;
 }
struct PhoneBook basicDetails(char level[200]){
struct PhoneBook ph;
menuDesign(level);
printf("\n\t\tEnter Name : ");
scanf("%s",&ph.name);
printf("\n\t\tEnter Address : ");
scanf("%s",&ph.address);
printf("\n\t\tEnter E-Mail : ");
scanf("%s",&ph.email);
printf("\n\t\tEnter phoneNo : ");
scanf("%d",&ph.phoneNo);
return ph;
}
void addContact(FILE *fp)
{
char another='Y';
struct PhoneBook ph;
while((another=='Y')||(another=='y')){
system("cls");
ph=basicDetails("ADD NEW CONTACT");
fseek(fp,0,SEEK_END);
fwrite(&ph,sizeof(ph),1,fp);
printf("\n\n\t\t-------------------------------------------------");
printf("\n\t\tAdded Successfully");
printf("\n\n\t\t-------------------------------------------------");
printf("\n\n\t\tWant to add Another Contact ( Y / N) : ");
fflush(stdin);
another=getche();
 }

if(another!='Y'||(another!='y')){
fclose(fp);
system("cls");
mainMenu();
 }
}
void readContacts(FILE *fp)
{
int count=0;
char keyPress;
rewind(fp);
struct PhoneBook ph;
menuDesign("ALL CONTACTS");
while(fread(&ph,sizeof(ph),1,fp)==1){
count++;
printf("\n \t\t Name : %s \n\t\t Address : %s \n\t\t E-Mail :%s\n\t\tPhone No : %d \n\n",ph.name,ph.address,ph.email,ph.phoneNo);
}
if(count==0){
showMessage("Nothing To Display ..... ");
}
fclose(fp);
pressForMainMenu();
}
void deleteContact(FILE *fp)
{
system("cls");
menuDesign("DELETE CONTACT");
struct PhoneBook ph;
FILE *temp;
int count=0;
char name[50];
temp=fopen("TEMP.DAT","wb+");
printf("\n\t\tEnter Contant Name to Delete : ");
scanf("%s",&name);
rewind(fp);
while(fread(&ph,sizeof(ph),1,fp)==1){
if(strcmp(strupr(ph.name),strupr(name))!=0){
fwrite(&ph,sizeof(ph),1,temp);
}else{
count++;
}
}
fclose(fp);
fclose(temp);
remove ( FILENAME ) ;
rename ( "TEMP.DAT", FILENAME ) ;
fp = fopen ( FILENAME, "rb+" ) ;
printf("\n\n\t\t-------------------------------------------------");
if(count!=0)
printf("\n\t\tDeleted Successfully");
else
printf("\n\t\tNo entry found with Name : %s",name);
printf("\n\n\t\t-------------------------------------------------");
fclose(fp);
pressForMainMenu();
}
void modifyContact(FILE *fp)
{
system("cls");
menuDesign("MODIFY CONTACT DETAILS");
rewind(fp);
int count=0;
struct PhoneBook ph;
char name[50];
printf("\n\t\tEnter Name to be Modified : ");
scanf("%s",&name);
while(fread(&ph,sizeof(ph),1,fp)==1){
if(strcmp(strupr(ph.name),strupr(name))==0){
count++;
ph=basicDetails("MODIFY CONTACT ");
fseek(fp,-sizeof(ph),SEEK_CUR) ;
fwrite(&ph,sizeof(ph),1,fp);
break;
}
}
printf("\n\n\t\t-------------------------------------------------");
if(count!=0)
printf("\n\t\tModified Successfully");
else
printf("\n\t\tNo entry found with Name : %s",name);
printf("\n\n\t\t-------------------------------------------------");
fclose(fp);
pressForMainMenu();
}
void menuDesign(char topic[])
{
char *pattern;
printf("\n\t\t=============================");
printf("\n\t\t%s",topic);
printf("\n\t\t=============================\n\n");
}
void showMessage(char message[])
{
printf("\n\t\t----------------------------------------------");
printf("\n\t\t%s",message);
printf("\n\t\t----------------------------------------------");
}
void pressForMainMenu()
{
char keyPress;
printf("\n\n\t\tPress Any Key For Main Menu ... ");
keyPress=getche();
if(keyPress!=' ')
system("cls");
mainMenu();

return 0;
}
