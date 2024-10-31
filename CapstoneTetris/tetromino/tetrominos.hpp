#pragma once

#include "tetromino.hpp"

class IShape : public Tetromino {
  public:
    IShape() : Tetromino() {
        int temp_shape[4][4] = {
            {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};

        std::copy(&temp_shape[0][0], &temp_shape[0][0] + 4 * 4, &shape[0][0]);
    }
};

class TShape : public Tetromino {
  public:
    TShape() : Tetromino() {
        int temp_shape[4][4] = {
            {0, 2, 0, 0}, {0, 2, 2, 0}, {0, 2, 0, 0}, {0, 0, 0, 0}};

        std::copy(&temp_shape[0][0], &temp_shape[0][0] + 4 * 4, &shape[0][0]);
    }
};

class LShape : public Tetromino {
  public:
    LShape() : Tetromino() {
        int temp_shape[4][4] = {
            {0, 0, 3, 0}, {3, 3, 3, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

        std::copy(&temp_shape[0][0], &temp_shape[0][0] + 4 * 4, &shape[0][0]);
    }
};

class JShape : public Tetromino {
  public:
    JShape() : Tetromino() {
        int temp_shape[4][4] = {
            {4, 0, 0, 0}, {4, 4, 4, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

        std::copy(&temp_shape[0][0], &temp_shape[0][0] + 4 * 4, &shape[0][0]);
    }
};

class SShape : public Tetromino {
  public:
    SShape() : Tetromino() {
        int temp_shape[4][4] = {
            {0, 5, 5, 0}, {5, 5, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

        std::copy(&temp_shape[0][0], &temp_shape[0][0] + 4 * 4, &shape[0][0]);
    }
};

class ZShape : public Tetromino {
  public:
    ZShape() : Tetromino() {
        int temp_shape[4][4] = {
            {6, 6, 0, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

        std::copy(&temp_shape[0][0], &temp_shape[0][0] + 4 * 4, &shape[0][0]);
    }
};

class OShape : public Tetromino {
  public:
    OShape() : Tetromino() {
        int temp_shape[4][4] = {
            {7, 7, 0, 0}, {7, 7, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

        std::copy(&temp_shape[0][0], &temp_shape[0][0] + 4 * 4, &shape[0][0]);
    }
};
