#pragma once
#include <blah.h>
#include <functional>
#include "../core/world.h"

using namespace Blah;

namespace VB
{
    class Timer : public Component, public Updatable
    {
    private:
        float m_duration = 0;

    public:
        Timer() = default;
        Timer(float duration, const std::function<void(Timer* self)>& on_end = nullptr);

        void start(float duration);
        std::function<void(Timer* self)> on_end;

        void update() override;
    };
}
