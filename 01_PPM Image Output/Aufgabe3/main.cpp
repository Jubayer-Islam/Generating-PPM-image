#include <iostream>
#include <fstream>


//format: magic number(ppm version),  width, height, maxval(maximum brightness), followed by RGB triplets

const unsigned int width = 100;     //columns of pixels
const unsigned int height = 100;    //rows of pixels




    /* quick way of creating a ppm file is:
            ofstream ppmFile;
            ppmFile.open("output.ppm");
    */
void printHeader(std::ofstream& ppmFile, const unsigned int width, const unsigned int height) {
    ppmFile << "P3" << std::endl; // Magic Number, we're doing a pixelmap here
    ppmFile << width << " " << height << std::endl;   // We need to specify width/height
    ppmFile << "255" << std::endl;    // Maximum value
}

struct pixel {
    double r,g,b;
};

// Sets the color of the pixel at x (horizontal) and y (vertical) in the screen
void setColor(pixel* screen, const unsigned int x, const unsigned int y, pixel color) {

            if (x < width && y < height)
            {
                screen[y * width + x] = color;
            }


}

void drawCircle(pixel* screen2, const  int x_circle, const int y_circle, const unsigned int radius, pixel color) {
    for (int y=0; y < height; y++) {
        for (int x=0;x < width; x++) {
            int x_res = x - x_circle;
            int y_res = y - y_circle;
            if ( (x_res * x_res) + (y_res * y_res) <= (radius * radius) )
            {
                setColor(screen2, x, y, color);

            }
        }
    }
}

void printScreenToPPMFile(const pixel* screen, std::ofstream& ppmFile, const unsigned int width, const unsigned int height) {
    printHeader(ppmFile, width ,height);
    for( int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            ppmFile << static_cast<int>(screen[y*width + x].r * 255.0) << " "; // we use static_cast to convert any string type value of pixel triplets to int type, it's a compile time cast
            ppmFile << static_cast<int>(screen[y*width + x].g * 255.0) << " ";
            ppmFile << static_cast<int>(screen[y*width + x].b * 255.0) << " ";  //here I just passed 1 RGB triplet in each loop
        }
        ppmFile << "\n";       //this line can be omitted bcz RGB triplets can also be fed without any whitespace or newline
    }
}


int main() {

  pixel screen[width*height];


    std::ofstream ppmFile("output.ppm"); // A PPM file for 11x11 gradient



    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {        //in simpler words, x=j=responsible for horizontal displacement
            double red = static_cast<double>(i) / (height - 1);  // Varies from 0 at top to 1 at bottom
            double blue = static_cast<double>(j) / (width - 1);  // Varies from 0 at left to 1 at right
            setColor(screen, j, i, {red,0,blue});      //green value is adjusted to 0 because all 4 colors have 0 RGB value for Green
        }
    }



    drawCircle(screen, 20,80,5, {0,1,0});

    printScreenToPPMFile(screen, ppmFile, width, height);
    ppmFile.close();



    return 0;
}
