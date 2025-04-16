#include <iostream>
#include <vector>
using namespace std;

void Print_Board(char B[5][7])
{
   for(int i=0; i<5; i++)
   {
      for(int j=0; j<7; j++)
      {
         cout << B[i][j];
      }
      cout << endl;
   }
}
void Calculation(int move,int& x, int& y,char B[5][7])
{
   x= -1;
   y= -1;
   for(int i=1; i<=3; i++)
   {
      for(int j=1; j<=5; j+=2)
      {
         if(B[i][j]==(move+'0'))
         {
            x=i;
            y=j;
            return;
         }
      }
   }
}
void movement(char B[5][7],int& x,int& y, char turn)//B=board
{
   bool flag = false; //i think that the number does not exist
   int i = 0;
   int j = 0;
   if(B[x][y]!='X' && B[x][y]!='O')
   {
      if(turn=='X')
      {
         cout << B[x][y] << "is changing to X \n";
         
         B[x][y] = 'X';
         flag = true;
      }
      else
      {
         cout << B[x][y] << "is changing to O";
         B[x][y] = 'O';
         flag = true;
      }
   }
   if(flag)
      cout << "The Movement Succesfully was made!\n";
   else 
      cout << "The Movement Does Not Exist!, please try again!\n";
}

bool isDraw(char B[5][7])
{
   for(int i=1; i<=3; i++)
   {
      for(int j=1; j<=5; j+=2)
      {
         if(B[i][j]!='X' && B[i][j]!='O')
         {
            return false;
         }
      }
   }
   return true;
}
bool Checking(char Board[5][7],char turn)
{
   if(turn=='X'|| turn =='O')
   {
      if    ((Board[1][1]==turn && Board[1][3]==turn && Board[1][5]==turn) || //lines
             (Board[2][1]==turn && Board[2][3]==turn && Board[2][5]==turn) ||
             (Board[3][1]==turn && Board[3][3]==turn && Board[3][5]==turn) ||
             (Board[1][1]==turn && Board[1][3]==turn && Board[1][5]==turn) || //columns
             (Board[1][3]==turn && Board[2][3]==turn && Board[3][3]==turn) ||
             (Board[1][5]==turn && Board[2][5]==turn && Board[3][5]==turn) ||
             (Board[1][1]==turn && Board[2][3]==turn && Board[3][5]==turn) ||//diagonal
             (Board[3][1]==turn && Board[2][3]==turn && Board[1][5]==turn)) 
      {
         return true;
      }
   }
   return false;
}



int main()
{
   char answer;
   char Board[5][7] =
   {
      {'-','-','-','-','-','-','-'},
      {'|','1','|','2','|','3','|'},
      {'|','4','|','5','|','6','|'},
      {'|','7','|','8','|','9','|'},
      {'-','-','-','-','-','-','-'}, 
   };
   //Print the Board
   Print_Board(Board);
   cout << "Two Players Participate ->";

   do//check for answers//
   {
      cout << "(Choose X Or O): ";
      cin >> answer;
      //fix
   }while(answer!='X' && answer!='O');

   int move;//movement of
   char turn; //player
   int line,column; //keep the position
   bool error = false; //I believe the number exists
   bool result;
   while(!Checking(Board, 'X') && !Checking(Board, 'O') && !isDraw(Board))
   {
      if(answer=='X' || answer=='O') //ANSWER = X or ANSWER= O
      {
         do{
            cout << answer <<" is your turn!, Choose your movement: ";
            turn = answer; //player
            cin >> move;
            Calculation(move,line, column,Board);
            if(line== -1 || column == -1 || Board[line][column]== 'X' || Board[line][column]== 'O' )
            {
               cout << "Error, Movement Does Not Exist or it is taken, Please Try Again!\n";
            }
         }while(line== -1 || column== -1);

         movement(Board,line,column, turn); //void 2 for search
         system("cls");
         Print_Board(Board);

         result = Checking(Board, turn);//checks if someone won or not
         if(result==true)
         {
            cout << "<" << turn << " player > IS THE WINNER\n";
            break;
         }
         else if(isDraw(Board))
         {
            cout << "Noone is the winner, The Game Ends In A Draw!\n";
         }
      }
      if(answer =='X'){ answer = 'O'; } //changes the turn for the oponnent
      else if(answer =='O') { answer = 'X';}
   }
   return 0;
}