/**
 * @file group.h
 * @author Tristan Perrot
 */

#ifndef GROUP_H
#define GROUP_H

#include <iostream>
#include <list>
#include <memory>
#include "multimedia.h"

using namespace std;

/**
 * @brief Group class, stores Multimedia objects in a list of shared smart pointers
 */

class Group : public list<shared_ptr<Multimedia>>
{
private:
    string groupName;

public:
    // Constructors
    Group();
    Group(string groupName);

    // Destructor
    virtual ~Group();

    // Getters and setters
    string getGroupName() const;
    void setGroupName(const string groupName);

    // Methods
    void addMultimedia(shared_ptr<Multimedia> multimedia);
    void removeMultimedia(shared_ptr<Multimedia> multimedia);
    void removeMultimedia(const string name);

    // Display
    void display(ostream &os) const;
};

#endif // GROUP_H