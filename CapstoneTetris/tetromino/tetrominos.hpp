#pragma once

#include "tetromino.hpp"

// Following SRS rotation rules

class IShape : public Tetromino
{
  public:
    IShape()
    {
        int rotation0[4][4] = {
            {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
        SetRotationState(0, rotation0);

        int rotation1[4][4] = {
            {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        int rotation2[4][4] = {
            {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
        SetRotationState(2, rotation2);

        int rotation3[4][4] = {
            {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class TShape : public Tetromino
{
  public:
    TShape()
    {
        int rotation0[4][4] = {
            {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
        SetRotationState(0, rotation0);

        int rotation1[4][4] = {
            {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        int rotation2[4][4] = {
            {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
        SetRotationState(2, rotation2);

        int rotation3[4][4] = {
            {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class LShape : public Tetromino
{
  public:
    LShape()
    {
        int rotation0[4][4] = {
            {2, 0, 0, 0}, {2, 2, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(0, rotation0);

        int rotation1[4][4] = {
            {0, 2, 2, 0}, {0, 2, 0, 0}, {0, 2, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        int rotation2[4][4] = {
            {0, 0, 0, 0}, {2, 2, 2, 0}, {0, 0, 2, 0}, {0, 0, 0, 0}};
        SetRotationState(2, rotation2);

        int rotation3[4][4] = {
            {0, 2, 0, 0}, {0, 2, 0, 0}, {2, 2, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class JShape : public Tetromino
{
  public:
    JShape()
    {
        int rotation0[4][4] = {
            {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
        SetRotationState(0, rotation0);

        int rotation1[4][4] = {
            {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        int rotation2[4][4] = {
            {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
        SetRotationState(2, rotation2);

        int rotation3[4][4] = {
            {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class SShape : public Tetromino
{
  public:
    SShape()
    {
        int rotation0[4][4] = {
            {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
        SetRotationState(0, rotation0);

        int rotation1[4][4] = {
            {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        int rotation2[4][4] = {
            {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
        SetRotationState(2, rotation2);

        int rotation3[4][4] = {
            {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class ZShape : public Tetromino
{
  public:
    ZShape()
    {
        int rotation0[4][4] = {
            {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
        SetRotationState(0, rotation0);

        int rotation1[4][4] = {
            {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        int rotation2[4][4] = {
            {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
        SetRotationState(2, rotation2);

        int rotation3[4][4] = {
            {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};

class OShape : public Tetromino
{
  public:
    OShape()
    {
        int rotation0[4][4] = {
            {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
        SetRotationState(0, rotation0);

        int rotation1[4][4] = {
            {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        SetRotationState(1, rotation1);

        int rotation2[4][4] = {
            {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
        SetRotationState(2, rotation2);

        int rotation3[4][4] = {
            {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
        SetRotationState(3, rotation3);
    }
};
