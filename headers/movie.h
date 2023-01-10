/**
 * @author Tristan Perrot
 */

#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include "video.h"

using namespace std;

class Movie : public Video
{
private:
    int chapterCount = 0;
    int *chapters = nullptr;

public:
    Movie();
    Movie(string name, string path, int duration);
    Movie(string name, string path, int duration, int numChapter, int *chapters);

    Movie(const Movie &from);
    Movie &operator=(const Movie &from);

    int *getChapters() const;
    void setChapters(int *chapters, int chapterCount);

    int getChapterCount() const;

    virtual void display(ostream &os) const override;

    virtual ~Movie();
};

#endif // MOVIE_H