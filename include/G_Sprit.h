#ifndef G_SPRIT_H
#define G_SPRIT_H

/*
	This is the class about sprit.
*/

#include "G_Object.h"

class G_Sprit : public G_Object
{
	protected:
		POS spr_p;
		SIZE spr_size;
		int pri_num;			// Priority num. Big is big.

	public:
		G_Sprit();
		~G_Sprit();
		
		virtual int Message_Process(const MESSAGE *)=0;
		virtual int operator () (int);
		
		POS Pos_Get() const;
		SIZE Size_Get() const;
		int Pri_Get() const;
		
		virtual void Pos_Set(POS);
		virtual void Size_Set(SIZE);
		virtual void Pri_Set(int);
		virtual void Move(POS);			// Move the spr_p by POS.
};

#endif
