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

        World world;

    private:
        FrameBufferRef m_gameplay_target;
    };
}