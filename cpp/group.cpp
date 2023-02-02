/**
 * @author Tristan Perrot
 * @file group.cpp
 */

#include "group.h"

using namespace std;

// Constructors
Group::Group() : list<shared_ptr<Multimedia>>(), groupName("Unnamed") {};

Group::Group(const string groupName) : list<shared_ptr<Multimedia>>(), groupName(groupName) {};

// Destructor
Group::~Group() {
    cout << "Group " << groupName << " destroyed" << endl;
}

// Getters and setters
string Group::getGroupName() const
{
    return groupName;
}

void Group::setGroupName(const string groupName)
{
    this->groupName = groupName;
}

// Display
void Group::display(ostream &os) const
{
    os << "Group name: " << groupName << "; ";
    for (auto & it : *this)
    {  
        it->display(os);
        os << "; ";
    }
}

// Methods
void Group::addMultimedia(shared_ptr<Multimedia> multimedia)
{
    this->push_back(multimedia);
}

void Group::removeMultimedia(shared_ptr<Multimedia> multimedia)
{
    this->remove(multimedia);
}

void Group::removeMultimedia(const string name)
{
    for (auto it = this->begin(); it != this->end(); ++it)
    {
        if ((*it)->getName() == name)
        {
            this->remove(*it);
            break;
        }
    }
}