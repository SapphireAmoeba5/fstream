#pragma once



#ifdef _FSTREAM_IMP_

#include <iostream>

namespace fileio
{
    void Hello()
    {
        std::cout<<"Hello, World!\n";
    }
}

#endif


namespace fileio
{
    void Hello();
}