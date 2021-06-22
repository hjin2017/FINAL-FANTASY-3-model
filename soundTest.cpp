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
	SOUNDMANAGER->addSound("닌자참치", "Kalimba.mp3", true, true);
	SOUNDMANAGER->addSound("닌자참치2", "Kalimba.mp3", true, true);
	SOUNDMANAGER->addSound("닌자참치3", "Kalimba.mp3", true, true);

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
			ofn.lpstrFilter = ("음악 파일이지롱");
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
		SOUNDMANAGER->play("닌자참치", 1.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		SOUNDMANAGER->play("닌자참치2", 0.5f);
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->stop("닌자참치2");
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SOUNDMANAGER->play("닌자참치3", 0.8f);
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		SOUNDMANAGER->stop("닌자참치3");
	}


	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->stop("닌자참치");
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		SOUNDMANAGER->pause("닌자참치");
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		SOUNDMANAGER->resume("닌자참치");
	}

}

void soundTest::render()
{
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}
