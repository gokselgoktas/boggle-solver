#ifndef BOGGLE_API_HPP
#define BOGGLE_API_HPP

struct Results {
        char const *const *Words;

        unsigned Count;
        unsigned Score;

        void *UserData;
};

void LoadDictionary(char const *path);

Results FindWords(char const* board, unsigned width, unsigned height);

// Why is results passed by-value?  It's triggering my OCD. :D
void FreeWords(Results results);
void FreeDictionary();

#endif
