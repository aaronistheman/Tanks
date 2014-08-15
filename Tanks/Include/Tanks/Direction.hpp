#ifndef TANKS_DIRECTION_HPP
#define TANKS_DIRECTION_HPP


struct Direction
{
  Direction(float movementAngle, float distance, float rotation)
    : angle(movementAngle)
    , distance(distance)
    , rotation(rotation)
  {
  }

  float angle; // gives the direction to move
  float distance;
  float rotation;
};

#endif // TANKS_DIRECTION_HPP