#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <boost/filesystem.hpp>

std::string getFile(const std::string &filename)
{
    using namespace boost::filesystem;
    path program_path(initial_path<path>());
    if (program_path.filename() == "debug" ||
        program_path.filename() == "release")
    {
        program_path = program_path.parent_path();
    }
    program_path = program_path.parent_path();
    program_path /= filename;
    return program_path.file_string();
}

#endif // UTILS_H
