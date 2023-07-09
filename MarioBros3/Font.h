#pragma once
#include "GameObject.h"
#pragma warning(disable:4996)

#define ID_FONT_A	77441
#define ID_FONT_B	77442
#define ID_FONT_C	77443
#define ID_FONT_D	77444
#define ID_FONT_E	77445
#define ID_FONT_F	77446
#define ID_FONT_G	77447
#define ID_FONT_H	77448
#define ID_FONT_I	77449
#define ID_FONT_J	77450
#define ID_FONT_K	77451
#define ID_FONT_L	77452
#define ID_FONT_M	77453
#define ID_FONT_N	77454
#define ID_FONT_O	77455
#define ID_FONT_P	77456
#define ID_FONT_Q	77457
#define ID_FONT_R	77458
#define ID_FONT_S	77459
#define ID_FONT_T	77460
#define ID_FONT_U	77461
#define ID_FONT_V	77462
#define ID_FONT_W	77463
#define ID_FONT_X	77464
#define ID_FONT_Y	77465
#define ID_FONT_Z	77466
#define ID_FONT_SPACE	77467
#define ID_FONT_EXCLAMATION 	77468

class CFont : public CGameObject
{
protected:
	char* content;
public:
	CFont(float x, float y, const char* content) :CGameObject(x, y) {
		int length = int(strlen(content) + 1);
		this->content = new char[length];
		strcpy(this->content, content);
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};
