#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "functions.h"

typedef struct Student STU;
FILE *datafile1,*datafile2;

#define dbg if(1)

void wlc_txt();
void reg_stu(); // register studento
void show_stu();
void search();  // search for student
void search_name(char name[]);
void search_room(int room_id);
void stu_access();
void update();
void update_id(int id);
void del();
void del_id(int id);
void ask();
void sort();
void read_file1(STU *s, int *size);
int read_id();
void write_file1(STU s[],int size);
void print_list(STU students[], int size);
void print_student(STU s);
void restoqueries(int x);


void greet();
void login();

void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
  //	return;
}


int main(){
    system("color 1f");
    fullscreen();
    greet();
}

void wlc_txt(){
    char g_mes1[]="WELCOME TO MY HOSTEL";
    char g_mes2[]="HOSTEL STUDENTS RECORD MANAGEMENT SYSTEM";

    gotoxy(x_cor,5);
    int len1=strlen(g_mes1), len2=strlen(g_mes2),x = 80;

    printf("+");
    h_border(x,'-');
    chline();

    // printf("\n");
    printf("|%*s%*s|",(x+len1)/2,g_mes1,(x-len1)/2,"");
    chline();

    printf("+");
    h_border(x,'-');
    chline();

    // printf("\n");
    printf("|%*s%*s|",(x+len2)/2,g_mes2,(x-len2)/2,"");
    chline();

    printf("+");
    h_border(x,'-');
    chline();
}

void main_menu(){
    int x = 82;
    char menu[]="  MAIN MENU  ";
    chline();
    h_line(x,'-');
    chline();
    h_line((x-strlen(menu))/2,'-');
    printf("%s",menu);
    h_line((x-strlen(menu))/2+1,'-');
    chline();
    h_line(x,'-');
    chnline(2);
    time(&now);
    printf("%s",ctime(&now));
    chline();
}

void greet(){
    wlc_txt();
    // printf("\n");
    login();
}



void login(){
    wlc_txt();

    static int count = 0;
    char pass[4];
    if (!count) {
        chline();
        printf("Hello!\n");
    }
    chline();
    if (count==0) printf("Enter password to login: ");
    else {
        printf("Incorrect password.");
        chnline(2);
        printf("Please enter password again: ");
    }

    scanf("%s",&pass);
    count=1;
    if (strcmp(pass, "pass")==0){
        system("cls");
        //printf("%s\n %d",pass,strcmp(pass, "pass")==0);
        gotoxy(x_cor,5);
        printf("Successfully logged in..\n");
        ask();
    }
    else {
        system("cls");
        Beep(600,500);
        gotoxy(x_cor,5);
        login();
    }
}



void ask(){
    static int count = 0;

    if (count) {
        chnline(2);
        printf("Press any key to go to main menu.");
        getch();
        system("cls");
    }
    wlc_txt();
    main_menu();
    chline();
    chline();
    count++;
    printf("1. Student Registeration\n");
    chline();
    printf("2. View All Students Details\n");
    chline();
    printf("3. Search Student Details\n");
    chline();
    printf("4. Student Access\n");
    chline();
    printf("5. Update Student Details\n");
    chline();
    printf("6. Delete Student Details\n");
    chline();
    printf("7. Exit\n\n");
    chline();
    printf("Select Option: ");
    int x;
    scanf("%d",&x);
    restoqueries(x);
}


void restoqueries(int x){
    system("cls");
    gotoxy(x_cor,5);
    switch (x){
        case 1:
        reg_stu();
        break;
        case 2:
        show_stu();
        break;
        case 3:
        search();
        break;
        case 4:
        stu_access();
        break;
        case 5:
        update();
        break;
        case 6:
        del();
        break;
        case 7:
        exit(1);
    }
    ask();
}



void reg_stu(){
    STU stu;
    int id=read_id();
    gotoxy(x_cor,5);
    printf("Id of student: %d",id);

    chnline(2);
    fflush(stdin);
    printf("Enter Student's name: ");
    gets(stu.name);
    ucase(stu.name);

    chline();
    printf("Enter Student's mobile number: ");
    gets(stu.number);

    chline();
    printf("Enter Student's School: ");
    gets(stu.inst);

    chline();
    printf("Enter Student's Guardian Name: ");
    gets(stu.guardian_name);

    chline();
    printf("Enter Student's Guardian Mobile Number: ");
    gets(stu.guardian_no);

    chline();
    printf("Enter the room allocated to the student: ");
    scanf("%d",&stu.room_no);
    chnline(3);

    printf("Student Successfully registered.");
    chline();

    stu.stu_no=id;

    time(&now);
    strcpy(stu.date, ctime(&now));

    // last char of return of ctime is \n so replaced it with \0.
    stu.date[strlen(stu.date)-1]='\0';
    
    // print the details of student added.
    print_student(stu);
    
    // append to the file.
    datafile1 = fopen("data.bin","a");
    encrypt(&stu);
    fwrite(&stu,sizeof(STU),1,datafile1);
    fclose(datafile1);

    // sort the data in file according to the name
    sort();
}


