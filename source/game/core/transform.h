#pragma once
#include "blah.h"

using namespace Blah;

class Transform
{
private:
    Vec2 m_position = Vec2(0, 0);
    Vec2 m_scale = Vec2(1, 1);
    Vec2 m_origin = Vec2(0, 0);
    float m_rotation = 0;
    Mat3x2 m_matrix = Mat3x2::identity;
    Mat3x2 m_matrix_floor = Mat3x2::identity;
    bool m_dirty = true;

protected:
    virtual void transformed() {}

public:
    Transform() = default;
    virtual ~Transform() = default;

    float x() const { return m_position.x; }
    void x(float value) { m_position.x = value; make_dirty(); }
    float y() const { return m_position.y; }
    void y(float value) { m_position.y = value; make_dirty(); }

    const Vec2& position() const { return m_position; }
    void position(const Vec2& value) { m_position = value; make_dirty(); }
    void move(const Vec2& value) { m_position += value; make_dirty(); }

    const Vec2& scale() const { return m_scale; }
    void scale(const Vec2& value) { m_scale = value; make_dirty(); }

    const Vec2& origin() const { return m_origin; }
    void origin(const Vec2& value) { m_origin = value; make_dirty(); }

    float rotation() const { return m_rotation; }
    void rotation(float value) { m_rotation = value; make_dirty(); }
    void rotate(float value) { m_rotation += value; make_dirty(); }

    void copy(Transform& transform)
    {
        m_position = transform.m_position;
        m_scale = transform.m_scale;
        m_origin = transform.m_origin;
        m_rotation = transform.m_rotation;
        m_matrix = transform.m_matrix;
        m_matrix_floor = transform.m_matrix_floor;
        m_dirty = false;
    }

    void make_dirty() {
        m_dirty = true;
    }
};