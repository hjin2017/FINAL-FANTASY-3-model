#include "stdafx.h"
#include "soundTest.h"


soundTest::soundTest()
{
}


soundTest::~soundTest()
{
}

HRESULT soundTest::init()
{
	SOUNDMANAGER->addSound("������ġ", "Kalimba.mp3", true, true);
	SOUNDMANAGER->addSound("������ġ2", "Kalimba.mp3", true, true);
	SOUNDMANAGER->addSound("������ġ3", "Kalimba.mp3", true, true);

	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);

	return S_OK;
}

void soundTest::release()
{

}

void soundTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			OPENFILENAME ofn;
			char filePathSize[1028] = "";
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = filePathSize;
			ofn.nMaxFile = sizeof(filePathSize);
			ofn.nFilterIndex = true;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = NULL;
			ofn.lpstrInitialDir = NULL;
			ofn.lpstrFilter = ("���� ����������");
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetOpenFileName(&ofn) == FALSE) return;

			char temp[1028];
			strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));

			char* context = NULL;
			char* token = strtok_s(temp, "\\", &context);
			while (strlen(context))
			{
				token = strtok_s(NULL, "\\", &context);
			}

			SOUNDMANAGER->addSound(token, ofn.lpstrFile, false, false);
		}
		SOUNDMANAGER->play("Kalimba.mp3");
	}


	
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		SOUNDMANAGER->play("������ġ", 1.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SOUNDMANAGER->play("������ġ2", 0.5f);
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->stop("������ġ2");
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SOUNDMANAGER->play("������ġ3", 0.8f);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		SOUNDMANAGER->stop("������ġ3");
	}


	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->stop("������ġ");
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		SOUNDMANAGER->pause("������ġ");
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		SOUNDMANAGER->resume("������ġ");
	}

}

void soundTest::render()
{
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}
