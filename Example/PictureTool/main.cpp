#include <stdio.h>
#include <iostream>

#include "../../God.h"
#include "../../L_Window.h"
#include "../../E_2Dto2D.h"
#include "../../T_Picture.h"

using std::cin;

class PicDraw : public G_Sprit
{
	private:
		SIZE pic_size;
		POS pic_pos;
		void *pic_buf;
		int type;

	public:
		PicDraw(POS pos=POS(0,0)):pic_pos(pos)
		{
			pic_buf=0;
			type=0;
		}

		void Picture_Set(const unsigned char * p,SIZE s)
		{
			pic_buf=(void *)p;
			pic_size=s;
			type=1;
		}
		
		void Image_Set(const unsigned char * p,SIZE s)
		{
			L_Window::T_PicBuf_To_Image(p,s,pic_buf);
			
			pic_size=s;
			type=0;
		}

		void Redraw()
		{
			MESSAGE mes={M_PIC_DRW,0,0,pic_size.w,pic_size.h,type};
			mes.p=(void *)pic_buf;
			p_world->Message_Send(mes);
		}

		int Message_Process(const MESSAGE *mes)
		{
			return 0;
		}
};

int main(int argc,char **argv)
{
	if(argc<3)
	{
		std::cerr<<"Please input the name of picture and the paint type(1 is Point Draw & 2 is Image Draw)!\n";
		return 1;
	}

	God god;

	G_World * p_world = new G_World;
	god.World_Register(p_world);

	L_Window win(POS(10,10),SIZE(700,500));
	win.Window_Show();
	win.Event_Register(EVENT{M_EXPOSE});
	win.Register_To_World(p_world);

	E_2Dto2D * eye = new E_2Dto2D(SIZE(700,500));
	p_world->Object_Register(eye);
	p_world->Message_Process_Register(M_EXPOSE,eye->Obj_Num_Get());

	T_JPEG * picbuf = new T_JPEG;
	picbuf->Jpg_Open(argv[1]);
	
	PicDraw * pic = new PicDraw;
	
	if(argv[2][0]=='1')
		pic->Picture_Set(picbuf->Pic_Buf_Get(),picbuf->Size_Get());
	else if(argv[2][0]=='2')
		pic->Image_Set(picbuf->Pic_Buf_Get(),picbuf->Size_Get());

	p_world->Object_Register(pic);

	god.Run();

	return 0;
}
