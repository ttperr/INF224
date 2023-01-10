/**
 * @author Tristan Perrot
 */

#include <iostream>
#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include "movie.h"
#include "group.h"
#include <unistd.h>
using namespace std;

int main(int argc, const char *argv[])
{
     // Step 4
     cout << endl
          << "### Step 4: Photos & videos" << endl;

     Photo *photo = new Photo("photo.png", "data/", 0.2, 0.1);
     photo->display(cout);

     Video *video = new Video("video.mp4", "data/", 3);
     video->display(cout);

     // photo->play();
     // video->play();

     // Step 5
     cout << endl
          << "### Step 5: Polymorphism" << endl;
     Multimedia **tableau = new Multimedia *[2];
     unsigned int count = 0;
     tableau[count++] = new Photo("photo.png", "data/", 0.2, 0.1);
     tableau[count++] = new Video("video.mp4", "data/", 3);
     for (unsigned int i = 0; i < count; i++)
     {
          tableau[i]->display(cout);
          // tableau[i]->play();
     }

     // Step 6
     cout << endl
          << "### Step 6: Movies" << endl;

     int *tab = new int[2]{60, 62};
     Movie *movie = new Movie("./", "inception.mkv", 122, 2, tab);
     movie->display(cout);
     delete[] tab;
     tab = nullptr;
     tab = new int[2]{52, 70};
     Movie *movie2(movie);
     movie2->setChapters(tab, 2);
     movie->display(cout);
     movie2->display(cout);
     delete movie;
     delete[] tab;
     movie = new Movie("./", "test.mkv", 93);
     tab = new int[3]{32, 28, 33};
     movie->setChapters(tab, 3);
     movie->display(cout);

     // Step 7
     cout << endl
          << "### Step 7: Groups" << endl;

     Group *group1 = new Group("Group 1");
     group1->push_back(shared_ptr<Photo>(photo));
     group1->push_back(shared_ptr<Video>(video));
     group1->push_back(shared_ptr<Movie>(movie));

     Group *group2 = new Group("Group 2");
     group2->push_back(shared_ptr<Photo>(photo));
     group2->push_back(shared_ptr<Photo>(photo));

     group1->display(cout);
     group2->display(cout);
     return 0;
}
