#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define MAXGAMEMOVES 10000

char board[12][12] = {
    {0,0,'A','B','C','D','E','F','G','H',0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {'8',0,'R','N','B','Q','K','B','N','R',0,'8'},
    {'7',0,'P','P','P','P','P','P','P','P',0,'7'},     // black (turn 2)
    {'6',0,'-','.','-','.','-','.','-','.',0,'6'},
    {'5',0,'.','-','.','-','.','-','.','-',0,'5'},
    {'4',0,'-','.','-','.','-','.','-','.',0,'4'},
    {'3',0,'.','-','.','-','.','-','.','-',0,'3'},
    {'2',0,'p','p','p','p','p','p','p','p',0,'2'},
    {'1',0,'r','n','b','q','k','b','n','r',0,'1'},      //white (turn 1)
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,'A','B','C','D','E','F','G','H',0,0}
};
int turn=1,king_move1=0,king_move2=0,right1=0,left1=0,right2=0,left2=0;
int rook_move11=0,rook_move12=0,rook_move21=0,rook_move22=0;
int i=0,j=0;
int counter=0,counter1=0,counter2=0,redo_counter=0;
char killed1[15],killed2[15];
char undo_arr[MAXGAMEMOVES][7];
char redo_arr[MAXGAMEMOVES][7];
int undoCheck[MAXGAMEMOVES][6],countercheck=0;
char rookplace;
char knightplace;
char bishopplace;
char queenplace;
char Kingplace;
char kingplace;
char pawnplace;



//Prototypes
int pawn(int x,int y,int x1,int y1,int turn);
int knight(int x,int y,int x1,int y1,int turn);
int rook(int x,int y,int x1,int y1,int turn);
int bishop(int x,int y,int x1,int y1,int turn);
int queen(int x,int y,int x1,int y1,int turn);
int king(int x,int y,int x1,int y1,int turn);

//functions
int scan(int turn);
int check_x(int f);
int check_y(int y);
int promotion1(int x,int y,int x1,int y1,int turn,int n);
int promotion2(int x,int y,int x1,int y1,int turn,int n);
void checkboard (int x,int y);
void print_board();
int f_turn(int turn);
bool find(int turn);
bool protect(int turn);
void undoProtect(int turn);
bool check(char kingplace,int i,int j,int turn);
bool castling_check(char kingplace,int i,int j);
bool knightcheck(int i,int j,char knightplace,int turn);
int rookcheck(int i,int j,char rookplace,char queenplace,int turn);
int bishopcheck(int i,int j,char bishopplace ,char queenplace,int turn);
bool pawncheck(int i,int j,char pawnplace,int turn);
void save(int turn);
int load(int turn);
void readLine(char str[], int n);
int undo(int turn,int counter,int *redo_counter);
int undoAll(int turn,int counter,int *redo_counter);
int redo(int turn,int redo_counter,int *counter);
int redoAll(int turn,int redo_counter,int *counter);
int pawn2(int x,int y,int x1,int y1,int turn);
bool findPawn(int turn);
bool PawnMovesCheck(int h,int k,int turn);
bool findRook(int turn);
bool RookMovesCheck(int i,int j,int turn);
bool findKnight(int turn);
bool KnightMovesCheck(int i,int j,int turn);
bool findBishop(int turn);
bool BishopMovesCheck(int i,int j,int turn);
bool findQueen(int turn);
bool QueenMovesCheck(int i,int j,int turn);
bool findKing(int turn);
bool KingMovesCheck(int i,int j,int turn);
void undoCheckFun(int turn,int countercheck);
bool draw();
bool stalemate(int turn);
bool checkmate(int turn);



int main()
{
    char arr[4];
    printf("\t\t\t\t\t\t Welcome to the game\n\n");
    printf("enter 'SAVE' or 'save' to save the game\n");
    printf("enter 'LOAD' or 'load' to get the saved game\n");
    printf("enter 'UNDO' or 'undo' to go to the previous  move\n");
    printf("enter 'REDO' or 'redo' to go to the next move\n");
    printf("enter 'UALL' or 'uall' to go to the beginning of the game\n");
    printf("enter 'RALL' or 'rall' to go to the end of the game\n\n");
    printf("\t\t\t\t\t**enter the moves in CAPITAL or small letters**\n\n");
    print_board();
    while(checkmate(turn)==false){
        if(stalemate(turn)==true){
            printf("GAME OVER\n");
            printf("stalemate\n");
            printf("\n\nenter 'SAVE' or 'save' if you want to save the game, if not enter any letter: ");
            readLine(arr,4);
            if((arr[0]=='S' && arr[1]=='A' && arr[2]=='V' && arr[3]=='E') || (arr[0]=='s' && arr[1]=='a' && arr[2]=='v' && arr[3]=='e'))
              save(turn);
            return 0;
        }
        else if(draw()==true){
            printf("GAME OVER\n");
            printf("draw\n");
            printf("\n\nenter 'SAVE' or 'save' if you want to save the game, if not enter any letter: ");
            readLine(arr,4);
            if((arr[0]=='S' && arr[1]=='A' && arr[2]=='V' && arr[3]=='E') || (arr[0]=='s' && arr[1]=='a' && arr[2]=='v' && arr[3]=='e'))
              save(turn);
            return 0;
        }
        else{
        turn=scan(turn);
        turn=f_turn(turn);
        }
    }
    printf("GAME OVER\n");
    printf("player %d wins\n",f_turn(turn));
    printf("\n\nenter 'SAVE' or 'save' if you want to save the game, if not enter any letter: ");
    readLine(arr,4);
    if((arr[0]=='S' && arr[1]=='A' && arr[2]=='V' && arr[3]=='E') || (arr[0]=='s' && arr[1]=='a' && arr[2]=='v' && arr[3]=='e'))
        save(turn);
    return 0;
}


