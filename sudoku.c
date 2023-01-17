#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_sudoku(int sudoku[9][9])
{
  printf("Current Sudoku:\n");
  printf("+-------+-------+-------+\n");
  for (int j = 0; j < 9; j++)
  {
    printf("| ");
    for (int i = 0; i < 9; i++)
    {
      printf("%d ", sudoku[j][i]);
      if (i % 3 == 2)
        printf("| ");
    }
    printf("\n");
    if (j % 3 == 2)
      printf("+-------+-------+-------+\n");
  }
}

int is_valid_sudoku(int sudoku[9][9])
{
  int nodupe[9];
  //checks 3x3 grid for dupe
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      for(int k = 0; k < 9; k++) nodupe[k] = 0;
      for(int r = 0; r < 3; r++)
      {
        for(int c = 0; c < 3; c++)
        {
          if(sudoku[i*3 + r][j*3 + c] != 0)
          {
            if(nodupe[sudoku[i*3 + r][j*3 + c] - 1]) return 0;
            nodupe[sudoku[i*3 + r][j*3 + c] - 1] = 1;
          }
        }
      }
    }
  }
  //checks each row for dupe
  for(int i = 0; i < 9; i++)
  {
    for(int k = 0; k < 9; k++) nodupe[k] = 0;
    for(int j = 0; j < 9; j++)
    {
      if(sudoku[i][j] != 0)
      {
        if(nodupe[sudoku[i][j] - 1]) return 0;
        nodupe[sudoku[i][j] - 1] = 1;
      }
    }
  }
  //checks each column for dupe
  for(int j = 0; j < 9; j++)
  {
    for(int k = 0; k < 9; k++) nodupe[k] = 0;
    for(int i = 0; i < 9; i++)
    {
      if(sudoku[i][j] != 0)
      {
        if(nodupe[sudoku[i][j] - 1]) return 0;
        nodupe[sudoku[i][j] - 1] = 1;
      }
    }
  }
  return 1;
}

int solve_sudoku(int sudoku[9][9])
{
  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      if(sudoku[i][j] == 0)
      {
        for(int num = 1; num < 10; num++)
        {
          sudoku[i][j] = num;
          if(is_valid_sudoku(sudoku))
          {
            if(solve_sudoku(sudoku)) return 1;
            else sudoku[i][j] = 0;
          }
          else sudoku[i][j] = 0;
        }
        return 0;
      }
    }
  }
  return 1;
}

int populate_sudoku(int sudoku[9][9]){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      sudoku[i][j] = 0;
    }
  }

  char name[1024];
  printf("Please enter the name of the sudoku file you are trying to solve: ");
  fgets(name, 1024, stdin);
  if(name[strlen(name) - 1] == '\n'){
    name[strlen(name) - 1] = '\0';
  }

  FILE *infile = fopen(name, "r");
  while(infile == NULL){
    printf("File not found! Please enter a proper file name.");
    printf("Please enter the name of the sudoku file you are trying to solve: ");
    fgets(name, 1024, stdin);
    if(name[strlen(name) - 1] == '\n'){
      name[strlen(name) - 1] = '\0';
    } 
    infile = fopen(name, "r");
  }
  char info[127];
  char *endPoint;
  if(infile != NULL){
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
       fscanf(infile, "%s", info);
       sudoku[i][j] = strtol(info, NULL, 10);
      }
      endPoint = NULL;
    }
  }
  fclose(infile);
  return 1;
}

int sudoku_process(int sudoku[9][9]){
  populate_sudoku(sudoku);
  print_sudoku(sudoku);

  int solved = solve_sudoku(sudoku);

  if(solved){
    printf("The sudoku has been solved!\n");
    print_sudoku(sudoku);
  }
  else{
    printf("Impossible sudoku!\n");
  }
}

int main()
{

  int sudoku_grid[9][9] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0}};
  sudoku_process(sudoku_grid);
  int choice = 1;
  while(choice != 0){
    printf("Would you like to go again? 1 - Yes | 0 - Exit\n");
    scanf("%d", &choice);
    getchar();

    if(choice == 1){
      sudoku_process(sudoku_grid);
    }
  }

  return 0;
}