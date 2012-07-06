//
//  Render.h
//  cpp-project
//
//  Created by Celso Dantas on 12/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef cpp_project_Render_h
#define cpp_project_Render_h

class Render {
public:
    Render();
    void draw();
    void inline clearScreen();
    void inline clearScreenColor(float red, float green, float blue, float alpha);
    
private:
    float _red, _green, _blue, _alpha;
};

#endif
