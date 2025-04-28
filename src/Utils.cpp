#include "Utils.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

bool readmesh(PolygonalMesh& mesh)
{
    if(!readcell0d(mesh))
    {
        return false;
    }

    if(!readcell1d(mesh))
    {
        return false;
    }

    if(!readcell2d(mesh))
    {
        return false;
    }

    return true;
}

bool readfile(const string& filename, list<string>& lineslist)
{
    ifstream ifstr(filename); 

    if(ifstr.fail())
    {
        cerr << "error in " << filename << endl;
        return false;
    }
    
    string str;

    while(ifstr >> str)
    {
        lineslist.push_back(str);
    }

    ifstr.close();

    lineslist.pop_front();

    return true;
}


bool readcell0d(PolygonalMesh& mesh)
{
    string filename = "Cell0Ds.csv";
    list<string> lineslist;
    readfile(filename, lineslist);

    mesh.num_cell0d = lineslist.size();

    if(mesh.num_cell0d == 0)
    {
        cerr << "cell is empty" << endl;
        return false;
    }

    mesh.id_cell0d.reserve(mesh.num_cell0d);
    mesh.coords_cell0d = MatrixXd::Zero(3, mesh.num_cell0d);

    string str;
    char sep;
    unsigned int id;
    unsigned int marker;

    for(const auto& str : lineslist)
    {
        stringstream sstr(str);

        sstr >> id >> sep >> marker >> sep >> mesh.coords_cell0d(0, id) >> sep >> mesh.coords_cell0d(1, id);
        
        mesh.id_cell0d.push_back(id);

        auto x = mesh.marker_cell0d.find(marker);
        if(x == mesh.marker_cell0d.end())
        {
            mesh.marker_cell0d.insert({marker, {id}}); 
        }
        else
        {
            mesh.marker_cell0d[marker].push_back(id); 
        }
    }

    return true;
}


bool read_cell1d(PolygonalMesh& mesh)
{
    string filename = "Cell1Ds.csv";
    list<string> lineslist;
    readfile(filename, lineslist);

    mesh.num_cell1d = lineslist.size();

    if(mesh.num_cell1d == 0)
    {
        cerr << "Empty cell 1D" << endl;
        return false;
    }

    mesh.id_cell1d.reserve(mesh.num_cell1d);

    mesh.extrema_cell1d = MatrixXi::Zero(2, mesh.num_cell1d);

    string str;
    char sep;
    unsigned int id;
    unsigned int marker;

    for(const auto& str : lineslist)
    {
        stringstream sstr(str);

        sstr >> id >> sep >> marker >> sep >> mesh.extrema_cell1d(0, id) >> sep >> mesh.extrema_cell1d(1, id);
        
        mesh.id_cell1d.push_back(id);

        auto x = mesh.marker_cell1d.find(marker);
        if(x == mesh.marker_cell1d.end())
        {
            mesh.marker_cell1d.insert({marker, {id}}); 
        }
        else
        {
            mesh.marker_cell1d[marker].push_back(id); 
        }
    }

    return true;
}


bool readcell2d(PolygonalMesh& mesh)
{
    string filename = "Cell2Ds.csv";
    list<string> lineslist;
    readfile(filename, lineslist);

    mesh.num_cell2d = lineslist.size();

    if(mesh.num_cell2d == 0)
    {
        cerr << "cell is empty" << endl;
        return false;
    }

    mesh.id_cell2d.reserve(mesh.num_cell2d);
    mesh.vertices_cell2d.resize(mesh.num_cell2d);
    mesh.edges_cell2d.resize(mesh.num_cell2d);

    string str;
    char sep;
    unsigned int id;
    unsigned int marker;
    size_t numvertices;
    size_t numedges;

    for(const auto& str : lineslist)
    {
        stringstream sstr(str);

        sstr >> id >> sep >> marker >> sep >> numvertices >> sep;
        
        mesh.id_cell2d.push_back(id);

        mesh.vertices_cell2d[id].resize(numvertices);

        for(size_t i = 0; i < numvertices; i++)
        {
            sstr >> mesh.vertices_cell2d[id][i] >> sep;
        }

        sstr >> numedges >> sep;

        if(numvertices != numedges)
        {
            cerr << "error with " << id << endl;
            return false;
        }

        mesh.edges_cell2d[id].resize(numedges);

        for(size_t i = 0; i < numedges; i++)
        {
            sstr >> mesh.edges_cell2d[id][i] >> sep;
        }

        auto x = mesh.marker_cell2d.find(marker);
        if(x == mesh.marker_cell2d.end())
        {
            mesh.marker_cell2d.insert({marker, {id}}); 
        }
        else
        {
            mesh.marker_cell2d[marker].push_back(id); 
        }
    }

    return true;
}


void markersprint(const map<unsigned int, list<unsigned int>>& markers)
{
    for(const auto& pair : markers)
    {
        cout << pair.first << " : ";

        for(const auto& val : pair.second)
        {
            cout << val << " ";
        }

        cout << endl;
    }
}

