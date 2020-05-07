#include "stdafx.h"
#include "Color.h"
#include "Vector4.h"

CU::Color::Color()
{
	myR = 1.f;
	myG = 1.f;
	myB = 1.f;
	myA = 1.f;
}

CU::Color::Color(unsigned int aHexColour)
{
	myA = ((aHexColour & 0xFF000000) >> 24) / 255.f;
	myR = ((aHexColour & 0x00FF0000) >> 16) / 255.f;
	myG = ((aHexColour & 0x0000FF00) >> 8 ) / 255.f;
	myB = ((aHexColour & 0x000000FF)	  ) / 255.f;
	//unsigned char r = static_cast<unsigned char>(myR * 255.0f);
	//unsigned char g = static_cast<unsigned char>(myG * 255.0f);
	//unsigned char b = static_cast<unsigned char>(myB * 255.0f);
	//unsigned char a = static_cast<unsigned char>(myA * 255.0f);
	//
	//unsigned int final = 0;
	//final |= (a << 24);
	//final |= (r << 16);
	//final |= (g << 8);
	//final |= (b);
	//return final;
}

CU::Color::Color(const CU::Vector4f & aColor)
{
	myR = aColor.x;
	myG = aColor.y;
	myB = aColor.z;
	myA = aColor.w;
}

CU::Color::Color(float aR, float aG, float aB, float aA)
{
	myR = aR;
	myG = aG;
	myB = aB;
	myA = aA;
}

bool CU::Color::operator==(const CU::Color& aCol) const
{
	return (aCol.myR == myR && aCol.myG == myG && aCol.myB == myB && aCol.myA == myA);
}

bool CU::Color::operator!=(const CU::Color& aCol) const
{
	return (aCol.myR != myR || aCol.myG != myG || aCol.myB != myB || aCol.myA != myA);
}

CU::Color CU::Color::operator*(const float aValue) const
{
	return{ myR * aValue, myG * aValue, myB * aValue, myA * aValue };
}

CU::Color CU::Color::operator*(const CU::Color& aColour) const
{
	return{ myR * aColour.myR, myG * aColour.myG, myB * aColour.myB, myA * aColour.myA };
}

CU::Vector4f CU::Color::AsVec4() const
{
	return Vector4f(myR, myG, myB, myA);
}

unsigned int CU::Color::AsHex() const
{
	unsigned char r = static_cast<unsigned char>(myR * 255.0f);
	unsigned char g = static_cast<unsigned char>(myG * 255.0f);
	unsigned char b = static_cast<unsigned char>(myB * 255.0f);
	unsigned char a = static_cast<unsigned char>(myA * 255.0f);

	unsigned int final = 0;
	final |= (a << 24);
	final |= (r << 16);
	final |= (g << 8);
	final |= (b);
	return final;
}

CU::Color CU::Color::From255Scale(unsigned __int8 aR, unsigned __int8 aG, unsigned __int8 aB, unsigned __int8 aA)
{
	return CU::Color(aR / 255.f, aG / 255.f, aB / 255.f, aA / 255.f);
}

CU::Color CU::Color::Clear				(0x00000000u);

//Reds
CU::Color CU::Color::IndianRed			(0xFFCD5C5Cu);
CU::Color CU::Color::LightCoral			(0xFFF08080u);
CU::Color CU::Color::Coral				(0xFFFF7F50u);
CU::Color CU::Color::Salmon				(0xFFFA8072u);
CU::Color CU::Color::DarkSalmon			(0xFFE9967Au);
CU::Color CU::Color::LightSalmon		(0xFFFFA07Au);
CU::Color CU::Color::Crimson			(0xFFDC143Cu);
CU::Color CU::Color::Red				(0xFFFF0000u);
CU::Color CU::Color::FireBrick			(0xFFB22222u);
CU::Color CU::Color::DarkRed			(0xFF8B0000u);
CU::Color CU::Color::Tomato				(0xFFFF6347u);
CU::Color CU::Color::OrangeRed			(0xFFFF4500u);

