#include "Discovery.h"

Discovery::Discovery(std::string srcDir)
{
    sourceDir = srcDir;
}

void Discovery::start() {
    readDir(sourceDir);
}


void Discovery::readDir(const std::string& path) {
    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR)
                readDir(path + f->d_name + "/");

            if (f->d_type == DT_REG)
                std::cout << "=> " << path + f->d_name << "\n";
        }
        closedir(dir);
    }
}