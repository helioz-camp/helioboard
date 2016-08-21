#ifndef COLOR_H
#define COLOR_H

struct Color {
    int r = 0;
    int g = 0;
    int b = 0;

    Color() {
        r = 0;
        g = 0;
        b = 0;
    }

    Color(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    Color(int h, int v) {
        unsigned char s = 255;
        unsigned char region, remainder, p, q, t;

        if (s == 0)
        {
            r = v;
            g = v;
            b = v;
            return;
        }

        region = h / 43;
        remainder = (h - (region * 43)) * 6; 

        p = (v * (255 - s)) >> 8;
        q = (v * (255 - ((s * remainder) >> 8))) >> 8;
        t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

        switch (region)
        {
            case 0:
                r = v; g = t; b = p;
                break;
            case 1:
                r = q; g = v; b = p;
                break;
            case 2:
                r = p; g = v; b = t;
                break;
            case 3:
                r = p; g = q; b = v;
                break;
            case 4:
                r = t; g = p; b = v;
                break;
            default:
                r = v; g = p; b = q;
                break;
        }
    }


    friend bool operator==(const Color& lhs, const Color& rhs) {
        return lhs.r == rhs.r && lhs.g == rhs.g &&  lhs.b == rhs.b;
    }

    friend bool operator!=(const Color& lhs, const Color& rhs) {
        return !(lhs == rhs);
    }
};


#define BAD Color(0, 0, 0)
#define OFF Color(0, 0, 0)
#define RED 15
#define ORANGE 23
#define AMBER 63
#define GREEN 60
#define YELLOW 62

#endif