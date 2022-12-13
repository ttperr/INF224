/**
 * @author Tristan Perrot
 */

#ifndef PHOTO_H
#define PHOTO_H

#include <string>
#include <iostream>
#include "multimedia.h"

class Photo : public Multimedia
{
public:
    Photo() : Multimedia()
    {
        latitude = 0.;
        longitude = 0.;
    };
    Photo(string name, string path, double latitude, double longitude) : Multimedia(name, path)
    {
        this->latitude = latitude;
        this->longitude = longitude;
    };

    double getLatitude() const { return latitude; };
    double getLongitude() const { return longitude; };

    void setLatitude(double latitude) { this->latitude = latitude; };
    void setLongitude(double longitude) { this->longitude = longitude; };

    void display(std::ostream &os) const override
    {
        os << "Multimedia{Name : " << getName() << " | Path : " << getPath() << " | Latitude : " << latitude << " | Longitude : " << longitude << "}\n";
    };

    /**
     * Play the photo
     */
    void play() const override
    {
        string command = "eog ";
        command += getPath() + getName();
        command += " &";
        cout << "Playing photo " << getName() << " located at " << getPath() << endl;
        system(command.data());
    };

private:
    double latitude{};
    double longitude{};
};

#endif // PHOTO_H
