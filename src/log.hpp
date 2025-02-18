#pragma once

#include <cstdio>
#include <filesystem>

// Nice little macro for printing pretty logs to the console.
#define LOG(fmt, ...)                                                          \
    printf("\033[32m[%s:%d][%s()]\033[0m " fmt "\n",                           \
           std::filesystem::path(__FILE__).filename().string().c_str(),        \
           __LINE__, __func__, ##__VA_ARGS__)
