#include <map>
#include <memory>
#include <string>
#include "group.h"
#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include "movie.h"


using namespace std;

class MultimediaManager {
    private:
        map<string, shared_ptr<Multimedia>> MultimediaTable;
        map<string, shared_ptr<Group>> groupTable;

    public:
        shared_ptr<Multimedia> createPhoto(string name, string path, double latitude, double longitude) {
            shared_ptr<Multimedia> photo = make_shared<Photo>(name, path, latitude, longitude);
            MultimediaTable[name] = photo;
            return photo;
        }

        shared_ptr<Multimedia> createVideo(string name, string path, int duration) {
            shared_ptr<Multimedia> video = make_shared<Video>(name, path, duration);
            MultimediaTable[name] = video;
            return video;
        }

        shared_ptr<Multimedia> createMovie(string name, string path, int duration, int numChapter, int *chapters) {
            shared_ptr<Multimedia> movie = make_shared<Movie>(name, path, duration, numChapter, chapters);
            MultimediaTable[name] = movie;
            return movie;
        }

        shared_ptr<Group> createGroup(string name) {
            shared_ptr<Group> group = make_shared<Group>(name);
            groupTable[name] = group;
            return group;
        }

        void displayMultimedia(ostream &os ,string name) {
            auto it = MultimediaTable.find(name);
            if (it != MultimediaTable.end()) {
                it->second->display(os);
            } else {
                cout << "Multimedia not found." << endl;
            }
        }

        void displayGroup(ostream &os, string name) {
            auto it = groupTable.find(name);
            if (it != groupTable.end()) {
                it->second->display(os);
            } else {
                cout << "Group not found." << endl;
            }
        }

        void playMultimedia(string name) {
            auto it = MultimediaTable.find(name);
            if (it != MultimediaTable.end()) {
                it->second->play();
            } else {
                cout << "Multimedia not found." << endl;
            }
        }

        void removeMultimedia(string name) {
            auto it = MultimediaTable.find(name);
            if (it != MultimediaTable.end()) {
                for (auto &group : groupTable) {
                    group.second->removeMultimedia(name);
                }
                MultimediaTable.erase(it);
            } else {
                cout << "Multimedia not found." << endl;
            }
        }

        void removeGroup(string name) {
            auto it = groupTable.find(name);
            if (it != groupTable.end()) {
                groupTable.erase(it);
            } else {
                cout << "Group not found." << endl;
            }
        }
};
