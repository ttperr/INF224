# TP INF224 - Tristan Perrot

>Tristan Perrot

## C++

### Étape 4 : Méthode `play()`

La méthode `play()` n'a pas d'implémentation au niveau de la classe de base. C'est une méthode **abstraite**. Elle se déclare comme ceci :

```c++
virtual void play() const = 0;
```

### Étape 5 : Traitement uniforme

```c++
Multimedia **tableau = new Multimedia *[2];
unsigned int count = 0;
tableau[count++] = new Photo("photo.png", "../data/", 0.2, 0.1);
tableau[count++] = new Video("video.mp4", "../data/", 3);
for (unsigned int i = 0; i < count; i++)
{
    tableau[i]->display(cout);
    tableau[i]->play();
}
```

*Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?*

Le polymorphisme.

*Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?*

Il est nécessaire de d'initialiser le tableau avec des éléments Multimedia, cet élément doit avoir un constructeur par défaut (sans paramètre).

*Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.*

Le tableau doit contenir des pointeurs vers ces objets. Cela permet de pouvoir stocker des objets de type Photo et Video dans le tableau.

### Étape 7 : Destruction et copie des objets

*La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ?*

Le problème est que les pointeurs pointent vers la même adresse mémoire que les objets d'origine. La solution est de faire une copie profonde. Il faut redéfini l'opérateur d'affectation de Movie.

```c++
Movie &Movie::operator=(const Movie &m)
{
    if (this != &m)
    {
        Multimedia::operator=(m);
        this->duration = m.duration;
        this->chapters = new string[m.nbChapters];
        for (unsigned int i = 0; i < m.nbChapters; i++)
        {
            this->chapters[i] = m.chapters[i];
        }
    }
    return *this;
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
```

### Étape 8 : Créer des groupes

*On rappelle aussi que la liste d'objets doit en fait être une liste de pointeurs d'objets. Pourquoi ?*

Pour pouvoir stocker des objets de type Photo, Video et Movie dans le tableau.

### Étape 10

*Les méthodes précédentes permettent d'assurer la cohérence de la base de données car quand on crée un objet on l'ajoute à la table adéquate. Par contre, ce ne sera pas le cas si on crée un objet directement avec new (il n'appartiendra à aucune table). Comment peut-on l'interdire, afin que seule la classe servant à manipuler les objets puisse en créer de nouveaux ?*

On peut interdire la création d'objets directement avec new en rendant le constructeur de la classe Multimedia privé, et définir la classe DataMap comme amie de la classe Multimedia.

```c++
class Multimedia
{
    friend class DataMap;
    ...
}
```

### Étape 12 et 13

Non traitées.

## Java Swing

### Étape 1

*Lancez votre programme, cliquez plusieurs fois sur les deux premiers bouton, retaillez la fenêtre. Que constate-t'on ?*

On constate que le texte dépasse de la fenêtre, nous l'insérons au sein d'un composant `JScrollPane` qui rajoute un ascenseur vertical et horizontal lorsque c'est nécessaire.
