#include "Engine/Other/Printer.hpp"

#include <cstdlib>
#include <ctime>
#include <stdarg.h>
#include <iostream>
#include <chrono>

#define SOURCE_PART_SIZE 10

namespace MyEngine {
    std::string Printer::GetTime()
    {
        std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string timeStr = std::ctime(&time);
        return timeStr.substr(11, 8);
    }

    void Printer::Print(const char* format, ...)
    {
        std::cout << "\033[1;96m(" << GetTime() << ") \033[0;47m \033[0m ";

        va_list args;
        va_start(args, format);
        std::vfprintf(stdout, format, args);
        va_end(args);

        std::cout << '\n';
    }

    void Printer::Print(Printer::PRINT_CATEGORY category, const char* format, ...)
    {
        std::cout << "\033[1;96m(" << GetTime() << ")\033[0m ";
        PrintCategoryTag(category);
        // PrintSource(source);

        va_list args;
        va_start(args, format);
        std::vfprintf(stdout, format, args);
        va_end(args);

        std::cout << '\n';
    }

    void Printer::PrintError(const char* format, ...)
    {
        std::cout << "\033[1;96m(" << GetTime() << ") \033[0;101mERROR\033[1;40;97m \033[0m";

        va_list args;
        va_start(args, format);
        std::vfprintf(stderr, format, args);
        va_end(args);

        std::cout << '\n';
    }

    void Printer::PrintError(Printer::PRINT_CATEGORY category, const char* format, ...)
    {
        std::cout << "\033[1;96m(" << GetTime() << ")\033[0m ";
        PrintCategoryTag(category);
        std::cout << "\033[0;101mERROR\033[1;40;97m \033[0m";

        va_list args;
        va_start(args, format);
        std::vfprintf(stdout, format, args);
        va_end(args);

        std::cout << '\n';
    }

    void Printer::PrintWarning(const char* format, ...)
    {
        std::cout << "\033[1;96m(" << GetTime() << ") \033[0;30;103mWARNING\033[1;40;97m \033[0m";

        va_list args;
        va_start(args, format);
        std::vfprintf(stdout, format, args);
        va_end(args);

        std::cout << '\n';
    }

    void Printer::PrintWarning(Printer::PRINT_CATEGORY category, const char* format, ...)
    {
        std::cout << "\033[1;96m(" << GetTime() << ")\033[0m ";
        PrintCategoryTag(category);
        std::cout << "\033[0;30;103mWARNING\033[1;40;97m \033[0m";

        va_list args;
        va_start(args, format);
        std::vfprintf(stdout, format, args);
        va_end(args);

        std::cout << '\n';
    }

    void Printer::PrintSource(std::string source)
    {
        if (source.size() > SOURCE_PART_SIZE)
        {
            for (int i = 0; i < SOURCE_PART_SIZE + 1; i++)
                std::cout << ' ';
            return;
        }

        std::string slots(SOURCE_PART_SIZE, ' ');

        for (int i = 0; i < source.size(); i++)
        {
            slots[i] = source[i];
        }

        std::cout << slots << "   ";
    }

    void Printer::PrintCategoryTag(Printer::PRINT_CATEGORY category)
    {
        switch (category)
        {
            case ECS:
                std::cout << "\033[0;105m \033[0m ";
                break;

            case GRAPHICS:
                std::cout << "\033[0;102m \033[0m ";
                break;

            case PHYSICS:
                std::cout << "\033[0;104m \033[0m ";
                break;

            default:
                std::cout << "\033[0;47m \033[0m ";
                break;
        }
    }
}
