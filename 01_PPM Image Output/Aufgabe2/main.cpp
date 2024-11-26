#include <iostream>
#include <fstream>


//format: magic number(ppm version),  width, height, maxval(maximum brightness), followed by RGB triplets

const unsigned int width = 11;     //columns of pixels
const unsigned int height = 11;    //rows of pixels




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
//desired factors of r,g& b are being inserted in the screen array in each call 


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
/*
arguments breakdown:
"pixel* screen"

Type: Pointer to an array of pixel objects.
 Purpose: Represents the 2D "screen" or image where the circle will be drawn. Each element in this array corresponds to a pixel in the image, stored in a 1D format (row-major order).
    Why a Pointer?: It allows the function to directly modify the pixel array (the "screen") passed to it, avoiding unnecessary copying of large data structures.


question: could we have also used "pixel& screen" instead of "pixel* screen" as an argument inside the "void drawCircle" function above?

ChatGPT:


No, you cannot use pixel& screen instead of pixel* screen for the drawCircle function in its current implementation. Here's why:
1. Nature of the Argument

    pixel* screen:
        This represents a pointer to a dynamically allocated or statically sized array of pixel objects (essentially, a memory block containing multiple pixel elements).
        The pointer allows you to manipulate individual pixels within this 1D array.
    pixel& screen:
        A reference to a single pixel object.
        It cannot represent an entire array of pixel objects.

If you attempt to pass an array to pixel& screen, the function would only reference a single pixel (likely the first element in the array).
2. Why pixel& screen Won't Work

The code accesses pixels in a 1D array using:

screen[y * width + x]

    This syntax calculates an index to access a specific element within the screen array.For this to work, screen must be an array or a pointer to the first element of an array.

If you replaced pixel* screen with pixel& screen, the compiler would throw an error because screen would no longer represent an array, and indexing ([]) would not be allowed.

3. When to Use pixel& screen

A pixel& reference could be used if you’re working with a single pixel, not an array. For example, in a function to modify a single pixel:

void setPixelColor(pixel& screenPixel, const pixel& color) {
    screenPixel = color;
}

Here, the reference would allow direct modification of the specific pixel passed to the function without creating a copy.

**4. Alternative: std::vector

If you want to avoid pointers altogether and still handle a collection of pixel objects, you could use a std::vector:

void drawCircle(std::vector<pixel>& screen, int width, int height,
                int x_circle, int y_circle, unsigned int radius, pixel color) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int dx = x - x_circle;
            int dy = y - y_circle;
            if (dx * dx + dy * dy <= radius * radius) {
                screen[y * width + x] = color;
            }
        }
    }
}

Advantages of std::vector

    Safety: No need to manually manage memory.
    Readability: Avoids raw pointers, making the code easier to understand.
    Flexibility: Automatically handles resizing if needed (though not applicable for fixed-width screens).

To use this approach, you would initialize the screen like this:

std::vector<pixel> screen(width * height);


Conclusion

    You cannot use pixel& screen as it only represents a single pixel, not an array.
    The current implementation with pixel* screen works for arrays.
    Using std::vector<pixel> could be a modern and safer alternative to raw pointers.



*/
void printScreenToPPMFile(const pixel* screen, std::ofstream& ppmFile, const unsigned int width, const unsigned int height) {
    printHeader(ppmFile, width ,height);
    for( int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            ppmFile << static_cast<int>(screen[y*width + x].r * 255.0) << " "; // we use static_cast to convert any string type value of pixel triplets to int type, it's a compile time cast
            ppmFile << static_cast<int>(screen[y*width + x].g * 255.0) << " ";
            ppmFile << static_cast<int>(screen[y*width + x].b * 255.0) << " ";  //here I just passed 1 RGB triplet (3 values for 1 pixel)in each loop
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
