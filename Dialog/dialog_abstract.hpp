#pragma once
#include <string>
#ifdef _WIN32

#include "Windows/dialog_win.hpp"

#else

#include "Linux/dialog_linux.hpp"

#endif

class AbstractRpgDialogBox
{
public:
    virtual ~AbstractRpgDialogBox() {}

    virtual void message(const std::wstring &message) = 0;
    virtual std::wstring question(const std::wstring &message) = 0;
};