#include "feel/feelcore/timekeeper.hpp"
#include <ktirio/geom/meshio.hpp>
#include <ktirio/geom/algorithms.hpp>
#include <ktirio/geom/terrain/grid_mesher.hpp>

int
main( int argc, char** argv )
{
    using namespace Feel;
    using namespace Feel::Ktirio::Geom;

    po::options_description desc( "Allowed options" );
    desc.add_options()
        ( "cubes", po::value<int>()->default_value( 10 ), "Number of cubes in each of the two grids to autorefine" )
        ( "output-dirpath", po::value<std::string>()->default_value( "outputs" ), "Output directory path" )
    ;

    Timekeeper::instance()->setEnabled( true );

    auto env = createEnvironment( argc, argv, desc );
    Timekeeper::instance()->setEnabled(true);

    int nCubes = option( _name="cubes" ).as<int>();


    Terrain::LTriangleGridMesher gridMesher;
    std::unique_ptr<Mesh> cube = gridMesher.matrixToMesh( Eigen::MatrixXd::Zero( 1, 1 ) );
    std::vector<Mesh::triangle_type const*> triangles;
    for ( auto const& tri : cube->triangles() )
        triangles.push_back( tri.get() );
    algorithms::extrusion( *cube, triangles, Eigen::Matrix<double, 3, 1>(0,0,1) );


    auto cubesGrid = std::make_unique<Mesh>();
    for ( int i = 0; i < nCubes; ++i )
        for ( int j = 0; j < nCubes; ++j )
            for ( int k = 0; k < nCubes; ++k )
                cubesGrid->merge(*cube,Mesh::affine_transformation_type::fromTranslation(i, j,k ));

    algorithms::autorefine(*cubesGrid);

    Timer t("surfaceTetrahedralization","Surface Tetrahedralization");
    auto res = algorithms::surfaceTetrahedralization( *cubesGrid );
    t.toc();

    fs::path outputDirpath = option( _name="output-dirpath" ).as<std::string>();
    exportMesh(_mesh=*res, _filename=outputDirpath/"cubes_tetrahedralization.msh");
    Timekeeper::instance()->save( outputDirpath/"timekeeper.json" );

    return 0;
}
