#include "game.h"

using namespace VB;

void Game::startup()
{
    // framebuffer for the game
    m_gameplay_target = FrameBuffer::create(1280, 720);

    // set batcher to use Nearest Filter
    batch.default_sampler = TextureSampler(TextureFilter::Nearest);
}

void Game::shutdown()
{

}

void Game::update()
{

}

void Game::render()
{
    // draw gameplay stuff
    {
        m_gameplay_target->clear(Color::black);

        // TODO: draw gameplay objects

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