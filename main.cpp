#include<cmath>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

const double tol = 1e-10;

int main()
{
    PolygonalMesh mesh;

    if(!readmesh(mesh))
    {
        cerr << "file not found" << endl;
        return false;
    }

    Gedim::UCDUtilities utilities;
    utilities.ExportPoints("./Cell0Ds.inp",
                           mesh.coords_cell0d);
                           
    utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.coords_cell0d,
                             mesh.extrema_cell1d);

    cout << "markers of the points: " << endl;
    markersprint(mesh.marker_cell0d);

    cout << "markers of the segments: " << endl;
    markersprint(mesh.marker_cell1d);

    cout << "markers of the polygons: " << endl;
    markersprint(mesh.marker_cell2d);

    for(size_t i = 0; i < mesh.num_cell1d; i++)
    {
        unsigned int a = mesh.extrema_cell1d(0,i);
        unsigned int b = mesh.extrema_cell1d(1,i);

        if(mesh.coords_cell0d.col(a).isApprox(mesh.coords_cell0d.col(b)))
        {
            cerr << "segment " << i << " has length zero" << endl;
            return false;
        }
    }

    
    for(auto vec : mesh.edges_cell2d)
    {
        sort(vec.begin(), vec.end());

        size_t len = vec.size();

        for(size_t i = 0; i < len - 1; i++)
        {
            if(vec[i] == vec[i+1])
            {
                cerr << "a polygon is invalid" << endl;
                return false;
            }
        }
    }

    for(const auto& vec : mesh.edges_cell2d)
    {

        size_t len = vec.size();

        double surf = 0;
        
        for(size_t i = 0; i < len; i++)
        {
            unsigned int c = mesh.extrema_cell1d(0, vec[i]);
            unsigned int d = mesh.extrema_cell1d(1, vec[i]);

            double x_1 = mesh.coords_cell0d(0, c);
            double y_1 = mesh.coords_cell0d(1, c);
            double x_2 = mesh.coords_cell0d(0, d);
            double y_2 = mesh.coords_cell0d(1, d);

            surf += ((x_1 * y_2) - (x_2 * y_1));
        }

        surf = .5 * abs(surf);

        if(surf < tol){
            cerr << "area of a polygon is 0" << endl;
        }

    }
    return 0;
}
