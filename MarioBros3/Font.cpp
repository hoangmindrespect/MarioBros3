#include "Font.h"
#include "PlayScene.h"

void CFont::Render()
{
	CSprites* s = CSprites::GetInstance();
	float distance = 8.0f;
	
	for (int i = 0; i <  strlen(content) ; i++)
	{
		switch (content[i])
		{	
		case 'A':
			s->Get(ID_FONT_A)->Draw(x + i * distance, y);
			break;
		case 'B':
			s->Get(ID_FONT_B)->Draw(x + i * distance, y);
			break;
		case 'C':
			s->Get(ID_FONT_C)->Draw(x + i * distance, y);
			break;
		case 'D':
			s->Get(ID_FONT_D)->Draw(x + i * distance, y);
			break;
		case 'E':
			s->Get(ID_FONT_E)->Draw(x + i * distance, y);
			break;
		case 'F':
			s->Get(ID_FONT_F)->Draw(x + i * distance, y);
			break;
		case 'G':
			s->Get(ID_FONT_G)->Draw(x + i * distance, y);
			break;
		case 'H':
			s->Get(ID_FONT_H)->Draw(x + i * distance, y);
			break;
		case 'I':
			s->Get(ID_FONT_I)->Draw(x + i * distance, y);
			break;
		case 'J':
			s->Get(ID_FONT_J)->Draw(x + i * distance, y);
			break;
		case 'K':
			s->Get(ID_FONT_K)->Draw(x + i * distance, y);
			break;
		case 'L':
			s->Get(ID_FONT_L)->Draw(x + i * distance, y);
			break;
		case 'M':
			s->Get(ID_FONT_M)->Draw(x + i * distance, y);
			break;
		case 'N':
			s->Get(ID_FONT_N)->Draw(x + i * distance, y);
			break;
		case 'O':
			s->Get(ID_FONT_O)->Draw(x + i * distance, y);
			break;
		case 'P':
			s->Get(ID_FONT_P)->Draw(x + i * distance, y);
			break;
		case 'Q':
			s->Get(ID_FONT_Q)->Draw(x + i * distance, y);
			break;
		case 'R':
			s->Get(ID_FONT_R)->Draw(x + i * distance, y);
			break;
		case 'S':
			s->Get(ID_FONT_S)->Draw(x + i * distance, y);
			break;
		case 'T':
			s->Get(ID_FONT_T)->Draw(x + i * distance, y);
			break;
		case 'U':
			s->Get(ID_FONT_U)->Draw(x + i * distance, y);
			break;
		case 'V':
			s->Get(ID_FONT_V)->Draw(x + i * distance, y);
			break;
		case 'W':
			s->Get(ID_FONT_W)->Draw(x + i * distance, y);
			break;
		case 'X':
			s->Get(ID_FONT_X)->Draw(x + i * distance, y);
			break;
		case 'Y':
			s->Get(ID_FONT_Y)->Draw(x + i * distance, y);
			break;
		case 'Z':
			s->Get(ID_FONT_Z)->Draw(x + i * distance, y);
			break;
		case ' ':
			s->Get(ID_FONT_SPACE)->Draw(x + i * distance, y);
			break;
		case '!':
			s->Get(ID_FONT_EXCLAMATION)->Draw(x + i * distance, y);
			break;
		default:
			break;
		}
	}
	//RenderBoundingBox();
}

void CFont::GetBoundingBox(float& l, float& t, float& r, float& b){}
