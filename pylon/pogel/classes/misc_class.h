#ifndef _MISC_CLASS_H
#define _MISC_CLASS_H

#include <GL/gl.h>

//class POGEL::COLOR;

#include "../pogel_internals.h"

namespace POGEL {
class COLOR {
	public:
		float r, g, b, a;

		COLOR() { r=g=b=a=0.0f; }
		COLOR(float red, float green, float blue, float alpha) { r=red; g=green; b=blue; a=alpha; }

		COLOR(std::string s) { sscanf(s.c_str(), "{[%f],[%f],[%f],[%f]}", &r, &g, &b, &a); }

		inline void setcolors(float red, float green, float blue, float alpha) { r=red; g=green; b=blue; a=alpha; }
		inline void getcolors(float *red, float *green, float *blue, float *alpha) const { *red=r; *green=g; *blue=b; *alpha=a; }
		inline void set() const { glColor4f(r,g,b,a); }
		inline void setasbgcolor() const { glClearColor(r, g, b, a); }

		/*inline POGEL::COLOR& operator=(const POGEL::COLOR& c)
			{ r = c.r; g = c.g; b = c.b; return *this; }*/

		inline std::string toString() const
		{
			char *sr=POGEL::string("%f",r), *sg=POGEL::string("%f",g), *sb=POGEL::string("%f",b), *sa=POGEL::string("%f",a);
			std::string s = "{["+std::string(sr)+"],["+std::string(sg)+"],["+std::string(sb)+"],["+std::string(sa)+"]}";
			free(sr); free(sg); free(sb); free(sa);
			return s;
		}
};
}

#endif /* _MISC_CLASS_H */
