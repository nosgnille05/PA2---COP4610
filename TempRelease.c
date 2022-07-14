#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void) 
{
  int memory1[] = {-3,19,19,1,-3,2,1,1,2,4,1,1,1,1,4,2,1,1,2,-3,0,0,1,-3};//Both Blocks (CASE 1)
  int memory2[] = {-3,15,15,1,-3,2,1,1,2,4,1,1,1,1,4,-2,0,0,-2,3,1,1,1,3};//Right Hole (CASE 2)
  int memory3[] = {3,1,1,1,3,-2,19,19,-2,4,1,1,1,1,4,2,1,1,2,-3,5,5,1,-3};//Left Hole (CASE 3)
  int memory4[] = {3,1,1,1,3,-2,15,15,-2,4,1,1,1,1,4,-2,5,5,-2,3,1,1,1,3};//Left & Right Holes (CASE 4)
  int block_start_index = 9;
  int hole_start_index;
  //block start index val = memory[block_start_index]

  int *memory = memory3;
  //Print Initial Array
  for (int i=0; i<24; i++){
    printf("%d ", memory[i]);
  }
  printf("\n");

  if((memory[block_start_index-1]) < 0 && memory[block_start_index + (memory[block_start_index] + 2)] < 0)  {
    printf("Left & Right Holes (CASE 4)\n");
  }
  else if(memory[block_start_index-1] < 0)
  {
    printf("Left Hole (CASE 3)\n");
    hole_start_index = block_start_index + memory[block_start_index-1] -2;
    memory[hole_start_index] = memory[block_start_index + (memory[block_start_index] + 1)] =  memory[hole_start_index] - memory[block_start_index] - 2;
  }
  else if(memory[block_start_index + (memory[block_start_index] + 2)] < 0)
  {
    printf("Right Hole (CASE 2)\n");
    hole_start_index = block_start_index + memory[block_start_index] + 1;
    memory[hole_start_index] = memory[block_start_index + (memory[block_start_index] + 1)] =  memory[hole_start_index] - memory[block_start_index] - 2;
  }
  else
  {
    printf("Both Blocks (CASE 1)\n");
    hole_start_index = block_start_index;
    //hole start index val = -(block start index val + 2)
    memory1[hole_start_index] = -1 * (memory1[block_start_index] + 2); 
    //hole start index + block start index val + 2 - 1 = hole start index val
    memory1[hole_start_index + memory1[block_start_index + 2] - 1] = memory1[hole_start_index];
    //hole start index + 1 = (next hole start index + 1) val
      //while to check for next hole
      int negCount = 0, indexciesToNextHole = 0;
      while (negCount != 2){
        if (memory1[hole_start_index + indexciesToNextHole] < 0)
          negCount++;
        indexciesToNextHole++;//indexciesToNextHole = 11 (CASE 1)
        } 
    printf("indexciesToNextHole %d\n", indexciesToNextHole);
    memory1[hole_start_index + 1] = memory1[hole_start_index + indexciesToNextHole];
    //hole start index + 2 = next hole start index 
    
    //next hole start index + 1 = hole start index
    
  }

  //Print Array After Block Removal
  for (int i=0; i<24; i++){
    printf("%d ", memory[i]);
  }
  printf("\n");

  return 0;
}