//// function (scan) is used to get the input from user and check if it's valid or not.(depends on the move itself is valid or not and it'll result in check on the player or not)
//// it scans all the inputs as char then convert them by functions(check_x) and (check_y).
int scan(int turn)
{

    char input[5];
    int x,x1,y,y1,n,v,a=0;
    printf("player %d move: ",turn);
    readLine(input,5);
    if((input[0]=='S' && input[1]=='A' && input[2]=='V' && input[3]=='E') || (input[0]=='s' && input[1]=='a' && input[2]=='v' && input[3]=='e')){
        save(turn);
        return (f_turn(turn));
    }
    else if((input[0]=='L' && input[1]=='O' && input[2]=='A' && input[3]=='D') || (input[0]=='l' && input[1]=='o' && input[2]=='a' && input[3]=='d')){
        turn=load(turn);
        return (f_turn(turn));
    }
    else if((input[0]=='U' && input[1]=='N' && input[2]=='D' && input[3]=='O') || (input[0]=='u' && input[1]=='n' && input[2]=='d' && input[3]=='o')){
        if(counter==0){
            printf("can't undo more\n");
            return (f_turn(turn));
        }
        counter=undo(turn,counter,&redo_counter);
        return turn;
    }

    if((input[0]=='U' && input[1]=='A' && input[2]=='L' && input[3]=='L') || (input[0]=='u' && input[1]=='a' && input[2]=='l' && input[3]=='l')){
        if(counter==0){
            printf("can't undo more\n");
            return 2;
        }
        counter=undoAll(turn,counter,&redo_counter);
        return 2;
    }

    else if((input[0]=='R' && input[1]=='E' && input[2]=='D' && input[3]=='O') || (input[0]=='r' && input[1]=='e' && input[2]=='d' && input[3]=='o')){
        if(redo_counter==0){
            printf("can't redo more\n");
            return (f_turn(turn));
        }
        redo_counter=redo(turn,redo_counter,&counter);
        return turn;
    }

    else if((input[0]=='R' && input[1]=='A' && input[2]=='L' && input[3]=='L') || (input[0]=='r' && input[1]=='a' && input[2]=='l' && input[3]=='l')){
        if(redo_counter==0){
            printf("can't redo more\n");
            return (f_turn(turn));
        }
        turn=redoAll(turn,redo_counter,&counter);
        redo_counter=0;
        return (f_turn(turn));
    }

    else{
    undo_arr[counter][0]=input[0];
    undo_arr[counter][1]=input[1];
    undo_arr[counter][2]=input[2];
    undo_arr[counter][3]=input[3];
    x=check_x(input[0]);
    x1=check_x(input[2]);
    y=check_y(input[1]);
    y1=check_y(input[3]);
    n=check_x(input[4]);
    if(turn==1){
        if(board[y][x]=='p'){
        v=pawn(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            right2=0,left2=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-')
            {
                counter++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed2[counter2]=board[y1][x1];
                counter2++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }

        }
        else if(v==2)
        {
                redo_counter=0;
                turn=promotion1(x,y,x1,y1,turn,n);
        }
        else if(v==3)
        {
            redo_counter=0;
            undo_arr[counter][4]=board[y][x+1];
            undo_arr[counter][6]=1;
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            killed2[counter2]=board[y][x+1];
            counter2++;
            checkboard(x+1,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            right2=0;
        }
        else if(v==4)
        {
            redo_counter=0;
            undo_arr[counter][4]=board[y][x-1];
            undo_arr[counter][6]=2;
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            killed2[counter2]=board[y][x-1];
            counter2++;
            checkboard(x-1,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            left2=0;
        }
    }
    else if(board[y][x]=='r'){
        v=rook(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            right2=0,left2=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            if(y==9 && x==9)
               rook_move11++;
            else if(y==9 && x==2)
               rook_move12++;
            print_board();
            find(turn);
            }
            else {
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed2[counter2]=board[y1][x1];
                counter2++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                if(y==9 && x==9)
                     rook_move11++;
                else if(y==9 && x==2)
                     rook_move12++;
                print_board();
                find(turn);
            }
        }
    }

    else if(board[y][x]=='n'){
        v=knight(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            right2=0,left2=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed2[counter2]=board[y1][x1];
                counter2++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
    }

    else if(board[y][x]=='b'){
        v=bishop(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            right2=0,left2=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed2[counter2]=board[y1][x1];
                counter2++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
    }

    else if(board[y][x]=='q'){
        v=queen(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            right2=0,left2=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed2[counter2]=board[y1][x1];
                counter2++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
    }

    else if(board[y][x]=='k'){
        v=king(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            right2=0,left2=0,redo_counter=0;
            king_move1++;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
                counter++;
                 board[y1][x1]=board[y][x];
                 checkboard(x,y);
                 if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                 print_board();
                 find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed2[counter2]=board[y1][x1];
                counter2++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
        else if(v==2)
        {
            right2=0,left2=0,redo_counter=0;
            counter++;
            king_move1++;
            board[y1][x1-1]=board[y][x];
            checkboard(x,y);
            board[y][x+1]=board[y1][x1];
            checkboard(x1,y1);
            print_board();
            find(turn);
        }
        else if(v==3)
        {
            right2=0,left2=0,redo_counter=0;
            counter++;
            king_move1++;
            board[y1][x-2]=board[y][x];
            checkboard(x,y);
            board[y][x-1]=board[y1][x1];
            checkboard(x1,y1);
            print_board();
            find(turn);
        }

    }
    else
    {
        printf("please enter a valid move\n");
        return (f_turn(turn));
    }
    }
    else if(turn==2)
    {
        if(board[y][x]=='P'){
        v=pawn(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            left1=0;right1=0,redo_counter=0;
            if(board[y1][x1]!='.' && board[y1][x1]!='-'){
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed1[counter1]=board[y1][x1];
                counter1++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
            else
            {
                counter++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
        else if(v==2)
        {
                redo_counter=0;
                turn=promotion2(x,y,x1,y1,turn,n);
        }
        else if(v==3)
        {
            redo_counter=0;
            undo_arr[counter][4]=board[y][x+1];
            undo_arr[counter][6]=1;
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            killed1[counter1]=board[y][x+1];
            counter1++;
            checkboard(x+1,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            left1=0;
        }
        else if(v==4)
        {
            redo_counter=0;
            undo_arr[counter][4]=board[y][x-1];
            undo_arr[counter][6]=2;
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            killed1[counter1]=board[y][x-1];
            counter1++;
            checkboard(x-1,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            right1=0;
        }
    }
    else if(board[y][x]=='R'){
        v=rook(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            left1=0;right1=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            if(y==2 && x==9)
                 rook_move21++;
            else if(y==2 && x==2)
                 rook_move22++;
            print_board();
            find(turn);
            }
            else {
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed1[counter1]=board[y1][x1];
                counter1++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                if(y==2 && x==9)
                 rook_move21++;
               else if(y==2 && x==2)
                 rook_move22++;
                print_board();
                find(turn);
            }
        }
    }

    else if(board[y][x]=='N'){
        v=knight(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            left1=0;right1=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed1[counter1]=board[y1][x1];
                counter1++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
    }

    else if(board[y][x]=='B'){
        v=bishop(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            left1=0;right1=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed1[counter1]=board[y1][x1];
                counter1++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
    }

    else if(board[y][x]=='Q'){
        v=queen(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            left1=0;right1=0,redo_counter=0;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed1[counter1]=board[y1][x1];
                counter1++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
    }

    else if(board[y][x]=='K'){
        v=king(x,y,x1,y1,turn);
        if(v==0)
        {
            printf("please enter a valid move\n");
            return (f_turn(turn));
        }
        else if(v==1)
        {
            left1=0;right1=0,redo_counter=0;
            king_move2++;
            if(board[y1][x1]=='.' || board[y1][x1]=='-'){
            counter++;
            board[y1][x1]=board[y][x];
            checkboard(x,y);
            if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
            print_board();
            find(turn);
            }
            else{
                undo_arr[counter][4]=board[y1][x1];
                counter++;
                killed1[counter1]=board[y1][x1];
                counter1++;
                board[y1][x1]=board[y][x];
                checkboard(x,y);
                if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }
                print_board();
                find(turn);
            }
        }
        else if(v==2)
        {
            left1=0;right1=0,redo_counter=0;
            counter++;
            king_move2++;
            board[y1][x1-1]=board[y][x];
            checkboard(x,y);
            board[y][x+1]=board[y1][x1];
            checkboard(x1,y1);
            print_board();
            find(turn);
        }
        else if(v==3)
        {
            left1=0;right1=0,redo_counter=0;
            counter++;
            king_move2++;
            board[y1][x-2]=board[y][x];
            checkboard(x,y);
            board[y][x-1]=board[y1][x1];
            checkboard(x1,y1);
            print_board();
            find(turn);
        }
    }

    else
    {
        printf("please enter a valid move\n");
        return (f_turn(turn));
    }
    }
    }
    return turn;
}


//// function (f_turn) is used to reverse the trun.
int f_turn(int turn)
{
    if(turn==1){
        turn=2;
    }
    else if(turn==2){
        turn=1;
    }
    return turn;
}

//// function (print_board) is used to print the board and the taken out from the both players.
void print_board()
{
    int a=0;
    printf("\n");
    for(int h=0;h<12;h++)
    {
        printf("\t\t\t\t\t\t");
        for(int k=0;k<12;k++)
        {
            printf("%c ",board[h][k]);
        }
        if(h==2){
            printf("  taken from player 2: ");
            for(a=0;a<counter2;a++){
                printf("%c, ",killed2[a]);
                if(a==3)
                    break;
            }
        }
        if(h==3 && a==3){
                printf("   ");
                for(a=4;a<counter2;a++)
                    printf("%c, ",killed2[a]);
            }
        if(h==7)
            {
                printf("  taken from player 1: ");
                for(a=0;a<counter1;a++){
                    printf("%c, ",killed1[a]);
                    if(a==3)
                    break;
                }
            }
            if(h==8 && a==3){
                printf("   ");
                for(a=4;a<counter1;a++)
                    printf("%c, ",killed1[a]);
            }
        printf("\n");
    }
}

//// function (check_x) is used to convert the char letters(the x_axis of the board) to numbers(int) so we can deal with.
int check_x(int f)
{
    int x;
    if(f=='A' || f=='a')
        x=2;
    else if(f=='B' || f=='b')
        x=3;
    else if(f=='C' || f=='c')
        x=4;
    else if(f=='D' || f=='d')
        x=5;
    else if(f=='E' || f=='e')
        x=6;
    else if(f=='F' || f=='f')
        x=7;
    else if(f=='G' || f=='g')
        x=8;
    else if(f=='H' || f=='h')
        x=9;
    else if(f=='Q' || f=='q')
        x=10;
    else if(f=='R' || f=='f')
        x=12;
    else if(f=='N' || f=='n')
        x=13;
    else
        return 0;

    return x;
}


//// function (check_y) is used to convert the char numbers(the y_axis of the board) to numbers(int) so we can deal with.
int check_y(int y)
{
    int a;
    if(y=='1')
        a=9;
    else if(y=='2')
        a=8;
    else if(y=='3')
        a=7;
    else if(y=='4')
        a=6;
    else if(y=='5')
        a=5;
    else if(y=='6')
        a=4;
    else if(y=='7')
        a=3;
    else if(y=='8')
        a=2;
    else
        return 0;

    return a;
}



//////PAWN/////
//// check the move is valid or not (it includes en passent capture and the validation of the promotion) and return value depends on the move.
int pawn(int x,int y,int x1,int y1,int turn){
	int a=0;
	if(turn==2){
        if(right1==1)
        {
             if(y1==y+1 && x1==x-1 && (board[y1][x1]=='.' || board[y1][x1]=='-') && board[y][x-1]=='p')
                a=4;
        }
        if(left1==1){
            if(y1==y+1 && x1==x+1 && (board[y1][x1]=='.' || board[y1][x1]=='-') && board[y][x+1]=='p')
                a=3;
        }
		if(y==3){
		  if(y1==(y+2) && x1==x){
		     if((board[y1][x1]=='.' || board[y1][x1]=='-') && (board[y+1][x]=='.' || board[y+1][x]=='-')){
				a = 1;
				if(board[y1][x-1]=='p')
                    right2=1;
                else if(board[y1][x+1]=='p')
                    left2=1;
			   }
			}
			}
		 if(y1==y+1 && x1==x){
			if(board[y1][x1]=='.' || board[y1][x1]=='-')
				a = 1;
			 }
	   else if(y1==(y+1) && (x1==(x+1)||x1==(x-1))){
		   if( board[y1][x1]=='r' || board[y1][x1]=='n' || board[y1][x1]=='b' || board[y1][x1]=='q' || board[y1][x1]=='p' )
			 a = 1;
		  }
		}
	  else if(turn==1){
        if(right2==1)
        {
            if(y1==y-1 && x1==x+1 && (board[y1][x1]=='.' || board[y1][x1]=='-') && board[y][x+1]=='P')
                a=3;
        }
        if(left2==1){
             if(y1==y-1 && x1==x-1 && (board[y1][x1]=='.' || board[y1][x1]=='-') && board[y][x-1]=='P')
                a=4;
        }
		if(y==8){
		   if( y1==(y-2) && x1==x){
			if((board[y1][x1]=='.' || board[y1][x1]=='-') && (board[y-1][x]=='.' || board[y-1][x]=='-')){
				a = 1;
				if(board[y1][x+1]=='P')
                    right1=1;
                else if(board[y1][x-1]=='P')
                    left1=1;
			   }
			}
            }
		  if( y1==(y-1) && x1==x){
			if(board[y1][x1]=='.' || board[y1][x1]=='-')
				a = 1;
			 }
	   else if(y1==(y-1) && (x1==(x-1)||x1==(x+1))){
		   if( board[y1][x1]=='R' || board[y1][x1]=='N' || board[y1][x1]=='B' || board[y1][x1]=='Q' || board[y1][x1]=='P' )
			 a = 1;
		  }
	 }
   if(a==1)
   {
     if(turn==1)
     {
	 if(y1==2)
	    return 2;
     }
     else if(turn==2)
     {
	 if(y1==9)
	    return 2;
     }
    }

 return a;
}


//// function (checkboard) it's only used for display the '.' (black squares) and '-' (white squares).
void checkboard (int x,int y)
{
    if(y%2==1 && x%2==0)
        board[y][x]='.';
    else if(y%2==0 && x%2==0)
        board[y][x]='-';
    else if(y%2==1 && y%2==1)
        board[y][x]='-';
    else if(y%2==0 && x%2==1)
        board[y][x]='.';
}


///// function (promotion1) is used to promote the pawn for player 1.
int promotion2(int x,int y,int x1,int y1,int turn,int n)
{
    switch(n)
        {
        case 10: if(board[y1][x1]!='.' && board[y1][x1]!='-'){
                  undo_arr[counter][4]=board[y1][x1];
                killed1[counter1]=board[y1][x1];
                counter1++;
        }
        board[y1][x1]='Q'; undo_arr[counter][5]='Q'; counter++; checkboard(x,y); if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                } print_board(); find(turn); return turn;
        case 3: if(board[y1][x1]!='.' && board[y1][x1]!='-'){
                  undo_arr[counter][4]=board[y1][x1];
                killed1[counter1]=board[y1][x1];
                counter1++;
        }
            board[y1][x1]='B'; undo_arr[counter][5]='B'; counter++; checkboard(x,y); if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                } print_board(); find(turn); return turn;
        case 13: if(board[y1][x1]!='.' && board[y1][x1]!='-'){
                  undo_arr[counter][4]=board[y1][x1];
                killed1[counter1]=board[y1][x1];
                counter1++;
        }
            board[y1][x1]='N'; undo_arr[counter][5]='N'; counter++; checkboard(x,y); if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                } print_board(); find(turn); return turn;
        case 12:
            if(board[y1][x1]!='.' && board[y1][x1]!='-'){
                  undo_arr[counter][4]=board[y1][x1];
                killed1[counter1]=board[y1][x1];
                counter1++;
        }board[y1][x1]='R'; undo_arr[counter][5]='R'; counter++; checkboard(x,y); if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                } print_board(); find(turn); return turn;
        default : printf("enter a valid character to promote\n"); return(f_turn(turn));
        }
}


///// function (promotion2) is used to promote the pawn for player 2.
int promotion1(int x,int y,int x1,int y1,int turn,int n)
{
    switch(n)
        {
        case 10: if(board[y1][x1]!='.' && board[y1][x1]!='-'){
            undo_arr[counter][4]=board[y1][x1];
                killed2[counter2]=board[y1][x1];
                counter2++;
        }
            board[y1][x1]='q'; undo_arr[counter][5]='q'; counter++; checkboard(x,y); if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                } print_board(); find(turn); return turn;
        case 3: if(board[y1][x1]!='.' && board[y1][x1]!='-'){
            undo_arr[counter][4]=board[y1][x1];
                killed2[counter2]=board[y1][x1];
                counter2++;
        }
            board[y1][x1]='b'; undo_arr[counter][5]='b'; counter++; checkboard(x,y); if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                } print_board(); find(turn); return turn;
        case 13: if(board[y1][x1]!='.' && board[y1][x1]!='-'){
            undo_arr[counter][4]=board[y1][x1];
                killed2[counter2]=board[y1][x1];
                counter2++;
        }
             board[y1][x1]='n'; undo_arr[counter][5]='n'; counter++; checkboard(x,y);if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                }  print_board(); find(turn); return turn;
        case 12: if(board[y1][x1]!='.' && board[y1][x1]!='-'){
            undo_arr[counter][4]=board[y1][x1];
                killed2[counter2]=board[y1][x1];
                counter2++;
        }
            board[y1][x1]='r'; undo_arr[counter][5]='r'; counter++; checkboard(x,y); if(protect(turn)){
                    printf("enter a valid move\n");
                    undoProtect(turn);
                    return (f_turn(turn));
                } print_board(); find(turn); return turn;
        default : printf("please enter a valid character to promote\n"); return(f_turn(turn));
        }
}


////knight//////
//// check the move is valid or not.
int knight(int x,int y,int x1,int y1,int turn)
{
	int a=0;
	if(turn==1){
        if((y1==y+2 && x1==x+1)||(y1==y+2 && x1==x-1)||(y1==y+1 && x1==x+2)||(y1==y+1 && x1==x-2)||(y1==y-1 && x1==x+2)||(y1==y-1 && x1==x-2)||(y1==y-2 && x1==x+1)||(y1==y-2 && x1==x-1)){
                if(board[y1][x1]=='.' || board[y1][x1]=='-' ||  board[y1][x1]=='R' || board[y1][x1]=='N' || board[y1][x1]=='B' || board[y1][x1]=='Q' || board[y1][x1]=='P')
		              a = 1;
		}
	}
	else if(turn==2){
        if((y1==y+2 && x1==x+1)||(y1==y+2 && x1==x-1)||(y1==y+1 && x1==x+2)||(y1==y+1 && x1==x-2)||(y1==y-1 && x1==x+2)||(y1==y-1 && x1==x-2)||(y1==y-2 && x1==x+1)||(y1==y-2 && x1==x-1)){
                if(board[y1][x1]=='.' || board[y1][x1]=='-' || board[y1][x1]=='r' || board[y1][x1]=='n' || board[y1][x1]=='b' || board[y1][x1]=='q' || board[y1][x1]=='p')
		             a = 1;
		}
	}


	return a;
}



/////KING////
//// check the move is valid or not(include the castling).
int king(int x,int y,int x1,int y1,int turn)
{
     int a = 0;
     if((y1==y+1 && x1==x) || (y1==y+1 && x1==x+1) || (y1==y+1 && x1==x-1) ){
         if(turn==1){
             if(board[y1][x1]=='p' || board[y1][x1]=='b' || board[y1][x1]=='r' || board[y1][x1]=='q' || board[y1][x1]=='n')
                  return 0;
             else if(board[y1+1][x1]!='K' && board[y1+1][x1-1]!='K' && board[y1+1][x1+1]!='K')
                    a=1;
               }
        else if(turn==2){
            if(board[y1][x1]=='P' || board[y1][x1]=='B' || board[y1][x1]=='R' || board[y1][x1]=='Q' || board[y1][x1]=='N')
                  return 0;
            else if(board[y1+1][x1]!='k' && board[y1+1][x1-1]!='k' && board[y1+1][x1+1]!='k')
                    a=1;
         }
     }
    else if((y1==y-1 && x1==x) ||(y1==y-1 && x1==x+1)||(y1==y-1 && x1==x-1)){
             if(turn==1){
                if(board[y1][x1]=='p' || board[y1][x1]=='b' || board[y1][x1]=='r' || board[y1][x1]=='q' || board[y1][x1]=='n')
                  return 0;
                else if(board[y1-1][x1]!='K' && board[y1-1][x1-1]!='K' && board[y1-1][x1+1]!='K')
                       a=1;
             }
             else if(turn==2){
                if(board[y1][x1]=='P' || board[y1][x1]=='B' || board[y1][x1]=='R' || board[y1][x1]=='Q' || board[y1][x1]=='N')
                  return 0;
                else if(board[y1-1][x1]!='k' && board[y1-1][x1-1]!='k' && board[y1-1][x1+1]!='k')
                       a=1;
             }
         }
         else if(y1==y && x1==x+1){
            if(turn==1){
                if(board[y1][x1]=='p' || board[y1][x1]=='b' || board[y1][x1]=='r' || board[y1][x1]=='q' || board[y1][x1]=='n')
                  return 0;
                else if(board[y1][x1+1]!='K' && board[y1+1][x1+1]!='K' && board[y1-1][x1+1]!='K')
                       a=1;
             }
             else if(turn==2){
                if(board[y1][x1]=='P' || board[y1][x1]=='B' || board[y1][x1]=='R' || board[y1][x1]=='Q' || board[y1][x1]=='N')
                  return 0;
                else if(board[y1][x1+1]!='k' && board[y1-1][x1+1]!='k' && board[y1+1][x1+1]!='k')
                       a=1;
             }
         }
         else if(y1==y && x1==x-1){
                if(turn==1){
                   if(board[y1][x1]=='p' || board[y1][x1]=='b' || board[y1][x1]=='r' || board[y1][x1]=='q' || board[y1][x1]=='n')
                      return 0;
                   else if(board[y1][x1-1]!='K' && board[y1+1][x1-1]!='K' && board[y1-1][x1-1]!='K')
                       a=1;
             }
             else if(turn==2){
                 if(board[y1][x1]=='P' || board[y1][x1]=='B' || board[y1][x1]=='R' || board[y1][x1]=='Q' || board[y1][x1]=='N')
                    return 0;
                 else if(board[y1][x1-1]!='k' && board[y1-1][x1-1]!='k' && board[y1+1][x1-1]!='k')
                       a=1;
             }
         }

   /////CASTLING//////

     else{
        if(turn==1){
            if(king_move1==0 && rook_move11==0 && y==9 && y1==9 && (board[y][x+1]=='.' || board[y][x+1]=='-') && (board[y][x+2]=='.' || board[y][x+2]=='-')
               && board[y1][x1]=='r' && board[y][x+3]=='r' && castling_check('k',y,x)==false && castling_check('k',y,x+1)==false && castling_check('k',y,x+2)==false )
                    a=2;

            else if(king_move1==0 && rook_move12==0 && y==9 && y1==9 && (board[y][x-1]=='.' || board[y][x-1]=='-') && (board[y][x-2]=='.' || board[y][x-2]=='-') && (board[y][x-3]=='.' || board[y][x-3]=='-' )
                    && board[y1][x1]=='r' && board[y][x-4]=='r' && castling_check('k',y,x)==false && castling_check('k',y,x-2)==false && castling_check('k',y,x-1)==false )
                    a=3;


        }
        else if(turn==2)
        {
            if(king_move2==0 && rook_move21==0 && y==2 && y1==2 && (board[y][x+1]=='.' || board[y][x+1]=='-') && (board[y][x+2]=='.' || board[y][x+2]=='-') && board[y1][x1]=='R'
               && board[y][x+3]=='R' && castling_check('K',y,x)==false && castling_check('K',y,x+1)==false && castling_check('K',y,x+2)==false )
                    a=2;
            else if(king_move2==0 && rook_move22==0 && y==2 && y1==2 && (board[y][x-1]=='.' || board[y][x-1]=='-') && (board[y][x-2]=='.' || board[y][x-2]=='-') && (board[y][x-3]=='.' || board[y][x-3]=='-' )
                        && board[y1][x1]=='R' && board[y][x-4]=='R' && castling_check('K',y,x)==false && castling_check('K',y,x-2)==false && castling_check('K',y,x-1)==false )
                    a=3;
     }
     }

    return a;

}


//////BISHOP/////
//// check the move is valid or not.
int bishop(int x,int y,int x1,int y1,int turn)
{
		int h;
		if(abs(x1-x)!=abs(y1-y))
			return 0;
        else if(turn==1){
            if(board[y1][x1]=='p' || board[y1][x1]=='b' || board[y1][x1]=='r' || board[y1][x1]=='q' || board[y1][x1]=='k' || board[y1][x1]=='n')
                  return 0;
            else if((x<x1) && (y<y1))
		    {
			for(h=1;(h+x)<x1;h++)
			{
				 if(board[y+h][x+h]!='.' && board[y+h][x+h]!='-')
				    return 0;
			}
		    }

       else if((x>x1)&&(y>y1)){
	       for(h=1;(x-h)>x1;h++){
	           if(board[y-h][x-h]!='.' && board[y-h][x-h]!='-')
	              return 0;
            }
        }
	    else if((x>x1)&&(y<y1)){
	        for(h=1;(x-h)>x1;h++){
                if(board[y+h][x-h]!='.' && board[y+h][x-h]!='-')
	                 return 0;
	        }
	    }
	    else if((x<x1)&&(y>y1)){
	        for(h=1;(y-h)>y1;h++){
                if(board[y-h][x+h]!='.' && board[y-h][x+h]!='-')
	                return 0;
	        }
        }
        }
        else if(turn==2){
            if(board[y1][x1]=='P' || board[y1][x1]=='B' || board[y1][x1]=='R' || board[y1][x1]=='Q' || board[y1][x1]=='K' || board[y1][x1]=='N')
                  return 0;
            else if((x<x1)&&(y<y1)){
			for(h=1;(h+x)<x1;h++)
			{
				 if(board[y+h][x+h]!='.' && board[y+h][x+h]!='-')
				     return 0;
			}
		}

       else if((x>x1)&&(y>y1)){
	       for(h=1;(x-h)>x1;h++){
	           if(board[y-h][x-h]!='.' && board[y-h][x-h]!='-')
	                return 0;
	        }
        }
	    else if((x>x1)&&(y<y1)){
	        for(h=1;(x-h)>x1;h++){
                if(board[y+h][x-h]!='.' && board[y+h][x-h]!='-')
	                 return 0;
	        }
	    }
	    else if((x<x1)&&(y>y1)){
	        for(h=1;(y-h)>y1;h++){
                if(board[y-h][x+h]!='.' && board[y-h][x+h]!='-')
	                  return 0;
	        }
        }
        }
	return 1;
}


////ROOK///
//// check the move is valid or not.
int rook(int x,int y,int x1,int y1,int turn){
	int h;
	if(turn==1){
        if(board[y1][x1]=='p' || board[y1][x1]=='b' || board[y1][x1]=='r' || board[y1][x1]=='q' || board[y1][x1]=='k' || board[y1][x1]=='n')
                  return 0;
        else if(y1==y){
	    if(x1>x){
		for(h=x+1;h<x1;h++){
			if(board[y1][h]!='.' && board[y1][h]!='-')
				return 0;
		}
	    }
	    else if(x1<x){
		for(h=x-1;h>x1;h--){
			if(board[y1][h]!='.' && board[y1][h]!='-')
			return 0;
		}
	    }
        }
	   else if(x1==x){
	    if(y1>y){
		for(h=y+1;h<y1;h++){
			if(board[h][x1]!='.' && board[h][x1]!='-')
			return 0;
		}
	    }
	    else if(y1<y){
		for(h=y-1;h>y1;h--){
			if(board[h][x1]!='.' && board[h][x1]!='-')
			   return 0;
		}
	    }
	}
	else
        return 0;
	}
	else if(turn==2){
        if(board[y1][x1]=='P' || board[y1][x1]=='B' || board[y1][x1]=='R' || board[y1][x1]=='Q' || board[y1][x1]=='K' || board[y1][x1]=='N')
                  return 0;
        else if(y1==y){
	    if(x1>x){
		for(h=x+1;h<x1;h++){
			if(board[y1][h]!='.' && board[y1][h]!='-' )
			    return 0;
		}
	    }
	    else if(x1<x){
		for(h=x-1;h>x1;h--){
			if(board[y1][h]!='.' && board[y1][h]!='-' )
	            return 0;
		}
	    }
        }

	else if(x1==x){
	    if(y1>y){
		for(h=y+1;h<y1;h++){
			if(board[h][x1]!='.' && board[h][x1]!='-')
		         return 0;
		}
	    }
	    else if(y1<y){
		for(h=y-1;h>y1;h--){
			if(board[h][x1]!='.' && board[h][x1]!='-' )
		        return 0;
		}
	    }
	}
	else
        return 0;
    }
	return 1;
}



////////QUEEN///////
//// check the move is valid or not.
int queen(int x,int y,int x1,int y1,int turn){
   if(x==x1||y==y1){
  //if queen moves in + direction
	 return rook(x,y,x1,y1,turn);
   }
   else if(abs(x1-x)==abs(y-y1)){
  //if queen moves in diagonal direction
	 return bishop(x,y,x1,y1,turn);
   }
   else
	 return 0;
}


///// function (pawncheck) is used to check if the pawn cause a check for the opposite player or not.
bool pawncheck(int i,int j,char pawnplace,int turn){
    if(turn==2){
    if(board[i+1][j-1]==pawnplace||board[i+1][j+1]==pawnplace){
        return true;
    }
    return false;
    }

    else if(turn==1){
        if(board[i-1][j-1]==pawnplace||board[i-1][j+1]==pawnplace){
        return true;
    }
    return false;
    }
}

///// function (bishopcheck) is used to check if the bishop cause a check for the opposite player or not.
int bishopcheck(int i,int j,char bishopplace ,char queenplace,int turn){
        int k,m;
        int a=0;
            for(m=j+1,k=i-1;m<10,k>1;m++,k--){
                if(board[k][m]==bishopplace)
                    a=1;
                else if(board[k][m]==queenplace)
                    a=2;
                else if((board[k][m]>'a'&&board[k][m]<'z')||(board[k][m]>'A'&&board[k][m]<'Z'))
                    break;
            }

            for(m=j-1,k=i+1;m>2,k<10;m--,k++){
                if(board[k][m]==bishopplace)
                    a=1;
                else if(board[k][m]==queenplace)
                    a=2;
                else if((board[k][m]>'a'&&board[k][m]<'z')||(board[k][m]>'A'&&board[k][m]<'Z'))
                    break;
            }

            for(m=j-1,k=i-1;m>1,k>1;m--,k--){
                if(board[k][m]==bishopplace)
                    a=1;
                else if(board[k][m]==queenplace)
                    a=2;
                else if((board[k][m]>'a'&&board[k][m]<'z')||(board[k][m]>'A'&&board[k][m]<'Z'))
                    break;
            }

            for(m=j+1,k=i+1;m<10,k<10;m++,k++){
                if(board[k][m]==bishopplace)
                    a=1;
                else if(board[k][m]==queenplace)
                    a=2;
                else if((board[k][m]>'a'&&board[k][m]<'z')||(board[k][m]>'A'&&board[k][m]<'Z'))
                    break;
            }
        return a;
}


///// function (rookcheck) is used to check if the rook cause a check for the opposite player or not.
int rookcheck(int i,int j,char rookplace,char queenplace,int turn){
    int a=0;
        for(int k=i+1;k<10;k++){
            if(board[k][j]==rookplace)
                a=1;
            else if(board[k][j]==queenplace)
                a=2;
            else if((board[k][j]>'a'&&board[k][j]<'z')||(board[k][j]>'A'&&board[k][j]<'Z'))
                break;
    }
    for( int k=j+1;k<10;k++){
            if(board[i][k]==rookplace)
                a=1;
            else if(board[i][k]==queenplace)
                a=2;
            else if((board[i][k]>'a'&&board[i][k]<'z')||(board[i][k]>'A'&&board[i][k]<'Z'))
                break;
    }
    for(int k=i-1;k>1;k--){
            if(board[k][j]==rookplace)
                a=1;
            else if(board[k][j]==queenplace)
                a=2;
            else if((board[k][j]>'a'&&board[k][j]<'z')||(board[k][j]>'A'&&board[k][j]<'Z'))
                break;
    }
     for( int k=j-1;k>1;k--){
            if(board[i][k]==rookplace)
                a=1;
            else if(board[i][k]==queenplace)
                a=2;
            else if((board[i][k]>'a'&&board[i][k]<'z')||(board[i][k]>'A'&&board[i][k]<'Z'))
                break;
     }
     return a;
}


///// function (knightcheck) is used to check if the knight cause a check for the opposite player or not.
bool knightcheck(int i,int j,char knightplace,int turn){
    if(board[i+1][j+2]==knightplace){
        return true;
    }
    else if(board[i-1][j+2]==knightplace){
        return true;
    }
    else if(board[i+1][j-2]==knightplace){
        return true;
    }
    else if(board[i-1][j-2]==knightplace){
        return true;
    }
    else if(board[i+2][j+1]==knightplace){
        return true;
    }
    else if(board[i+2][j-1]==knightplace){
        return true;
    }
    else if(board[i-2][j+1]==knightplace){
        return true;
    }
    else if(board[i-2][j-1]==knightplace){
        return true;
    }
    else{
        return false;
    }
}


///// function (check) is used to determine if there check or not.
bool check(char kingplace,int i,int j,int turn){

if(kingplace=='k'){
    rookplace='R';
    knightplace='N';
    bishopplace='B';
    queenplace='Q';
    Kingplace='K';
    pawnplace='P';
}
else if(kingplace=='K'){
    rookplace='r';
    knightplace='n';
    bishopplace='b';
    queenplace='q';
    Kingplace='k';
    pawnplace='p';
}
if(knightcheck(i,j,knightplace,turn) == true)
    printf("check by knight by player %d\n",turn);

if(rookcheck(i,j,rookplace,queenplace,turn) == 1)
    printf("check by rook by player %d\n",turn);

if(rookcheck(i,j,rookplace,queenplace,turn)== 2)
    printf("check by queen by player %d\n",turn);

if(bishopcheck(i,j,bishopplace,queenplace,turn)== 1)
    printf("check by bishop by player %d\n",turn);

if(bishopcheck(i,j,bishopplace,queenplace,turn)== 2)
    printf("check by queen by player %d\n",turn);

if(pawncheck(i,j,pawnplace,turn)== true)
    printf("check by pawn by player %d\n",turn);

if( rookcheck(i,j,rookplace,queenplace,turn)==1 || rookcheck(i,j,rookplace,queenplace,turn)==2 || knightcheck(i,j,knightplace,turn) ==true
   || bishopcheck(i,j,bishopplace,queenplace,turn)==1 || bishopcheck(i,j,bishopplace,queenplace,turn)==2 || pawncheck(i,j,pawnplace,turn)==true){
    return true;
}

if( rookcheck(i,j,rookplace,queenplace,turn)==0 && knightcheck(i,j,knightplace,turn) ==false && bishopcheck(i,j,bishopplace,queenplace,turn)==0 && pawncheck(i,j,pawnplace,turn)==false){
    return false;
}
}

///// function (castling_check) is used determine the king is checked or the place he passes over or the place it will stay in is.
///// it used in the condition of castling.
bool castling_check(char kingplace,int i,int j){


if(kingplace=='k'){
    rookplace='R';
    knightplace='N';
    bishopplace='B';
    queenplace='Q';
    Kingplace='K';
    pawnplace='P';
}
else if(kingplace=='K'){
    rookplace='r';
    knightplace='n';
    bishopplace='b';
    queenplace='q';
    Kingplace='k';
    pawnplace='p';
}
if(knightcheck(i,j,knightplace,turn) == true)
    return true;


if(rookcheck(i,j,rookplace,queenplace,turn) != 0)
    return true;


if(bishopcheck(i,j,bishopplace,queenplace,turn)!= 0)
    return true;


if(pawncheck(i,j,pawnplace,turn)== true)
    return true;


if( rookcheck(i,j,rookplace,queenplace,turn)==0 && knightcheck(i,j,knightplace,turn) ==false && bishopcheck(i,j,bishopplace,queenplace,turn)==0 && pawncheck(i,j,pawnplace,turn)==false)
    return false;

}


///// function (find) is used to determine the place of the opposite player's king then pass this place to function check to check if there check or not.
bool find(int turn){
    char kingplace ;
    if(turn==1){
    kingplace='K';
    }
    else if(turn==2){
    kingplace ='k';
    }
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){

           if(board[i][j] == kingplace){
            return check(kingplace,i,j,turn);
           }
        }
    }
}


///// function (protect) is used to determine the place of the player's king then pass this place to function check to check if there check or not.
bool protect(int turn){
    char kingplace ;
    if(turn==2){
    kingplace='K';
    }
    else if(turn==1){
    kingplace ='k';
    }
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){

           if(board[i][j] == kingplace){
            return castling_check(kingplace,i,j);
           }
        }
    }
}


