
#ifndef /* é Linux? */ _WIN32
#include "dialog_linux.hpp"

using namespace std;

#define NEGRITO "\033[1m"
#define RESET "\033[0m"
#define COR_FUNDO "\033[40m"
#define AMARELO_PROMPT "\033[0;33m"
#define REMOVE_CURSOR_TERMINAL "\033[?25l"
#define MOVE_CURSOR_PARA_DIRETA_10 "\033[10C"
#define PRETO "\033[0;30m"
#define VERMELHO "\033[0;31m"
#define VERDE "\033[0;32m"
#define AMARELO "\033[0;33m"
#define AZUL "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CIANO "\033[0;36m"
#define BRANCO "\033[0;37m"

void clearScreen()
{
    system("clear");
}

void waitForEnter()
{
    wcout << endl
          << REMOVE_CURSOR_TERMINAL;
    wcout << MOVE_CURSOR_PARA_DIRETA_10;
    wcout << AMARELO_PROMPT << COR_FUNDO << "< Pressione Enter para Continuar >" << RESET;
    cin.clear(); // Clear any error flags if necessary
    cin.ignore('\n');
}

wstring askForAnswer()
{
    wcout << endl
          << REMOVE_CURSOR_TERMINAL;
    wcout << MOVE_CURSOR_PARA_DIRETA_10;
    wcout << AMARELO_PROMPT << COR_FUNDO << "Entre Resposta > " << RESET;
    wstring answer;
    getline(wcin, answer);
    return answer;
}

void printColoredChar(wchar_t c)
{
    char *colors[] = {
        // PRETO,
        VERMELHO,
        VERDE,
        AMARELO,
        // AZUL,
        MAGENTA,
        CIANO,
        BRANCO};
    int color = rand() % sizeof(colors) / sizeof(colors[0]);

    wcout
        << NEGRITO << colors[color] << COR_FUNDO << c << RESET << flush;
}

atomic<bool> isEnterPressed(false);

void printColoredDialog(wstring &str)
{

    wcout << COR_FUNDO;
    wstring dialogArt =
        L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
        L"┃                                                       ┃\n"
        L"┃                                                       ┃\n"
        L"┃                                                       ┃\n"
        L"┃                                                       ┃\n"
        L"┃                                                       ┃\n"
        L"┃                                                       ┃\n"
        L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

    int startX = 0;
    int startY = 0;

    wcout << "\033[" << startY << ";" << startX << "H";

    int contentX = startX + 4;
    int contentY = startY + 3;

    wcout << endl
          << dialogArt;
    wcout << "\033[" << contentY << ";" << contentX << "H";

    for (wchar_t c : str)
    {
        if (contentY >= startY + 7)
        {
            break;
        }
        if (c == L'\n')
        {
            contentY++;
            wcout << "\033[" << contentY << ";" << contentX << "H";
            continue;
        }

        printColoredChar(c);
        if (!isEnterPressed)
            this_thread::sleep_for(chrono::milliseconds(10));
        contentX++;
        if (contentX >= startX + 55)
        {
            contentX = startX + 4;
            contentY++;
            wcout << "\033[" << contentY << ";" << contentX << "H";
        }
    }
    wcout << endl;
}

// função que vai ser executada numa thread, a cada 15ms vai
// verificar se foi apertado enter, se sim, vai setar a atomic
void checkEnterPressed()
{
    while (!isEnterPressed)
    {
        if (cin.peek() == '\n')
        {
            isEnterPressed = true;
            return;
        }
    }
}

void startDialog(wstring &str)
{
    // bloqueia entrada de caracteres:
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    if (isEnterPressed)
    {
        isEnterPressed = false;
    }
    thread dialogThread(printColoredDialog, str);
    thread checkThread(checkEnterPressed);
    dialogThread.join();
    checkThread.detach();
    if (isEnterPressed)
    {
        cin.ignore('\n');
    }
    // finaliza a thread checkThread
    isEnterPressed = true;
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void dialogWaitForEnter(wstring &str)
{
    startDialog(str);
    waitForEnter();
}

wstring dialogAskForAnswer(wstring &str)
{
    startDialog(str);
    return askForAnswer();
}

#endif
