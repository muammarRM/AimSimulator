#include "Game.h"
// mingw32-make
// 
using namespace std;
// using namespace sf;

int main() {
    //init srand
    std::srand(static_cast<unsigned>(time(NULL)));
\
    //init game engine
    Game game;

    
    //Game Loop
    while (game.running() && !game.getEndGame())
    {
        // update 
        game.update();
        // render
        game.render();

    }

    //End of Application
    return 0;
}