///// function (save) is used to save the game at any time.
void save(int turn){
char savedfile[100];
int k=0,m=0;
FILE *sf;
sf=fopen("savedfile.txt","w");
for(k=0;k<12;k++){
    for(m=0;m<12;m++){
        fputc(board[k][m],sf);
    }
}
fprintf(sf,"\n");
for(int h=0;h<15;h++){
    fputc(killed1[h],sf);
}

for(int f=0;f<15;f++){
    fputc(killed2[f],sf);
}
fprintf(sf,"\n");
fprintf(sf,"%d",turn);
fprintf(sf,"\n");
fprintf(sf,"%d",king_move1);
fprintf(sf,"\n");
fprintf(sf,"%d",king_move2);
fprintf(sf,"\n");
fprintf(sf,"%d",rook_move11);
fprintf(sf,"\n");
fprintf(sf,"%d",rook_move12);
fprintf(sf,"\n");
fprintf(sf,"%d",rook_move21);
fprintf(sf,"\n");
fprintf(sf,"%d",rook_move22);
fprintf(sf,"\n");
fprintf(sf,"%d",right1);
fprintf(sf,"\n");
fprintf(sf,"%d",right2);
fprintf(sf,"\n");
fprintf(sf,"%d",left1);
fprintf(sf,"\n");
fprintf(sf,"%d",left2);
fprintf(sf,"\n");
fprintf(sf,"%d",counter1);
fprintf(sf,"\n");
fprintf(sf,"%d",counter2);



fclose(sf);
printf("The game is saved successfully\n");
}


