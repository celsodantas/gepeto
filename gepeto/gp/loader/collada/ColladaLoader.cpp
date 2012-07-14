//
//  ColladaLoader.cpp
//  gepeto
//
//  Created by Celso Dantas on 11/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ColladaLoader.h"
#include "../../render/opengl.h"

std::vector<geometry_asset>* ColladaLoader::load(std::string file_name)
{
    using namespace std;
    
    cout << "Loading file \"" << file_name << "\"" << endl;

    
    tinyxml2::XMLElement *mesh, 
                         *vertices, 
                         *input, 
                         *source,
                         *primitive;
    
    string source_name;    

    vector<geometry_asset>* geometries = new vector<geometry_asset>();
    
    tinyxml2::XMLDocument doc;
    doc.LoadFile(file_name.c_str());
    
    tinyxml2::XMLElement *geometry = doc.RootElement()->FirstChildElement("library_geometries")->FirstChildElement("geometry");

    if(geometry != NULL)
    {
        geometry_asset geo;
        
        geo.name = geometry->Attribute("id");
        
        mesh = geometry->FirstChildElement("mesh");
        while(mesh != NULL) {         
            vertices = mesh->FirstChildElement("vertices");
            input = vertices->FirstChildElement("input");  
                
            while(input != NULL)
            {
                source_name = input->Attribute("source");
                source_name = source_name.erase(0, 1);
                
                source = mesh->FirstChildElement("source");
                while (source != NULL)
                {
                    if (string( source->Attribute("id") ) == source_name)
                    {
                        geo.map[string( input->Attribute("semantic") )] = parseSource(source);
                    }
                    
                    source = source->NextSiblingElement("source");
                }
                
                input = input->NextSiblingElement("input");
            }
            
            
            // POLYLIST primitive
            primitive = mesh->FirstChildElement("polylist");
            if (primitive == NULL)
            {
                cout << "Primitive from geometry " << geometry->Attribute("id") << " not supported yet!" << endl;
                continue;
            }
            
            
            // Setting primitive
            char* vcount = (char*) primitive->FirstChildElement("vcount")->GetText();
            if (vcount[0] == '3')
                geo.primitive   = GL_TRIANGLES;
            else if (vcount[0] == '4')
                geo.primitive   = GL_QUADS;
            
            // Index and count
            int elements_count = atoi(primitive->Attribute("count")) * 3;
            
            cout << "count: " << atoi(primitive->Attribute("count")) << "  vcount: " << atoi(vcount) << endl;
            
            char* text = (char*) primitive->FirstChildElement("p")->GetText();
        
            geo.indices_qtd = elements_count;
            geo.indices     = (unsigned short*) malloc(elements_count * sizeof(unsigned short));
            
            // Setting indices values
            bool skip = true;
            ((unsigned short*)geo.indices)[0] = atoi( strtok(text, " ") );
            for (int i = 1; i < elements_count;) {
                int tmp = atoi( strtok(NULL, " ") );
                
                if (skip)
                {
                    skip = !skip;
                    continue;
                }
                    
                ((unsigned short*)geo.indices)[i] = tmp;
                
                skip = !skip;
                ++i;
            }
            
            // Getting normals
            input = primitive->FirstChildElement("input");
            while (input != NULL) {
                if (string(input->Attribute("semantic")) != "NORMAL" ) {
                    input = input->NextSiblingElement("input");
                    continue;
                }
                
                source_name = input->Attribute("source");
                source_name = source_name.erase(0, 1);
                
                source = mesh->FirstChildElement("source");
                while (source != NULL)
                {
                    if (string( source->Attribute("id") ) == source_name)
                    {
                        geo.map[string( input->Attribute("semantic") )] = parseSource(source);
                    }
                    
                    source = source->NextSiblingElement("source");
                }
                
                input = input->NextSiblingElement("input");
            }

            
            
            mesh = mesh->NextSiblingElement("mesh");
        }
        
        geometries->push_back(geo);
        
        geometry = geometry->NextSiblingElement("geometry");
    }
    
    return geometries;
}

SourceData ColladaLoader::parseSource(tinyxml2::XMLElement *source)
{
    SourceData source_data;
    
    source_data.stride = getTechniqueCommonStride(source);    
    
    setSourceDataAndType(source, source_data);
    
    return source_data;
}

int ColladaLoader::getTechniqueCommonStride(tinyxml2::XMLElement *source)
{
    unsigned int stride;
    int r = source->FirstChildElement("technique_common")->FirstChildElement("accessor")->QueryUnsignedAttribute("stride", &stride);
    
    if (r == tinyxml2::XML_NO_ATTRIBUTE)
        return 1;
    else 
        return stride;
    
}

void ColladaLoader::setSourceDataAndType(tinyxml2::XMLElement *source, SourceData &sdata)
{
    tinyxml2::XMLElement *array = source->FirstChildElement("float_array");
    
    unsigned int vect_count;
    array->QueryUnsignedAttribute("count", &vect_count);
    
    char *text = (char*) array->GetText();
    
    sdata.type = GL_FLOAT;
    sdata.size = vect_count * sizeof(float);
    sdata.data = malloc(sdata.size);
    
    ((float*)sdata.data)[0] = (float) atof(strtok(text, " "));
    for (unsigned int i = 1; i < vect_count; i++) {
        ((float*)sdata.data)[i] = (float) atof(strtok(NULL, " "));
    }
}

