#import "@preview/grape-suite:1.0.0": exercise
#import exercise: project, task, subtask

#let task = task.with(numbering-format: (..n) => numbering("1", ..n))
#let subtask = subtask.with(markers: ("a)", "1)"))

#show: project.with(
    title: "Praktikum 1: PPM Image Output",

    university: [University of Duisburg-Essen],
    institute: [Distributed Systems],
    seminar: [Objektorientied Programming in C++],

    abstract: [In dieser ersten Praktikumsaufgabe geht es darum ein Bild mit C++ zu malen. Viel Erfolg!
    
    Bei Fragen oder Problemen schreiben Sie gerne im Moodle!],
    

    author: "Peter Zdankin",

    show-solutions: false,
    show-hints: true,
    task-type: [Aufgabe],
)

#task[PPM Nachschlagen][
    #subtask[
        Lesen Sie sich die Spezifikation zu PPM Dateien durch #link("https://netpbm.sourceforge.net/doc/ppm.html").
        PPM bietet eine einfache Möglichkeit selber Bilder zu generieren, indem man angibt wie viele Pixel in der Höhe/Breite sind, was der Maximalwert eines Farbwertes ist und abschließend werden die Werte für rot/grün/blau pro Pixel angegeben. 
        ```
        P3
# feep.ppm
4 4
15
 0  0  0    0  0  0    0  0  0   15  0 15
 0  0  0    0 15  7    0  0  0    0  0  0
 0  0  0    0  0  0    0 15  7    0  0  0
15  0 15    0  0  0    0  0  0    0  0  0
```
In diesem Beispiel oben sehen Sie, wie so eine einfache PPM Datei aus 4 mal 4 Pixeln aussehen kann.
    ]
    

    #task[Gradient zeichnen][]
#figure(
  image("gradient.png", width: 30%),
  caption: [
    Ein Gradient der horizontal den Blauwert und vertikal den Rotwert eines Pixels erhöht.
  ],
)

    #subtask[
        Öffnen Sie #link("https://git.uni-due.de/vs.ude/objektorientierte-programmierung-cpp"). Nutzen Sie git um das Repository zu _clonen_ und importieren Sie das Projekt in 01_ImageOutput/.
    ]

    #subtask[
        Passen Sie den Quelltext so an, damit das Bild aus Figure 1 erreicht ist. Das Bild ist 11 mal 11 Pixel dimensioniert und ist pur schwarz oben links, pur blau oben rechts, pur rot unten links und pur magenta unten rechts. 
    ]

    #task[Kreis zeichnen][]
#figure(
  image("circle.png", width: 30%),
  caption: [
    Ein einsamer Kreis wurde hier eingezeichnet.
  ],
)

#subtask[
        Erweitern Sie das Projekt darum dass Kreise eingezeichnet werden können. 
        Schreiben Sie eine Methode `void drawCircle(pixel* screen, const  int x_circle, const int y_circle, const unsigned int radius, pixel color)`, mit der ein Kreis mit einem bestimmten Radius eingezeichnet wird.
    ]

][]