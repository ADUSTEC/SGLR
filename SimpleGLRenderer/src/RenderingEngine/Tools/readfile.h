#pragma once
#include <mio/mmap.hpp>
#include <string>

// really basic file reader

namespace SGLR {

    class file {
        public:
            static const char* read(const char* filename)
            {
                mio::mmap_source mmap_file(filename);
                std::string* fileContent = new std::string(mmap_file.data(), mmap_file.size());
                return fileContent->c_str();
                delete fileContent;
            }
        };
}