#include "Daw.h"

int main()
{
    pul::AudioEngine* daw = new pul::Daw;

    daw -> run();

    delete daw;

    std::cin.get();

    return EXIT_SUCCESS;
}