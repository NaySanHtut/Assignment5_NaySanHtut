#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include "pixel.h"

// parsing "x,y,r,g,b" into a pixel. Validity checks
bool parseLine(std::string line, Pixel &p) {
    
    // trailing
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    std::string tokens[5];
    size_t start = 0;

    for (int i = 0; i < 5; i++) {
        size_t comma = line.find(',', start);

        if (i < 4) {
            if (comma == std::string::npos) {
                return false; // missing a field
            }
            tokens[i] = line.substr(start, comma - start); // text b/w commas
            start = comma + 1;
        }

        else {
            tokens[i] = line.substr(start); // last value runs to the end of line
        }
    }

    try {
        p.x = std::stoi(tokens[0]);
        p.y = std::stoi(tokens[1]);
        p.r = std::stof(tokens[2]);
        p.g = std::stof(tokens[3]);
        p.b = std::stof(tokens[4]);
    }

    catch (...) {
        return false;
    }
    return true;
}

// Average rgb individually over all pixels and print results
void average_colors(std::vector<Pixel> &pixel_list) {
    if (pixel_list.empty()) {
        std::cout << "No pixels to average." << std::endl;
        return;
    }

    // double = precision loss
    double sumR = 0.0, sumG = 0.0, sumB = 0.0;
    for (size_t i = 0; i < pixel_list.size(); i++) {
        sumR += pixel_list[i].r;
        sumG += pixel_list[i].g;
        sumB += pixel_list[i].b;
    }

    double n = static_cast<double>(pixel_list.size());
    std::cout << "Average R: " << sumR / n << std::endl;
    std::cout << "Average G: " << sumG / n << std::endl;
    std::cout << "Average B: " << sumB / n << std::endl;
}

// Flip image vertically
// pixel at (x,y) takes color of pixel at (x , maxY - y). x,y coords stay in same order as input file.
// Therefore only the colors are swapped
void flip_vertically(std::vector<Pixel> &pixel_list) {
    if (pixel_list.empty()) {
        return;
    }

    int maxY = 0;
    for (size_t i = 0; i < pixel_list.size(); i++) {
        if (pixel_list[i].y > maxY) {
            maxY = pixel_list[i].y;
        }
    }

    for (size_t i = 0; i < pixel_list.size(); i++) {
        int y = pixel_list[i].y;
        if (y < maxY - y) { // only swap each pair once (top half)
            size_t j = i + static_cast<size_t>(maxY - 2 * y);
            std::swap(pixel_list[i].r, pixel_list[j].r);
            std::swap(pixel_list[i].g, pixel_list[j].g);
            std::swap(pixel_list[i].b, pixel_list[j].b);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::vector<Pixel> pixel_list;

    // Read
    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Could not open " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        Pixel p;
        if (parseLine(line, p)) {
            pixel_list.push_back(p);
        }
        else {
            std::cerr << "Skipping malformed line: " << line << std::endl;
        }
    }
    infile.close();

    std::cout << "Read " << pixel_list.size() << " pixels." << std::endl;

    // Process
    average_colors(pixel_list);
    flip_vertically(pixel_list);

    // Write
    std::ofstream outfile("flipped.dat");
    if (!outfile.is_open()) {
        std::cerr << "Could not open flipped.dat for writing" << std::endl;
        return 1;
    }

    outfile << std::setprecision(std::numeric_limits<float>::max_digits10);
    for (size_t i = 0; i < pixel_list.size(); i++) {
        outfile << pixel_list[i].x << "," << pixel_list[i].y << "," << pixel_list[i].r << "," << pixel_list[i].g << "," << pixel_list[i].b << "\n";
    }
    outfile.close();

    return 0;
}
