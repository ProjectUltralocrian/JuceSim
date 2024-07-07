#include "Daw.h"

int main()
{
    pul::AudioEngine* daw = new pul::Daw;

    daw -> run();

    delete daw;

    return EXIT_SUCCESS;

}