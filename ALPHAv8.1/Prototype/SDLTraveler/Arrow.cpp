#include "Arrow.h"

Arrow::Arrow()
{
}

void Arrow::Update()
{
	count++;
	if (count % 100 == 0)
	{
		if (source.x == 288)
		{
			source.x = 352;
		}
		else
		{
			source.x = 288;
		}
	}

}
void Arrow::SetX(int x)
{
	dest.x = x;

}
Arrow::~Arrow()
{
}
