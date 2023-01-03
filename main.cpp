/**
 * @author Tristan Perrot
 */

#include <iostream>
#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include "movie.h"
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

     int *tab = new int[2]();
     tab[0] = 60;
     tab[1] = 62;
     Movie *movie = new Movie("Inception", "inception.mkv", 122, 2, tab);
     cout << "Nombre de chapitre: " << movie->getChapterCount() << endl;
     const int *durationOld = movie->getChapters();
     cout << "Duree des chapitres: ";
     for (int i = 0; i < 2; ++i)
     {
          cout << durationOld[i] << ' ';
     }
     cout << endl;
     delete[] tab;
     tab = nullptr;
     delete[] durationOld;
     durationOld = nullptr;
     tab = new int[2]();
     tab[0] = 52;
     tab[1] = 70;
     movie->setChapters(tab, 2);
     cout << "Nombre de chapitre: " << movie->getChapterCount() << endl;
     const int *durationNew = movie->getChapters();
     cout << "Duree des chapitres: ";
     for (int i = 0; i < 2; ++i)
     {
          cout << durationNew[i] << ' ';
     }
     cout << endl;
     delete movie;
     delete[] tab;
     delete[] durationNew;
     tab = new int[3]();
     tab[0] = 32;
     tab[1] = 28;
     tab[2] = 33;
     movie = new Movie("Dodoro", "Dodoro.mkv", 93, 3, tab);
     cout << "Nombre de chapitre: " << movie->getChapterCount() << endl;
     durationNew = movie->getChapters();
     cout << "Duree des chapitres: ";
     for (int i = 0; i < 3; ++i)
     {
          cout << durationNew[i] << ' ';
     }
     cout << endl;
     return 0;
}
