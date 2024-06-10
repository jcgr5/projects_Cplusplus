#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

bool gameOver = false;


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

class nave{
    int x,y,vidas;
public:
    nave(int _x,int _y,int _vida): x(_x),y(_y),vidas(_vida){};
    void pintar();
    void borrar();
    void mover();
    void redibujar();
    void pintarVidas();
};
//--------------------METODOS CLASE: NAVE-----------------------
void nave::pintar() {
    gotoxy(x,y);printf("  %c",30);
    gotoxy(x,y+1);printf(" %c%c%c",40,207,41);
    gotoxy(x,y+2);printf("%c%c %c%c",30,190,190,30);

}
void nave::borrar() {
    gotoxy(x,y);printf("   ");
    gotoxy(x,y+1);printf("     ");
    gotoxy(x,y+2);printf("      ");

}
void nave::mover() {
    if(_kbhit()) {
        char tecla = getch();
        borrar();
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
        redibujar();
        pintar();
        pintarVidas();
        cleanInputBuff();
        Sleep(100);
    }
}
void nave::redibujar() {
    if(x-2==0)x+=2;
    if(x+2==78)x-=2;
    if(y-1==0)y+=1;
    if(y+2==9)y-=2;
}
void nave::pintarVidas(){
    gotoxy(60,1);printf("vidas: ");
    printf("   ");
    for (int i = 0; i < vidas; ++i) {
        gotoxy(68+i,1);
        printf("%c",3);
    }
}
//--------------------------------------------------------------

void pintarLimites(){
    gotoxy(0,0);printf("%c",201);
    gotoxy(0,10);printf("%c",200);
    gotoxy(79,0);printf("%c",187);
    gotoxy(79,10);printf("%c",188);
    for (int i = 1; i < 79; ++i) {
        gotoxy(i,0);printf("%c",205);
        gotoxy(i,10);printf("%c",205);
    }
}



int main(){
    esconderCursor();
    pintarLimites();
    nave n(5,5,3);
    n.pintar();
    n.pintarVidas();
    while(!gameOver){
        n.mover();

    }
    return 0;
}