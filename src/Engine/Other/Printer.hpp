#ifndef Other_H
#define Other_H

#include <string>

namespace MyEngine {
    namespace Printer
    {
        std::string GetTime();

        enum PRINT_CATEGORY { ECS, GRAPHICS, PHYSICS, OTHER };

        void Print(const char* message, ...);
        void Print(PRINT_CATEGORY category, const char* message, ...);

        void PrintError(PRINT_CATEGORY, const char* message, ...);
        void PrintError(const char* message, ...);

        void PrintWarning(const char* message, ...);
        void PrintWarning(PRINT_CATEGORY category, const char* message, ...);

        void PrintCategoryTag(PRINT_CATEGORY category);
        void PrintSource(std::string source);
    }
}

#endif