void show_stu(){
    STU s[1000];
    int size=0;
    read_file1(s,&size);
    print_list(s,size);
}


void search(){

    char name[20];
    fflush(stdin);
    chline();
    printf("Do you want to search student by:");
    chline();
    printf("1. Name");
    chline();
    printf("2. Room Number");
    chnline(2);
    printf("Enter your option (1 or 2): ");
    char x;
    scanf("%c",&x);

    chnline(2);
    if (x=='1'){
        fflush(stdin);
        chline();
        printf("Enter the student name: ");
        gets(name);
        ucase(name);
        search_name(name);
    }
    else if (x == '2'){
        int room;
        chline();
        printf("Enter room number: ");
        scanf("%d",&room);
        search_room(room);
    }
    chline();
}


void search_name(char name[]){
    STU temp[1000],found[1000];
    int size=0,count_found=0;
    read_file1(temp,&size);
    for (int i=0;i<size;i++){
        if (issubstring(name,temp[i].name)){
            found[count_found++]=temp[i];
        }
    }
    if (!count_found){
        printf("Sorry! No Student found with name %s.",name);
        return;
    }
    print_list(found,count_found);
}


void search_room(int room){
    STU temp[1000],found[1000];
    int size=0,count_found=0;
    read_file1(temp,&size);
    for (int i=0;i<size;i++){
        if (temp[i].room_no==room){
            found[count_found++]=temp[i];
        }
    }
    if (!count_found){
        printf("Sorry! No Student found in the room %d.",room);
        return;
    }
    print_list(found,count_found);
}


void stu_access(){

    STU temp[1000],found[1000];
    int size=0,count_found=0;

    // print all
    read_file1(temp,&size);
    t_row1();
    printf("|%-20s |%15s |","Name","Mobile No.");
    chline();
    t_row1();
    t_row1();
    for (int i=0;i<size;i++){
        printf("|%-20s |%15s |",temp[i].name,temp[i].number);
        chline();
        t_row1();
    }
}


void update(){
    
    printf("Do you know the id(or form no.) of student: ");
    char response;
    fflush(stdin);
    response = getche();

    if (response != 'y' && response != 'Y'){
        char name[20];
        chnline(2);
        printf("Enter the name of student: ");
        fflush(stdin);
        gets(name);
        ucase(name);
        search_name(name);
    }
    int id,found=0;

    chnline(2);
    printf("Enter the id number: ");
    scanf("%d",&id);
    update_id(id);
}

void update_id(int id){

    STU temp[1000];
    int size=0,ind=-1;

    read_file1(temp,&size);
    for (int i=0;i<size;i++){
        if (temp[i].stu_no==id){
            ind = i;
            break;
        }
    }

    if (ind == -1){
        chline();
        printf("Sorry! No Student found with id %d",id);
        return;
    }

    STU new;
    new.stu_no = temp[ind].stu_no;
    strcpy(new.date,temp[ind].date);
    char x;
    chline();
    printf("Enter (y or Y) if you want to update each.");
    chline();
    fflush(stdin);
    printf("Name (y/n): ");
    x = getche();
    if (x=='y' || x == 'Y') {
        chline();
        printf("Enter New Name: ");
        gets(new.name);
        ucase(new.name);
    }
    else strcpy(new.name,temp[ind].name);

    chline();
    printf("Number (y/n): ");
    x = getche();
    if (x=='y' || x == 'Y') {
        chline();
        printf("Enter New Number: ");
        gets(new.number);
    }
    else strcpy(new.number,temp[ind].number);

    chline();
    printf("School/College (y/n): ");
    x = getche();
    if (x=='y' || x == 'Y') {
        chline();
        printf("Enter New School/College Name: ");
        gets(new.inst);
    }
    else strcpy(new.inst,temp[ind].inst);

    chline();
    printf("Guardian Name (y/n): ");
    x = getche();
    if (x=='y' || x == 'Y') {
        chline();
        printf("Enter New Guardian Name: ");
        gets(new.guardian_name);
    }
    else strcpy(new.guardian_name,temp[ind].guardian_name);

    chline();
    printf("Guardian Number (y/n): ");
    x = getche();
    if (x=='y' || x == 'Y') {
        chline();
        printf("Enter New Guardian Number: ");
        gets(new.guardian_no);
    }
    else strcpy(new.guardian_no,temp[ind].guardian_no);

    chline();
    printf("Room (y/n): ");
    x = getche();
    if (x=='y' || x == 'Y') {
        chline();
        printf("Enter New Room Number: ");
        scanf("%d",&new.room_no);
    }
    else new.room_no=temp[ind].room_no;
    system("cls");
    gotoxy(x_cor,5);
    printf("Details updated.");
    chnline(3);
    printf("Old Detail of student.");
    print_student(temp[ind]);
    temp[ind] = new;


    chnline(2);
    printf("New Detail of student.");
    print_student(temp[ind]);
    write_file1(temp,size);
    sort();
}


