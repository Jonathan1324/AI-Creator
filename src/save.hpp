#ifndef SAVE_HPP
#define SAVE_HPP

#include "storage/storage.hpp"
#include "data/data.hpp"

void saveData(Data* data, char* filename);

void loadData(Data* data, char* filename);

#endif