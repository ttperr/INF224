/**
 * @author Tristan Perrot
 */

#include <string>
#include <iostream>
#include "multimedia.h"

using namespace std;

Multimedia::Multimedia() = default;

Multimedia::Multimedia(string name, string path) : name(name), path(path) {}

Multimedia::~Multimedia()
{
    cout << "Multimedia object " << name << " destroyed" << endl;
}

string Multimedia::getName() const
{
    return name;
}

string Multimedia::getPath() const
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
