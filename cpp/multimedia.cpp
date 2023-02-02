/**
 * @author Tristan Perrot
 * @file multimedia.cpp
 */

#include <string>
#include <iostream>
#include "multimedia.h"

using namespace std;

// Constructors
Multimedia::Multimedia() = default;

Multimedia::Multimedia(string name, string path) : name(name), path(path) {}

// Destructor
Multimedia::~Multimedia()
{
    cout << "Multimedia object " << name << " destroyed" << endl;
}

// Getters and setters
const string &Multimedia::getName() const
{
    return name;
}

const string &Multimedia::getPath() const
{
    return path;
}

void Multimedia::setName(string name)
{
    this->name = name;
}

void Multimedia::setPath(string path)
{
    this->path = path;
}

/**
 * Display Method
 *
 * @param os os stream
 */
void Multimedia::display(ostream &os) const
{
    os << "Multimedia{Name : " << name << " | Path : " << path << "}\n";
}
