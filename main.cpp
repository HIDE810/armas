#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class Temp
{
public:
    Temp() {
        fs::create_directory("tmp");
    }

    ~Temp() {
        fs::remove_all("tmp");
    }
};

int main(int argc, const char *argv[]) {

    std::string code;

    if(argc != 2) {
        std::cout << "error: invalid parameter" << std::endl;
        return -1;
    }

    Temp temp;

    std::ofstream ofs("tmp/code.s");
    ofs << ".text;.global main;main:" << argv[1] << std::endl;

    if(system("arm-linux-gnueabi-as tmp/code.s -o tmp/code.o"))
        return -1;

    if(system("arm-linux-gnueabi-objdump -d tmp/code.o > tmp/dump.s"))
        return -1;

    std::ifstream ifs("tmp/dump.s");

    for(int i=0; i<7; i++)
        getline(ifs, code);

    getline(ifs, code);

    std::cout << code.substr(6, 8) << std::endl;

    return 0;
}
