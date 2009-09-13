// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#include <cmath>

#include "Common.h"
#include "IniFile.h"
#include "Config.h"
#include "VideoCommon.h"

Config g_Config;
Config g_ActiveConfig;

void UpdateActiveConfig() 
{
	g_ActiveConfig = g_Config;
}

Config::Config()
{
	bRunning = false;
}

void Config::Load(const char *ini_file)
{
    std::string temp;
    IniFile iniFile;
    iniFile.Load(ini_file);

	// get resolution
    iniFile.Get("Hardware", "WindowedRes", &temp, "640x480");
    strncpy(cInternalRes, temp.c_str(), 16);
	iniFile.Get("Hardware", "FullscreenRes", &temp, "640x480");
    strncpy(cFSResolution, temp.c_str(), 16);
    
    iniFile.Get("Hardware", "Fullscreen", &bFullscreen, 0); // Hardware
    iniFile.Get("Hardware", "VSync", &bVSync, 0); // Hardware
    iniFile.Get("Hardware", "RenderToMainframe", &RenderToMainframe, false);
    iniFile.Get("Settings", "StretchToFit", &bNativeResolution, true);
	iniFile.Get("Settings", "2xResolution", &b2xResolution, false);
	iniFile.Get("Settings", "wideScreenHack", &bWidescreenHack, false);
	iniFile.Get("Settings", "KeepAR_4_3", &bKeepAR43, false);
	iniFile.Get("Settings", "KeepAR_16_9", &bKeepAR169, false);
	iniFile.Get("Settings", "Crop", &bCrop, false);
    iniFile.Get("Settings", "HideCursor", &bHideCursor, false);
    iniFile.Get("Settings", "UseXFB", &bUseXFB, 0);
    iniFile.Get("Settings", "AutoScale", &bAutoScale, true);
    
    iniFile.Get("Settings", "SafeTextureCache", &bSafeTextureCache, false); // Settings
    iniFile.Get("Settings", "ShowFPS", &bShowFPS, false); // Settings
    iniFile.Get("Settings", "OverlayStats", &bOverlayStats, false);
	iniFile.Get("Settings", "OverlayProjStats", &bOverlayProjStats, false);
	iniFile.Get("Settings", "ShowEFBCopyRegions", &bShowEFBCopyRegions, false);
    iniFile.Get("Settings", "DLOptimize", &iCompileDLsLevel, 0);
    iniFile.Get("Settings", "DumpTextures", &bDumpTextures, 0);
    iniFile.Get("Settings", "HiresTextures", &bHiresTextures, 0);
	iniFile.Get("Settings", "DumpEFBTarget", &bDumpEFBTarget, 0);
	iniFile.Get("Settings", "DumpFrames", &bDumpFrames, 0);
    iniFile.Get("Settings", "FreeLook", &bFreeLook, 0);
    iniFile.Get("Settings", "ShowShaderErrors", &bShowShaderErrors, 0);
    iniFile.Get("Settings", "MSAA", &iMultisampleMode, 0);
    iniFile.Get("Settings", "DstAlphaPass", &bDstAlphaPass, false);
    
    iniFile.Get("Settings", "TexFmtOverlayEnable", &bTexFmtOverlayEnable, 0);
    iniFile.Get("Settings", "TexFmtOverlayCenter", &bTexFmtOverlayCenter, 0);
    iniFile.Get("Settings", "WireFrame", &bWireFrame, 0);
    iniFile.Get("Settings", "DisableLighting", &bDisableLighting, 0);
    iniFile.Get("Settings", "DisableTexturing", &bDisableTexturing, 0);
	iniFile.Get("Settings", "DisableFog", &bDisableFog, 0);
    
    iniFile.Get("Enhancements", "ForceFiltering", &bForceFiltering, 0);
    iniFile.Get("Enhancements", "MaxAnisotropy", &iMaxAnisotropy, 3);  // NOTE - this is x in (1 << x)
	iniFile.Get("Enhancements", "PostProcessingShader", &sPostProcessingShader, "");
    
    iniFile.Get("Hacks", "EFBCopyDisable", &bEFBCopyDisable, 0);
    iniFile.Get("Hacks", "EFBCopyDisableHotKey", &bEFBCopyDisableHotKey, 0);
	iniFile.Get("Hacks", "EFBToTextureEnable", &bCopyEFBToRAM, 0);
	iniFile.Get("Hacks", "ProjectionHack", &iPhackvalue, 0);

	iniFile.Get("Hardware", "Adapter", &iAdapter, 0);
	if (iAdapter == -1) 
		iAdapter = 0;
	iniFile.Get("Hardware", "WindowedRes", &iWindowedRes, 0);
	iniFile.Get("Hardware", "VSync", &bVsync, 0);
	iniFile.Get("Hardware", "FullscreenRes", &iFSResolution, 0);

	// Load common settings
	iniFile.Load(CONFIG_FILE);
	bool bTmp;
	iniFile.Get("Interface", "UsePanicHandlers", &bTmp, true);
	SetEnableAlert(bTmp);
}

