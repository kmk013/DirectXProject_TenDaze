#ifndef _RGENGINE_H_
#define _RGENGINE_H_

// 시작점을 int main으로
#pragma comment(linker, "/ENTRY:mainCRTStartup")

#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:CONSOLE") // 디버그일시 콘솔창표시
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS") // 릴리즈일시 콘솔창없엠
#endif

#include "RGApplication.h"
#include "RGGameObject.h"
#include "RGComponent.h"
#include "RGTypes.h"
#include "RGMath.h"

#include "RGComponentBoxCollider.h"
#include "RGComponentCircleCollider.h"
#include "RGComponentSpriteRenderer.h"
#include "RGComponentAnimationRenderer.h"
#include "RGComponentTextRenderer.h"
#include "RGComponentAudioSource.h"
#include "RGComponentAudioListener.h"

#include "RGDataStreamFile.h"
#include "RGDataStreamJSON.h"
#include "RGDataStreamXML.h"

#include <iostream>
#include "Enum.h"

using namespace std;

#endif //_RGENGINE_H_