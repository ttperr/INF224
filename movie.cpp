/**
 * @author Tristan Perrot
 */

#include "movie.h"

using namespace std;

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

int *Movie::getChapters() const
{
    int *chapterCopy = new int[chapterCount];
    for (int i = 0; i < chapterCount; i++)
    {
        chapterCopy[i] = chapters[i];
    }
    return chapterCopy;
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

void Movie::display(ostream &os) const
{
    os << "Movie{Name : " << getName() << " | Path : " << getPath() << " | Duration : " << getDuration() << " | chapterCount : " << chapterCount << " | Chapters : ";
    for (int i = 0; i < chapterCount; i++)
    {
        os << chapters[i] << " ";
    }
    os << "}\n";
}

Movie::~Movie()
{
    delete[] chapters;
}
