/*
 * compile with:
 * g++ -std=c++14 -o grid_test grid_tests.cpp ../src/grid.h ../src/pivoptions.cpp ../src/int_map.cpp
 *
 */

#define CATCH_CONFIG_MAIN
#include "../tests/catch.hpp"

#include <string>
#include <memory>
#include "../src/int_map.h"
#include "../src/pivoptions.h"
#include "../src/grid.h"

TEST_CASE( "Grid: Square Image"){
	
	/* 512 x 512 test image, 16 x 16 pixel windows with 8 pixel overlap */

	PivOptions::Uptr opt(new PivOptions());
	IntMap::Uptr im(new IntMap(512, 512));

	Grid g(opt, im);

	SECTION( "Number of x grid points should equal 63") {
		CHECK(g.get_noPointsX() == 63);
	}

	SECTION( "Number of y grid points should equal 63") {
		CHECK(g.get_noPointsY() == 63);
	}

	SECTION( "Length of x coordinate vector should equal 63" ) {
		CHECK(g.get_xCoordVector().size() == 63);
	}
	
	SECTION( "Length of y coordinate vector should equal 63" ) {
		CHECK(g.get_yCoordVector().size() == 63);
	}
	
	SECTION( "Total grid points should equal 3969" ) {
		CHECK(g.get_totalGridPoints() == 3969);
	}
	
	auto coordsVec = g.get_coordPairsVector();

	SECTION( "Coord pair vector should have size 3969" ) {
		CHECK(coordsVec.size() == 3969);
	}
	
	SECTION( "First coords should be (7, 7)" ) {
		CHECK(coordsVec[0].first == 7);
		CHECK(coordsVec[0].second == 7);
	}
	
	SECTION( "Point 2364 should be (7, 7)" ) {
		CHECK(coordsVec[2364].first == 271);
		CHECK(coordsVec[2364].second == 303);
	}
	

}
