#ifndef _SPRITE_CLASS_H
#define _SPRITE_CLASS_H

namespace POGEL {
class SPRITE;
}

#include "point_class.h"
#include "object_class.h"

class POGEL::SPRITE : public POGEL::OBJECT {
	public:
		/*SPRITE();
		~SPRITE();*/

		inline virtual int GetType() const { return POGEL_TYPE_SPRITE; }

		void draw();
};

#endif /* _SPRITE_CLASS_H */
