#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y){
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

void cleanInputBuff(){//consume all inputs
    int i;
    while(( i = _kbhit()) != 0){
        if(i == EOF)break; //(EOF, means end of file or end of a stream input)
        getch();
    }
}

void esconderCursor(){
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
    cursor.bVisible=FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
}

int main(){
    esconderCursor();
    bool gameOver = false;
    int x{5},y{5};
    gotoxy(x,y);printf("*");
    while(!gameOver){
       if(_kbhit()) {
           char tecla = getch();
           gotoxy(x,y);
           printf(" ");
           switch (tecla) {
                case 'j':
                    x--;
                    break;
                case 'l':
                    x++;
                    break;
                case 'i':
                    y--;
                    break;
                case 'k':
                    y++;
                    break;
                case 'e':
                    gameOver = true;
                    break;
                default:
                    printf("use las teclas i,j,k,l para moverse");
           }
           gotoxy(x,y);
           printf("*");
           cleanInputBuff();
           Sleep(100);
        }
    }
    return 0;
}