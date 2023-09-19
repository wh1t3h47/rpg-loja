
#include "dialog_abstract.hpp"

using namespace std;

class RpgDialogBox : public AbstractRpgDialogBox
{
private:
    bool isQuestion;
    wstring ans;
    wstring executeDialog(const wstring &message)
    {
        vector<wstring> messageVector;

        for (wchar_t c : message)
        {
            messageVector.push_back(wstring(1, c));
        }

        const int messageSize = messageVector.size();
        int chunkSize = 200;

        srand(time(NULL));

        for (int currentIndex = 0; currentIndex < messageSize;)
        {
            int remainingSize = messageSize - currentIndex;

            // Encontre as posições das quebras de linha no restante da mensagem
            int numeroLinhas = 0;
            for (int i = currentIndex; i < currentIndex + min(chunkSize, remainingSize); ++i)
            {
                if (messageVector[i] == L"\n")
                {
                    if (++numeroLinhas > 4)
                    {
                        chunkSize = i - currentIndex + 1;
                        break;
                    }
                    else
                    {
                        chunkSize = 200;
                    }
                }
            }

            int currentChunkSize = min(chunkSize, remainingSize);

            wstring chunk;
            for (int i = 0; i < currentChunkSize; ++i)
            {
                chunk += messageVector[currentIndex + i];
            }

            bool isLastChunk = !(currentIndex + currentChunkSize < messageSize);

            if (this->isQuestion)
            {
                if (isLastChunk)
                    return dialogAskForAnswer(chunk);
                else
                    dialogWaitForEnter(chunk);
            }
            else
            {
                dialogWaitForEnter(chunk);
            }

            currentIndex += currentChunkSize;
        }

        clearScreen();
        return L"";
    }

    void message(const wstring &message)
    {
        this->isQuestion = false;
        this->executeDialog(message);
    }

    wstring question(const wstring &message)
    {
        this->isQuestion = true;
        return this->executeDialog(message);
    }

public:
    RpgDialogBox()
    {
        // setlocale(LC_ALL, "pt_BR.UTF-8");
#ifdef _WIN32
        wcout << "Rodando no Windows";
#else
        wcout << "Rodando no Linux";
#endif
        for (int i = 0; i < 3; i++)
        {
            wcout << "." << flush;
            this_thread::sleep_for(chrono::seconds(1));
        }
        clearScreen();
    }

    RpgDialogBox &operator<<(const wstring &message)
    {
        this->message(message);
        return *this;
    }

    template <typename T>
    RpgDialogBox &operator<<(const T &value)
    {
        wstringstream ss;
        ss << value;
        this->message(ss.str());
        return *this;
    }

    RpgDialogBox &operator>>(const wstring &question)
    {
        this->ans = this->question(question);
        return *this;
    }

    RpgDialogBox &operator>>(wstring &ans)
    {
        ans = this->ans;
        return *this;
    }
};

extern RpgDialogBox dialogBox;
