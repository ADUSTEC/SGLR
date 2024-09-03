#pragma once
#include <mio/mmap.hpp>
#include <string>

// really basic file reader

namespace SGLR {

    class file {
        public:
            static std::string read(std::string filename)
            {
                mio::mmap_source mmap_file(filename.c_str());
                return std::string(mmap_file.data(), mmap_file.size());
            }
        };
}