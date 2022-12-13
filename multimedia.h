/**
 * @author Tristan Perrot
 */

#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>
#include <iostream>

using namespace std;

class Multimedia
{
public:
    Multimedia();

    Multimedia(string name, string path);

    virtual ~Multimedia();

    string getName() const;
    string getPath() const;

    void setName(string name);
    void setPath(string path);

    /**
     * Display Method
     *
     * @param os os stream
     */
    virtual void display(ostream &os) const;

    virtual void play() const = 0; // Abstract method

private:
    string name;
    string path;
};

#endif // MEDIA_H