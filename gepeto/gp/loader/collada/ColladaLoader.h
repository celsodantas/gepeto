//
//  ColladaLoader.h
//  gepeto
//
//  Created by Celso Dantas on 11/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gepeto_ColladaLoader_h
#define gepeto_ColladaLoader_h

#include <string>
#include <map>
#include <vector>
#include <tinyxml2.h>

struct SourceData {
    int type;
    unsigned int size;
    unsigned int stride;
    void* data;
};

struct geometry_asset
{  
    std::string name;
    std::map<std::string, SourceData> map;
    int primitive;
    
    unsigned short *indices;
    unsigned short  indices_qtd;
};

class ColladaLoader
{
public:
    std::vector<geometry_asset>* load(std::string file_name);
    
    
private:
    SourceData parseSource(tinyxml2::XMLElement *source);
    int   getTechniqueCommonStride(tinyxml2::XMLElement *source);
    void  setSourceDataAndType(tinyxml2::XMLElement *source, SourceData &data);
};

#endif
