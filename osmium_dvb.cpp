/*
 * ===========================================================================
 *
 *       Filename:  osmium_dvb.cpp
 *
 *    Description:  stdin: osmpbf
 *    	            stdout: filtered output
 *
 *    	            based on simplyfied osmium example. 
 *    	            osmium is provided in git submodule.
 *    	            see documentation there
 *
 *        Version:  1.0
 *        Created:  19.04.2013 23:26:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  _john (), 
 *   Organization:  <<</>>
 *
 * ==========================================================================
 */
#include <iostream>
#include <cstring>

#define OSMIUM_WITH_PBF_INPUT
#include <osmium.hpp>

class 
MyFilterHandler :public Osmium::Handler::Base 
{

	public:
	MyFilterHandler() : Osmium::Handler::Base(){ }

	void 
	node( const boost::shared_ptr<Osmium::OSM::Node const>& node) 
	{
		const char* op = node->tags().get_value_by_key("operator");
		if(  op && 
		     !strncmp(op ,"DVB",3) 
		     //  &&  !strcmp(node->tags().get_value_by_key("public_transport"),"stop_position") 
		    ) { std::cout << "ha!: " 
				  << node->id() 
				  << "[" 
				  << node->tags().get_value_by_key("name") 
				  << "] \n";
		}
	}
};



int main(int, char *argv[]) 
{
	Osmium::OSMFile infile(argv[1]);
	MyFilterHandler dvbfilterhandler;
	Osmium::Input::read(infile, dvbfilterhandler);
	google::protobuf::ShutdownProtobufLibrary();
}

