#pragma once

#include "tetromino.hpp"

// Following SRS rotation rules

class IShape : public Tetromino
{
  public:
    IShape()
    {
        Uint8 rotation0[4][4] = {
            {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
        SetRotationState(0, rotation0);

        Uint8 rotation1[4][4] = {
            {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        Uint8 rotation2[4][4] = {
            {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
        SetRotationState(2, rotation2);

        Uint8 rotation3[4][4] = {
            {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class TShape : public Tetromino
{
  public:
    TShape()
    {
        Uint8 rotation0[4][4] = {
            {0, 2, 0, 0}, {2, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(0, rotation0);

        Uint8 rotation1[4][4] = {
            {0, 2, 0, 0}, {0, 2, 2, 0}, {0, 2, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        Uint8 rotation2[4][4] = {
            {0, 0, 0, 0}, {2, 2, 2, 0}, {0, 2, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(2, rotation2);

        Uint8 rotation3[4][4] = {
            {0, 2, 0, 0}, {2, 2, 0, 0}, {0, 2, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class JShape : public Tetromino
{
  public:
    JShape()
    {
        Uint8 rotation0[4][4] = {
            {4, 0, 0, 0}, {4, 4, 4, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(0, rotation0);

        Uint8 rotation1[4][4] = {
            {0, 4, 4, 0}, {0, 4, 0, 0}, {0, 4, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        Uint8 rotation2[4][4] = {
            {0, 0, 0, 0}, {4, 4, 4, 0}, {0, 0, 4, 0}, {0, 0, 0, 0}};
        SetRotationState(2, rotation2);

        Uint8 rotation3[4][4] = {
            {0, 4, 0, 0}, {0, 4, 0, 0}, {4, 4, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class LShape : public Tetromino
{
  public:
    LShape()
    {
        Uint8 rotation0[4][4] = {
            {0, 0, 3, 0}, {3, 3, 3, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(0, rotation0);

        Uint8 rotation1[4][4] = {
            {0, 3, 0, 0}, {0, 3, 0, 0}, {0, 3, 3, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        Uint8 rotation2[4][4] = {
            {0, 0, 0, 0}, {3, 3, 3, 0}, {3, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(2, rotation2);

        Uint8 rotation3[4][4] = {
            {3, 3, 0, 0}, {0, 3, 0, 0}, {0, 3, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class SShape : public Tetromino
{
  public:
    SShape()
    {
        Uint8 rotation0[4][4] = {
            {0, 5, 5, 0}, {5, 5, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(0, rotation0);

        Uint8 rotation1[4][4] = {
            {0, 5, 0, 0}, {0, 5, 5, 0}, {0, 0, 5, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        Uint8 rotation2[4][4] = {
            {0, 0, 0, 0}, {0, 5, 5, 0}, {5, 5, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(2, rotation2);

        Uint8 rotation3[4][4] = {
            {5, 0, 0, 0}, {5, 5, 0, 0}, {0, 5, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class ZShape : public Tetromino
{
  public:
    ZShape()
    {
        Uint8 rotation0[4][4] = {
            {6, 6, 0, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(0, rotation0);

        Uint8 rotation1[4][4] = {
            {0, 0, 6, 0}, {0, 6, 6, 0}, {0, 6, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        Uint8 rotation2[4][4] = {
            {0, 0, 0, 0}, {6, 6, 0, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}};
        SetRotationState(2, rotation2);

        Uint8 rotation3[4][4] = {
            {0, 6, 0, 0}, {6, 6, 0, 0}, {6, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class OShape : public Tetromino
{
    public:
      OShape()
      {
          Uint8 rotation0[4][4] = {
              {0, 7, 7, 0}, {0, 7, 7, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
          for (int i = 0; i < 4; i++)
          {
              SetRotationState(i, rotation0);
          }
      }
    void RotateClockwise()
    {
        return;
    }
};
