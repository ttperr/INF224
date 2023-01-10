/**
 * @author Tristan Perrot
 */

#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <list>
#include <memory>
#include "multimedia.h"

using namespace std;

class Group : public list<shared_ptr<Multimedia>>
{
private:
    string groupName;

public:
    Group();
    Group(string groupName);

    virtual ~Group();

    string getGroupName() const;
    void setGroupName(string groupName);

    

    void display(ostream &os) const;
};

#endif // GROUP_H