///// function (load) is used to load the saved game at any time.
int load(int turn){
char a,load[256];
char undoo[256],redoo[256];
int k=0,m=0,c=0,h,t=0,g=0;
FILE *sf;
sf=fopen("savedfile.txt","r");
if(sf==NULL){
    printf("there is no saved game to load\n");
    return turn;
}

else{
fgets(load,256,sf);
for(k=0;k<12;k++){
    for(m=0;m<12;m++){
        board[k][m]=load[c++];
    }
}
for(int h=0;h<15;h++){
    fscanf(sf,"%c,",&killed1[h]);
}
for(int f=0;f<15;f++){
    fscanf(sf,"%c,",&killed2[f]);
}

fscanf(sf,"%d",&turn);
fscanf(sf,"%d",&king_move1);
fscanf(sf,"%d",&king_move2);
fscanf(sf,"%d",&rook_move11);
fscanf(sf,"%d",&rook_move12);
fscanf(sf,"%d",&rook_move21);
fscanf(sf,"%d",&rook_move22);
fscanf(sf,"%d",&right1);
fscanf(sf,"%d",&right2);
fscanf(sf,"%d",&left1);
fscanf(sf,"%d",&left2);
fscanf(sf,"%d",&counter1);
fscanf(sf,"%d",&counter2);


fclose(sf);
print_board();
printf("The game is loaded successfully\n");
return turn;
}
}

