/**
 * @author Tristan Perrot
 */

#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <iostream>
#include "multimedia.h"

using namespace std;

class Video : public Multimedia
{
public:
    Video() : Multimedia() { duration = 0; };
    Video(string name, string path, int duration) : Multimedia(name, path) { this->duration = duration; };

    int getDuration() const { return duration; };
    void setDuration(int duration) { this->duration = duration; };

    /**
     * Display Method
     *
     * @param os os stream
     */
    void display(ostream &os) const override
    {
        os << "Multimedia{Name : " << getName() << " | Path : " << getPath() << " | Duration : " << duration << "}\n";
    };

    /**
     * Play the video
     */
    void play() const override
    {
        string command = "mpv ";
        command += getPath() + getName();
        command += " &";
        cout << "Playing video " << getName() << " located at " << getPath() << endl;
        system(command.data());
    };

private:
    int duration{};
};

#endif // VIDEO_H
