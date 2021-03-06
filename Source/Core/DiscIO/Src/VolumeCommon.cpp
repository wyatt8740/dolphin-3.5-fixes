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
#include "Volume.h"

namespace DiscIO
{
IVolume::ECountry CountrySwitch(u8 CountryCode)
{
	switch (CountryCode) 
	{
		// Region free - fall through to European defaults for now
		case 'A':

		
		// PAL
		case 'D': // German
		case 'X': // Used by a couple PAL games
		case 'Y': // German, french


		case 'L': // Japanese import to PAL regions
		case 'M': // Japanese import to PAL regions
		case 'S': // Spanish-speaking regions
		case 'P':
		case 'U': // Australia 
			return IVolume::COUNTRY_EUROPE;
			break;
			
		case 'F':
			return IVolume::COUNTRY_FRANCE;
			break;
			
		case 'I':
			return IVolume::COUNTRY_ITALY;
			break;
			
		case 'R':
			return IVolume::COUNTRY_RUSSIA;
			break;

		// NTSC
		case 'E':
		case 'N': // Japanese import to USA and other NTSC regions
		case 'Z': // Prince Of Persia - The Forgotten Sands (WII)
			return IVolume::COUNTRY_USA;
			break;

		case 'J':
			return IVolume::COUNTRY_JAPAN;
			break;

		case 'K':
		case 'T': // Korea with English language
		case 'Q': // Korea with Japanese language
			return IVolume::COUNTRY_KOREA;
			break;			

		case 'O':
			return IVolume::COUNTRY_SDK;
			break;

		case 'W':
			return IVolume::COUNTRY_TAIWAN;
			break;

		default:
			if (CountryCode > 'A') // Silently ignore IOS wads
				WARN_LOG(DISCIO, "Unknown Country Code! %c", CountryCode);
			return IVolume::COUNTRY_UNKNOWN;
			break;
	}
}

u8 GetSysMenuRegion(u16 _TitleVersion)
{
	switch(_TitleVersion)
	{
	case 128:	case 192:	case 224:	case 256:
	case 288:	case 352:	case 384:	case 416:
	case 448:	case 480:	case 512:
		return 'J';
	case 97:	case 193:	case 225:	case 257:
	case 289:	case 353:	case 385:	case 417:
	case 449:	case 481:	case 513:
		return 'E';
	case 130:	case 162:	case 194:	case 226:
	case 258:	case 290:	case 354:	case 386:
	case 418:	case 450:	case 482:	case 514:
		return 'P';
	case 326:	case 390:	case 454:	case 486:
	case 518:
		return 'K';
	default:
		return 'A';
	}
}

};

