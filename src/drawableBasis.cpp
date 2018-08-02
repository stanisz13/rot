#include "drawableBasis.hpp"

inline void DrawableBasis::init(const Vector2f& position, const Vector2f& dimensions,
      Texture* texture)
{
    pos = position;
    size = dimensions;
    color = nullptr;
    scaling = {1.0f, 1.0f};
    tex = texture;
}

inline void DrawableBasis::init(const Vector2f& position, const Vector2f& dimensions,
     Color* colorOfObject)
{
    pos = position;
    size = dimensions;
    color = colorOfObject;
    scaling = {1.0f, 1.0f};
    tex = nullptr;
}

inline DrawableBasis::DrawableBasis(const Vector2f& position, const Vector2f& dimensions,
      Texture* texture)
{
    init(position, dimensions, texture);
}

inline DrawableBasis::DrawableBasis(const Vector2f& position, const Vector2f& dimensions,
      Color* colorOfObject)
{
    init(position, dimensions, colorOfObject);
}
