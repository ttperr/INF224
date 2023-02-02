/**
 * @author Tristan Perrot
 * @file main.cpp
 */

#define VERSION_2

#include <iostream>
#include "photo.h"
#include "movie.h"
#include "group.h"
#include "multimediaManager.h"
#include <unistd.h>
using namespace std;

#ifdef VERSION_1

int main(int argc, const char *argv[])
{
     // Step 4
     cout << endl
          << "### Step 4: Photos & videos" << endl;

     Photo *photo = new Photo("photo.png", "../data/", 0.2, 0.1);
     photo->display(cout);
     cout << endl;

     Video *video = new Video("video.mp4", "../data/", 3);
     video->display(cout);
     cout << endl;

     // photo->play();
     // video->play();

     // Step 5
     cout << endl
          << "### Step 5: Polymorphism" << endl;
     Multimedia **tableau = new Multimedia *[2];
     unsigned int count = 0;
     tableau[count++] = new Photo("photo.png", "../data/", 0.2, 0.1);
     tableau[count++] = new Video("video.mp4", "../data/", 3);
     for (unsigned int i = 0; i < count; i++)
     {
          tableau[i]->display(cout);
          cout << endl;
          // tableau[i]->play();
     }

     // Step 6 & 7
     cout << endl
          << "### Step 6 & 7: Movies" << endl;

     int *tab = new int[2]{60, 62};
     Movie *movie = new Movie("inception.mkv", "../data", 122, 2, tab);
     movie->display(cout);
     cout << endl;
     delete[] tab;
     tab = nullptr;
     tab = new int[2]{52, 70};
     Movie *movie2(movie);
     movie2->setChapters(tab, 2);
     movie->display(cout);
     cout << endl;
     movie2->display(cout);
     cout << endl;
     delete movie;
     delete[] tab;
     movie = new Movie("./", "test.mkv", 93);
     tab = new int[3]{32, 28, 33};
     movie->setChapters(tab, 3);
     movie->display(cout);
     cout << endl;

     // Step 8 & 9
     cout << endl
          << "### Step 8 & 9: Groups" << endl;

     Group *group1 = new Group("Group 1");
     Group *group2 = new Group("Group 2");
     shared_ptr<Multimedia> shrdVideo(new Video("video.mp4", "../data/", 20));
     shared_ptr<Multimedia> shrdPhoto(new Photo("photo.png", "../data/", 20.0, 20.0));
     group1->push_back(shrdVideo);
     group1->push_back(shrdPhoto);
     group2->push_back(shrdVideo);
     group1->display(cout);
     cout << endl;
     group2->display(cout);
     cout << endl;
     group1->pop_back();
     group1->pop_back();
     delete group1;
     group2->display(cout);
     cout << endl;

     cout << "The Photo is destroyed because it's no longer pointed by anyone"
          << endl;

     // Step 10
     cout << endl
          << "### Step 10: Memory" << endl;

     MultimediaManager *manager = new MultimediaManager();
     shared_ptr<Photo> photo_ = manager->createPhoto("photo.png", "../data/", 0.2, 0.1);
     shared_ptr<Video> video_ = manager->createVideo("video.mp4", "../data/", 3);
     shared_ptr<Movie> movie_ = manager->createMovie("film.mkv", "../data/", 122, 2, tab);
     shared_ptr<Group> group0 = manager->createGroup("group0");
     group0->addMultimedia(photo_);
     group0->addMultimedia(video_);
     group0->addMultimedia(movie_);
     manager->displayMultimedia(cout, "photo.png");
     cout << endl;
     manager->displayMultimedia(cout, "video.mp4");
     cout << endl;
     manager->displayMultimedia(cout, "film.mkv");
     cout << endl;
     manager->displayMultimedia(cout, "group0");
     cout << endl;
     manager->removeMultimedia("group0");
     manager->playMultimedia("video.mp4");
     delete manager;
     
     cout << endl
          << "Exiting Main" << endl;

     return 0;
}

#endif
#ifdef VERSION_2

#include <sstream>
#include "tcpserver.h"

const int PORT = 3331;

enum class Command
{
     SEARCH_OBJECT,
     SEARCH_GROUP,
     PLAY_OBJECT,
     STOP,
     NOT_FOUND
};

map<string, Command> commands_table = {
    {"search", Command::SEARCH_OBJECT},
    {"search_group", Command::SEARCH_GROUP},
    {"play", Command::PLAY_OBJECT},
    {"stop", Command::STOP},
};

Command getCommand(string command)
{
     if (commands_table.find(command) != commands_table.end())
     {
          return commands_table[command];
     }
     return Command::NOT_FOUND;
}

int main(int argc, const char *argv[])
{
     MultimediaManager *manager = new MultimediaManager();
     shared_ptr<Photo> photo_ = manager->createPhoto("photo.png", "../data/", 0.2, 0.1);
     shared_ptr<Video> video_ = manager->createVideo("video.mp4", "../data/", 3);
     int *tab = new int[3]{32, 28, 33};
     shared_ptr<Movie> movie_ = manager->createMovie("film.mkv", "../data/", 122, 2, tab);
     shared_ptr<Group> group0 = manager->createGroup("group0");
     group0->addMultimedia(photo_);
     group0->addMultimedia(video_);
     group0->addMultimedia(movie_);

     auto *server = new TCPServer([&](std::string const &request, std::string &response)
                                  {
          istringstream iss(request);
          string command;
          iss >> command;

          stringstream res_stream = stringstream();

          switch (getCommand(command))
          {
          case Command::SEARCH_OBJECT:
          {
               string name;
               iss >> name;
               manager->displayMultimedia(res_stream, name);
               response = res_stream.str();
               break;
          }
          case Command::SEARCH_GROUP:
          {
               string name;
               iss >> name;
               manager->displayGroup(res_stream, name);
               response = res_stream.str();
               break;
          }
          case Command::PLAY_OBJECT:
          {
               string name;
               iss >> name;
               manager->playMultimedia(name);
               response = "Playing " + name;
               break;
          }
          case Command::STOP:
          {
               response = "stop";
               return false;
               break;
          }
          default:
               response = "Command not found";
               break;
          } 
          
          cout << response << endl;
          cout << endl;
          
          return true; });

     cout << "Starting Server on port " << PORT << endl;
     int status = server->run(PORT);

     if (status < 0)
     {
          cerr << "Could not start Server on port " << PORT << ", status: " << status << endl;
          return 1;
     }
     return 0;
}

#endif