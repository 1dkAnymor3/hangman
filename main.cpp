#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> importTxtFileAsVec(std::string txtFileLoc)
{
    std::string line;
    std::ifstream txtFile(txtFileLoc);
    std::vector<std::string> vec;
    if (txtFile.is_open())
    {
        while(getline(txtFile, line))
        {
            vec.push_back(line);
        }
        txtFile.close();
    }
    else throw("File is not found");
    return vec;
}

int randint(int min, int max)
{
    return rand() % (max - min) + min;
}

int main()
{
    srand(time(nullptr));
    std::vector<std::string> wordList = importTxtFileAsVec("wordlist.txt");
    int r = 0;
    while (r++ < 10) std::cout << wordList.at(randint(0, wordList.size() - 1)) << "\n";
    return 0;
}