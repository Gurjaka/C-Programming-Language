void reverse(char *string) {
  char *end = string;

  while (*end)
    end++;

  --end;

  while (end > string) {
    char temp = *string;
    *string++ = *end;
    *end-- = temp;
  }
}
