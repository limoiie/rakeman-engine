//
// Created by limo on 1/8/18.
//

#include "string2wstring.h"

#include <codecvt>
#include <locale>


std::wstring String2WString(const std::string &c) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(c);
}

std::string WString2String(const std::wstring &w) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(w);
}
