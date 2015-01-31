#include "engine.h"
#include <vector>

int main (int argc, char * argv[]) {
    std::vector <const char *> arguments(argv + 1, argv + argc);

	// create Engine object and evaluate
    Engine * engine = new Engine(arguments);
    while (engine -> executeTurn()){}
    delete engine;
}
