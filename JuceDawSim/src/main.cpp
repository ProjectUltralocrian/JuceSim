#include "Daw.h"


int main(int argc, const char** argv)
{
    std::cout << argv[0] << std::endl;
    
    pul::AudioEngine* daw = new pul::Daw;

    daw -> run();

    delete daw;

    std::cin.get();

    return EXIT_SUCCESS;
}