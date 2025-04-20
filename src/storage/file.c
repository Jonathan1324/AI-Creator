#include "file.h"
#include <stdlib.h>

void write_metadata(FILE* file, MetadataSave *metadata) {
    size_t written = fwrite(metadata, sizeof(MetadataSave) - 2 * sizeof(IOEntrySave*), 1, file);
    if (written != 1) {
        perror("Error writing Metadata to file");
        return;
    }


    // Write the inputs and outputs

    written = fwrite(metadata->inputs, sizeof(IOEntrySave), metadata->input_count, file);
    if (written != metadata->input_count) {
        perror("Error writing inputs to file");
        return;
    }

    written = fwrite(metadata->outputs, sizeof(IOEntrySave), metadata->output_count, file);
    if (written != metadata->output_count) {
        perror("Error writing outputs to file");
        return;
    }
}

int read_metadata(FILE* file, MetadataSave* metadata) {
    if (!file || !metadata) return 0;

    // Lese das Metadata-Struct (ohne Inputs und Outputs) ein
    size_t read = fread(metadata, sizeof(MetadataSave) - 2 * sizeof(IOEntrySave*), 1, file);
    if (read != 1) {
        perror("Error reading Metadata from file");
        return 0;
    }

    // Allokiere Speicher für Inputs und Outputs
    metadata->inputs = malloc(sizeof(IOEntrySave) * metadata->input_count);
    metadata->outputs = malloc(sizeof(IOEntrySave) * metadata->output_count);

    if (!metadata->inputs || !metadata->outputs) {
        perror("Error allocating memory for inputs or outputs");
        return 0;
    }

    // Lese die Eingabedaten (inputs)
    read = fread(metadata->inputs, sizeof(IOEntrySave), metadata->input_count, file);
    if (read != metadata->input_count) {
        perror("Error reading inputs from file");
        return 0;
    }

    // Lese die Ausgabedaten (outputs)
    read = fread(metadata->outputs, sizeof(IOEntrySave), metadata->output_count, file);
    if (read != metadata->output_count) {
        perror("Error reading outputs from file");
        return 0;
    }

    return 1;
}

void write_ruleset(FILE* file, RuleSetSave *ruleset) {
    size_t written = fwrite(ruleset, sizeof(RuleSetSave) - sizeof(RuleSave*), 1, file);
    if (written != 1) {
        perror("Error writing ruleset to file");
        return;
    }

    written = fwrite(ruleset->rules, sizeof(RuleSave), ruleset->rule_count, file);
    if (written != ruleset->rule_count) {
        perror("Error writing rules to file");
        return;
    }
}

void read_ruleset(FILE* file, RuleSetSave *ruleset) {
    if (!file || !ruleset) return;

    size_t read = fread(ruleset, sizeof(RuleSetSave) - sizeof(RuleSave*), 1, file);
    if (read != 1) {
        perror("Error reading ruleset from file");
        return;
    }

    ruleset->rules = (RuleSave*)malloc(ruleset->rule_count * sizeof(RuleSave));
    if (ruleset->rules == NULL) {
        perror("Error allocating memory for rules");
        return;
    }

    read = fread(ruleset->rules, sizeof(RuleSave), ruleset->rule_count, file);
    if (read != ruleset->rule_count) {
        perror("Error reading rules from file");
        free(ruleset->rules); // Speicher freigeben bei Fehler
        return;
    }

    return;
}