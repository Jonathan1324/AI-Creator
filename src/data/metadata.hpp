#ifndef METADATA_HPP
#define METADATA_HPP

#include <vector>

struct IOEntry {
    uint16_t id;
    char name[254];

    IOEntry() : id(0) {
        std::memset(name, 0, sizeof(name));
    }
};

struct Metadata {
    char name[255];
    uint8_t type;

    uint16_t input_count;
    uint16_t output_count;

    std::vector<IOEntry> inputs;
    std::vector<IOEntry> outputs;

    Metadata() : type(0), input_count(0), output_count(0) {
        std::memset(name, 0, sizeof(name));
    }

    void addInput(uint16_t id, const char* name) {
        IOEntry entry;
        entry.id = id;

        std::memset(entry.name, 0, sizeof(entry.name));
        std::strncpy(entry.name, name, sizeof(entry.name)); 

        inputs.push_back(entry);
        input_count = static_cast<uint16_t>(inputs.size());
    }

    void removeInput(uint16_t id) {
        for (std::vector<IOEntry>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
            if (it->id == id) {
                inputs.erase(it);
                input_count = static_cast<uint16_t>(inputs.size());
                return;
            }
        }
    }

    void addOutput(uint16_t id, const char* name) {
        IOEntry entry;
        entry.id = id;

        std::memset(entry.name, 0, sizeof(entry.name));
        std::strncpy(entry.name, name, sizeof(entry.name)); 

        outputs.push_back(entry);
        output_count = static_cast<uint16_t>(outputs.size());
    }

    void removeOutput(uint16_t id) {
        for (std::vector<IOEntry>::iterator it = outputs.begin(); it != outputs.end(); ++it) {
            if (it->id == id) {
                outputs.erase(it);
                output_count = static_cast<uint16_t>(outputs.size());
                return;
            }
        }
    }
};

#endif