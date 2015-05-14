#ifndef LANDTYPE_H
#define LANDTYPE_H

const int number_of_land_types = 15;

enum class LandType : int {
    none             =  -1,
    space            =   0,
    sky              =   1,
    island           =   2,
    coast_west       =   3,
    coast_east       =   4,
    coast_north      =   5,
    coast_south      =   6,
    ocean            =   7,
    volcano          =   8,
    mountain         =   9,
    wasteland        =  10,
    forest           =  11,
    desert           =  12,
    snowland         =  13,
    swamp            =  14,
};

#endif // LANDTYPE_H
