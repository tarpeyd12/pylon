#ifndef _LINE_CLASS_H
#define _LINE_CLASS_H

namespace POGEL
{
    class LINE;
}

#include "point_class.h"
#include "bounding_class.h"
#include "misc_class.h"
#include "../pogel_internals.h"

namespace POGEL
{
    class LINE
    {
        private:
            //unsigned int properties; // the mushed options
        public:
            POGEL::POINT ends[2]; // the 2 ends of the line
            POGEL::COLOR color;
            unsigned int line_width;
            POGEL::BOUNDING bounding;

            bool stippled;
            unsigned int stp_width;
            unsigned short patern;

            LINE()
            {
                ends[0] = POGEL::POINT(); ends[1] = POGEL::POINT();
                line_width = 1;
                color = POGEL::COLOR(1,1,1,1);
                stippled = false; stp_width = 1;
                patern = 0xFFFF;
            }

            LINE( const POGEL::POINT& a, const POGEL::POINT& b )
            {
                ends[0] = a; ends[1] = b;
                line_width = 1;
                color = POGEL::COLOR(1,1,1,1);
                stippled = false; stp_width = 1;
                patern = 0xFFFF;
                bounding.addpoint(a,a); bounding.addpoint(a,b);
            }

            LINE( const POGEL::POINT& a, const POGEL::POINT& b, unsigned int lw )
            {
                ends[0] = a; ends[1] = b;
                line_width = lw;
                color = POGEL::COLOR(1,1,1,1);
                stippled = false; stp_width = 1;
                patern = 0xFFFF;
                bounding.addpoint(a,a); bounding.addpoint(a,b);
            }

            LINE( const POGEL::POINT& a, const POGEL::POINT& b, const POGEL::COLOR& c )
            {
                ends[0] = a; ends[1] = b;
                line_width = 1;
                color = c;
                stippled = false; stp_width = 1;
                patern = 0xFFFF;
                bounding.addpoint(a,a); bounding.addpoint(a,b);
            }

            LINE( const POGEL::POINT& a, const POGEL::POINT& b, unsigned int lw, const POGEL::COLOR& c )
            {
                ends[0] = a; ends[1] = b;
                line_width = lw;
                color = c;
                stippled = false; stp_width = 1;
                patern = 0xFFFF;
                bounding.addpoint(a,a); bounding.addpoint(a,b);
            }


            LINE( const POGEL::POINT& a, const POGEL::POINT& b, unsigned int lw, const POGEL::COLOR& c, unsigned int wdth, unsigned short pat)
            {
                ends[0] = a; ends[1] = b;
                line_width = lw;
                color = c;
                stippled = true; stp_width = wdth;
                patern = pat;
                bounding.addpoint(a,a); bounding.addpoint(a,b);
            }

            inline POGEL::POINT getStart() const { return ends[0]; }
            inline POGEL::POINT getEnd() const { return ends[1]; }

            inline POGEL::POINT getMiddle() const { return (getStart()+getEnd())/2; }

            //PROPERTIES_METHODS;

            inline void draw() const
            {
                #ifdef OPENGL
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_LIGHTING);
                glLineWidth(line_width);
                if(stippled) {
                    glEnable(GL_LINE_STIPPLE);
                    glLineStipple(stp_width, patern);
                }
                color.set();
                glBegin(GL_LINES);
                    glVertex3f(ends[0].x,ends[0].y,ends[0].z);
                    glVertex3f(ends[1].x,ends[1].y,ends[1].z);
                glEnd();
                glLineWidth(1);
                //glColor3f(1.0f,1.0f,1.0f);
                POGEL::COLOR(1,1,1,1).set();
                if(stippled) {
                    glDisable(GL_LINE_STIPPLE);
                    glLineStipple(1, 0xFFFF);
                }
                glEnable(GL_LIGHTING);
                glEnable(GL_TEXTURE_2D);
                #endif
            }
    };
}

#endif /* _LINE_CLASS_H */
