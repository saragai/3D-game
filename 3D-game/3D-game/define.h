/*
define.h

(c) 2018 Saragai Takanori
*/
#pragma once

#define SAFE_RELEASE(ptr) {if(ptr) { (ptr)->Release(); (ptr)=NULL; }}
#define SAFE_DELETE(ptr) {if(ptr) { delete(ptr); (ptr)=NULL; }}

#include "constant.h"
#include "video-driver.h"

int WINAPI WinMain(	HINSTANCE ,	HINSTANCE ,	LPSTR ,	int );

#include "graphics.h"