/*
define.h

(c) 2018 Saragai Takanori
*/
#pragma once

#define SAFE_RELEASE(ptr) {if(ptr) { (ptr)->Release(); (ptr)=NULL; }}
#define SAFE_DELETE(ptr) {if(ptr) { delete(ptr); (ptr)=NULL; }}

#define FATAL_ERROR -1
#define WARNING 1

#include "constant.h"
#include "game_error.h"

#include "video_driver.h"

int WINAPI WinMain(	HINSTANCE ,	HINSTANCE ,	LPSTR ,	int );

#include "graphics.h"