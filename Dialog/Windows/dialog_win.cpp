#include "dialog_win.hpp"
#ifdef /* é Windows? */ _WIN32
#define COR_FUNDO BACKGROUND_BLUE | 0x00
#define BRANCO_NEGRITO FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define ENTER_KEYCODE 0x8000
#define X_START 4
#define Y_START 2

using namespace std;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void clearScreen()
{
    system("cls");
}

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color | COR_FUNDO);
}

void setCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void waitForEnter()
{

    setCursorPosition(10, 7);

    setColor(14);
    cout << "< Pressione Enter para Continuar >";

    setColor(7);
    while (cin.get() != '\n')
        ;
    cin.clear();
}

wstring askForAnswer()
{
    cin.clear();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    wcout << L"Entre Resposta > ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    wstring answer;
    getline(wcin, answer); // Read the entire line as an answer
    return answer;
}

void printColoredChar(wchar_t c)
{
    int color = rand() % 5;
    setColor((color + 10) | FOREGROUND_INTENSITY);
    wcout << c;
    setColor(7);
}

atomic<bool> isEnterPressed(false);
void *printColoredDialog(void *ptr)
{
    wstring str = *(wstring *)ptr;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COR_FUNDO | BRANCO_NEGRITO);
    string dialogArt =
        "+--------------------------------------------------------+\n"
        "|                                                        |\n"
        "|                                                        |\n"
        "|                                                        |\n"
        "|                                                        |\n"
        "|                                                        |\n"
        "|                                                        |\n"
        "+--------------------------------------------------------+\n";

    int startX = 0;
    int startY = 0;

    int contentX = startX + X_START;
    int contentY = startY + Y_START;

    setCursorPosition(startX, startY);
    cout << endl
         << dialogArt;
    setCursorPosition(contentX, contentY);

    for (wchar_t c : str)
    {
        if (contentY >= startY + 7)
        {
            break;
        }
        if (c == L'\n')
        {
            contentY++;
            setCursorPosition(X_START, contentY);
            contentX = 0;
            continue;
        }

        printColoredChar(c);
        if (!isEnterPressed)
        {
            // Signal all waiting threads
            pthread_mutex_lock(&mutex);
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&mutex);
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        contentX++;
        if (contentX >= startX + 55)
        {
            contentX = startX + 4;
            contentY++;
            setCursorPosition(contentX, contentY);
        }
    }

    cout << endl;

    pthread_cond_broadcast(&cond);

    return (void *)nullptr;
}

void *checkEnterPressed(void *arg)
{
    while (!isEnterPressed)
    {
        // Lock the mutex and wait for a signal
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);

        if (cin.peek() == '\n')
        {
            isEnterPressed = true;

            return nullptr;
        }

        this_thread::sleep_for(chrono::milliseconds(10)); // Sleep to avoid busy-waiting
    }

    return nullptr;
}

void blockInput()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;

    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, prevMode & ~ENABLE_ECHO_INPUT);
}

void restoreInput()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prevMode;

    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, prevMode | ENABLE_ECHO_INPUT);
}

void *startDialog(void *thread_ptr)
{

    wstring str = *(wstring *)thread_ptr;
    if (isEnterPressed)
    {
        isEnterPressed = false;
    }

    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        perror("Erro na inicialização do mutex");
        exit(1);
    }

    pthread_t dialogThread;
    pthread_t checkThread;

    if (pthread_create(&dialogThread, nullptr, printColoredDialog, (void *)&str) != 0)
    {
        wcerr << "Erro ao criar a thread de diálogo." << endl;
        exit(1);
    }

    if (pthread_create(&checkThread, nullptr, checkEnterPressed, nullptr) != 0)
    {
        wcerr << "Erro ao criar a thread de verificação." << endl;
        exit(1);
    }

    if (pthread_detach(checkThread) != 0)
    {
        wcerr << "Erro ao desanexar a thread de verificação." << endl;
        exit(1);
    }

    blockInput();

    if (pthread_join(dialogThread, nullptr) != 0)
    {
        wcerr << "Erro ao aguardar a conclusão da thread de diálogo." << endl;
        exit(1);
    }

    restoreInput();

    if (isEnterPressed)
    {
        while (cin.get() != '\n')
            ;
    }
    // finaliza a thread checkThread
    //  isEnterPressed = true;
    pthread_cancel(checkThread);

    // limpa mutex
    pthread_mutex_destroy(&mutex);

    return (void *)nullptr;
}

void dialogWaitForEnter(wstring str)
{
    startDialog((void *)&str);
    waitForEnter();
}

wstring dialogAskForAnswer(wstring str)
{
    startDialog((void *)&str);
    return askForAnswer();
}

#endif
