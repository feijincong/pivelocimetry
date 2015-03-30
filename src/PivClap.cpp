#include "PivClap.hpp"

PivClap::PivClap(int argc, char** argv) : 
	Clap(argc, argv)
{
}

bool PivClap::userConfig()
{
	return hasParam("-c");
}

bool PivClap::printResults()
{
	return hasFlag("-p");
}

bool PivClap::doPostProc()
{
	return hasFlag("-s");
}

bool PivClap::writeResults()
{
	return hasParam("-o");
}

bool PivClap::viewVectors()
{
	return hasFlag("-v");
}

std::string PivClap::writeFile()
{
	return getParam("-o");
}

std::string PivClap::configFile()
{
	return getParam("-c");
}

PivClap::~PivClap()
{
}
