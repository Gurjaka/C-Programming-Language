#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char filename[256];
  printf("File path (max 256 char): ");
  scanf("%255s", filename);

  FILE *file = fopen(filename, "r"); // Open the file in read mode
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char line[256]; // Buffer to store each line
  while (fgets(line, sizeof(line), file) != NULL) {
    int i = 0;
    int in_comment = 0; // Flag to indicate we're inside a block comment
    int in_string = 0;  // Flag to indicate we're inside a string

    while (line[i] != '\0') {
      // Handle string literals: toggle in_string flag when encountering quotes
      if (line[i] == '"' &&
          (i == 0 || line[i - 1] != '\\')) { // Ignore escaped quotes
        in_string = !in_string;              // Toggle the string flag
      }
      // If we're not inside a comment, check for comment start
      if (!in_comment && i + 1 < sizeof(line) && line[i] == '/' &&
          line[i + 1] == '*') {
        in_comment = 1; // Found the start of a block comment
        i++;            // Skip the '*' to continue processing
      }
      // If we're inside a comment, check for comment end
      else if (in_comment && i + 1 < sizeof(line) && line[i] == '*' &&
               line[i + 1] == '/') {
        in_comment = 0; // Found the end of the block comment
        i++;            // Skip the '/' to continue processing
      }
      // If we're not inside a comment, check for line comment
      else if (!in_comment && i + 1 < sizeof(line) && line[i] == '/' &&
               line[i + 1] == '/') {
        break; // Skip the rest of the line (single-line comment)
      } else {
        if (!in_comment) {
          putchar(line[i]);
        }
      }
      i++; // Move to the next character
    }
  }

  fclose(file); // Close the file
  return EXIT_SUCCESS;
}
