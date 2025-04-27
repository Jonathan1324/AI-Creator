#ifndef SAVE_HPP
#define SAVE_HPP

#include "storage/storage.hpp"
#include "data/data.hpp"

int saveData(Data* data, const char* filename);

int loadData(Data* data, const char* filename);

#endif