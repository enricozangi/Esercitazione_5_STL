#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include "PolygonalMesh.hpp"

using namespace std;
using namespace PolygonalLibrary;

bool readmesh(PolygonalMesh& mesh);

bool readfile(const string& file_name, list<string>& lines);

bool readcell0d(PolygonalMesh& mesh);

bool readcell1d(PolygonalMesh& mesh);

bool readcell2d(PolygonalMesh& mesh);

void markersprint(const map<unsigned int, list<unsigned int>>& markers);

