#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define _USE_MATH_DEFINES
#define frand() (rand()/(double)RAND_MAX)
#define nrand() (sqrt(-2*log(frand()))*cos(2*M_PI*frand()))
double avg_utilization = 0;
double number_of_examined_holes = 0;
int head = 0;//head of the linked list of holes
int current_hole = 0;
void initialize(int n, int d, int v, int** mem, int**blocks){
  srand(time(NULL));
  int max_blocks = n/(d-v);//why?!
  *mem = (int*)malloc(sizeof(int)*n);
  (*mem)[0] = (*mem)[n-1] = -n+2;
  (*mem)[1] = (*mem)[2] = 0;
  *blocks = (int*)malloc(max_blocks*sizeof(int));
}
int nrand_gen(int d, double v, int n){
  double rv;
  do{
    rv=  nrand() * v + d;//use rand function here
    }while(rv < 3 || rv > n-4);
    return rv;
  
}
int request_best_fit(int* blocks, int* block_count, int* mem, int d, double v, int n){
  if(head == -1)//no hole is found!
    return 0;
  int size = nrand_gen(d, v, n);
  int iterator = head, pred, succ, new_size, block_address;
  while(size > -mem[iterator]){
    number_of_examined_holes++;
    iterator = mem[iterator + 2];//iterator = iterator->next
    if(head == iterator)
      return 0;//unsuccessful
  }
  int small = iterator;
  do{
    number_of_examined_holes++;
    if (mem[iterator] > mem[small] && size < -mem[iterator])
      small = iterator;
    iterator = mem[iterator + 2];//iterator = iterator->next
  }while(iterator != head);

  iterator = small;
  
  if(abs(size+mem[iterator]) <= 4){//fill completely
    //request size is almost equal to the hole size
    size = -mem[iterator];//block fills hole completely
    mem[iterator] = mem[iterator + size + 1] = size;
    //delete the current hole since it is full now
    pred = mem[iterator+1];
    succ = mem[iterator+2];
    if (pred == iterator)//current hole is the only hole
      head = -1;
    else{
      mem[pred+2] = succ;//current->prev->next = current->next
      mem[succ+1] = pred;//current->next->prev = current->prev 
    }
    block_address = iterator;
  }else{//fill partially
    mem[iterator] += (size+2);
    //adding pos by neg to make it less negative
    new_size = -mem[iterator];
    mem[iterator + new_size + 1] = mem[iterator];
    //block starts at iterator + new_size + 2
    block_address = iterator + new_size + 2;
    mem[block_address] = 
      mem[block_address + size + 1] = size;
  }
  blocks[*block_count] = block_address;
  (*block_count)++;
  return 1;//successful
}
int request_first_fit(int* blocks, int* block_count, int* mem, int d, double v, int n){
  if(head == -1)//no hole is found!
    return 0;
  int size = nrand_gen(d, v, n);
  int iterator = head, pred, succ, new_size, block_address;
  while(size > -mem[iterator]){
    number_of_examined_holes++;
    iterator = mem[iterator + 2];//iterator = iterator->next
    if(head == iterator)
      return 0;//unsuccessful
  }
  if(abs(size+mem[iterator]) <= 4){//fill completely
    //request size is almost equal to the hole size
    size = -mem[iterator];//block fills hole completely
    mem[iterator] = mem[iterator + size + 1] = size;
    //delete the current hole since it is full now
    pred = mem[iterator+1];
    succ = mem[iterator+2];
    if (pred == iterator)//current hole is the only hole
      head = -1;
    else{
      mem[pred+2] = succ;//current->prev->next = current->next
      mem[succ+1] = pred;//current->next->prev = current->prev 
    }
    block_address = iterator;
  }else{//fill partially
    mem[iterator] += (size+2);
    //adding pos by neg to make it less negative
    new_size = -mem[iterator];
    mem[iterator + new_size + 1] = mem[iterator];
    //block starts at iterator + new_size + 2
    block_address = iterator + new_size + 2;
    mem[block_address] = 
      mem[block_address + size + 1] = size;
  }
  blocks[*block_count] = block_address;
  (*block_count)++;
  return 1;//successful
}
int request_next_fit(int* blocks, int* block_count, int* mem, int d, double v, int n){
  if(head == -1)//no hole is found!
    return 0;
  int size = nrand_gen(d, v, n);
  int iterator = head, pred, succ, new_size, block_address;
  iterator = current_hole; // Setting the iterator to the hole we last allocated.
  while(size > -mem[iterator]){
    number_of_examined_holes++;
    iterator = mem[iterator + 2];//iterator = iterator->next
    if(head == iterator)
      return 0;//unsuccessful
  }
  if(abs(size+mem[iterator]) <= 4){//fill completely
    //request size is almost equal to the hole size
    size = -mem[iterator];//block fills hole completely
    mem[iterator] = mem[iterator + size + 1] = size;
    //delete the current hole since it is full now
    pred = mem[iterator+1];
    succ = mem[iterator+2];
    if (pred == iterator)//current hole is the only hole
      head = -1;
    else{
      mem[pred+2] = succ;//current->prev->next = current->next
      mem[succ+1] = pred;//current->next->prev = current->prev 
    }
    block_address = iterator;
  }else{//fill partially
    mem[iterator] += (size+2);
    //adding pos by neg to make it less negative
    new_size = -mem[iterator];
    mem[iterator + new_size + 1] = mem[iterator];
    //block starts at iterator + new_size + 2
    block_address = iterator + new_size + 2;
    mem[block_address] = 
      mem[block_address + size + 1] = size;
  }
  blocks[*block_count] = block_address;
  current_hole = iterator; //saving last allocated hole index.
  (*block_count)++;
  return 1;//successful
}
int request_worst_fit(int* blocks, int* block_count, int* mem, int d, double v, int n){
  if(head == -1)//no hole is found!
    return 0;
  int size = nrand_gen(d, v, n);
  int iterator = head, pred, succ, new_size, block_address;
  int largest_hole_size = -mem[iterator];
  while(-mem[iterator] >= largest_hole_size){//keep checking to find largest hole
    number_of_examined_holes++;
    largest_hole_size = -mem[iterator];
    iterator = mem[iterator + 2];//iterator = iterator->next
    if(head == iterator)
      return 0;//unsuccessful
  }
  int large = iterator;
  do{
    number_of_examined_holes++;
    if (mem[iterator] > mem[large] && size < -mem[iterator])
      large = iterator;
    iterator = mem[iterator + 2];//iterator = iterator->next
  }while(iterator != head);
  iterator = large;
  
  if(abs(size+mem[iterator]) <= 4){//fill completely
    //request size is almost equal to the hole size
    size = -mem[iterator];//block fills hole completely
    mem[iterator] = mem[iterator + size + 1] = size;
    //delete the current hole since it is full now
    pred = mem[iterator+1];
    succ = mem[iterator+2];
    if (pred == iterator)//current hole is the only hole
      head = -1;
    else{
      mem[pred+2] = succ;//current->prev->next = current->next
      mem[succ+1] = pred;//current->next->prev = current->prev 
    }
    block_address = iterator;
  }else{//fill partially
    mem[iterator] += (size+2);
    //adding pos by neg to make it less negative
    new_size = -mem[iterator];
    mem[iterator + new_size + 1] = mem[iterator];
    //block starts at iterator + new_size + 2
    block_address = iterator + new_size + 2;
    mem[block_address] = 
      mem[block_address + size + 1] = size;
  }
  blocks[*block_count] = block_address;
  (*block_count)++;
  return 1;//successful
}
void release(int* blocks, int* block_count, int* mem){
  if(!*block_count)
    return;
  int to_be_released = rand()%(*block_count);
  printf("releasing block at location (address) %d\n", blocks[to_be_released]);
  int hole_start_index;
  if((mem[blocks[to_be_released]-1]) < 0 && mem[blocks[to_be_released] + (mem[blocks[to_be_released]] + 2)] < 0)  {
    printf("Left & Right Holes (CASE 4)\n");
    hole_start_index = blocks[to_be_released] + mem[blocks[to_be_released]-1]-2; //set the starting index of the new hole
    mem[hole_start_index] = -1 * (mem[blocks[to_be_released]] + 2 + (-1*(mem[blocks[to_be_released]-1]-1)) + (-1*(mem[blocks[to_be_released] + (mem[blocks[to_be_released]] + 2)]-1))); //set start value of the new hole (-hole length)
    int hole_end_index = blocks[to_be_released] + (mem[blocks[to_be_released]]+2) + (-1*(mem[blocks[to_be_released]-1]-2)); 
    int initial_end_hole_index = mem[hole_end_index]; //calculates the end index of the new hole
    mem[hole_end_index] = mem[hole_start_index]; //sets the end index of the new hole to (-hole length)
    mem[hole_start_index + 2] = mem[hole_end_index + initial_end_hole_index +1]; //set the new holes NEXT controller
    int negCount = 0;
    int indexciesToNextHole = 0;
      while (negCount < 5){
        if (mem[hole_start_index + indexciesToNextHole] < 0)
          negCount++;
        indexciesToNextHole++;
        } 
    int next_hole_prev_index = hole_start_index + indexciesToNextHole;
    mem[next_hole_prev_index] = hole_start_index; //set the next holes PREVIOUS hole controller
    //Clearing previous block and hole data
    int initial_block_size = mem[blocks[to_be_released]];
    mem[blocks[to_be_released]] = 0;
    mem[blocks[to_be_released]-1] = 0;
    mem[blocks[to_be_released] + initial_block_size + 1] = 0;
    mem[blocks[to_be_released] + initial_block_size + 2] = 0;
    mem[blocks[to_be_released] + initial_block_size + 3] = 0;
    mem[blocks[to_be_released] + initial_block_size + 4] = 0; 
  }
  else if(mem[blocks[to_be_released]-1] < 0)
  {
    printf("Left Hole (CASE 3)\n");
    hole_start_index = blocks[to_be_released] + mem[blocks[to_be_released]-1] -2;
    mem[hole_start_index] = mem[blocks[to_be_released] + (mem[blocks[to_be_released]] + 1)] =  mem[hole_start_index] - mem[blocks[to_be_released]] - 2;
    mem[blocks[to_be_released]] = 0;  
    mem[blocks[to_be_released]-1] = 0;
  }
  else if((blocks[to_be_released] + (mem[blocks[to_be_released]] + 2)) < 0)
  {
    printf("Right Hole (CASE 2)\n");
    hole_start_index = blocks[to_be_released] + mem[blocks[to_be_released]] + 2; // Grab the index of the hole
    mem[blocks[to_be_released] + (mem[blocks[to_be_released]] + 1)] = 0; // remove the right size delimiter from the block
    mem[blocks[to_be_released]] = mem[hole_start_index] - mem[blocks[to_be_released]] - 2; //Resize left block size with plus the hole size
    mem[hole_start_index + -mem[hole_start_index]+1] = mem[blocks[to_be_released]]; // replace the right size delimiter from the hole with block size+hole size
    mem[hole_start_index] = 0; // remove the left size delimiter from the old hole
    mem[blocks[to_be_released]+1] = mem[hole_start_index+1]; // replace Next control point of blocke with hole control point
    mem[blocks[to_be_released]+2] = mem[hole_start_index+2]; // replace Right control point of block with hole control point
    mem[hole_start_index+1] = 0; // Clear old next and previous control point of hole
    mem[hole_start_index+2] = 0; // Clear old next and previous control point of hole
    mem[mem[blocks[to_be_released]+1]+2] = blocks[to_be_released]; // replace Next control point of left hole to the index of the new hole.
  }
  else
  {
    printf("Both Blocks (CASE 1)\n");
    hole_start_index = blocks[to_be_released]; //start index of releasing block set to the start index of new hole
    mem[hole_start_index] = -1 * (mem[blocks[to_be_released]]); //set start value of the new hole
    mem[hole_start_index + (-1*mem[blocks[to_be_released]]) + 1] = mem[hole_start_index]; //set end value of the new hole
      int negCountCase1 = 0, indexciesToNextHoleCase1 = 0;
      while (negCountCase1 < 3){
        if (mem[hole_start_index + indexciesToNextHoleCase1] < 0)
          negCountCase1++;
        indexciesToNextHoleCase1++;
        } 
    mem[hole_start_index + 1] = mem[hole_start_index + indexciesToNextHoleCase1]; //set the new holes PREVIOUS controller
    int next_hole_prev_index = hole_start_index + indexciesToNextHoleCase1;
      negCountCase1 = 0;
      int indexciesToPrevHole = 0;
      while (negCountCase1 < 2){
        if (mem[hole_start_index + indexciesToPrevHole] < 0)
          negCountCase1++;
        indexciesToPrevHole--;
        } 
    mem[hole_start_index + 2] = hole_start_index + indexciesToNextHoleCase1 - 1; //set the new holes NEXT controller
    int prev_hole_next_index = hole_start_index + indexciesToPrevHole + 2 + (mem[hole_start_index +  indexciesToPrevHole + 1]);
    mem[next_hole_prev_index] = hole_start_index; //set the next holes PREVIOUS hole controller
    mem[prev_hole_next_index] = hole_start_index; //set the Previous holes NEXT hole controller
  }
  //remove an integer at index to_be_released from blocks array...
  blocks[to_be_released] = blocks[(*block_count)-1];
  (*block_count)--;
}
void update_memory_utilization(int* blocks, int block_count, int* mem, int n, int x){
  double utilization = 0;
  for(int i = 0;i < block_count;i++)
    utilization += mem[blocks[i]];
  utilization /= n;
  //printf("%f\t",utilization);
  avg_utilization += utilization/x;
}
int main(int argc, char** argv) {
  int x,n,d;
  double v;
  while(*++argv){
    //./main -x 1000 -n 16000000 -d 1000000 -v 256000
    if(**argv != '-')
      return 1;
    switch((*argv)[1]){
      case 'x':
      x = atoi(*++argv);
      break;
      case 'n':
      n = atoi(*++argv);
      break;
      case 'd':
      d = atoi(*++argv);
      break;
      case 'v':
      v = atof(*++argv);
      break;
      default: //error
      return 1;
    }
  }
  int* mem;//the memory
  int* blocks;
  int block_count = 0;
  printf("Running the simulation with x=%d n=%d d=%d v=%.2f\n", x,n,d,v);
  initialize(n, d, v, &mem, &blocks);
  int originalX = x;
  while(x > 0){
    x--;
    while(request_first_fit(blocks, &block_count, mem, d, v, n));
    update_memory_utilization(blocks, block_count, mem, n, originalX);
    release(blocks,&block_count,mem);
  }
  printf("avg utilization is %.3f", avg_utilization);
  return 0;
}