///// function (readLine) is used to read the move from user(like b2b3) and it works for CAPITAL or small letters.
void readLine(char str[], int n)
{
int ch, a=0;
    while((ch=getchar()) != '\n')
    {
        if(a<n)
         {
           str[a++]=ch;
         }
    }
    str[a]='\0';
}

///// function (undo) is used to go to the previous  move.
int undo(int turn,int counter,int *redo_counter)
{
    int x,y,x1,y1;
    counter--;
    redo_arr[(*redo_counter)][0]=undo_arr[counter][0];
    redo_arr[(*redo_counter)][1]=undo_arr[counter][1];
    redo_arr[(*redo_counter)][2]=undo_arr[counter][2];
    redo_arr[(*redo_counter)][3]=undo_arr[counter][3];
    redo_arr[(*redo_counter)][4]=undo_arr[counter][4];
    redo_arr[(*redo_counter)][5]=undo_arr[counter][5];
    redo_arr[(*redo_counter)][6]=undo_arr[counter][6];
    (*redo_counter)++;
    x1=check_x(undo_arr[counter][0]);
    y1=check_y(undo_arr[counter][1]);
    x=check_x(undo_arr[counter][2]);
    y=check_y(undo_arr[counter][3]);
    if(x1==6 && y1==9 && x==2 && y==9){
        board[9][6]='k';
        board[9][2]='r';
        checkboard(5,9);
        checkboard(4,9);
        king_move1=0;
        rook_move12=0;
        print_board();
    }
    else if(x1==6 && y1==9 && x==9 && y==9){
        board[9][6]='k';
        board[9][9]='r';
        checkboard(7,9);
        checkboard(8,9);
        king_move1=0;
        rook_move11=0;
        print_board();
    }
    else if(x1==6 && y1==2 && x==2 && y==2){
        board[2][6]='K';
        board[2][2]='R';
        checkboard(5,2);
        checkboard(4,2);
        king_move2=0;
        rook_move22=0;
        print_board();
    }
    else if(x1==6 && y1==2 && x==9 && y==2){
        board[2][6]='K';
        board[2][9]='R';
        checkboard(7,2);
        checkboard(8,2);
        king_move2=0;
        rook_move21=0;
        print_board();
    }
    else{
    if(board[y][x]=='k')
        king_move1--;
    if(board[y][x]=='K')
        king_move2--;
    if(board[y][x]=='r' && y1==9 && x1==9)
        rook_move11--;
    if(board[y][x]=='r' && y1==9 && x1==2)
        rook_move12--;
    if(board[y][x]=='R' && y1==2 && x1==9)
        rook_move21--;
    if(board[y][x]=='R' && y1==2 && x1==2)
        rook_move22--;
    board[y1][x1]=board[y][x];
    checkboard(x,y);
    if(undo_arr[counter][4]!=0){
        if(turn==1){
            board[y][x]=undo_arr[counter][4];
            counter1--;
        }
        else if(turn==2){
            board[y][x]=undo_arr[counter][4];
            counter2--;
        }
    }
    if(undo_arr[counter][5]!=0){
        if(turn==1){
            board[y1][x1]='P';
        }
        else if(turn==2){
            board[y1][x1]='p';
        }
    }
    if(undo_arr[counter][6]!=0){
            board[y1][x]=board[y][x];
            checkboard(x,y);
            if(turn==1){
                if(x1==x-1)
                    left1=1;
                else if(x1==x+1)
                    right1=1;
            }
            else if(turn==2){
                if(x1==x+1)
                    left2=1;
                else if(x1==x-1)
                    right2=1;
            }
    }
    print_board();
    }
    find(turn);
    return counter;
}

///// function (undoAll) is used to go to the beginning of the game.
int undoAll(int turn,int counter,int *redo_counter)
{
    int x,y,x1,y1;
    while(counter){
        counter--;
    redo_arr[(*redo_counter)][0]=undo_arr[counter][0];
    redo_arr[(*redo_counter)][1]=undo_arr[counter][1];
    redo_arr[(*redo_counter)][2]=undo_arr[counter][2];
    redo_arr[(*redo_counter)][3]=undo_arr[counter][3];
    redo_arr[(*redo_counter)][4]=undo_arr[counter][4];
    redo_arr[(*redo_counter)][5]=undo_arr[counter][5];
    redo_arr[(*redo_counter)][6]=undo_arr[counter][6];
    (*redo_counter)++;
    x1=check_x(undo_arr[counter][0]);
    y1=check_y(undo_arr[counter][1]);
    x=check_x(undo_arr[counter][2]);
    y=check_y(undo_arr[counter][3]);
    if(x1==6 && y1==9 && x==2 && y==9){
        board[9][6]='k';
        board[9][2]='r';
        checkboard(5,9);
        checkboard(4,9);
        king_move1=0;
        rook_move12=0;
    }
    else if(x1==6 && y1==9 && x==9 && y==9){
        board[9][6]='k';
        board[9][9]='r';
        checkboard(7,9);
        checkboard(8,9);
        king_move1=0;
        rook_move11=0;
    }
    else if(x1==6 && y1==2 && x==2 && y==2){
        board[2][6]='K';
        board[2][2]='R';
        checkboard(5,2);
        checkboard(4,2);
        king_move2=0;
        rook_move22=0;
    }
    else if(x1==6 && y1==2 && x==9 && y==2){
        board[2][6]='K';
        board[2][9]='R';
        checkboard(7,2);
        checkboard(8,2);
        king_move2=0;
        rook_move21=0;
    }
    else{
    board[y1][x1]=board[y][x];
    checkboard(x,y);
    if(undo_arr[counter][4]!=0){
        if(turn==1){
            board[y][x]=undo_arr[counter][4];
            counter1--;
        }
        else if(turn==2){
            board[y][x]=undo_arr[counter][4];
            counter2--;
        }
    }
    if(undo_arr[counter][5]!=0){
        if(turn==1){
            board[y1][x1]='P';
        }
        else if(turn==2){
            board[y1][x1]='p';
        }
    }
    if(undo_arr[counter][6]!=0){
            board[y1][x]=board[y][x];
            checkboard(x,y);
            if(turn==1){
                if(x1==x-1)
                    left1=1;
                else if(x1==x+1)
                    right1=1;
            }
            else if(turn==2){
                if(x1==x+1)
                    left2=1;
                else if(x1==x-1)
                    right2=1;
            }
    }
    }
    turn=f_turn(turn);
    }
    king_move1=0;
    king_move2=0;
    rook_move11=0;
    rook_move12=0;
    rook_move21=0;
    rook_move22=0;
    print_board();
    return counter;
}


