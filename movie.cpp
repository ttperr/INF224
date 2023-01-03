/**
 * @author Tristan Perrot
 */

#include <string>
#include "movie.h"

using namespace std;

Movie::Movie() : Video()
{
    this->chapterCount = 0;
    this->chapters = nullptr;;
}

Movie::Movie(string name, string path, int duration, int chapterCount, int*chapters) : Video(name, path, duration) {
    this->chapterCount = chapterCount;
    this->chapters = new int[chapterCount];
    for (int i = 0; i < chapterCount; i++) {
        this->chapters[i] = chapters[i];
    }
}

int* Movie::getChapters() const {
    int*chapterCopy = new int[chapterCount];
    for (int i = 0; i < chapterCount; i++) {
        chapterCopy[i] = chapters[i];
    }
    return chapterCopy;
}

void Movie::setChapters(int* newChapters, int newChapterCount) {
    this->chapterCount = newChapterCount;
    if(newChapters) {
        delete[] chapters;
        this->chapters = new int[newChapterCount];
        for (int i = 0; i < newChapterCount; i++) {
            this->chapters[i] = chapters[i];
        }
    } else {
        if(chapters){
            delete[] chapters;
            chapters = nullptr;
        }
    }
}

int Movie::getChapterCount() const {
    return chapterCount;
}

void Movie::display(ostream &os) const {
    os << "Movie{Name : " << getName() << " | Path : " << getPath() << " | Duration : " << getDuration() << " | chapterCount : " << chapterCount << " | Chapters : ";
    for (int i = 0; i < chapterCount; i++) {
        os << chapters[i] << " ";
    }
    os << "}\n";
}

Movie::~Movie() {
    delete[] chapters;
    cout << "Movie object " << getName() << " destroyed" << endl;
}