void del(){
    
    printf("Do you know the id(or form no.) of student: ");
    char response;
    fflush(stdin);
    response = getche();
    chnline(2);

    if (response != 'y' && response != 'Y'){
        char name[20];
        printf("Enter the name of student: ");
        fflush(stdin);
        gets(name);
        ucase(name);
        search_name(name);
    }
    int id,found=0;
    chline();
    printf("Enter the id number: ");
    scanf("%d",&id);
    chline();
    del_id(id);
}

void del_id(int id){
    STU s[1000], newlist[1000];
    int size=0,found=0,count=0;


    read_file1(s,&size);
    for (int i=0;i<size;i++){
        if (s[i].stu_no == id && !found) {
            found=1;
            printf("Student Successfully Deleted.");
            chnline(2);
            print_student(s[i]);
            continue;
        }
        newlist[count++]=s[i];
    }
    if (!found){
        chline();
        printf("Sorry! No Student found with id %d.\n",id);
    }
    write_file1(newlist,count);
}

void print_student(STU s){
    
    chnline(2);
    printf("%-35s %30d\n","Id/Form number:",s.stu_no);
    chline();
    printf("%-35s %30s\n","Name:",s.name);
    chline();
    printf("%-35s %30s\n","Mobile Number:",s.number);
    chline();
    printf("%-35s %30s\n","School/College Name:",s.inst);
    chline();
    printf("%-35s %30s\n","Guardian Name:",s.guardian_name);
    chline();
    printf("%-35s %30s\n","Guardian Number:",s.guardian_no);
    chline();
    printf("%-35s %30s\n","Date of Enrollment:",s.date);
    chline();
    printf("%-35s %30d\n","Room Number:",s.room_no);
    chline();
}

void swap(STU *s1, STU *s2){
    STU temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void sort(){
    STU s[1000], temp;
    int size=0;

    read_file1(s,&size);

    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            if (i==j) continue;
            if (strcmp(s[i].name,s[j].name)<0) swap(&s[i],&s[j]);
        }
    }

    write_file1(s,size);

}

void print_list(STU s[], int size){
    chrow();
    table_row();
    //      id   name   mob   scho  guarname num
    printf("|%5s |%20s |%15s |%20s |%20s |%15s |%25s |%9s |","ID","Name","Mobile No.","School","Guard.. Name","Guard.. No.","Date of enroll","Room No.");
    chrow();
    for (int i=0; i<size; i++){
        table_row();
        printf("|%5d |%20s |%15s |%20s |%20s |%15s |%25s |%9d |",s[i].stu_no,s[i].name,s[i].number,s[i].inst,s[i].guardian_name,s[i].guardian_no,s[i].date,s[i].room_no);
        chrow();
    }
    table_row();
}


void read_file1(STU *s,int *size){
    datafile1 = fopen("data.bin","r");

    STU temp;
    *size = 0;
    while(fread(&temp,sizeof(STU),1,datafile1)){

        if (feof(datafile1)) break;
        dencrypt(&temp);
        *(s+*size)=temp;
        (*size)++;
    }
    fclose(datafile1);
}


int read_id(){
    int id = 1;
    datafile2 = fopen("count.bin","r");

    if (datafile2==NULL){
        id = 1;
        datafile2=fopen("count.bin","w");
        fwrite(&id,sizeof(int),1,datafile2);
        fclose(datafile2);
    }
    else {
        fread(&id,sizeof(int),1,datafile2);
        id++;
        fclose(datafile2);

        datafile2=fopen("count.bin","w");
        fwrite(&id,sizeof(int),1,datafile2);
        fclose(datafile2);
    }
    return id;
}

void write_file1(STU s[], int size){

    datafile1=fopen("data.bin","w");
    for (int i=0;i<size;i++){
        encrypt(&s[i]);
        fwrite(&s[i],sizeof(STU),1,datafile1);
    }
    fclose(datafile1);
}
