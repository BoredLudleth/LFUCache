#include <string>
#include <fstream>

std::string runBinary(const std::string& binaryPath, const std::string& input) {
    std::string command = binaryPath + " < " + input;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    char buffer[128];

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}