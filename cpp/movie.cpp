/**
 * @author Tristan Perrot
 * @file movie.cpp
 */

#include "movie.h"

using namespace std;

// Constructors
Movie::Movie() : Video(), chapterCount(0), chapters(nullptr)
{
}

Movie::Movie(string name, string path, int duration) : Video(name, path, duration), chapterCount(0), chapters(nullptr)
{
}

Movie::Movie(string name, string path, int duration, int chapterCount, int *chapters) : Video(name, path, duration)
{
    this->setChapters(chapters, chapterCount);
}

// Redefining operators
Movie::Movie(const Movie &from) : Video(from), chapterCount(from.chapterCount)
{
    if (from.chapters)
    {
        this->setChapters(from.chapters, from.chapterCount);
    }
    else
    {
        chapters = nullptr;
    }
}

Movie &Movie::operator=(const Movie &from)
{
    if (this != &from)
    {
        Video::operator=(from);
        this->setChapters(from.chapters, from.chapterCount);
    }
    return *this;
}

// Getters and setters
const int *Movie::getChapters() const
{
    return chapters;
}

void Movie::setChapters(int *newChapters, int newChapterCount)
{
    delete[] chapters;
    if (newChapters)
    {
        chapters = new int[newChapterCount];
        for (int i = 0; i < newChapterCount; i++)
        {
            chapters[i] = newChapters[i];
        }
        chapterCount = newChapterCount;
    }
    else
    {
        chapters = nullptr;
    }
}

int Movie::getChapterCount() const
{
    return chapterCount;
}

// Display
void Movie::display(ostream &os) const
{
    os << "Movie{Name : " << getName() << " | Path : " << getPath() << " | Duration : " << getDuration() << " | chapterCount : " << chapterCount << " | Chapters : ";
    for (int i = 0; i < chapterCount; i++)
    {
        os << chapters[i] << " ";
    }
    os << "}\n";
}

// Destructor
Movie::~Movie()
{
    delete[] chapters;
    cout << "Movie object " << getName() << " destroyed" << endl;
}
