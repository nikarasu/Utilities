#pragma once
namespace CommonUtilities
{
	struct Color
	{
	public:
		Color();
		Color(const Vector4f& aColor);
		Color(float aR, float aG, float aB, float aA);
		Color(unsigned int aHexColour);

		float myR;
		float myG;
		float myB;
		float myA;

		bool operator==(const Color & aCol) const;
		bool operator!=(const Color & aCol) const;
		Color operator*(const float aValue) const;
		Color operator*(const Color & aColour) const;
	
		Vector4f AsVec4() const;
		unsigned int AsHex() const;
		static Color From255Scale(unsigned __int8 aR, unsigned __int8 aG, unsigned __int8 aB, unsigned __int8 aA);


		static Color Clear;

		//Reds
		static Color IndianRed;
		static Color LightCoral;
		static Color Coral;
		static Color Salmon;
		static Color DarkSalmon;
		static Color LightSalmon;
		static Color Crimson;
		static Color Red;
		static Color FireBrick;
		static Color DarkRed;
		static Color Tomato;
		static Color OrangeRed;

		//Pink/Purples
		static Color Pink;
		static Color LightPink;
		static Color HotPink;
		static Color DeepPink;
		static Color MediumVioletRed;
		static Color PaleVioletRed;
		static Color Lavender;
		static Color Thistle;
		static Color Plum;
		static Color Violet;
		static Color Orchid;
		static Color Fuchsia;
		static Color Magenta;
		static Color MediumOrchid;
		static Color MediumPurple;
		static Color RebeccaPurple;
		static Color BlueViolet;
		static Color DarkViolet;
		static Color DarkOrchid;
		static Color DarkMagenta;
		static Color Purple;
		static Color Indigo;
		static Color SlateBlue;
		static Color DarkSlateBlue;

		//Yellows/Oranges
		static Color DarkOrange;
		static Color Orange;
		static Color Gold;
		static Color Yellow;
		static Color LightYellow;
		static Color LemonChiffon;
		static Color LightGoldenRodYellow;
		static Color PapayaWhip;
		static Color Moccasin;
		static Color PeachPuff;
		static Color PaleGoldenRod;
		static Color Khaki;
		static Color DarkKhaki;

		//Greens
		static Color GreenYellow;
		static Color Chartreuse;
		static Color LawnGreen;
		static Color Lime;
		static Color LimeGreen;
		static Color PaleGreen;
		static Color LightGreen;
		static Color MediumSpringGreen;
		static Color SpringGreen;
		static Color MediumSeaGreen;
		static Color SeaGreen;
		static Color ForestGreen;
		static Color Green;
		static Color DarkGreen;
		static Color YellowGreen;
		static Color OliveDrab;
		static Color Olive;
		static Color DarkOliveGreen;
		static Color MediumAquaMarine;
		static Color DarkSeaGreen;
		static Color LightSeaGreen;
		static Color DarkCyan;
		static Color Teal;

		//Blues
		static Color Aqua;
		static Color Cyan;
		static Color LightCyan;
		static Color PaleTurquoise;
		static Color AquaMarine;
		static Color Turquoise;
		static Color MediumTurquoise;
		static Color DarkTurquoise;
		static Color CadetBlue;
		static Color SteelBlue;
		static Color LightSteelBlue;
		static Color PowderBlue;
		static Color LightBlue;
		static Color SkyBlue;
		static Color LightSkyBlue;
		static Color DeepSkyBlue;
		static Color DodgerBlue;
		static Color CornFlowerBlue;
		static Color MediumSlateBlue;
		static Color RoyalBlue;
		static Color Blue;
		static Color MediumBlue;
		static Color DarkBlue;
		static Color Navy;
		static Color MidnightBlue;

		//Browns
		static Color CornSilk;
		static Color BlanchedAlmond;
		static Color Bisque;
		static Color NavajoWhite;
		static Color Wheat;
		static Color Burlywood;
		static Color Tan;
		static Color RosyBrown;
		static Color SandyBrown;
		static Color GoldenBrown;
		static Color DarkGoldenBrown;
		static Color Peru;
		static Color Chocolate;
		static Color SaddleBrown;
		static Color Sienna;
		static Color Brown;
		static Color Maroon;

		//Whites
		static Color White;
		static Color Snow;
		static Color Honeydew;
		static Color MintCream;
		static Color Azure;
		static Color AliceBlue;
		static Color GhostWhite;
		static Color WhiteSmoke;
		static Color Seashell;
		static Color Beige;
		static Color OldLace;
		static Color FloralWhite;
		static Color Ivory;
		static Color AntiqueWhite;
		static Color Linen;
		static Color LavenderBlush;
		static Color MistyRose;

		//Grays
		static Color Gainsboro;
		static Color LightGray;
		static Color Silver;
		static Color DarkGray;
		static Color Gray;
		static Color DimGray;
		static Color LightSlateGray;
		static Color SlateGray;
		static Color DarkSlateGray;
		static Color Jet;
		static Color Charcoal;
		static Color Black;
	};
}

namespace CU = CommonUtilities;