void Config::GameIniLoad(const char *ini_file)
{
    IniFile iniFile;
    iniFile.Load(ini_file);
	iniFile.Get("Video", "ForceFiltering", &bForceFiltering, 0);
	iniFile.Get("Video", "MaxAnisotropy", &iMaxAnisotropy, 3);  // NOTE - this is x in (1 << x)
	iniFile.Get("Video", "EFBCopyDisable", &bEFBCopyDisable, 0);
	iniFile.Get("Video", "EFBCopyDisableHotKey", &bEFBCopyDisableHotKey, 0);
	iniFile.Get("Video", "EFBToRAMEnable", &bCopyEFBToRAM, 0);
	iniFile.Get("Video", "SafeTextureCache", &bSafeTextureCache, false); 
	iniFile.Get("Video", "MSAA", &iMultisampleMode, 0);
	iniFile.Get("Video", "DstAlphaPass", &bDstAlphaPass, false);
	iniFile.Get("Video", "UseXFB", &bUseXFB, 0);
	iniFile.Get("Video", "ProjectionHack", &iPhackvalue, 0);
}

void Config::Save(const char *ini_file)
{
    IniFile iniFile;
    iniFile.Load(ini_file);
    iniFile.Set("Hardware", "WindowedRes", cInternalRes);
    iniFile.Set("Hardware", "FullscreenRes", cFSResolution);
    iniFile.Set("Hardware", "Fullscreen", bFullscreen);
    iniFile.Set("Hardware", "VSync", bVSync);
    iniFile.Set("Hardware", "RenderToMainframe", RenderToMainframe);
    iniFile.Set("Settings", "StretchToFit", bNativeResolution);
	iniFile.Set("Settings", "2xResolution", b2xResolution);
    iniFile.Set("Settings", "KeepAR_4_3", bKeepAR43);
	iniFile.Set("Settings", "KeepAR_16_9", bKeepAR169);
	iniFile.Set("Settings", "Crop", bCrop);
	iniFile.Set("Settings", "wideScreenHack", bWidescreenHack);
    iniFile.Set("Settings", "HideCursor", bHideCursor);
    iniFile.Set("Settings", "UseXFB", bUseXFB);
    iniFile.Set("Settings", "AutoScale", bAutoScale);

    iniFile.Set("Settings", "SafeTextureCache", bSafeTextureCache);
    iniFile.Set("Settings", "ShowFPS", bShowFPS);
    iniFile.Set("Settings", "OverlayStats", bOverlayStats);
	iniFile.Set("Settings", "OverlayProjStats", bOverlayProjStats);
    iniFile.Set("Settings", "DLOptimize", iCompileDLsLevel);
	iniFile.Set("Settings", "Show", iCompileDLsLevel);
    iniFile.Set("Settings", "DumpTextures", bDumpTextures);
    iniFile.Set("Settings", "HiresTextures", bHiresTextures);
	iniFile.Set("Settings", "DumpEFBTarget", bDumpEFBTarget);
	iniFile.Set("Settings", "DumpFrames", bDumpFrames);
    iniFile.Set("Settings", "FreeLook", bFreeLook);
    iniFile.Set("Settings", "ShowEFBCopyRegions", bShowEFBCopyRegions);
	iniFile.Set("Settings", "ShowShaderErrors", bShowShaderErrors);
    iniFile.Set("Settings", "MSAA", iMultisampleMode);
    iniFile.Set("Settings", "TexFmtOverlayEnable", bTexFmtOverlayEnable);
    iniFile.Set("Settings", "TexFmtOverlayCenter", bTexFmtOverlayCenter);
    iniFile.Set("Settings", "Wireframe", bWireFrame);
    iniFile.Set("Settings", "DisableLighting", bDisableLighting);
    iniFile.Set("Settings", "DisableTexturing", bDisableTexturing);
    iniFile.Set("Settings", "DstAlphaPass", bDstAlphaPass);
	iniFile.Set("Settings", "DisableFog", bDisableFog);
    
    iniFile.Set("Enhancements", "ForceFiltering", bForceFiltering);
    iniFile.Set("Enhancements", "MaxAnisotropy", iMaxAnisotropy);
	iniFile.Set("Enhancements", "PostProcessingShader", sPostProcessingShader);
    
    iniFile.Set("Hacks", "EFBCopyDisable", bEFBCopyDisable);
    iniFile.Set("Hacks", "EFBCopyDisableHotKey", bEFBCopyDisableHotKey);
	iniFile.Set("Hacks", "EFBToTextureEnable", bCopyEFBToRAM);
	iniFile.Set("Hacks", "ProjectionHack", iPhackvalue);

	iniFile.Set("Hardware", "Adapter", iAdapter);
	iniFile.Set("Hardware", "WindowedRes", iWindowedRes);
	iniFile.Set("Hardware", "VSync", bVsync);
	iniFile.Set("Hardware", "FullscreenRes", iFSResolution);

    iniFile.Save(ini_file);
}



