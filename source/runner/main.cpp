#include <blah.h>
#include "../game/game.h"

using namespace Blah;
using namespace VB;

namespace
{
    Game game;

    void startup()
    {
        game.startup();
    }

    void shutdown()
    {
        game.shutdown();
    }

    void update()
    {
        game.update();
    }

    void render()
    {
        game.render();
    }
}

int main()
{
    // setup config
    Config config;
    config.name = "Vaperboy";
    config.width = 1280;
    config.height = 720;
    config.target_framerate = 60;
    config.on_startup = startup;
    config.on_shutdown = shutdown;
    config.on_update = update;
    config.on_render = render;

    // run
    int result = App::run(&config);

    return result;
}
