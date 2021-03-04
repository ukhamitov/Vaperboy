#pragma once
#include <blah.h>

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
        FrameBufferRef m_gameplay_target;
    };
}