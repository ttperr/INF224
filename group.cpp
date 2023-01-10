/**
 * @author Tristan Perrot
 */

#include "group.h"

using namespace std;

Group::Group() : list<shared_ptr<Multimedia>>(), groupName("Unnamed") {};

Group::Group(const string groupName) : list<shared_ptr<Multimedia>>(), groupName(groupName) {};

string Group::getGroupName() const
{
    return groupName;
}

void Group::setGroupName(const string groupName)
{
    this->groupName = groupName;
}

void Group::display(ostream &os) const
{
    os << "Group name: " << groupName << endl;
    for (auto & it : *this)
    {
        it->display(os);
    }
}