///// function (redo) is used to go to the next move.
int redo(int turn,int redo_counter,int *counter)
{
    int x,y,x1,y1;
    redo_counter--;
    undo_arr[(*counter)][0]=redo_arr[redo_counter][0];
    undo_arr[(*counter)][1]=redo_arr[redo_counter][1];
    undo_arr[(*counter)][2]=redo_arr[redo_counter][2];
    undo_arr[(*counter)][3]=redo_arr[redo_counter][3];
    undo_arr[(*counter)][4]=redo_arr[redo_counter][4];
    undo_arr[(*counter)][5]=redo_arr[redo_counter][5];
    undo_arr[(*counter)][6]=redo_arr[redo_counter][6];
    (*counter)++;
    x=check_x(redo_arr[redo_counter][0]);
    y=check_y(redo_arr[redo_counter][1]);
    x1=check_x(redo_arr[redo_counter][2]);
    y1=check_y(redo_arr[redo_counter][3]);
    if(x==6 && y==9 && x1==2 && y1==9){
        board[9][4]='k';
        board[9][5]='r';
        checkboard(6,9);
        checkboard(2,9);
        king_move1=1;
        rook_move12=1;
        print_board();
    }
    else if(x==6 && y==9 && x1==9 && y1==9){
        board[9][8]='k';
        board[9][7]='r';
        checkboard(6,9);
        checkboard(9,9);
        king_move1=1;
        rook_move11=1;
        print_board();
    }
    else if(x==6 && y==2 && x1==2 && y1==2){
        board[2][4]='K';
        board[2][5]='R';
        checkboard(6,2);
        checkboard(2,2);
        king_move2=1;
        rook_move22=1;
        print_board();
    }
    else if(x==6 && y==2 && x1==9 && y1==2){
        board[2][8]='K';
        board[2][7]='R';
        checkboard(6,2);
        checkboard(9,2);
        king_move2=1;
        rook_move21=1;
        print_board();
    }
    else{
    if(turn==1){
        if(board[y][x]=='k')
                king_move1++;
        if(board[y][x]=='r' && y==9 && x==9)
                rook_move11++;
        if(board[y][x]=='r' && y==9 && x==2)
                rook_move12++;
        if(board[y1][x1]!='.' && board[y1][x1]!='-'){
            killed2[counter2]=board[y1][x1];
            counter2++;
        }
    }
    else if(turn==2)
    {
        if(board[y][x]=='K')
                king_move2++;
        if(board[y][x]=='R' && y==2 && x==9)
                rook_move21++;
        if(board[y][x]=='R' && y==2 && x==2)
                rook_move22++;
        if(board[y1][x1]!='.' && board[y1][x1]!='-'){
            killed1[counter1]=board[y1][x1];
            counter1++;
        }
    }
    if(redo_arr[redo_counter][6]==1){
            if(turn==1){
                killed2[counter2]=board[y][x+1];
                checkboard(x+1,y);
                counter2++;
                right2=0;

            }
            else if(turn==2){
                killed1[counter1]=board[y][x+1];
                checkboard(x+1,y);
                counter1++;
                left1=0;

            }
    }
    else if(redo_arr[redo_counter][6]==2){
        if(turn==1){
                killed2[counter2]=board[y][x-1];
                checkboard(x-1,y);
                counter2++;
                left2=0;

            }
            else if(turn==2){
                killed1[counter1]=board[y][x-1];
                checkboard(x-1,y);
                counter1++;
                right1=0;

            }
    }
    board[y1][x1]=board[y][x];
    if(redo_arr[redo_counter][5]!=0){
        board[y1][x1]=redo_arr[redo_counter][5];
    }
    checkboard(x,y);
    print_board();
    }
    find(turn);
    return redo_counter;

}


///// function (redoAll) is used to go to the end of the game.
int redoAll(int turn,int redo_counter,int *counter){
    int x,y,x1,y1;
    while(redo_counter){
        redo_counter--;
    undo_arr[(*counter)][0]=redo_arr[redo_counter][0];
    undo_arr[(*counter)][1]=redo_arr[redo_counter][1];
    undo_arr[(*counter)][2]=redo_arr[redo_counter][2];
    undo_arr[(*counter)][3]=redo_arr[redo_counter][3];
    undo_arr[(*counter)][4]=redo_arr[redo_counter][4];
    undo_arr[(*counter)][5]=redo_arr[redo_counter][5];
    undo_arr[(*counter)][6]=redo_arr[redo_counter][6];
    (*counter)++;
    x=check_x(redo_arr[redo_counter][0]);
    y=check_y(redo_arr[redo_counter][1]);
    x1=check_x(redo_arr[redo_counter][2]);
    y1=check_y(redo_arr[redo_counter][3]);
    if(x==6 && y==9 && x1==2 && y1==9){
        board[9][4]='k';
        board[9][5]='r';
        checkboard(6,9);
        checkboard(2,9);
        king_move1=1;
        rook_move12=1;
    }
    else if(x==6 && y==9 && x1==9 && y1==9){
        board[9][8]='k';
        board[9][7]='r';
        checkboard(6,9);
        checkboard(9,9);
        king_move1=1;
        rook_move11=1;
    }
    else if(x==6 && y==2 && x1==2 && y1==2){
        board[2][4]='K';
        board[2][5]='R';
        checkboard(6,2);
        checkboard(2,2);
        king_move2=1;
        rook_move22=1;
    }
    else if(x==6 && y==2 && x1==9 && y1==2){
        board[2][8]='K';
        board[2][7]='R';
        checkboard(6,2);
        checkboard(9,2);
        king_move2=1;
        rook_move21=1;
    }
    else{
    if(turn==1){
        if(board[y][x]=='k')
                king_move1++;
        if(board[y][x]=='r' && y==9 && x==9)
                rook_move11++;
        if(board[y][x]=='r' && y==9 && x==2)
                rook_move12++;
        if(board[y1][x1]!='.' && board[y1][x1]!='-'){
            killed2[counter2]=board[y1][x1];
            counter2++;
        }
    }
    else if(turn==2)
    {
        if(board[y][x]=='K')
                king_move2++;
        if(board[y][x]=='R' && y==2 && x==9)
                rook_move21++;
        if(board[y][x]=='R' && y==2 && x==2)
                rook_move22++;
        if(board[y1][x1]!='.' && board[y1][x1]!='-'){
            killed1[counter1]=board[y1][x1];
            counter1++;
        }
    }
    if(redo_arr[redo_counter][6]==1){
            if(turn==1){
                killed2[counter2]=board[y][x+1];
                checkboard(x+1,y);
                counter2++;
                right2=0;

            }
            else if(turn==2){
                killed1[counter1]=board[y][x+1];
                checkboard(x+1,y);
                counter1++;
                left1=0;

            }
    }
    else if(redo_arr[redo_counter][6]==2){
        if(turn==1){
                killed2[counter2]=board[y][x-1];
                checkboard(x-1,y);
                counter2++;
                left2=0;

            }
            else if(turn==2){
                killed1[counter1]=board[y][x-1];
                checkboard(x-1,y);
                counter1++;
                right1=0;

            }
    }
    board[y1][x1]=board[y][x];
    if(redo_arr[redo_counter][5]!=0){
        board[y1][x1]=redo_arr[redo_counter][5];
    }
    checkboard(x,y);
    }
    turn=f_turn(turn);
    }
    print_board();
    find(f_turn(turn));
    return turn;
}

//// to check if the move will result in check of the player's king of not we have to do the move to know first then undo this move and determine if it's valid or not.
//// so function (undoProtect) is used to undo the checked move.
void undoProtect(int turn)
{
    int x,y,x1,y1;
    counter--;
    x1=check_x(undo_arr[counter][0]);
    y1=check_y(undo_arr[counter][1]);
    x=check_x(undo_arr[counter][2]);
    y=check_y(undo_arr[counter][3]);
    board[y1][x1]=board[y][x];
    checkboard(x,y);
    if(undo_arr[counter][4]!=0){
        if(turn==1){
            board[y][x]=undo_arr[counter][4];
            counter1--;
        }
        else if(turn==2){
            board[y][x]=undo_arr[counter][4];
            counter2--;
        }
    }
    if(undo_arr[counter][5]!=0){
        if(turn==1){
            board[y1][x1]='p';
        }
        else if(turn==2){
            board[y1][x1]='p';
        }
    }

}

//// to know if the game is over or not we have to check all the possible moves.
//// so function (undoCheckFun) is used to undo the check possible moves.
void undoCheckFun(int turn,int countercheck)
{
    int x,y,x1,y1;
    countercheck--;
    x1=undoCheck[countercheck][0];
    y1=undoCheck[countercheck][1];
    x=undoCheck[countercheck][2];
    y=undoCheck[countercheck][3];
    board[y1][x1]=board[y][x];
    checkboard(x,y);
    if(undoCheck[countercheck][4]!=0)
        board[y][x]=undoCheck[countercheck][4];
    if(undoCheck[countercheck][5]!=0){
            board[y1][x]=undoCheck[countercheck][5];
            checkboard(x,y);
    }
}


//// function (pawn2) is used to determine if there are moves for the pawn or not.
int pawn2(int x,int y,int x1,int y1,int turn){
	if(turn==2){
        if(right1==1)
        {
             if(y1==y+1 && x1==x-1 && (board[y1][x1]=='.' || board[y1][x1]=='-') && board[y][x-1]=='p')
                return 1;
        }
        if(left1==1){
            if(y1==y+1 && x1==x+1 && (board[y1][x1]=='.' || board[y1][x1]=='-') && board[y][x+1]=='p')
                return 1;
        }
		if(y==3){
		  if(y1==(y+2) && x1==x){
		     if((board[y1][x1]=='.' || board[y1][x1]=='-') && (board[y+1][x]=='.' || board[y+1][x]=='-'))
				return 1;
			}
			}
		 if(y1==y+1 && x1==x){
			if(board[y1][x1]=='.' || board[y1][x1]=='-')
				return 1;
			 }
	   else if(y1==(y+1) && (x1==(x+1)||x1==(x-1))){
		   if( board[y1][x1]=='r' || board[y1][x1]=='n' || board[y1][x1]=='b' || board[y1][x1]=='q' || board[y1][x1]=='p' )
			 return 1;
		  }
		}
	  else if(turn==1){
        if(right2==1)
        {
            if(y1==y-1 && x1==x+1 && (board[y1][x1]=='.' || board[y1][x1]=='-') && board[y][x+1]=='P')
                return 1;
        }
        if(left2==1){
             if(y1==y-1 && x1==x-1 && (board[y1][x1]=='.' || board[y1][x1]=='-') && board[y][x-1]=='P')
                return 1;
        }
		if(y==8){
		   if( y1==(y-2) && x1==x){
			if((board[y1][x1]=='.' || board[y1][x1]=='-') && (board[y-1][x]=='.' || board[y-1][x]=='-'))
				return 1;
			}
            }
		  if( y1==(y-1) && x1==x){
			if(board[y1][x1]=='.' || board[y1][x1]=='-')
				return 1;
			 }
	   else if(y1==(y-1) && (x1==(x-1)||x1==(x+1))){
		   if( board[y1][x1]=='R' || board[y1][x1]=='N' || board[y1][x1]=='B' || board[y1][x1]=='Q' || board[y1][x1]=='P' )
			 return 1;
		  }
	 }
 return 0;
}