//Pink/Purples
CU::Color CU::Color::Pink				(0xFFFFC0CBu);
CU::Color CU::Color::LightPink			(0xFFFFB6C1u);
CU::Color CU::Color::HotPink			(0xFFFF69B4u);
CU::Color CU::Color::DeepPink			(0xFFFF1493u);
CU::Color CU::Color::MediumVioletRed	(0xFFC71585u);
CU::Color CU::Color::PaleVioletRed		(0xFFDB7093u);
CU::Color CU::Color::Lavender			(0xFFE6E6FAu);
CU::Color CU::Color::Thistle			(0xFFD8BFD8u);
CU::Color CU::Color::Plum				(0xFFDDA0DDu);
CU::Color CU::Color::Violet				(0xFFEE82EEu);
CU::Color CU::Color::Orchid				(0xFFDA70D6u);
CU::Color CU::Color::Fuchsia			(0xFFFF00FFu);
CU::Color CU::Color::Magenta			(0xFFFF00FFu);
CU::Color CU::Color::MediumOrchid		(0xFFBA55D3u);
CU::Color CU::Color::MediumPurple		(0xFF9370DBu);
CU::Color CU::Color::RebeccaPurple		(0xFF663399u);
CU::Color CU::Color::BlueViolet			(0xFF8A2BE2u);
CU::Color CU::Color::DarkViolet			(0xFF9400D3u);
CU::Color CU::Color::DarkOrchid			(0xFF9932CCu);
CU::Color CU::Color::DarkMagenta		(0xFF8B008Bu);
CU::Color CU::Color::Purple				(0xFF800080u);
CU::Color CU::Color::Indigo				(0xFF4B0082u);
CU::Color CU::Color::SlateBlue			(0xFF6A5ACDu);
CU::Color CU::Color::DarkSlateBlue		(0xFF483D8Bu);

//Yellows/Oranges
CU::Color CU::Color::DarkOrange			(0xFFFF8C00);
CU::Color CU::Color::Orange				(0xFFFFA500);
CU::Color CU::Color::Gold				(0xFFFFD700);
CU::Color CU::Color::Yellow				(0xFFFFFF00);
CU::Color CU::Color::LightYellow		(0xFFFFFFE0);
CU::Color CU::Color::LemonChiffon		(0xFFFFFACD);
CU::Color CU::Color::LightGoldenRodYellow(0xFFFAFAD2);
CU::Color CU::Color::PapayaWhip			(0xFFFFEFD5);
CU::Color CU::Color::Moccasin			(0xFFFFE4B5);
CU::Color CU::Color::PeachPuff			(0xFFFFDAB9);
CU::Color CU::Color::PaleGoldenRod		(0xFFEEE8AA);
CU::Color CU::Color::Khaki				(0xFFF0E68C);
CU::Color CU::Color::DarkKhaki			(0xFFBDB76B);

//Greens
CU::Color CU::Color::GreenYellow		(0xFFADFF2F);
CU::Color CU::Color::Chartreuse			(0xFF7FFF00);
CU::Color CU::Color::LawnGreen			(0xFF7CFC00);
CU::Color CU::Color::Lime				(0xFF00FF00);
CU::Color CU::Color::LimeGreen			(0xFF32CD32);
CU::Color CU::Color::PaleGreen			(0xFF98FB98);
CU::Color CU::Color::LightGreen			(0xFF90EE90);
CU::Color CU::Color::MediumSpringGreen	(0xFF00FA9A);
CU::Color CU::Color::SpringGreen		(0xFF00FF7F);
CU::Color CU::Color::MediumSeaGreen		(0xFF3CB371);
CU::Color CU::Color::SeaGreen			(0xFF2E8B57);
CU::Color CU::Color::ForestGreen		(0xFF228B22);
CU::Color CU::Color::Green				(0xFF008000);
CU::Color CU::Color::DarkGreen			(0xFF006400);
CU::Color CU::Color::YellowGreen		(0xFF9ACD32);
CU::Color CU::Color::OliveDrab			(0xFF6B8E23);
CU::Color CU::Color::Olive				(0xFF808000);
CU::Color CU::Color::DarkOliveGreen		(0xFF556B2F);
CU::Color CU::Color::MediumAquaMarine	(0xFF66CDAA);
CU::Color CU::Color::DarkSeaGreen		(0xFF8FBC8B);
CU::Color CU::Color::LightSeaGreen		(0xFF20B2AA);
CU::Color CU::Color::DarkCyan			(0xFF008B8B);
CU::Color CU::Color::Teal				(0xFF008080);

