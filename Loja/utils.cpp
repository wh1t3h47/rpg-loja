#include "utils.hpp"

using namespace std;

bool respostaSim(wstring pergunta)
{
    wstring ans;
    dialogBox >> pergunta >> ans;
    transform(ans.begin(), ans.end(), ans.begin(), towlower);
    return ans == L"s" || ans == L"sim";
}

// Formata o valor como uma string no formato "R$ X,XX"
wstring floatParaReais(float valor)
{
    wstringstream ss;
    ss << L"R$ " << fixed << setprecision(2) << valor;

    wstring resultado = ss.str();
    size_t pos = resultado.find(L".");
    if (pos != wstring::npos)
    {
        resultado.replace(pos, 1, L",");
    }

    return resultado;
}

int pedirInt(const wstring &mensagem)
{
    while (true)
    {
        wstring entrada;
        dialogBox >> mensagem >> entrada;

        try
        {
            int numero = stoi(entrada);
            return numero;
        }
        catch (const invalid_argument &)
        {
            return -1;
        }
    }
    return -1;
}

float pedirFloat(const wstring &mensagem)
{
    while (true)
    {
        wstring entrada;
        dialogBox >> mensagem >> entrada;

        try
        {
            float numero = stof(entrada);
            return numero;
        }
        catch (const invalid_argument &)
        {
            return -1;
        }
    }
    return -1;
}