// TODO: Figure out a better place for this function.
void ComputeDrawRectangle(int backbuffer_width, int backbuffer_height, bool flip, TargetRectangle *rc)
{
	float FloatGLWidth = (float)backbuffer_width;
	float FloatGLHeight = (float)backbuffer_height;
	float FloatXOffset = 0;
	float FloatYOffset = 0;

	// The rendering window size
	const float WinWidth = FloatGLWidth;
	const float WinHeight = FloatGLHeight;

	// Handle aspect ratio.
	if (g_ActiveConfig.bKeepAR43 || g_ActiveConfig.bKeepAR169)
	{
		// The rendering window aspect ratio as a proportion of the 4:3 or 16:9 ratio
		float Ratio = (WinWidth / WinHeight) / (g_Config.bKeepAR43 ? (4.0f / 3.0f) : (16.0f / 9.0f));
		// Check if height or width is the limiting factor. If ratio > 1 the picture is to wide and have to limit the width.
		if (Ratio > 1)
		{
			// Scale down and center in the X direction.
			FloatGLWidth /= Ratio;
			FloatXOffset = (WinWidth - FloatGLWidth) / 2.0f;
		}
		// The window is too high, we have to limit the height
		else
		{
			// Scale down and center in the Y direction.
			FloatGLHeight *= Ratio;
			FloatYOffset = FloatYOffset + (WinHeight - FloatGLHeight) / 2.0f;
		}
	}

	// -----------------------------------------------------------------------
	// Crop the picture from 4:3 to 5:4 or from 16:9 to 16:10.
	//		Output: FloatGLWidth, FloatGLHeight, FloatXOffset, FloatYOffset
	// ------------------
	if ((g_ActiveConfig.bKeepAR43 || g_ActiveConfig.bKeepAR169) && g_ActiveConfig.bCrop)
	{
		float Ratio = g_Config.bKeepAR43 ? ((4.0f / 3.0f) / (5.0f / 4.0f)) : (((16.0f / 9.0f) / (16.0f / 10.0f)));
		// The width and height we will add (calculate this before FloatGLWidth and FloatGLHeight is adjusted)
		float IncreasedWidth = (Ratio - 1.0f) * FloatGLWidth;
		float IncreasedHeight = (Ratio - 1.0f) * FloatGLHeight;
		// The new width and height
		FloatGLWidth = FloatGLWidth * Ratio;
		FloatGLHeight = FloatGLHeight * Ratio;
		// Adjust the X and Y offset
		FloatXOffset = FloatXOffset - (IncreasedWidth * 0.5f);
		FloatYOffset = FloatYOffset - (IncreasedHeight * 0.5f);
		//NOTICE_LOG(OSREPORT, "Crop       Ratio:%1.2f IncreasedHeight:%3.0f YOffset:%3.0f", Ratio, IncreasedHeight, FloatYOffset);
		//NOTICE_LOG(OSREPORT, "Crop       FloatGLWidth:%1.2f FloatGLHeight:%3.0f", (float)FloatGLWidth, (float)FloatGLHeight);
		//NOTICE_LOG(OSREPORT, "");
	}

	// round(float) = floor(float + 0.5)
	int XOffset = (int)(FloatXOffset + 0.5f);
	int YOffset = (int)(FloatYOffset + 0.5f);
	rc->left = XOffset;
	rc->top = flip ? (int)(YOffset + ceil(FloatGLHeight)) : YOffset;
	rc->right = XOffset + (int)ceil(FloatGLWidth);
	rc->bottom = flip ? YOffset : (int)(YOffset + ceil(FloatGLHeight));
}