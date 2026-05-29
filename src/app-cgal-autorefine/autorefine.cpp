#include <ktirio/geom/meshio.hpp>
#include <ktirio/geom/algorithms.hpp>
#include <ktirio/geom/timekeeper.hpp>
#include <ktirio/geom/terrain/grid_mesher.hpp>

int
main( int argc, char** argv )
{
    using namespace Feel;
    using namespace Feel::Ktirio::Geom;

    po::options_description desc( "Allowed options" );
    desc.add_options()
        ( "triangles", po::value<int>()->default_value( 10 ), "Number of triangles in each of the two grids to autorefine" )
        ( "output-dirpath", po::value<std::string>()->default_value( "outputs" ), "Output directory path" )
    ;

    Timekeeper::instance()->setEnabled( true );

    auto env = createEnvironment( argc, argv, desc );

    int nTriangles = option( _name="triangles" ).as<int>();

    Terrain::LTriangleGridMesher gridMesher;

    Eigen::MatrixXd gridPoints = Eigen::MatrixXd::Zero( nTriangles, nTriangles );

    std::unique_ptr<Mesh> grid1 = gridMesher.matrixToMesh( gridPoints );
    grid1->reverseFaceOrientation();
    std::unique_ptr<Mesh> grid2 = gridMesher.matrixToMesh( gridPoints );
    grid2->apply( AffineTransformation<double,3>( 1, 0, 0, 0, 
                                                  0, -1, 0, 1,
                                                  0, 0, -1, 0 )
    );

    auto res = std::make_unique<Mesh>();
    res->merge( *grid1 );
    res->merge( *grid2 );
    algorithms::mergeDuplicatePoints( *res );

    algorithms::autorefine( *res );

    fs::path outputDirpath = option( _name="output-dirpath" ).as<std::string>();
    exportMesh(_mesh=*res, _filename=outputDirpath/"autorefine.msh");
    Timekeeper::instance()->save( outputDirpath/"timekeeper.json" );

    return 0;
}
