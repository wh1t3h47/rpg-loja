#pragma once

#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "../Dialog/dialog.hpp"

std::wstring floatParaReais(float valor);
bool respostaSim(const std::wstring pergunta);
int pedirInt(const std::wstring &mensagem);
float pedirFloat(const std::wstring &mensagem);
