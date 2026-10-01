#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

class TemperatureMonitor {
private:
    std::string devicePath;

public:
    explicit TemperatureMonitor(const std::string& path)
        : devicePath(path) {}

    int readTemperature() const {
        int fd = open(devicePath.c_str(), O_RDONLY);

        if (fd == -1) {
            throw std::runtime_error(
                "Cannot open " + devicePath + ": " + std::strerror(errno));
        }

        char buffer[32] = {};
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);

        if (bytesRead == -1) {
            std::string message = std::strerror(errno);
            close(fd);
            throw std::runtime_error("Cannot read temperature: " + message);
        }

        close(fd);

        return std::stoi(std::string(buffer, bytesRead));
    }
};

int main() {
    try {
        TemperatureMonitor monitor("/dev/vtemp");
        int temperature = monitor.readTemperature();

        std::cout << "Virtual Temperature: "
                  << temperature << " C" << std::endl;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}
