#pragma once

#include <vector>
#include <map>
#include <list>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary
{

    struct PolygonalMesh
    {
        // Number of cells of each dimension
        size_t num_cell0d;
        size_t num_cell1d;
        size_t num_cell2d;

        // Vectors storing the Ids of each type cell
        vector<unsigned int> id_cell0d;
        vector<unsigned int> id_cell1d;
        vector<unsigned int> id_cell2d;

        // Maps storing the markers of each type of cell
        // The keys are the values of the markers (integers),
        // and the values are the Ids (stored in a list of integers)
        map<unsigned int, list<unsigned int>> marker_cell0d;
        map<unsigned int, list<unsigned int>> marker_cell1d;
        map<unsigned int, list<unsigned int>> marker_cell2d;

        // 0D cells are points
        // Matrix which stores the (X,Y,Z=0) coordinates for each point (as doubles)
        MatrixXd coords_cell0d;
        
        // 1D cells are segments
        // Matrix which stores the Ids of the two points at the ends of each segment (as integers)
        MatrixXi extrema_cell1d;

        // 2D cells are polygons
        // Vector of vectors storing the Ids of the vertices of each polygon
        vector<vector<unsigned int>> vertices_cell2d;
        // Vector of vectors storing the Ids of the edges of each polygon
        vector<vector<unsigned int>> edges_cell2d;

    };
}

