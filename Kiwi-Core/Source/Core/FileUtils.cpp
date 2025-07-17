#include "FileUtils.h"

namespace Kiwi {

    std::string ReadFile(std::filesystem::path filepath)
    {
        std::ifstream fileStream(filepath, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "ERROR: Could not open shader file: " << filepath << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        return buffer.str();
    }

}