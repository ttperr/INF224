/**
 * @author Tristan Perrot
 */

#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>

using namespace std;

class Multimedia
{
private:
    string name;
    string path;

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
};

#endif // MEDIA_H