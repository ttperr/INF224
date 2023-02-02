/**
 * @author Tristan Perrot
 * @file multimedia.h
 */

#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>

using namespace std;

/**
 * @brief Multimedia class, abstract class of multimedia
 * @details Multimedia is the root of any multimedia object.
 */
class Multimedia
{
private:
    string name;
    string path;

public:
    // Constructors
    Multimedia();

    Multimedia(string name, string path);

    // Destructor
    virtual ~Multimedia();

    // Getters and setters
    const string &getName() const;
    const string &getPath() const;

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