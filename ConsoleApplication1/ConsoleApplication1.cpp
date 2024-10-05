#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>


void displayGPUSummary() {
    std::cout << "+-----------------------------------------------------------------------------+" << std::endl;
    std::cout << "| NVIDIA-SMI 460.39       Driver Version: 460.39       CUDA Version: 11.2     |" << std::endl;
    std::cout << "|-------------------------------+----------------------+----------------------|" << std::endl;
    std::cout << "| GPU  Name             TCC/WDM | Bus-Id        Disp.A | Volatile Uncorr. ECC |" << std::endl;
    std::cout << "| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |" << std::endl;
    std::cout << "|                               |                      |               MIG M. |" << std::endl;
    std::cout << "|===============================+======================+======================|" << std::endl;
    std::cout << "|   0  GeForce GTX 1080    Off  | 00000000:26:00.0  On |                  N/A |" << std::endl;
    std::cout << "|  30%   65C    P2    60W / 180W|   4096MiB /  8192MiB |     40%      Default |" << std::endl;
    std::cout << "+-------------------------------+----------------------+----------------------+" << std::endl;
    std::cout << std::endl;
}

void displayProcessHeader() {
    std::cout << "+-----------------------------------------------------------------------------+" << std::endl;
    std::cout << "| Processes:                                                       GPU Memory |" << std::endl;
    std::cout << "|  GPU       PID   Type   Process name                             Usage      |" << std::endl;
    std::cout << "|=============================================================================|" << std::endl;
}

std::string truncateString(const std::string& str, size_t width) {
    if (str.length() > width) {
        return str.substr(0, width - 4) + "...";  
    }
    return str;
}

void displayProcess(int gpu, int pid, const std::string& type, const std::string& processName, const std::string& memoryUsage) {
    const int gpuWidth = 3;         
    const int pidWidth = 10;         
    const int typeWidth = 7;        
    const int processNameWidth = 41;
    const int memoryUsageWidth = 10;

    std::string truncatedProcessName = truncateString(processName, processNameWidth);

    std::cout << "|  " << std::setw(gpuWidth) << gpu
        << std::setw(pidWidth) << pid
        << std::setw(typeWidth) << type
        << "  " << std::setw(processNameWidth) << std::left << truncatedProcessName
        << std::setw(memoryUsageWidth) << std::right << memoryUsage
        << "  |" << std::endl;
}

void displayProcessList() {
    displayProcessHeader();

    std::cout << "+-----------------------------------------------------------------------------+" << std::endl;
    displayProcess(0, 1234, "C+G", "process1.exe", "1024MiB");
    displayProcess(0, 5678, "C+G", "very_long_process_name_for_testing_the_func_if_works.exe", "512MiB");
    displayProcess(0, 9101, "C+G", "process3.exe", "768MiB");
    displayProcess(0, 1121, "C+G", "another_extremely_long_process_name.exe", "256MiB");
    displayProcess(0, 3141, "C+G", "process5.exe", "128MiB");
    std::cout << "+-----------------------------------------------------------------------------+" << std::endl;

}

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::tm local_time;
    localtime_s(&local_time, &now_time);

    std::ostringstream timestamp;
    timestamp << std::put_time(&local_time, "%a %b %d %H:%M:%S %Y");

    return timestamp.str();
}

int main() {
    system("cls");
    std::cout << getCurrentTimestamp() << std::endl;
    displayGPUSummary();
    displayProcessList();
   
    return 0;
}
