#include "swap.h"


// Function definitions
// Pass By Value
void swap(int n1, int n2) {
  int temp;
  temp = n1;
  n1 = n2;
  n2 = temp;
}

// Pass By Pointer
void swap_by_pointers(int *n1, int *n2) {
  // TODO Complete this function
  int z = *n1;
  *n1 = *n2;
  *n2 = z;
}

// Function to reverse the array through pointers
void reverse(int array[], int array_size)
{
    // pointer1 pointing at the beginning of the array
    int *pointer1 = array;

    // pointer2 pointing at end of the array
    int *pointer2 = array + array_size - 1;
    // TODO Use the above swap function and update pointers to reverse your array
    while (pointer1 < pointer2) {
      swap_by_pointers(pointer1, pointer2);
      pointer1 += 1;
      pointer2 -= 1;
    }
}

// GOLD problem
// Function to do cumulative sum of the array
 void cumulative_sum(int array[], int array_size)
 {
   for (int i = 1; i < array_size; i++) {
     array[i] += array[i-1];
   }
 }
