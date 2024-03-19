#include <stdlib.h>
#include <stdio.h>

// Saves us having to add in __LINE__ every time we call line_die().
#define DIE(error) (line_die(__LINE__, error))

// Our error function. Prints out the line number and error message.
void line_die(int line, const char* error) {
  printf("%d: %s", line, error);
  exit(1);
}

// Initialise our memory.
int init(char** ptr) {
  int initial_size = 5;
  *ptr = calloc(initial_size, sizeof(char));

  if (ptr == NULL) {
    DIE("Could not initialise memory.");
  }
    
  return initial_size;
}

// Extend our memory.
int extend(char **ptr, int cur_len) {
  int new_len = cur_len + 5;

  *ptr = realloc(*ptr, new_len*(sizeof(char)));

  if (*ptr == NULL) {
    DIE("Could not reallocate memory.");
  }

  return new_len;
}

int main(void) {
  int length = 0;  // Keeps track of how much memory we have.
  char* ptr = NULL;   // A pointer to our memory.

  // Initialise our memory.
  length = init(&ptr);
  printf("Allocated %lu bytes.\n\n", (length * sizeof(char)));

  char c;  // Holds our current character.
  int last = 0; // Keeps track of our last assignment to ptr.

  printf("Enter characters.\n\t@ to view memory.\n\t# to exit.\n\n");

  // Main loop. We've set a limit of 79 characters.
  
  while(last < 80) {
    c = getchar();
    
    if (c == '\n') {
      continue;
    } else if (c == '#') {
      break;
    } else if (c == '@') {
      printf("Memory: %s\n", ptr);
    } else {
      if (last == length) {
	/* If we are at the end of the assigned memory, we call extend(). */
	length = extend(&ptr, length);
	printf("Extended. New size is %lu bytes.\n", length * sizeof(char));
      }

      ptr[last] = c;
      last++;
    }
  }
}
