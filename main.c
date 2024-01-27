#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUM_PAWNS 5
#define NUM_COLORS 8
#define NUM_ATTEMPTS 10

typedef enum {RED, GREEN, BLUE, YELLOW, BLACK, WHITE, GRAY, PURPLE} color_t;

  void read_proposed_combinations(color_t board[NUM_PAWNS])
  {
   for(int i=0;i<NUM_PAWNS;i++)
   {
     printf("Enter the number of the color %d (0-%d) : ", i + 1, NUM_COLORS );
        scanf("%d", &board[i]);
        board[i]=(color_t)board[i];
    if (board[i] < 0 || board[i] >= NUM_COLORS) {
            printf("Invalid color. Try again.\n");
            i--;
        }
   }
  }
  void evaluate_proposed_combinations(color_t color_hidden[NUM_PAWNS],color_t color_proposed[NUM_PAWNS],
     int *well_placed_pawn,int *misplaced_pawn)
  {
   *well_placed_pawn=0;
   *misplaced_pawn=0;
   for(int i=0;i<NUM_PAWNS;i++)
   {
    if (color_hidden[i]==color_proposed[i])
    {
     (*well_placed_pawn)++;
      color_hidden[i]= -1;
      color_proposed[i]= -1;
    }
   }
   for(int i=0;i<NUM_PAWNS;i++)
   {
    if (color_proposed== -1)
    {
      continue;
    }
    for(int j=0;j<NUM_PAWNS;j++)
    {
     if (color_hidden[j]==color_proposed[i])
     {
       (*misplaced_pawn)++;
       color_hidden[j]=-1;
       color_proposed[i]=-1;
       break;
     }
    }
   }

  }

     void generate_hidden_combination(color_t color_hidden[NUM_PAWNS]);

     void read_proposed_combinations(color_t board[NUM_PAWNS]);


     void evaluate_proposed_combinations(color_t color_hidden[NUM_PAWNS],color_t color_proposed[NUM_PAWNS],
     int *well_placed_pawn,int *misplaced_pawn);


    void generate_hidden_combination(color_t color_hidden[NUM_PAWNS]) {
    color_t colors[NUM_COLORS];
    for (int i = 0; i < NUM_COLORS; ++i) {
        colors[i] = i;
    }

     srand(time(NULL));

      for(int i=0;i<NUM_PAWNS;i++)
      {
       int j=rand()%(NUM_COLORS-i);
       int temp=colors[i];
       colors[i]=colors[j];
       colors[j]=temp;
      }
       for(int i=0;i<NUM_PAWNS;i++)
       {
        color_hidden[i]=colors[i];
       }

    }
     void game()
     {
       color_t color_hidden[NUM_PAWNS];
     color_t color_proposed[NUM_PAWNS];
      generate_hidden_combination(color_hidden);
      int well_placed_pawn,misplaced_pawn;
      for(int i=0;i<NUM_ATTEMPTS;i++)
      {
       printf("attempt %d:",i+1);
       read_proposed_combinations(color_proposed);
       evaluate_proposed_combinations(color_hidden,color_proposed,
       &well_placed_pawn,&misplaced_pawn);
       printf("well placed pawn:%d   misplaced pawn:%d \n",well_placed_pawn,misplaced_pawn);
       if (well_placed_pawn==NUM_PAWNS)
       {
        printf("congratulation you win");
       }

      }

     }
    int main() {
    printf("RED=1, GREEN=2, BLUE=3, YELLOW=4, BLACK=5, WHITE=6, GRAY=7, PURPLE=8 \n");
    game();
    return 0;
}


