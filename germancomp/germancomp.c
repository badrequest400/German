#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char** argv) {
  if(argc != 3) {
    printf("Usage: %s [input german file] [output file]\n", argv[0]);
    exit(0);
  }
  FILE* input;
  input = fopen(argv[1], "r");
  char* inputarray;
  char c = '\0';
  if(!input) {
    printf("Failed to open %s.Check if it exists\n", argv[1]);
    exit(0);
  }
  printf("Warning, this will overwrite %s, beginning in 3 seconds\n", argv[2]);
  for(int i = 3; i > 0; i--) {
    printf("%d...", i);
    fflush(stdout);
    sleep(1);
  }
  putchar('\n');
  FILE* output;
  output = fopen(argv[2], "w");
  fseek(input, 0L, SEEK_END);
  int size = ftell(input);
  fseek(input, 0L, SEEK_SET);
  inputarray = malloc(size * sizeof(char));
  for(int i = 0; i < size; i++)
    inputarray[i] = fgetc(input);
  int j = 0;
  for(int i = 0; i < size - 9; i++) {
    if(toupper(inputarray[i]) == 'L' && toupper(inputarray[i + 1]) == 'A' && toupper(inputarray[i + 2]) == 'D' && toupper(inputarray[i + 3]) == 'S') {
      c |= (1 << (7 - j));
      i+=4;
      j++;
    }
    else if(toupper(inputarray[i]) == 'B' && toupper(inputarray[i + 1]) == 'E' && toupper(inputarray[i + 2]) == 'E' && toupper(inputarray[i + 3]) == 'R' && toupper(inputarray[i + 4]) == 'S') {
      i+=9;
      j++;
    }
    if(j == 8)  {
      fputc(c, output);
      j = 0;
      c = '\0';
    }
  }
  return 0;
}
