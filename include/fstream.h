#pragma once

#include <cstdio>

#define BIT(x) 1 << x

namespace fileio
{
    namespace io
    {
        enum modifiers
        {
            write = BIT(0),
            read = BIT(1),
            app = BIT(2),
            binary = BIT(3),
            noerase = BIT(4)
        };
    }


    class File
    {
    public:
        File(const char* path, int modifier = io::read);
        File();
    public:
        ~File();

    public: // Public methods
        bool Write(const char* data);
        bool Write(unsigned char* data, size_t count);
    public: // Getters
        inline const bool IsOpen() const {return m_Open;}

    private: // Private non-static variables
        FILE* m_FileHandle;

        bool m_Open;
        bool m_WriteMode;
    private: // Private methods
        void Impl_OpenFile(const char* path, io::modifiers modifier);
    };
}

#ifdef _FSTREAM_IMP_
#include <iostream>
#include <cstring>

static void fopen_imp(const char* path, const char* modes, FILE*& file)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    fopen_s(&file, path, modes);
#else
    file = fopen(path, modes);
#endif
}

namespace fileio
{
    File::File(const char* path, int modifier)
        :m_FileHandle(nullptr), m_Open(false), m_WriteMode(false)
    {
        Impl_OpenFile(path, static_cast<io::modifiers>(modifier));

        if(m_FileHandle != nullptr) // File is open
            m_Open = true;
        else                        // File isn't open
            m_Open = false;
    }
    
    File::File()
    {

    }
    
    File::~File()
    {
        if(m_FileHandle != NULL)
        {
            fclose(m_FileHandle);
        }

    }

    bool File::Write(const char* data)
    {
        size_t count = strlen(data);

        if(m_WriteMode)
        {
            fwrite(data, 1, count, m_FileHandle);
            return true;
        }

        return false;
    }

    bool File::Write(unsigned char* data, size_t count)
    {
        if(m_WriteMode)
        {
            fwrite(data, 1, count, m_FileHandle);
            return true;
        }

        return false;
    }

    // Private methods
    void File::Impl_OpenFile(const char* path, io::modifiers modifier)
    {
        switch((int)modifier)
        {
            case io::write:
                //m_FileHandle = fopen(path, "w");
                fopen_imp(path, "w", m_FileHandle);
                m_WriteMode = true;
                break;
            
            case io::read | io::noerase:
            case io::read:
                fopen_imp(path, "r", m_FileHandle);
                break;
            
            case io::write | io::app:
            case io::write | io::app | io::noerase:
            case io::app | io::noerase:
            case io::write | io::noerase:
            case io::app:
                fopen_imp(path, "a", m_FileHandle);
                m_WriteMode = true;
                break;

            case io::binary | io::noerase:
            case io::binary:
            case io::read | io::binary:
                fopen_imp(path, "rb", m_FileHandle);
                break;
            
            case io::write | io::binary:
                fopen_imp(path, "wb", m_FileHandle);
                m_WriteMode = true;
                break;
            
            case io::app | io::binary:
                fopen_imp(path, "ab", m_FileHandle);
                m_WriteMode = true;
                break;
            
            case io::write | io::read:
                fopen_imp(path, "w+", m_FileHandle);
                m_WriteMode = true;
                break;
            
            case io::write | io::read | io::noerase:
            case io::app | io::read:
                fopen_imp(path, "a+", m_FileHandle);
                m_WriteMode = true;
                break;
            
            case io::write | io::read | io::binary:
                fopen_imp(path, "w+b", m_FileHandle);
                m_WriteMode = true;
                break;
            
            case io::write | io::read | io::noerase | io::binary:
            case io::app | io::read | io::binary:
                fopen_imp(path, "a+b", m_FileHandle);
                m_WriteMode = true;
                break;
            
        }
    }

}

#endif