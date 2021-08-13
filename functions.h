#include <stdio.h>
#include <string.h>
#include <windows.h>

const int x_cor = 60;
const int x_table = 30;
time_t now;

typedef struct Student
{
    int stu_no, room_no;
    char name[20], number[11], inst[40], guardian_name[20], guardian_no[11], date[25];
} STU;

// functions for border lines, table
// lince change
void h_border(int length, char c);
void table_row();
int issubstring(char *s, char *S);
void ucase(char *);
void t_row1();

void fullscreen();
// encrypt
void encrypt(STU *);
void dencrypt(STU *);
void encrypt_str(char *);
void encrypt_int(int *);
void dencrypt_str(char *);
void dencrypt_int(int *);

void gotoxy(int, int);
void chline();
void chnline(int n);
void chrow();

void table_row()
{
    h_border(0, ' ');
    h_border(6, '-');
    h_border(21, '-');
    h_border(16, '-');
    h_border(21, '-');
    h_border(21, '-');
    h_border(16, '-');
    h_border(26, '-');
    h_border(10, '-');
    chrow();
}

void h_line(int n, char c)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);
}

void h_border(int length, char c)
{
    while (length--)
    {
        putchar(c);
    }
    putchar('+');
}

int issubstring(char *s, char *S)
{
    ucase(s);
    ucase(S);
    int len1 = strlen(s), len2 = strlen(S);

    if (len2 < len1)
        return 0;
    for (int i = 0; i <= len2 - len1; i++)
    {
        char temp[len1 + 1];
        strcpy(temp, s);
        for (int j = 0; j < len1; j++)
        {
            temp[j] = S[j + i];
        }
        if (strcmp(temp, s) == 0)
            return 1;
    }
    return 0;
}

void t_row1()
{
    printf("+");
    h_border(21, '-');
    h_border(16, '-');
    chline();
}

void ucase(char *c)
{
    for (int i = 0; i < strlen(c); i++)
    {
        if (c[i] <= 'z' && c[i] >= 'a')
        {
            c[i] = (char)(c[i] + 'A' - 'a');
        }
    }
}

/**
 * COORD is just a simple structure with objects X and Y 
 * denoting the x and y coordinate. 
 **/
COORD get_pos()
{

    // learned from docs of windows.h

    // screen.dwCursorPosition is structure of COORD which have current position on console.
    // link: [https://docs.microsoft.com/en-us/windows/console/console-screen-buffer-info-str]
    // screen is just a structure variable which is present in "windows.h" header file
    CONSOLE_SCREEN_BUFFER_INFO screen;

    // link: [https://docs.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo]
    // this will give all the information of screen and location of the current cursor
    // the location is stored in structure COORD dwCursorPosition
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen);
    COORD c;
    c.X = screen.dwCursorPosition.X;
    c.Y = screen.dwCursorPosition.Y;
    return c;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void chnline(int n)
{
    COORD pos;
    pos = get_pos();
    gotoxy(x_cor, pos.Y + n);
}

void chrow()
{
    COORD pos;
    pos = get_pos();
    gotoxy(x_table, pos.Y + 1);
}

void chline()
{
    chnline(1);
}

// i just copied this from web 
void fullscreen()
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

// a simple encryption by increasing each character by 11
void encrypt_str(char *c)
{
    for (int i = 0; i < strlen(c); i++)
    {
        c[i] = (char)(c[i] + 11);
    }
}

// encryption for integer
void encrypt_int(int *x)
{
    *x += 29;
}

// then dencrypting the string by decreasing the character by 11
void dencrypt_str(char *c)
{
    for (int i = 0; i < strlen(c); i++)
    {
        c[i] = (char)(c[i] - 11);
    }
}

// dencryption for integer
void dencrypt_int(int *x)
{
    *x -= 29;
}

// encrypting the whole Student structure by using above encryption
void encrypt(STU *stu)
{
    STU new = *stu;
    encrypt_str(new.name);
    encrypt_str(new.number);
    encrypt_str(new.inst);
    encrypt_str(new.guardian_name);
    encrypt_str(new.guardian_no);
    encrypt_str(new.date);

    encrypt_int(&new.stu_no);
    encrypt_int(&new.room_no);
    *stu = new;
}

// dencryopting the whole Student structure by using above encryption
void dencrypt(STU *stu)
{
    STU new = *stu;
    dencrypt_str(new.name);
    dencrypt_str(new.number);
    dencrypt_str(new.inst);
    dencrypt_str(new.guardian_name);
    dencrypt_str(new.guardian_no);
    dencrypt_str(new.date);

    dencrypt_int(&new.stu_no);
    dencrypt_int(&new.room_no);
    *stu = new;
}