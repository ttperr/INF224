/**
 * @author Tristan Perrot
 */

#include <iostream>
#include "multimedia.h"
#include "photo.h"
#include "video.h"
#include <unistd.h>
using namespace std;

int main(int argc, const char *argv[])
{
    // Step 4
    cout << endl
         << "### Step 4: Photos & videos" << endl;

    Photo *photo = new Photo("photo.png", "./", 0.2, 0.1);
    photo->display(cout);

    Video *video = new Video("video.mp4", "./", 3);
    video->display(cout);

    // photo->play();
    // video->play();

    // Step 5
    cout << endl
         << "### Step 5: Polymorphism" << endl;
    Multimedia **tableau = new Multimedia *[2];
    unsigned int count = 0;
    tableau[count++] = new Photo("photo.png", "./", 0.2, 0.1);
    tableau[count++] = new Video("video.mp4", "./", 3);
    for (unsigned int i = 0; i < count; i++)
    {
        tableau[i]->display(cout);
        tableau[i]->play();
    }

    return 0;
}