//// function (findPawn) is used to determine the place for all the pawns of the player and then pass it to the function (PawnMovesCheck).
bool findPawn(int turn){
    char pawnmove;
    if(turn==1){
    pawnmove='p';
    }
    else if(turn==2){
    pawnmove ='P';
    }
    for(int h=2;h<10;h++){
        for(int k=2;k<10;k++){
           if(board[h][k] == pawnmove){
            if(PawnMovesCheck(h,k,turn)==true)
                return true;
            else
                continue;
           }
        }
    }
    return false;
}


///// function (PawnMovesCheck) is used to check if there is a valid move or not.
bool PawnMovesCheck(int h,int k,int turn)
{
    if(turn==1){
        if(pawn2(k,h,k,h-2,turn)!=0){
            undoCheck[countercheck][0]=k;
            undoCheck[countercheck][1]=h;
            undoCheck[countercheck][2]=k;
            undoCheck[countercheck][3]=h-2;
            countercheck++;
            board[h-2][k]=board[h][k];
            checkboard(k,h);
            if(protect(turn)){
                undoCheckFun(turn,countercheck);
            } else{
                 undoCheckFun(turn,countercheck);
                 return true;
            }
        }
        if((h-1)>1 && pawn2(k,h,k,h-1,turn)!=0){
            undoCheck[countercheck][0]=k;
            undoCheck[countercheck][1]=h;
            undoCheck[countercheck][2]=k;
            undoCheck[countercheck][3]=h-1;
            countercheck++;
            board[h-1][k]=board[h][k];
            checkboard(k,h);
            if(protect(turn)){
                undoCheckFun(turn,countercheck);
            } else{
                 undoCheckFun(turn,countercheck);
                return true;
            }
        }
        if((k+1)<10 && (h-1)>1 && pawn2(k,h,k+1,h-1,turn)!=0){
            undoCheck[countercheck][0]=k;
            undoCheck[countercheck][1]=h;
            undoCheck[countercheck][2]=k+1;
            undoCheck[countercheck][3]=h-1;
            undoCheck[countercheck][4]=board[h-1][k+1];
            if(board[h-1][k+1]=='.' || board[h-1][k+1]=='-'){
                undoCheck[countercheck][4]=0;
                undoCheck[countercheck][5]=board[h][k+1];
                checkboard(k+1,h);
            }
            countercheck++;
            board[h-1][k+1]=board[h][k];
            checkboard(k,h);
            if(protect(turn)){
                undoCheckFun(turn,countercheck);
            } else{
                 undoCheckFun(turn,countercheck);
                   return true;
            }
        }
        if((k-1)>1 && (h-1)>1 && pawn2(k,h,k-1,h-1,turn)!=0){
            undoCheck[countercheck][0]=k;
            undoCheck[countercheck][1]=h;
            undoCheck[countercheck][2]=k-1;
            undoCheck[countercheck][3]=h-1;
            undoCheck[countercheck][4]=board[h-1][k-1];
            if(board[h-1][k-1]=='.' || board[h-1][k-1]=='-'){
                undoCheck[countercheck][4]=0;
                undoCheck[countercheck][5]=board[h][k-1];
                checkboard(k-1,h);
            }
            countercheck++;
            board[h-1][k-1]=board[h][k];
            checkboard(k,h);
            if(protect(turn)){
                undoCheckFun(turn,countercheck);
            } else{
                 undoCheckFun(turn,countercheck);
                 return true;
            }
        }
    }
    else if(turn==2){
        if(pawn2(k,h,k,h+2,turn)!=0){
            undoCheck[countercheck][0]=k;
            undoCheck[countercheck][1]=h;
            undoCheck[countercheck][2]=k;
            undoCheck[countercheck][3]=h+2;
            countercheck++;
            board[h+2][k]=board[h][k];
            checkboard(k,h);
            if(protect(turn)){
                undoCheckFun(turn,countercheck);
            } else{
                 undoCheckFun(turn,countercheck);
                return true;
            }
        }
        if((h+1)<10 && pawn2(k,h,k,h+1,turn)!=0){
            undoCheck[countercheck][0]=k;
            undoCheck[countercheck][1]=h;
            undoCheck[countercheck][2]=k;
            undoCheck[countercheck][3]=h+1;
            countercheck++;
            board[h+1][k]=board[h][k];
            checkboard(k,h);
            if(protect(turn)){
                undoCheckFun(turn,countercheck);
            } else{
                 undoCheckFun(turn,countercheck);
                return true;
            }
        }
        if((k+1)<10 && (h+1)<10 && pawn2(k,h,k+1,h+1,turn)!=0){
            undoCheck[countercheck][0]=k;
            undoCheck[countercheck][1]=h;
            undoCheck[countercheck][2]=k+1;
            undoCheck[countercheck][3]=h+1;
            undoCheck[countercheck][4]=board[h+1][k+1];
            if(board[h+1][k+1]=='.' || board[h+1][k+1]=='-'){
                undoCheck[countercheck][4]=0;
                undoCheck[countercheck][5]=board[h][k+1];
                checkboard(k+1,h);
            }
            countercheck++;
            board[h+1][k+1]=board[h][k];
            checkboard(k,h);
            if(protect(turn)){
                undoCheckFun(turn,countercheck);
            } else{
                 undoCheckFun(turn,countercheck);
               return true;
            }
        }
        if((k-1)>1 && (h+1)<10 && pawn2(k,h,k-1,h+1,turn)!=0){
            undoCheck[countercheck][0]=k;
            undoCheck[countercheck][1]=h;
            undoCheck[countercheck][2]=k-1;
            undoCheck[countercheck][3]=h+1;
            undoCheck[countercheck][4]=board[h+1][k-1];
            if(board[h+1][k-1]=='.' || board[h+1][k-1]=='-'){
                undoCheck[countercheck][4]=0;
                undoCheck[countercheck][5]=board[h][k-1];
                checkboard(k-1,h);
            }
            countercheck++;
            board[h+1][k-1]=board[h][k];
            checkboard(k,h);
            if(protect(turn)){
                undoCheckFun(turn,countercheck);
            } else{
                 undoCheckFun(turn,countercheck);
                 return true;
            }
        }
    }
    return false;
}


//// function (findRook) is used to determine the place for all the rooks of the player and then pass it to the function (RookMovesCheck).
bool findRook(int turn)
{
    char rookmove;
    if(turn==1){
    rookmove='r';
    }
    else if(turn==2){
    rookmove ='R';
    }
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){
           if(board[i][j] == rookmove){
               if(RookMovesCheck(i,j,turn)==true)
                return true;
             else
                continue;
           }
        }
    }
    return false;
}


///// function (RookMovesCheck) is used to check if there is a valid move or not.
bool RookMovesCheck(int i,int j,int turn)
{
        for(int h=i+1;h<10;h++)
        {
            if(rook(j,i,j,h,turn)!=0){
                undoCheck[countercheck][0]=j;
                undoCheck[countercheck][1]=i;
                undoCheck[countercheck][2]=j;
                undoCheck[countercheck][3]=h;
                if(board[h][j]!='.' && board[h][j]!='-')
                    undoCheck[countercheck][4]=board[h][j];
                countercheck++;
                board[h][j]=board[i][j];
                checkboard(j,i);
                if(protect(turn)){
                undoCheckFun(turn,countercheck);
             }else{
                 undoCheckFun(turn,countercheck);
                 return true;
            }
            }
        }
        for(int h=i-1;h>1;h--)
        {
            if(rook(j,i,j,h,turn)!=0){
                undoCheck[countercheck][0]=j;
                undoCheck[countercheck][1]=i;
                undoCheck[countercheck][2]=j;
                undoCheck[countercheck][3]=h;
                if(board[h][j]!='.' && board[h][j]!='-')
                    undoCheck[countercheck][4]=board[h][j];
                countercheck++;
                board[h][j]=board[i][j];
                checkboard(j,i);
                if(protect(turn)){
                undoCheckFun(turn,countercheck);
             }else{
                 undoCheckFun(turn,countercheck);
               return true;
            }
            }
        }
        for (int k=j+1;k<10;k++){
            if(rook(j,i,k,i,turn)!=0){
                undoCheck[countercheck][0]=j;
                undoCheck[countercheck][1]=i;
                undoCheck[countercheck][2]=k;
                undoCheck[countercheck][3]=i;
                if(board[i][k]!='.' && board[i][k]!='-')
                    undoCheck[countercheck][4]=board[i][k];
                countercheck++;
                board[i][k]=board[i][j];
                checkboard(j,i);
                if(protect(turn)){
                undoCheckFun(turn,countercheck);
             }else{
                 undoCheckFun(turn,countercheck);
                return true;
            }
            }
        }
        for (int k=j-1;k>1;k--){
            if(rook(j,i,k,i,turn)!=0){
                undoCheck[countercheck][0]=j;
                undoCheck[countercheck][1]=i;
                undoCheck[countercheck][2]=k;
                undoCheck[countercheck][3]=i;
                if(board[i][k]!='.' && board[i][k]!='-')
                    undoCheck[countercheck][4]=board[i][k];
                countercheck++;
                board[i][k]=board[i][j];
                checkboard(j,i);
                if(protect(turn)){
                undoCheckFun(turn,countercheck);
             }else{
                 undoCheckFun(turn,countercheck);
                 return true;
            }
            }
        }
    return false;
}


//// function (findKnight) is used to determine the place for all the Knights of the player and then pass it to the function (KnightMovesCheck).
bool findKnight(int turn)
{
    char knightmove;
    if(turn==1){
    knightmove='n';
    }
    else if(turn==2){
    knightmove ='N';
    }
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){

           if(board[i][j] == knightmove){
             if(KnightMovesCheck(i,j,turn)==true)
                return true;
             else
                continue;
           }
        }
    }
    return false;
}


