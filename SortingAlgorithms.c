//---------------------------------------------------------------------------------------------------------------------
// a2.c
//
// My implementation of sorting algorithms. There are 3 sorting algorithms in total: Bubble, Merge and Heap sorts.
// The program takes the params and following them performs specified sorting. Arrar is printed every iteration of the sort
//
// Group: Group 3
//
// Author: 12134500
//---------------------------------------------------------------------------------------------------------------------
//
#include <stdio.h>
#define MAX_SIZE 100
#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)



//operation with strings
int stringToInt(const char *str);
void swap(int *a, int *b);
void swapStrings(char word_a[], char word_b[]);
void copyString(char word_b[], const char word_a[]);
int compareStrings(const char* str1, const char* str2);

//bubble sort
void bubbleSortInt(int arr[][MAX_SIZE], int length);
void bubbleSortStr(char arr[][MAX_SIZE], int length);

//merge sort
void mergeInt(int arr[][MAX_SIZE], int left_start, int left_end, int right_end);
void mergeStr(char arr[][MAX_SIZE], int left_start, int left_end, int right_end);
void mergeSortInt(int arr[][MAX_SIZE], int start, int end);
void mergeSortStr(char arr[][MAX_SIZE], int start, int end);

//heap sort
void buildHeapInt(int arr[][MAX_SIZE], int size);
void buildHeapStr(char arr[][MAX_SIZE], int size);
void heapifyInt(int root_index, int arr[][MAX_SIZE], int size);
void heapifyStr(int root_index, char arr[][MAX_SIZE], int size);
void heapSortInt(int arr[][MAX_SIZE], int size);
void heapSortStr(char arr[][MAX_SIZE], int size);

//main function parts
void arrayOutputStr(char arr[][MAX_SIZE], int length);
void arrayOutputInt(int arr[][MAX_SIZE], int length);
void sortingLogicInt(int elements_to_sort_int[][MAX_SIZE], int number_elements, char algorith[7]);
void sortingLogicStr(char elements_to_sort[][MAX_SIZE], int number_elements, char algorithm[7]);
void arrayConvertStrToInt(int elements_to_sort_int[][MAX_SIZE], char elements_to_sort[][MAX_SIZE], int number_elements);
int ErrorsCheck(int argc, char* argv[],char sort_type[], char data_type[], int number_elements, char elements_to_sort[][MAX_SIZE]);


