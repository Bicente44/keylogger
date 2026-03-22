#include <stdio.h>

void windows_keylogger(int argc, char *argv[]) {

  if (argc < 2) {
    /* TODO make output file */
    printf("Usage: ./[PROGRAM NAME] [OPTION] [outputfile]\n"
           "Option 1\n"
           "Outputfile as an option if you want to log your key inputs\n");
    return;
  }
  printf("Keylogger started\n");
}
