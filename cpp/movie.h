/**
 * @author Tristan Perrot
 * @file movie.h
 */

#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include "video.h"

using namespace std;


/**
 * @brief Movie class, represents a movie
 * @details A movie is a video with chapters who are a int[]
 */
class Movie : public Video
{
private:
    int chapterCount = 0;
    int *chapters = nullptr;

public:
    // Constructors
    Movie();
    Movie(string name, string path, int duration);
    Movie(string name, string path, int duration, int numChapter, int *chapters);

    // Redefining operators
    Movie(const Movie &from);
    Movie &operator=(const Movie &from);

    // Getters and setters
    const int *getChapters() const;
    void setChapters(int *chapters, int chapterCount);

    int getChapterCount() const;

    // Display
    virtual void display(ostream &os) const override;

    // Destructor
    virtual ~Movie();
};

#endif // MOVIE_H