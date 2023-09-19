#ifndef /* é Linux? */ _WIN32
#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <locale.h>
#include <atomic>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#else
#include <unistd.h>
#include <csignal>
#include <termios.h>
#endif

// Protótipos das funções compartilhadas entre linux e windows
extern void clearScreen();
extern void waitForEnter();
extern std::wstring askForAnswer();
extern void printColoredChar(wchar_t c);
extern void printColoredDialog(std::wstring &str);
extern void checkEnterPressed();
extern void startDialog(std::wstring &str);
extern void dialogWaitForEnter(std::wstring &str);
extern std::wstring dialogAskForAnswer(std::wstring &str);

#endif // DIALOG_HPP
#endif // Linux