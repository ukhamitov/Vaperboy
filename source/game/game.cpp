#include "game.h"
#include "components/timer.h"

using namespace VB;

void Game::startup()
{
    // hello world
    m_world = new World();

    // framebuffer for the game
    m_gameplay_target = FrameBuffer::create(1280, 720);

    // set batcher to use Nearest Filter
    batch.default_sampler = TextureSampler(TextureFilter::Nearest);

    // create our first entity
    auto en = m_world->create(Point(12, 2));
    if (en)
    {
        Log::print("Entity Created");
        // ... and try to add a component
        en->add(Timer(1, [](Timer* self) {
            Log::print("Entity Created 2");
        }));
    }
}

void Game::shutdown()
{
    m_world->clear();
}

void Game::update()
{
    // Update Objects
    m_world->update();
}

void Game::render()
{
    // draw gameplay stuff
    {
        m_gameplay_target->clear(Color::black);

        // draw gameplay objects
        m_world->render(batch);

        // draw to the gameplay buffer
        batch.render(m_gameplay_target);
        batch.clear();
    }

    // draw game buffer to the screen
    {
        float game_scale = Calc::min(App::backbuffer->width() / m_gameplay_target->width(),App::backbuffer->height() / m_gameplay_target->height());

        Vec2 screen_center = Vec2(App::backbuffer->width(), App::backbuffer->height()) / 2;
        Vec2 buffer_center = Vec2(m_gameplay_target->width(), m_gameplay_target->height()) / 2;

        App::backbuffer->clear(Color::black);
        batch.push_matrix(Mat3x2::create_transform(screen_center, buffer_center, Vec2::one * game_scale, 0));
        batch.tex(m_gameplay_target->attachment(0), Vec2::zero, Color::white);
        batch.pop_matrix();
        batch.render(App::backbuffer);
        batch.clear();
    }
}