#pragma once
#include <blah.h>
#include "core/world.h"

using namespace Blah;

namespace VB
{
    class Game
    {
    public:
        Batch batch;

        void startup();
        void shutdown();
        void update();
        void render();

    private:
        World* m_world;
        FrameBufferRef m_gameplay_target;
    };
}