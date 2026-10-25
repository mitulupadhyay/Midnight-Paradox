#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "Evidence.h"
#include <vector>
using namespace std;

class Notebook
{
private:
    vector<Evidence> collectedEvidence;

public:
    bool addEvidence(const Evidence& evidence);
    bool hasEvidence(string id) const;
    void displayNotebook() const;
    int getEvidenceCount() const;
};

#endif