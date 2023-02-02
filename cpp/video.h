/**
 * @author Tristan Perrot
 * @file video.h
 */

#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include "multimedia.h"

using namespace std;

/**
 * @brief Video class, derived from Multimedia
 * @details Video is a Multimedia object with a duration.
 * It can open the related video file from its path + name attributes
 */

class Video : public Multimedia
{
private:
    int duration{};

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

    ~Video() override
    {
        cout << "Video object " << getName() << " destroyed" << endl;
    };
};

#endif // VIDEO_H
