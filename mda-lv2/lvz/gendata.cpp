/* LVZ - A C++ interface for writing LV2 plugins.
 * Copyright (C) 2008 Dave Robillard <http://drobilla.net>
 *  
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <dlfcn.h>
#include "audioeffectx.h"

using namespace std;

#define NS_LV2CORE "http://lv2plug.in/ns/lv2core#"

// VST is so incredibly awful.  Just.. wow.
#define MAX_NAME_LENGTH 1024
char name[MAX_NAME_LENGTH];


struct Record {
	Record(const string& u, const string& n) : uri(u), base_name(n) {}
	string uri;
	string base_name;
};

typedef std::list<Record> Manifest;
Manifest manifest;


void
write_plugin(AudioEffectX* effect, const string& lib_file_name)
{
	string base_name = lib_file_name.substr(0, lib_file_name.find_last_of("."));
	string data_file_name = base_name + ".ttl";
	
	fstream os(data_file_name.c_str(), ios::out);
	effect->getProductString(name);
	
	os << "@prefix : <http://lv2plug.in/ns/lv2core#> ." << endl;
	os << "@prefix doap: <http://usefulinc.com/ns/doap#> ." << endl << endl;
	os << "<" << effect->getURI() << ">" << endl;
	os << "\t:symbol \"" << effect->getUniqueID() << "\" ;" << endl;
	os << "\tdoap:name \"" << name << "\" ;" << endl;
	os << "\tdoap:license <http://usefulinc.com/doap/licenses/gpl> ;" << endl;
	os << "\t:pluginProperty :hardRtCapable";

	uint32_t num_params     = effect->getNumParameters();
	uint32_t num_audio_ins  = effect->getNumInputs();
	uint32_t num_audio_outs = effect->getNumOutputs();
	uint32_t num_ports      = num_params + num_audio_ins + num_audio_outs;
		
	if (num_ports > 0)
		os << " ;" << endl << "\t:port [" << endl;
	else
		os << " ." << endl;
	
	uint32_t idx = 0;

	for (uint32_t i = idx; i < num_params; ++i, ++idx) {
		effect->getParameterName(i, name);
		os << "\t\ta :InputPort, :ControlPort ;" << endl;
		os << "\t\t:index" << " " << idx << " ;" << endl;
		os << "\t\t:name \"" << name << "\" ;" << endl;
		os << ((idx == num_ports - 1) ? "\t] ." : "\t] , [") << endl;
	}

	for (uint32_t i = 0; i < num_audio_ins; ++i, ++idx) {
		os << "\t\ta :InputPort, :AudioPort ;" << endl;
		os << "\t\t:index" << " " << idx << " ;" << endl;
		os << ((idx == num_ports - 1) ? "\t] ." : "\t] , [") << endl;
	}
	
	for (uint32_t i = 0; i < num_audio_outs; ++i, ++idx) {
		os << "\t\ta :OutputPort, :AudioPort ;" << endl;
		os << "\t\t:index" << " " << idx << " ;" << endl;
		os << ((idx == num_ports - 1) ? "\t] ." : "\t] , [") << endl;
	}

	os.close();

	manifest.push_back(Record(effect->getURI(), base_name));
}


void
write_manifest(ostream& os)
{
	os << "@prefix : <http://lv2plug.in/ns/lv2core#> ." << endl;
	os << "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> ." << endl << endl;
	for (Manifest::iterator i = manifest.begin(); i != manifest.end(); ++i) {
		os << "<" << i->uri << "> a :Plugin ;" << endl;
		os << "\trdfs:seeAlso <" << i->base_name << ".ttl> ;" << endl;
		os << "\t:binary <" << i->base_name << ".so> ." << endl << endl;
	}
}


int
main(int argc, char** argv)
{
	if (argc == 0) {
		cout << "Usage: gendata [PLUGINLIB1] [PLUGINLIB2]..." << endl;
		cout << "Each argument is a path to a LVZ plugin library." << endl;
		cout << "For each library an LV2 data file with the same name" << endl;
		cout << "will be output containing the data for that plugin." << endl;
		cout << "A manifest of the plugins found is written to stdout" << endl;
		return 1;
	}
	
	typedef AudioEffectX* (*new_effect_func)();
	typedef AudioEffectX* (*plugin_uri_func)();

	new_effect_func constructor = NULL;
	AudioEffectX*   effect      = NULL; 

	for (int i = 1; i < argc; ++i) {
		void* handle = dlopen(argv[i], RTLD_NOW);
		if (handle == NULL) {
			cerr << "ERROR: " << argv[i] << " is not a shared library, ignoring" << endl;
			continue;
		}

		constructor = (new_effect_func)dlsym(handle, "lvz_new_audioeffectx");
		if (constructor == NULL) {
			dlclose(handle);
			cerr << "ERROR: " << argv[i] << " is not an LVZ plugin library, ignoring" << endl;
			continue;
		}

		effect = constructor();
		string lib_path = argv[i];
		size_t last_slash = lib_path.find_last_of("/");
		if (last_slash != string::npos)
			lib_path = lib_path.substr(last_slash + 1);
		
		write_plugin(effect, lib_path);

		dlclose(handle);
	}

	write_manifest(cout);
	
	return 0;
}