//---------------------------------------------------------------------------------------------------------------------
///
/// Main function. Takes in paramets, such as: type of data, type of sort, number of elements to sort
/// and the elements themselves separeted by commas. Then using switch-cse performs sorting according to
/// the argc given. Prints sorted array in the end
///
//
int main(int argc, char* argv[])
{
  //variables init
  int number_elements = stringToInt(argv[3]);
  char sort_type[7] = {0};
  char data_type[7] = {0};
  char elements_to_sort[number_elements][MAX_SIZE];
  int elements_to_sort_int[number_elements][MAX_SIZE];

  int error = 0;
  error = ErrorsCheck(argc, argv, sort_type, data_type, number_elements, elements_to_sort); //error check and init
  if(error!=0)//if any error occurs, terminate the program
  {
    return error;
  }

  switch (compareStrings(data_type, "int"))
  {
  case 0:
    arrayConvertStrToInt(elements_to_sort_int, elements_to_sort, number_elements);
    sortingLogicInt(elements_to_sort_int, number_elements, sort_type);
    break;
  
  default:
    sortingLogicStr(elements_to_sort, number_elements, sort_type);
    break;
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// compares two strings, took it from lecture
///
/// @param str1 first string
/// @param str2 second string
///
/// @return 0, if matched
//
int compareStrings(const char* str1, const char* str2)
{
  while(*str1 && *str2 && *str1==*str2)
  {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}



//---------------------------------------------------------------------------------------------------------------------
///
/// swap function for strings
///
/// @param word_a first string
/// @param word_a second string
///
/// @return swapped strings
//
void swapStrings(char word_a[], char word_b[])
{
  char temp[MAX_SIZE];
  int count;
  for (count = 0; word_a[count] != '\0'; count++)
  {
    temp[count] = word_a[count];
  }
  temp[count] = '\0';
  for (count = 0; word_b[count] != '\0'; count++)
  {
    word_a[count] = word_b[count];
  }
  word_a[count] = '\0';
  for (count = 0; temp[count] != '\0'; count++)
  {
    word_b[count] = temp[count];
  }
  word_b[count] = '\0';
}



//---------------------------------------------------------------------------------------------------------------------
///
/// This function converts string to int
///
/// @param str string to convert
///
/// @return converted number
//
int stringToInt(const char *str) 
{
  int result = 0;
  int sign = 1;
  int count = 0;
  while (str[count] != '\0') 
  {
    if (str[count] >= '0' && str[count] <= '9') 
    {
      result = result * 10 + (str[count] - '0');
    } 
    else return 0;
    count++;
  }
  return result * sign;
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Custom function to copy string src to string dest
///
/// @param word_b where to copy
/// @param word_a what to copy
///
/// @return copied str
//
void copyString(char word_b[], const char word_a[]) 
{
  int count = 0;
  while (word_a[count] != '\0') 
  {
    word_b[count] = word_a[count];
    count++;
  }
  word_b[count] = '\0';
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Simply swap function for bubble sort with integers
///
/// @param a first number
/// @param b second number
///
/// @return swapped numbers
//
void swap(int *a, int *b) 
{
  int temp = *a;
  *a = *b;
  *b = temp;
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Bubble sort for integers. Takes in an array of integers and sorts it with bubble sort algorithm. Each iteration is printed 
///
/// @param arr an array to sort
/// @param length length of an array
///
/// @return sorted array
//
void bubbleSortInt(int arr[][MAX_SIZE], int length)
{
  for (int i = length - 1; i >= 1; i--) 
  {
    for (int j = 0; j < i; j++) 
    {
      if (arr[j][0] > arr[j+1][0]) 
      {
        swap(&arr[j][0], &arr[j + 1][0]);
      }
    }
    arrayOutputInt(arr, length); 
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Bubble sort for string. Takes in an array of strings and sorts it with bubble sort algorithm. Each iteration is printed
///
/// @param arr an array to sort
/// @param length length of an array
///
/// @return sorted array
//
void bubbleSortStr(char arr[][MAX_SIZE], int length) 
{
  char temp[MAX_SIZE];
  for (int i = 0; i < length - 1; i++) 
  {
    for (int j = 0; j < length - i - 1; j++) 
    {
      int k = 0;
      while (arr[j][k] != '\0' && arr[j+1][k] != '\0') 
      {
        if (arr[j][k] > arr[j+1][k]) 
        {
          // Swap the strings
          for (int l = 0; arr[j][l] != '\0' || arr[j+1][l] != '\0'; l++) 
          {
              temp[l] = arr[j][l];
              arr[j][l] = arr[j+1][l];
              arr[j+1][l] = temp[l];
          }
          break;
        }
        else if (arr[j][k] < arr[j+1][k]) 
        {
          break;
        }
        k++;
      }
    }
    arrayOutputStr(arr, length); // pomenyat ili ostavit hz
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Prints an string array
///
/// @param arr an array to output
/// @param length length of an array
///
/// @return output array
//
void arrayOutputStr(char arr[][MAX_SIZE], int length)
{
  printf("[");    
  for (int i = 0; i < length; i++)
  {
    printf("%s", arr[i]);
    if (i < length - 1) 
    {
      printf(", ");
    }
  }
  printf("]\n");
}


//---------------------------------------------------------------------------------------------------------------------
///
/// Prints an integer array
///
/// @param arr an array to output
/// @param length length of an array
///
/// @return output array
//
void arrayOutputInt(int arr[][MAX_SIZE], int length)
{
  printf("[");    
  for (int i = 0; i < length; i++)
  {
    printf("%d", arr[i][0]);
    if (i < length - 1) 
    {
      printf(", ");
    }
  }
  printf("]\n");
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Converts string array to an integer array
///
/// @param elements_to_sort_int an integer array
/// @param elements_to_sort a string array
/// @param number_elements length of an array
///
/// @return converted array
//
void arrayConvertStrToInt(int elements_to_sort_int[][MAX_SIZE], char elements_to_sort[][MAX_SIZE], int number_elements)
{
  for(int count = 0; count < number_elements;count++)
  {
    elements_to_sort_int[count][0] = stringToInt(elements_to_sort[count]);
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Sorting logic function for integers. Performs sort according to parametrs given
///
/// @param elements_to_sort_int an integer array
/// @param number_elements length of an array
/// @param algorithm sorting algorithm
///
/// @return sorted array
//
void sortingLogicInt(int elements_to_sort_int[][MAX_SIZE], int number_elements, char algorithm[7])
{
  arrayOutputInt(elements_to_sort_int, number_elements);
  printf("--- Start sorting ---\n");
  if (compareStrings(algorithm, "bubble") == 0) 
  {
    bubbleSortInt(elements_to_sort_int, number_elements);     
  } 
  else if (compareStrings(algorithm, "merge") == 0) 
  {
    mergeSortInt(elements_to_sort_int, 0, number_elements - 1);
  } 
  else if (compareStrings(algorithm, "heap") == 0) 
  {
    heapSortInt(elements_to_sort_int, number_elements);  
  }
  printf("--- Finished sorting ---\n");
  arrayOutputInt(elements_to_sort_int, number_elements);
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Sorting logic function for string. Performs sort according to parametrs given
///
/// @param elements_to_sort an string array
/// @param number_elements length of an array
/// @param algorithm sorting algorithm
///
/// @return sorted array
//
void sortingLogicStr(char elements_to_sort[][MAX_SIZE], int number_elements, char algorithm[7])
{
  arrayOutputStr(elements_to_sort, number_elements);
  printf("--- Start sorting ---\n");
  if (compareStrings(algorithm, "bubble") == 0) 
  {
    bubbleSortStr(elements_to_sort, number_elements);     
  } 
  else if (compareStrings(algorithm, "merge") == 0) 
  {
    mergeSortStr(elements_to_sort, 0, number_elements - 1);
  } 
  else if (compareStrings(algorithm, "heap") == 0) 
  {
    heapSortStr(elements_to_sort, number_elements);
  }
  printf("--- Finished sorting ---\n");
  arrayOutputStr(elements_to_sort, number_elements);
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Merge part of merge sort for integers
///
/// @param arr an integer array
/// @param left_start left array start
/// @param left_end left array end
/// @param right_end right array end
///
/// @return merged array 
//
void mergeInt(int arr[][MAX_SIZE], int left_start, int left_end, int right_end) 
{
  int size_left = left_end - left_start + 1;
  int size_right = right_end - left_end;

  int left_array[size_left];
  int right_array[size_right];

  // Copy data to temp arrays
  for (int i = 0; i < size_left; i++)
      left_array[i] = arr[left_start + i][0];
  for (int j = 0; j < size_right; j++)
      right_array[j] = arr[left_end + 1 + j][0];

  int left_index = 0, right_index = 0, merge_index = left_start;

  // Merge the temp arrays back into arr[left_start...right_end]
  while (left_index < size_left && right_index < size_right) 
  {
    if (left_array[left_index] <= right_array[right_index])
    {  
      arr[merge_index++][0] = left_array[left_index++];
    }
    else
    {
      arr[merge_index++][0] = right_array[right_index++];
    }
  }

  // Copy the remaining elements of left_array[], if any
  while (left_index < size_left)
  {
    arr[merge_index++][0] = left_array[left_index++];
  }
  // Copy the remaining elements of right_array[], if any
  while (right_index < size_right)
  {
    arr[merge_index++][0] = right_array[right_index++];
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Merge sort for integer. Performs merge sort recursevly, each iteration is printed
///
/// @param arr an integer array
/// @param start where to start
/// @param left_end where to end
///
/// @return sorted array
//
void mergeSortInt(int arr[][MAX_SIZE], int start, int end) 
{
  if (start < end) 
  {
    int mid = start + (end - start) / 2;

    mergeSortInt(arr, start, mid);
    mergeSortInt(arr, mid + 1, end);

    mergeInt(arr, start, mid, end);

    printf("[");
    for(int i = start; i <= end; i++) // here i didnt use array output function because the start is not always 0
    {
      printf("%d", arr[i][0]);
      if (i < end) 
      {
        printf(", ");
      }
    }
    printf("]\n");
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Merge part of merge sort for strings
///
/// @param arr a string array
/// @param left_start left array start
/// @param left_end left array end
/// @param right_end right array end
///
/// @return merged array 
//
void mergeStr(char arr[][MAX_SIZE], int left_start, int left_end, int right_end)
{
  int left_size = left_end - left_start + 1;
  int right_size = right_end - left_end;

  char left_array[left_size][MAX_SIZE];
  char right_array[right_size][MAX_SIZE];

  // Copy data to temporary arrays
  for (int i = 0; i < left_size; i++)
  {
    copyString(left_array[i], arr[left_start + i]);
  }
  for (int j = 0; j < right_size; j++)
  {
    copyString(right_array[j], arr[left_end + 1 + j]);
  }

  int left_index = 0, right_index = 0, merge_index = left_start;
  while (left_index < left_size && right_index < right_size) 
  {
    if (compareStrings(left_array[left_index], right_array[right_index]) <= 0)
    {
      copyString(arr[merge_index++], left_array[left_index++]);
    }
    else
    {
      copyString(arr[merge_index++], right_array[right_index++]);
    }
  }

  // Copy the remaining elements of left_array[], if any
  while (left_index < left_size)
  {
    copyString(arr[merge_index++], left_array[left_index++]);
  }
  // Copy the remaining elements of right_array[], if any
  while (right_index < right_size)
  {
    copyString(arr[merge_index++], right_array[right_index++]);
  }
}




//---------------------------------------------------------------------------------------------------------------------
///
/// Merge sort for strings. Performs merge sort recursevly, each iteration is printed
///
/// @param arr an integer array
/// @param start where to start
/// @param left_end where to end
///
/// @return sorted array
//
void mergeSortStr(char arr[][MAX_SIZE], int start, int end) 
{
  if (start < end) 
  {
    int mid = start + (end - start) / 2;

    mergeSortStr(arr, start, mid);
    mergeSortStr(arr, mid + 1, end);

    mergeStr(arr, start, mid, end);
      
    printf("[");
    for(int i = start; i <= end; i++) // here i didnt use array output function because the start is not always 0
    {
      printf("%s", arr[i]);
      if (i < end) 
      {
        printf(", ");
      }
    }
    printf("]\n");
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Heapify for heap sort(integer)
///
/// @param root_index root index
/// @param arr an integer array
/// @param size size of an array
///
//
void heapifyInt(int root_index, int arr[][MAX_SIZE], int size) 
{
  int largest = root_index;
  int left = LEFT(root_index);
  int right = RIGHT(root_index);

  if (left < size && arr[left][0] > arr[largest][0])
  {
    largest = left;
  }
  if (right < size && arr[right][0] > arr[largest][0])
  {
    largest = right;
  }
  if (largest != root_index) 
  {
    swap(&arr[root_index][0], &arr[largest][0]);
    heapifyInt(largest, arr, size);
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Heapify for heap sort(string)
///
/// @param root_index root index
/// @param arr an string array
/// @param size size of an array
///
//
void heapifyStr(int root_index, char arr[][MAX_SIZE], int size) 
{
  int largest = root_index;
  int left = LEFT(root_index);
  int right = RIGHT(root_index);

  if (left < size && compareStrings(arr[left], arr[largest]) > 0)
  {
    largest = left;
  }
  if (right < size && compareStrings(arr[right], arr[largest]) > 0)
  {
    largest = right;
  }
  if (largest != root_index) 
  {
    swapStrings(arr[root_index], arr[largest]);
    heapifyStr(largest, arr, size);
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Build heap for heap sort
///
/// @param arr an string array
/// @param size where to start
///
//
void buildHeapStr(char arr[][MAX_SIZE], int size) 
{
  for (int i = size / 2 - 1; i >= 0; i--)
  {
    heapifyStr(i, arr, size);
  }
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Build heap for heap sort
///
/// @param arr an integer array
/// @param size where to start
///
//
void buildHeapInt(int arr[][MAX_SIZE], int size) 
{
  for (int i = size / 2 - 1; i >= 0; i--)
  {
    heapifyInt(i, arr, size);
  }  
}



//---------------------------------------------------------------------------------------------------------------------
///
/// Heap sort for string. Performs heap sort recursevly, each iteration is printed
///
/// @param arr an string array
/// @param size length of an array
///
/// @return sorted array
//
void heapSortStr(char arr[][MAX_SIZE], int size) {
    buildHeapStr(arr, size);
    for (int i = size - 1; i > 0; i--) {
        swapStrings(arr[0], arr[i]);
        heapifyStr(0, arr, i);
        arrayOutputStr(arr, size);
    }
}


//---------------------------------------------------------------------------------------------------------------------
///
/// Heap sort for integer. Performs heap sort recursevly, each iteration is printed
///
/// @param arr an integer array
/// @param size length of an array
///
/// @return sorted array
//
void heapSortInt(int arr[][MAX_SIZE], int size) 
{
  buildHeapInt(arr, size);
  for (int i = size - 1; i > 0; i--) 
  {
    swap(&arr[0][0], &arr[i][0]);
    heapifyInt(0, arr, i);
    arrayOutputInt(arr,size);
  }
}



int ErrorsCheck(int argc, char* argv[],char sort_type[], char data_type[], int number_elements, char elements_to_sort[][MAX_SIZE])
{
  if (argc != 5) 
  {
    printf("Usage: ./a2 <algorithm> <type> <count> <data>\n");
    return 1;
  }
  copyString(sort_type,argv[1]);
  copyString(data_type,argv[2]);
  if(compareStrings(sort_type, "merge") && compareStrings(sort_type, "bubble") && compareStrings(sort_type, "heap"))
  {
    printf("Invalid sorting algorithm!\n");
    return 2;
  }
  if(compareStrings(data_type, "int") && compareStrings(data_type, "string"))
  {
    printf("Invalid data type!\n");
    return 3;
  }
  if (!stringToInt(argv[3]))
  {
    printf("Element count is not an integer!\n");
    return 4;
  }
  if ((*argv[3] - '0') < 1)
  {
    printf("Invalid element count!\n");
    return 5;
  }
  int count = 0; 
  int count2 = 0; 
  for (int i = 0; argv[4][i] != '\0'; i++) 
  {
    if (argv[4][i] == ',') 
    { 
      elements_to_sort[count][count2] = '\0'; 
      count++; 
      count2 = 0; 
    } 
    else 
    {
      elements_to_sort[count][count2++] = argv[4][i];
    }
  }
  elements_to_sort[count][count2] = '\0'; 
  count++;
  if(count < number_elements)
  {
    printf("Not enough elements given!\n");
    return 6;
  }
  if(count > number_elements)
  {
    printf("Too many elements given!\n");
    return 7;
  }
  return 0;
}