//Blues
CU::Color CU::Color::Aqua				(0xFF00FFFF);
CU::Color CU::Color::Cyan				(0xFF00FFFF);
CU::Color CU::Color::LightCyan			(0xFFE0FFFF);
CU::Color CU::Color::PaleTurquoise		(0xFFAFEEEE);
CU::Color CU::Color::AquaMarine			(0xFF7FFFD4);
CU::Color CU::Color::Turquoise			(0xFF40E0D0);
CU::Color CU::Color::MediumTurquoise	(0xFF48D1CC);
CU::Color CU::Color::DarkTurquoise		(0xFF00CED1);
CU::Color CU::Color::CadetBlue			(0xFF5F9EA0);
CU::Color CU::Color::SteelBlue			(0xFF4682B4);
CU::Color CU::Color::LightSteelBlue		(0xFFB0C4DE);
CU::Color CU::Color::PowderBlue			(0xFFB0E0E6);
CU::Color CU::Color::LightBlue			(0xFFADD8E6);
CU::Color CU::Color::SkyBlue			(0xFF87CEEB);
CU::Color CU::Color::LightSkyBlue		(0xFF87CEFA);
CU::Color CU::Color::DeepSkyBlue		(0xFF00BFFF);
CU::Color CU::Color::DodgerBlue			(0xFF1E90FF);
CU::Color CU::Color::CornFlowerBlue		(0xFF6495ED);
CU::Color CU::Color::MediumSlateBlue	(0xFF7B68EE);
CU::Color CU::Color::RoyalBlue			(0xFF4169E1);
CU::Color CU::Color::Blue				(0xFF0000FF);
CU::Color CU::Color::MediumBlue			(0xFF0000CD);
CU::Color CU::Color::DarkBlue			(0xFF00008B);
CU::Color CU::Color::Navy				(0xFF000080);
CU::Color CU::Color::MidnightBlue		(0xFF191970);

//Browns
CU::Color CU::Color::CornSilk			(0xFFFFF8DC);
CU::Color CU::Color::BlanchedAlmond		(0xFFFFEBCD);
CU::Color CU::Color::Bisque				(0xFFFFE4C4);
CU::Color CU::Color::NavajoWhite		(0xFFFFDEAD);
CU::Color CU::Color::Wheat				(0xFFF5DEB3);
CU::Color CU::Color::Burlywood			(0xFFDEB887);
CU::Color CU::Color::Tan				(0xFFD2B48C);
CU::Color CU::Color::RosyBrown			(0xFFBC8F8F);
CU::Color CU::Color::SandyBrown			(0xFFF4A460);
CU::Color CU::Color::GoldenBrown		(0xFFDAA520);
CU::Color CU::Color::DarkGoldenBrown	(0xFFB8860B);
CU::Color CU::Color::Peru				(0xFFCD853F);
CU::Color CU::Color::Chocolate			(0xFFD2691E);
CU::Color CU::Color::SaddleBrown		(0xFF8B4513);
CU::Color CU::Color::Sienna				(0xFFA0522D);
CU::Color CU::Color::Brown				(0xFFA52A2A);
CU::Color CU::Color::Maroon				(0xFF800000);

//Whites
CU::Color CU::Color::White				(0xFFFFFFFF);
CU::Color CU::Color::Snow				(0xFFFFFAFA);
CU::Color CU::Color::Honeydew			(0xFFF0FFF0);
CU::Color CU::Color::MintCream			(0xFFF5FFFA);
CU::Color CU::Color::Azure				(0xFFF0FFFF);
CU::Color CU::Color::AliceBlue			(0xFFF0F8FF);
CU::Color CU::Color::GhostWhite			(0xFFF8F8FF);
CU::Color CU::Color::WhiteSmoke			(0xFFF5F5F5);
CU::Color CU::Color::Seashell			(0xFFFFF5EE);
CU::Color CU::Color::Beige				(0xFFF5F5DC);
CU::Color CU::Color::OldLace			(0xFFFdF5DC);
CU::Color CU::Color::FloralWhite		(0xFFFFFAF0);
CU::Color CU::Color::Ivory				(0xFFFFFFF0);
CU::Color CU::Color::AntiqueWhite		(0xFFFAEBD7);
CU::Color CU::Color::Linen				(0xFFFAF0E6);
CU::Color CU::Color::LavenderBlush		(0xFFFFF0F5);
CU::Color CU::Color::MistyRose			(0xFFFFE4E1);

//Grays
CU::Color CU::Color::Gainsboro			(0xFFDCDCDC);
CU::Color CU::Color::LightGray			(0xFFD3D3D3);
CU::Color CU::Color::Silver				(0xFFC0C0C0);
CU::Color CU::Color::DarkGray			(0xFFA9A9A9);
CU::Color CU::Color::Gray				(0xFF808080);
CU::Color CU::Color::DimGray			(0xFF696969);
CU::Color CU::Color::LightSlateGray		(0xFF778899);
CU::Color CU::Color::SlateGray			(0xFF708090);
CU::Color CU::Color::DarkSlateGray		(0xFF2F4F4F);
CU::Color CU::Color::Jet				(0xFF343434);
CU::Color CU::Color::Charcoal			(0xFF222021);
CU::Color CU::Color::Black				(0xFF000000);