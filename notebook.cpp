#include "Notebook.h"
#include <iostream>
using namespace std;

bool Notebook::hasEvidence(string id) const
{
    for (const Evidence& evidence : collectedEvidence)
    {
        if (evidence.getId() == id)
        {
            return true;
        }
    }

    return false;
}

bool Notebook::addEvidence(const Evidence& evidence)
{
    // Prevent duplicate clues
    if (hasEvidence(evidence.getId()))
    {
        return false;
    }

    collectedEvidence.push_back(evidence);

    cout << "\n[NEW EVIDENCE DISCOVERED]" << endl;
    cout << evidence.getTitle() << endl;

    return true;
}

void Notebook::displayNotebook() const
{
    cout << "\n==================================" << endl;
    cout << "        MITUL'S NOTEBOOK" << endl;
    cout << "==================================" << endl;

    if (collectedEvidence.empty())
    {
        cout << "No evidence collected yet." << endl;
        return;
    }

    cout << "Total Evidence: " << collectedEvidence.size() << endl;

    for (const Evidence& evidence : collectedEvidence)
    {
        evidence.display();
    }
}

int Notebook::getEvidenceCount() const
{
    return collectedEvidence.size();
}