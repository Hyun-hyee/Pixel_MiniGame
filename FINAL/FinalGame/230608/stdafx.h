// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <map>
#include <unordered_map>
#include <algorithm>
#include<cstdlib> //rand(), srand()
#include<ctime> //time()
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <typeinfo>
#include <deque>
using namespace std;

#include <ole2.h>
#pragma comment(lib, "gdiplus.lib") //gdiplus���̺귯��
#include <gdiplus.h> //gdiplus����� ���� ���


// ���̺귯�� : ���̳ʸ��� ����(������)�� �Լ����� ��� ���� ����

//- �ڵ� ������ ���� ��â�� ��� �� �ϳ�, �ٸ� ���α׷����� ����� �� �ֵ��� �ü���� ����Ʈ���� �����ڿ� ���� ����
//- ���̺귯���� ��ټ��� �Լ����� �Լ��� ���� �� ���ǵ��� �ʿ�� �ϱ� ������ ��ũ�Ǳ� ���� ��ó���� ������ �ش� ��������� ���� ���α׷����� ���Խ��Ѿ� �Ѵ�.
//- ���̺귯������ ������� ���α׷��� ��ũ�Ǿ� ������ ������ ������ ���α׷��� �̷�� �ȴ�.

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#include <io.h>


//DX
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")




//���� ��� �ڵ�
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