///// function (KnightMovesCheck) is used to check if there is a valid move or not.
bool KnightMovesCheck(int i,int j,int turn)
{
        if(knight(j,i,j+1,i+2,turn)!=0 && (i+2)<10 && (j+2)<10){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j+1;
            undoCheck[countercheck][3]=i+2;
            if(board[i+2][j+1]!='.' && board[i+2][j+1]!='-')
                undoCheck[countercheck][4]=board[i+2][j+1];
            countercheck++;
            board[i+2][j+1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }

        }
        if(knight(j,i,j-1,i+2,turn)!=0 && (j-1)>1 && (i+2)<10){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j-1;
            undoCheck[countercheck][3]=i+2;
            if(board[i+2][j-1]!='.' && board[i+2][j-1]!='-')
                undoCheck[countercheck][4]=board[i+2][j-1];
            countercheck++;
            board[i+2][j-1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }

        }
        if(knight(j,i,j+2,i+1,turn)!=0 && (j+2)<10 && (i+1)<10){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j+2;
            undoCheck[countercheck][3]=i+1;
            if(board[i+1][j+2]!='.' && board[i+1][j+2]!='-')
                undoCheck[countercheck][4]=board[i+1][j+2];
            countercheck++;
            board[i+1][j+2]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }

        }
        if(knight(j,i,j-2,i+1,turn)!=0 && (j-2)>1 && (i+1)<10){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j-2;
            undoCheck[countercheck][3]=i+1;
            if(board[i+1][j-2]!='.' && board[i+1][j-2]!='-')
                undoCheck[countercheck][4]=board[i+1][j-2];
            countercheck++;
            board[i+1][j-2]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }

        }
        if(knight(j,i,j+2,i-1,turn)!=0 && (j+2)<10 && (i-1)>1){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j+2;
            undoCheck[countercheck][3]=i-1;
            if(board[i-1][j+2]!='.' && board[i-1][j+2]!='-')
                undoCheck[countercheck][4]=board[i-1][j+2];
            countercheck++;
            board[i-1][j+2]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }

        }
        if(knight(j,i,j-2,i-1,turn)!=0 && (j-2)>1 && (i-1)>1){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j-2;
            undoCheck[countercheck][3]=i-1;
            if(board[i-1][j-2]!='.' && board[i-1][j-2]!='-')
                undoCheck[countercheck][4]=board[i-1][j-2];
            countercheck++;
            board[i-1][j-2]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }

        }
        if(knight(j,i,j+1,i-2,turn)!=0 && (j+1)<10 && (i-2)>1){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j+1;
            undoCheck[countercheck][3]=i-2;
            if(board[i-2][j+1]!='.' && board[i-2][j+1]!='-')
                undoCheck[countercheck][4]=board[i-2][j+1];
            countercheck++;
            board[i-2][j+1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }

        }
        if(knight(j,i,j-1,i-2,turn)!=0 && (j-1)>1 && (i-2)>1){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j-1;
            undoCheck[countercheck][3]=i-2;
            if(board[i-2][j-1]!='.' && board[i-2][j-1]!='-')
                undoCheck[countercheck][4]=board[i-2][j-1];
            countercheck++;
            board[i-2][j-1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }

        }
    return false;
}


//// function (findBishop) is used to determine the place for all the bishops of the player and then pass it to the function (BishopMovesCheck).
bool findBishop(int turn)
{
    char bishopmove;
    if(turn==1){
    bishopmove='b';
    }
    else if(turn==2){
    bishopmove ='B';
    }
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){

           if(board[i][j] == bishopmove){
             if(BishopMovesCheck(i,j,turn)==true)
                return true;
             else
                continue;
           }
        }
    }
    return false;
}


///// function (BishopMovesCheck) is used to check if there is a valid move or not.
bool BishopMovesCheck(int i,int j,int turn)
{
    int m,k;
    m=j+1;
    k=i+1;
     while(m<10 && k<10){
        if(bishop(j,i,m,k,turn)!=0){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=m;
            undoCheck[countercheck][3]=k;
            if(board[k][m]!='.' && board[k][m]!='-')
                undoCheck[countercheck][4]=board[k][m];
            countercheck++;
            board[k][m]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
        }
        }
        m++;
        k++;
     }
     m=j+1;
     k=i-1;
     while(m<10 && k>1){
        if(bishop(j,i,m,k,turn)!=0){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=m;
            undoCheck[countercheck][3]=k;
            if(board[k][m]!='.' && board[k][m]!='-')
                undoCheck[countercheck][4]=board[k][m];
            countercheck++;
            board[k][m]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
        }
        }
        m++;
        k--;
     }
     m=j-1;
     k=i+1;
     while(m>1 && k<10){
        if(bishop(j,i,m,k,turn)!=0){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=m;
            undoCheck[countercheck][3]=k;
            if(board[k][m]!='.' && board[k][m]!='-')
                undoCheck[countercheck][4]=board[k][m];
            countercheck++;
            board[k][m]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
        }
        }
        m--;
        k++;
     }
     m=j-1;
     k=i-1;
     while(m>1 && k>1){
        if(bishop(j,i,m,k,turn)!=0){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=m;
            undoCheck[countercheck][3]=k;
            if(board[k][m]!='.' && board[k][m]!='-')
                undoCheck[countercheck][4]=board[k][m];
            countercheck++;
            board[k][m]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
        }
        }
        m--;
        k--;
     }
    return false;
}



//// function (findQueen) is used to determine the place for all the queen of the player and then pass it to the function (QueenMovesCheck).
bool findQueen(int turn)
{
    char queenmove;
    if(turn==1){
    queenmove='q';
    }
    else if(turn==2){
    queenmove ='Q';
    }
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){

           if(board[i][j] == queenmove){
             if(QueenMovesCheck(i,j,turn)==true)
                return true;
             else
                continue;
           }
        }
    }
    return false;
}


///// function (QueenMovesCheck) is used to check if there is a valid move or not.
bool QueenMovesCheck(int i,int j,int turn)
{
    if(BishopMovesCheck(i,j,turn)==true)
        return true;
    else if(RookMovesCheck(i,j,turn)== true)
        return true;
    else
        return false;
}

//// function (findKing) is used to determine the place for all the king of the player and then pass it to the function (KingMovesCheck).
bool findKing(int turn)
{
    char kingmove;
    if(turn==1){
    kingmove='k';
    }
    else if(turn==2){
    kingmove ='K';
    }
    for(int i=2;i<10;i++){
        for(int j=2;j<10;j++){

           if(board[i][j] == kingmove){
             if(KingMovesCheck(i,j,turn)==true)
                return true;
             else
                continue;
           }
        }
    }
    return false;
}


///// function (KingMovesCheck) is used to check if there is a valid move or not.
bool KingMovesCheck(int i,int j,int turn)
{
    if(king(j,i,j,i+1,turn)==1 && (i+1)<10){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j;
            undoCheck[countercheck][3]=i+1;
            if(board[i+1][j]!='.' && board[i+1][j]!='-')
                undoCheck[countercheck][4]=board[i+1][j];
            countercheck++;
            board[i+1][j]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }
    }
    if(king(j,i,j,i-1,turn)==1 && (i-1)>1){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j;
            undoCheck[countercheck][3]=i-1;
            if(board[i-1][j]!='.' && board[i-1][j]!='-')
                undoCheck[countercheck][4]=board[i-1][j];
            countercheck++;
            board[i-1][j]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }
    }
    if(king(j,i,j+1,i+1,turn)==1 && (j+1)<10 && (i+1)<10){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j+1;
            undoCheck[countercheck][3]=i+1;
            if(board[i+1][j+1]!='.' && board[i+1][j+1]!='-')
                undoCheck[countercheck][4]=board[i+1][j+1];
            countercheck++;
            board[i+1][j+1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }
    }
    if(king(j,i,j-1,i+1,turn)==1 && (j-1)>1 && (i+1)<10){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j-1;
            undoCheck[countercheck][3]=i+1;
            if(board[i+1][j-1]!='.' && board[i+1][j-1]!='-')
                undoCheck[countercheck][4]=board[i+1][j-1];
            countercheck++;
            board[i+1][j-1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }
    }
    if(king(j,i,j+1,i-1,turn)==1 && (j+1)<10 && (i-1)>1){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j+1;
            undoCheck[countercheck][3]=i-1;
            if(board[i-1][j+1]!='.' && board[i-1][j+1]!='-')
                undoCheck[countercheck][4]=board[i-1][j+1];
            countercheck++;
            board[i-1][j+1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }
    }
    if(king(j,i,j-1,i-1,turn)==1 && (j-1)>1 && (i-1)>1){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j-1;
            undoCheck[countercheck][3]=i-1;
            if(board[i-1][j-1]!='.' && board[i-1][j-1]!='-')
                undoCheck[countercheck][4]=board[i-1][j-1];
            countercheck++;
            board[i-1][j-1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }
    }
    if(king(j,i,j+1,i,turn)==1 && (j+1)<10){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j+1;
            undoCheck[countercheck][3]=i;
            if(board[i][j+1]!='.' && board[i][j+1]!='-')
                undoCheck[countercheck][4]=board[i][j+1];
            countercheck++;
            board[i][j+1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }
    }
    if(king(j,i,j-1,i,turn)==1 && (j-1)>1){
            undoCheck[countercheck][0]=j;
            undoCheck[countercheck][1]=i;
            undoCheck[countercheck][2]=j-1;
            undoCheck[countercheck][3]=i;
            if(board[i][j-1]!='.' && board[i][j-1]!='-')
                undoCheck[countercheck][4]=board[i][j-1];
            countercheck++;
            board[i][j-1]=board[i][j];
            checkboard(j,i);
            if(protect(turn)){
            undoCheckFun(turn,countercheck);
            }else{
                undoCheckFun(turn,countercheck);
                return true;
            }
    }

}

//// function (draw) is used to determine if the there is a dead position or not.
bool draw()
{
    char arr[3];
    int l=0,h,k;
    for(h=2;h<10;h++){
        for(k=2;k<10;k++){
            if(board[h][k]!='k' && board[h][k]!='K' && board[h][k]!='.' && board[h][k]!='-'){
                arr[l]=board[h][k];
                l++;
                if(l<3)
                    continue;
                else
                   return false;
            }
        }
    }
    if(l==0)
        return true;
    else if(l==1){
        if(arr[0]=='b' || arr[0]=='B'){
            return true;
        }
        else if(arr[0]=='n' || arr[0]=='N'){
            return true;
        }
    }
    else if(l==2){
        if((arr[0]=='n' && arr[1]=='n') || (arr[0]=='N' && arr[1]=='N') || (arr[0]=='N' && arr[1]=='n') || (arr[0]=='n' && arr[1]=='N') || (arr[0]=='b' && arr[1]=='B') || (arr[0]=='B' && arr[1]=='b'))
            return true;
    }
    return false;
}

//// function (checkmate) return true if there is no moves are valid and the king is checked and then the game is over.
bool checkmate(int turn)
{
    if(findPawn(turn)==false && findRook(turn)==false && findKnight(turn)==false && findBishop(turn)==false && findQueen(turn)==false && findKing(turn)==false && protect(turn)==true)
        return true;
    else
        return false;
}


//// function (stalemate) return true if there is no moves are valid and the king is not checked.
bool stalemate(int turn)
{
    if(findPawn(turn)==false && findRook(turn)==false && findKnight(turn)==false && findBishop(turn)==false && findQueen(turn)==false && findKing(turn)==false && protect(turn)==false)
        return true;
    else
        return false;
}
