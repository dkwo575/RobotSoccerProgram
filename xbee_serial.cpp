#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#define SERIAL_PORT "/dev/cu.usbserial-D30DU04O"  // Change this if needed
#define BAUDRATE B9600  // Match XBee baud rate (default 9600)

int openSerialPort(const char* port) {
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        std::cerr << "Error: Cannot open serial port " << port << std::endl;
        return -1;
    }

    struct termios options;
    tcgetattr(fd, &options);

    cfsetispeed(&options, BAUDRATE);
    cfsetospeed(&options, BAUDRATE);

    options.c_cflag |= (CLOCAL | CREAD); // Enable receiver
    options.c_cflag &= ~PARENB;  // No parity
    options.c_cflag &= ~CSTOPB;  // 1 stop bit
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;  // 8 data bits

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    options.c_oflag &= ~OPOST; // Raw output

    tcsetattr(fd, TCSANOW, &options);
    return fd;
}

void sendCommand(int fd, const std::string& cmd) {
    write(fd, cmd.c_str(), cmd.length());
    write(fd, "\r", 1);  // Send carriage return
}

std::string readResponse(int fd) {
    char buffer[256];
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        return std::string(buffer);
    }
    return "";
}

int main() {
    int fd = openSerialPort(SERIAL_PORT);
    if (fd == -1) return 1;

    std::cout << "Connected to XBee. Enter commands (e.g., dd1 to turn LED on):" << std::endl;

    while (true) {
        std::string command;
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") break;

        sendCommand(fd, command);
        usleep(100000);  // Wait for response
        std::string response = readResponse(fd);
        
        if (!response.empty()) {
            std::cout << "Arduino Response: " << response << std::endl;
        }
    }

    close(fd);
    return 0;
}
