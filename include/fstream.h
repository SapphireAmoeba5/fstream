#pragma once



#ifdef _FSTREAM_IMP_

#include <iostream>

namespace fileio
{
    
}

#endif


namespace fileio
{
    enum class Modes
    {
        write = 2,
        read = 4,
        binary = 8,
        
    };

    class File
    {
    public:
        File(const char* path); 
    
    };
}