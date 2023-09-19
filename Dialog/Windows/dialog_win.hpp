#ifdef /* é Windows? */ _WIN32
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
#include <functional>
#include <pthread.h>
#include <mutex>
#include <condition_variable>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#else
#include <unistd.h>
#endif

// Protótipos das funções compartilhadas entre linux e windows
extern void clearScreen();
extern void setColor(int color);
extern void waitForEnter();
extern std::wstring askForAnswer();
extern void printColoredChar(wchar_t c);
extern void *startDialog(void *thread_ptr);
extern void checkEnterPressed();
void *startDialog(void *thread_ptr);
extern void dialogWaitForEnter(const std::wstring str);
extern std::wstring dialogAskForAnswer(const std::wstring str);

// Windows apenas
extern void setCursorPosition(int x, int y);
extern void blockInput();
extern void restoreInput();

#endif // DIALOG_HPP
#endif // Windows