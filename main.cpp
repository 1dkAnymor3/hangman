#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>

#define endl "\n"
#define cout std::cout
#define cin std::cin

std::vector<std::string> importTxtFileAsVec(std::string txtFileLoc)
{
    std::string line;
    std::ifstream txtFile(txtFileLoc);
    std::vector<std::string> vec;
    if (txtFile.is_open())
    {
        while (getline(txtFile, line))
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

void addSymbolByNTimes(std::string &s, char symbol, int n)
{
    for (int i = 0; i < n; i++)
    {
        s = s + symbol;
    }
}

bool findCharInString(int &index, char c, std::string s)
{
    for (index = 0; index < s.size(); index++) // a simple loop will do fine, its not like we're doing 10000 letters long words
    {
        if (s.at(index) == c)
        {
            return true;
        }
    }
    index = 0;
    return false;
}

void smallLetterIfy(std::string &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if ((int)s.at(i) >= 65 && (int)s.at(i) <= 90) s.at(i) += 32; // difference between capital and small letter in ascii table is 32 (97 - 65)
    }
}

int main()
{
    // init
    srand(time(nullptr)); // set seed
    std::vector<std::string> wordList = importTxtFileAsVec("wordlist.txt"); // get wordlist
    std::vector<std::vector<std::string>> costumes(7);
    for (int i = 0; i < 7; i++) costumes[i] = importTxtFileAsVec("costumes/costume" + std::to_string(i + 1) + ".txt"); // import all costumes
    int maxTurns = costumes.size();
    int fail = 0;
    std::string answer = wordList.at(randint(0, wordList.size() - 1));
    std::string view = ""; addSymbolByNTimes(view, '_', answer.size());

    // main loop
    do
    {
        for (std::string line : costumes.at(fail)) cout << line << endl;
        cout << view << endl;
        if (fail >= maxTurns) break; // see if already past the max fail limit, but still allows it to show the hangman
        std::string guess = ""; getline(cin, guess);
        smallLetterIfy(guess);
        if (guess.size() < 2)
        {
            int index = 0;
            char cGuess = guess.c_str()[0];
            if (findCharInString(index, cGuess, answer))
            {
                view.at(index) = cGuess;
            }
            else fail++;
        }
        else
        {
            if (guess == answer) view = answer;
            else fail++;
        }
    } while (fail < maxTurns && view != answer);
    
    if (view == answer) cout << "You Win!" << endl;
    else cout << "You Lose. The answer was " << answer << endl;

    return 0;
}